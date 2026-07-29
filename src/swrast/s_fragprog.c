/*
 * Mesa 3-D graphics library
 * Version:  7.0.3
 *
 * Copyright (C) 1999-2007  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "glheader.h"
#include "colormac.h"
#include "context.h"
#include "prog_instruction.h"

#include "s_fragprog.h"
#include "s_span.h"
#include "s_texfilter.h"


/**
 * Fetch a texel.
 */
static void
fetch_texel(GLcontext *ctx, const GLfloat texcoord[4], GLfloat lambda,
	    GLuint unit, GLfloat color[4])
{
    SWcontext *swrast = SWRAST_CONTEXT(ctx);
    const struct gl_texture_object *texObj = ctx->Texture.Unit[unit]._Current;

    if (texObj)
	lambda = CLAMP(lambda, texObj->MinLod, texObj->MaxLod);

    if (texObj && texObj->Image[0][texObj->BaseLevel] &&
	texObj->Image[0][texObj->BaseLevel]->TexFormat->DataType == GL_FLOAT &&
	swrast->TextureSampleF[unit]) {
	/* Use float-valued sampler to preserve HDR precision */
	swrast->TextureSampleF[unit](ctx, texObj, 1,
				     (const GLfloat(*)[4]) texcoord,
				     &lambda, (GLfloat(*)[4]) color);
    } else {
	GLchan rgba[4];
	swrast->TextureSample[unit](ctx, texObj, 1,
				    (const GLfloat(*)[4]) texcoord,
				    &lambda, &rgba);
	color[0] = CHAN_TO_FLOAT(rgba[0]);
	color[1] = CHAN_TO_FLOAT(rgba[1]);
	color[2] = CHAN_TO_FLOAT(rgba[2]);
	color[3] = CHAN_TO_FLOAT(rgba[3]);
    }
}


/**
 * Fetch a texel with the given partial derivatives to compute a level
 * of detail in the mipmap.
 */
static void
fetch_texel_deriv(GLcontext *ctx, const GLfloat texcoord[4],
		  const GLfloat texdx[4], const GLfloat texdy[4],
		  GLfloat lodBias, GLuint unit, GLfloat color[4])
{
    SWcontext *swrast = SWRAST_CONTEXT(ctx);
    const struct gl_texture_object *texObj = ctx->Texture.Unit[unit]._Current;
    GLfloat lambda = 0.0F;

    if (texObj) {
	const struct gl_texture_image *texImg = texObj->Image[0][texObj->BaseLevel];
	const GLfloat texW = (GLfloat) texImg->WidthScale;
	const GLfloat texH = (GLfloat) texImg->HeightScale;

	lambda = _swrast_compute_lambda(texdx[0], texdy[0], /* ds/dx, ds/dy */
					texdx[1], texdy[1], /* dt/dx, dt/dy */
					texdx[3], texdy[2], /* dq/dx, dq/dy */
					texW, texH,
					texcoord[0], texcoord[1], texcoord[3],
					1.0F / texcoord[3]) + lodBias;

	lambda = CLAMP(lambda, texObj->MinLod, texObj->MaxLod);
    }

    if (texObj && texObj->Image[0][texObj->BaseLevel] &&
	texObj->Image[0][texObj->BaseLevel]->TexFormat->DataType == GL_FLOAT &&
	swrast->TextureSampleF[unit]) {
	swrast->TextureSampleF[unit](ctx, texObj, 1,
				     (const GLfloat(*)[4]) texcoord,
				     &lambda, (GLfloat(*)[4]) color);
    } else {
	GLchan rgba[4];
	swrast->TextureSample[unit](ctx, texObj, 1, (const GLfloat(*)[4]) texcoord,
				    &lambda, &rgba);
	color[0] = CHAN_TO_FLOAT(rgba[0]);
	color[1] = CHAN_TO_FLOAT(rgba[1]);
	color[2] = CHAN_TO_FLOAT(rgba[2]);
	color[3] = CHAN_TO_FLOAT(rgba[3]);
    }
}


/**
 * Initialize the virtual fragment program machine state prior to running
 * fragment program on a fragment.  This involves initializing the input
 * registers, condition codes, etc.
 * \param machine  the virtual machine state to init
 * \param program  the fragment program we're about to run
 * \param span  the span of pixels we'll operate on
 * \param col  which element (column) of the span we'll operate on
 */
static void
init_machine(GLcontext *ctx, struct gl_program_machine *machine,
	     const struct gl_fragment_program *program,
	     const SWspan *span, GLuint col)
{
    if (program->Base.Target == GL_FRAGMENT_PROGRAM_NV) {
	/* Clear temporary registers (undefined for ARB_f_p) */
	_mesa_bzero(machine->Temporaries,
		    MAX_PROGRAM_TEMPS * 4 * sizeof(GLfloat));
    }

    /* Setup pointer to input attributes */
    machine->Attribs = span->array->attribs;

    machine->DerivX = (GLfloat(*)[4]) span->attrStepX;
    machine->DerivY = (GLfloat(*)[4]) span->attrStepY;
    machine->NumDeriv = FRAG_ATTRIB_MAX;

    if (ctx->Shader.CurrentProgram) {
	/* Store front/back facing value in register FOGC.Y */
	machine->Attribs[FRAG_ATTRIB_FOGC][col][1] = 1.0 - span->facing;
    }

    machine->CurElement = col;

    /* init condition codes */
    machine->CondCodes[0] = COND_EQ;
    machine->CondCodes[1] = COND_EQ;
    machine->CondCodes[2] = COND_EQ;
    machine->CondCodes[3] = COND_EQ;

    /* init call stack */
    machine->StackDepth = 0;

    machine->FetchTexelLod = fetch_texel;
    machine->FetchTexelDeriv = fetch_texel_deriv;
}


/**
 * Execute and commit one fragment through the complete scalar path.
 */
static void
run_scalar_fragment(GLcontext *ctx,
		    SWspan *span,
		    const struct gl_fragment_program *program,
		    struct gl_program_fast *fast,
		    struct gl_program_machine *machine,
		    GLbitfield outputsWritten,
		    GLuint column)
{
    SWcontext *swrast = SWRAST_CONTEXT(ctx);

    init_machine(ctx, machine, program, span, column);
    if (fast ? _mesa_execute_fast_program(fast) :
	_mesa_execute_program(ctx, &program->Base, machine)) {

	/* Store result color */
	if (outputsWritten & (1 << FRAG_RESULT_COLR)) {
	    COPY_4V(span->array->attribs[FRAG_ATTRIB_COL0][column],
		    machine->Outputs[FRAG_RESULT_COLR]);
	} else {
	    /* Multiple drawbuffers / render targets
	     * Note that colors beyond 0 and 1 will overwrite other
	     * attributes, such as FOGC, TEX0, TEX1, etc.  That's OK.
	     */
	    GLuint output;
	    for (output = 0; output < swrast->_NumColorOutputs; output++) {
		if (outputsWritten & (1 << (FRAG_RESULT_DATA0 + output))) {
		    COPY_4V(
			span->array->attribs[FRAG_ATTRIB_COL0 + output][column],
			machine->Outputs[FRAG_RESULT_DATA0 + output]);
		}
	    }
	}

	/* Store result depth/z */
	if (outputsWritten & (1 << FRAG_RESULT_DEPR)) {
	    const GLfloat depth = machine->Outputs[FRAG_RESULT_DEPR][2];
	    if (depth <= 0.0)
		span->array->z[column] = 0;
	    else if (depth >= 1.0)
		span->array->z[column] = ctx->DrawBuffer->_DepthMax;
	    else
		span->array->z[column] =
		    IROUND(depth * ctx->DrawBuffer->_DepthMaxF);
	}
    } else {
	/* killed fragment */
	span->array->mask[column] = GL_FALSE;
	span->writeAll = GL_FALSE;
    }
}


/**
 * Run fragment program on the pixels in span from 'start' to 'end' - 1.
 */
static void
run_program(GLcontext *ctx, SWspan *span, GLuint start, GLuint end)
{
    SWcontext *swrast = SWRAST_CONTEXT(ctx);
    const struct gl_fragment_program *program = ctx->FragmentProgram._Current;
    const GLbitfield outputsWritten = program->Base.OutputsWritten;
    struct gl_program_machine *machine = &swrast->FragProgMachine;
    struct gl_program_fast *fast;
    GLuint columns[4];
    GLuint columnCount = 0;
    GLboolean useSimd;
    GLuint i;

    if (swrast->FragProgFastSource != &program->Base ||
	swrast->FragProgFastInstructions != program->Base.Instructions ||
	swrast->FragProgFastInstructionCount !=
	    program->Base.NumInstructions) {
	_mesa_destroy_fast_program(swrast->FragProgFast);
	swrast->FragProgFast = _mesa_create_fast_program(
	    ctx, &program->Base, machine);
	swrast->FragProgFastSource = &program->Base;
	swrast->FragProgFastInstructions = program->Base.Instructions;
	swrast->FragProgFastInstructionCount =
	    program->Base.NumInstructions;
    }
    fast = swrast->FragProgFast;
    useSimd =
	outputsWritten == (1u << FRAG_RESULT_COLR) &&
	_mesa_fast_fragment_simd_supported(fast);
    if (useSimd && swrast->FragProgStatsEnabled)
	++swrast->FragProgSimdEligibleSpans;

    for (i = start; i < end; i++) {
	if (!span->array->mask[i])
	    continue;

	if (!useSimd) {
	    if (swrast->FragProgStatsEnabled)
		++swrast->FragProgScalarFragments;
	    run_scalar_fragment(ctx, span, program, fast, machine,
				outputsWritten, i);
	    continue;
	}

	columns[columnCount++] = i;
	if (columnCount == 4) {
	    GLfloat colors[4][4];
	    GLuint lane;

	    /* init_machine establishes span pointers, derivatives, texture
	     * callbacks, and invocation defaults.  Facing is itself a fragment
	     * input, so initialize all four gathered columns before the SIMD
	    * executor loads its component-major state. */
	    if (ctx->Shader.CurrentProgram) {
		machine->Attribs = span->array->attribs;
		for (lane = 0; lane < 4; ++lane)
		    machine->Attribs[FRAG_ATTRIB_FOGC][columns[lane]][1] =
			1.0F - span->facing;
	    }
	    init_machine(ctx, machine, program, span, columns[0]);

	    if (_mesa_execute_fast_fragment_program_simd(
		    fast, columns, colors)) {
		if (swrast->FragProgStatsEnabled)
		{
		    ++swrast->FragProgSimdGroups;
		    swrast->FragProgSimdFragments += 4;
		}
		for (lane = 0; lane < 4; ++lane)
		    COPY_4V(
			span->array->attribs[FRAG_ATTRIB_COL0][columns[lane]],
			colors[lane]);
	    } else {
		if (swrast->FragProgStatsEnabled) {
		    ++swrast->FragProgSimdFallbacks;
		    swrast->FragProgScalarFragments += 4;
		}
		/* Eligibility is conservative, but retaining this fallback makes
		 * a rejected SIMD execution observationally identical to the
		 * established scalar path. */
		for (lane = 0; lane < 4; ++lane)
		    run_scalar_fragment(ctx, span, program, fast, machine,
					outputsWritten, columns[lane]);
	    }
	    columnCount = 0;
	}
    }

    if (useSimd && columnCount >= 2) {
	GLfloat colors[4][4];
	const GLuint actualCount = columnCount;
	GLuint lane;

	/* A two- or three-fragment tail is still cheaper as one SIMD program
	 * invocation than as independent scalar interpreter runs.  Duplicate
	 * the final source column into inactive lanes; only actual lanes are
	 * committed, so derivatives and framebuffer ordering are unchanged. */
	while (columnCount < 4) {
	    columns[columnCount] = columns[actualCount - 1];
	    ++columnCount;
	}
	if (ctx->Shader.CurrentProgram) {
	    machine->Attribs = span->array->attribs;
	    for (lane = 0; lane < actualCount; ++lane)
		machine->Attribs[FRAG_ATTRIB_FOGC][columns[lane]][1] =
		    1.0F - span->facing;
	}
	init_machine(ctx, machine, program, span, columns[0]);
	if (_mesa_execute_fast_fragment_program_simd(fast, columns, colors)) {
	    if (swrast->FragProgStatsEnabled) {
		++swrast->FragProgSimdGroups;
		swrast->FragProgSimdFragments += actualCount;
		if (actualCount == 2)
		    ++swrast->FragProgSimdTwoTails;
		else
		    ++swrast->FragProgSimdThreeTails;
	    }
	    for (lane = 0; lane < actualCount; ++lane)
		COPY_4V(
		    span->array->attribs[FRAG_ATTRIB_COL0][columns[lane]],
		    colors[lane]);
	} else {
	    if (swrast->FragProgStatsEnabled) {
		++swrast->FragProgSimdFallbacks;
		swrast->FragProgScalarFragments += actualCount;
	    }
	    for (lane = 0; lane < actualCount; ++lane)
		run_scalar_fragment(ctx, span, program, fast, machine,
				    outputsWritten, columns[lane]);
	}
    } else {
	for (i = 0; i < columnCount; ++i) {
	    if (swrast->FragProgStatsEnabled) {
		++swrast->FragProgScalarFragments;
		if (useSimd)
		    ++swrast->FragProgScalarSingleTails;
	    }
	    run_scalar_fragment(ctx, span, program, fast, machine,
				outputsWritten, columns[i]);
	}
    }
}


/**
 * Execute the current fragment program for all the fragments
 * in the given span.
 */
void
_swrast_exec_fragment_program(GLcontext *ctx, SWspan *span)
{
    const struct gl_fragment_program *program = ctx->FragmentProgram._Current;

    /* incoming colors should be floats */
    if (program->Base.InputsRead & FRAG_BIT_COL0) {
	ASSERT(span->array->ChanType == GL_FLOAT);
    }

    ctx->_CurrentProgram = GL_FRAGMENT_PROGRAM_ARB; /* or NV, doesn't matter */

    run_program(ctx, span, 0, span->end);

    /* gl_FragData[] writes are color outputs too.  Without marking the span
     * as carrying shader-produced RGBA here, the generic span path restores
     * the interpolated fixed-function color over gl_FragData[0]. */
    if ((program->Base.OutputsWritten & (1 << FRAG_RESULT_COLR)) ||
	(program->Base.OutputsWritten >> FRAG_RESULT_DATA0)) {
	span->interpMask &= ~SPAN_RGBA;
	span->arrayMask |= SPAN_RGBA;
    }

    if (program->Base.OutputsWritten & (1 << FRAG_RESULT_DEPR)) {
	span->interpMask &= ~SPAN_Z;
	span->arrayMask |= SPAN_Z;
    }

    ctx->_CurrentProgram = 0;
}


/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
