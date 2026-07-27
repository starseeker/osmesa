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

/**
 * \file prog_execute.c
 * Software interpreter for vertex/fragment programs.
 * \author Brian Paul
 */

/*
 * NOTE: we do everything in single-precision floating point; we don't
 * currently observe the single/half/fixed-precision qualifiers.
 *
 */


#include "glheader.h"
#include "colormac.h"
#include "context.h"
#include "program.h"
#include "prog_execute.h"
#include "prog_instruction.h"
#include "prog_parameter.h"
#include "prog_print.h"
#include "slang_library_noise.h"


/* debug predicate */
#define DEBUG_PROG 0


/**
 * Set x to positive or negative infinity.
 */
#define SET_POS_INFINITY(x)  ( x = INFINITY )
#define SET_NEG_INFINITY(x)  ( x = -INFINITY )

static const GLfloat ZeroVec[4] = { 0.0F, 0.0F, 0.0F, 0.0F };

/**
 * Return a pointer to the 4-element float vector specified by the given
 * source register.
 */
static INLINE const GLfloat *
get_register_pointer(const struct prog_src_register *source,
		     const struct gl_program_machine *machine)
{
    if (source->RelAddr) {
	const GLint reg = source->Index + machine->AddressReg[0][0];
	if (source->File == PROGRAM_ENV_PARAM)
	    if (reg < 0 || reg >= MAX_PROGRAM_ENV_PARAMS)
		return ZeroVec;
	    else
		return machine->EnvParams[reg];
	else {
	    const struct gl_program_parameter_list *params;
	    ASSERT(source->File == PROGRAM_LOCAL_PARAM ||
		   source->File == PROGRAM_STATE_VAR ||
		   source->File == PROGRAM_CONSTANT ||
		   source->File == PROGRAM_UNIFORM ||
		   source->File == PROGRAM_NAMED_PARAM);
	    params = machine->CurProgram->Parameters;
	    if (reg < 0 || (GLuint)reg >= params->NumParameters)
		return ZeroVec;
	    else
		return params->ParameterValues[reg];
	}
    }

    switch (source->File) {
	case PROGRAM_TEMPORARY:
	    ASSERT(source->Index < MAX_PROGRAM_TEMPS);
	    return machine->Temporaries[source->Index];

	case PROGRAM_INPUT:
	    if (machine->CurProgram->Target == GL_VERTEX_PROGRAM_ARB) {
		ASSERT(source->Index < VERT_ATTRIB_MAX);
		return machine->VertAttribs[source->Index];
	    } else {
		ASSERT(source->Index < FRAG_ATTRIB_MAX);
		return machine->Attribs[source->Index][machine->CurElement];
	    }

	case PROGRAM_OUTPUT:
	    ASSERT(source->Index < MAX_PROGRAM_OUTPUTS);
	    return machine->Outputs[source->Index];

	case PROGRAM_LOCAL_PARAM:
	    ASSERT(source->Index < MAX_PROGRAM_LOCAL_PARAMS);
	    return machine->CurProgram->LocalParams[source->Index];

	case PROGRAM_ENV_PARAM:
	    ASSERT(source->Index < MAX_PROGRAM_ENV_PARAMS);
	    return machine->EnvParams[source->Index];

	case PROGRAM_STATE_VAR:
	/* Fallthrough */
	case PROGRAM_CONSTANT:
	/* Fallthrough */
	case PROGRAM_UNIFORM:
	/* Fallthrough */
	case PROGRAM_NAMED_PARAM:
	    ASSERT(source->Index <
		   (GLint) machine->CurProgram->Parameters->NumParameters);
	    return machine->CurProgram->Parameters->ParameterValues[source->Index];

	default:
	    _mesa_problem(NULL,
			  "Invalid input register file %d in get_register_pointer()",
			  source->File);
	    return NULL;
    }
}

/**
 * Fetch a 4-element float vector from the given source register.
 * Apply swizzling and negating as needed.
 */
static void
fetch_vector4(const struct prog_src_register *source,
	      const struct gl_program_machine *machine, GLfloat result[4])
{
    const GLfloat *src = get_register_pointer(source, machine);
    ASSERT(src);

    if (source->Swizzle == SWIZZLE_NOOP) {
	/* no swizzling */
	COPY_4V(result, src);
    } else {
	ASSERT(GET_SWZ(source->Swizzle, 0) <= 3);
	ASSERT(GET_SWZ(source->Swizzle, 1) <= 3);
	ASSERT(GET_SWZ(source->Swizzle, 2) <= 3);
	ASSERT(GET_SWZ(source->Swizzle, 3) <= 3);
	result[0] = src[GET_SWZ(source->Swizzle, 0)];
	result[1] = src[GET_SWZ(source->Swizzle, 1)];
	result[2] = src[GET_SWZ(source->Swizzle, 2)];
	result[3] = src[GET_SWZ(source->Swizzle, 3)];
    }

    if (source->NegateBase) {
	result[0] = -result[0];
	result[1] = -result[1];
	result[2] = -result[2];
	result[3] = -result[3];
    }
    if (source->Abs) {
	result[0] = FABSF(result[0]);
	result[1] = FABSF(result[1]);
	result[2] = FABSF(result[2]);
	result[3] = FABSF(result[3]);
    }
    if (source->NegateAbs) {
	result[0] = -result[0];
	result[1] = -result[1];
	result[2] = -result[2];
	result[3] = -result[3];
    }
}


/**
 * Fetch the derivative with respect to X or Y for the given register.
 * XXX this currently only works for fragment program input attribs.
 */
static void
fetch_vector4_deriv(GLcontext * ctx,
		    const struct prog_src_register *source,
		    const struct gl_program_machine *machine,
		    char xOrY, GLfloat result[4])
{
    if (source->File == PROGRAM_INPUT && (GLuint)source->Index < machine->NumDeriv) {
	const GLint col = machine->CurElement;
	const GLfloat w = machine->Attribs[FRAG_ATTRIB_WPOS][col][3];
	const GLfloat invQ = 1.0f / w;
	const GLfloat dwdx = machine->DerivX[FRAG_ATTRIB_WPOS][3];
	const GLfloat dwdy = machine->DerivY[FRAG_ATTRIB_WPOS][3];
	GLfloat deriv[4];

	if (xOrY == 'X') {
	    deriv[0] = (machine->DerivX[source->Index][0] -
			machine->Attribs[source->Index][col][0] * dwdx) * invQ;
	    deriv[1] = (machine->DerivX[source->Index][1] -
			machine->Attribs[source->Index][col][1] * dwdx) * invQ;
	    deriv[2] = (machine->DerivX[source->Index][2] -
			machine->Attribs[source->Index][col][2] * dwdx) * invQ;
	    deriv[3] = (machine->DerivX[source->Index][3] -
			machine->Attribs[source->Index][col][3] * dwdx) * invQ;
	} else {
	    deriv[0] = (machine->DerivY[source->Index][0] -
			machine->Attribs[source->Index][col][0] * dwdy) * invQ;
	    deriv[1] = (machine->DerivY[source->Index][1] -
			machine->Attribs[source->Index][col][1] * dwdy) * invQ;
	    deriv[2] = (machine->DerivY[source->Index][2] -
			machine->Attribs[source->Index][col][2] * dwdy) * invQ;
	    deriv[3] = (machine->DerivY[source->Index][3] -
			machine->Attribs[source->Index][col][3] * dwdy) * invQ;
	}

	result[0] = deriv[GET_SWZ(source->Swizzle, 0)];
	result[1] = deriv[GET_SWZ(source->Swizzle, 1)];
	result[2] = deriv[GET_SWZ(source->Swizzle, 2)];
	result[3] = deriv[GET_SWZ(source->Swizzle, 3)];

	if (source->NegateBase) {
	    result[0] = -result[0];
	    result[1] = -result[1];
	    result[2] = -result[2];
	    result[3] = -result[3];
	}
	if (source->Abs) {
	    result[0] = FABSF(result[0]);
	    result[1] = FABSF(result[1]);
	    result[2] = FABSF(result[2]);
	    result[3] = FABSF(result[3]);
	}
	if (source->NegateAbs) {
	    result[0] = -result[0];
	    result[1] = -result[1];
	    result[2] = -result[2];
	    result[3] = -result[3];
	}
    } else {
	ASSIGN_4V(result, 0.0, 0.0, 0.0, 0.0);
    }
}


/**
 * As above, but only return result[0] element.
 */
static void
fetch_vector1(const struct prog_src_register *source,
	      const struct gl_program_machine *machine, GLfloat result[4])
{
    const GLfloat *src = get_register_pointer(source, machine);
    ASSERT(src);

    result[0] = src[GET_SWZ(source->Swizzle, 0)];

    if (source->NegateBase) {
	result[0] = -result[0];
    }
    if (source->Abs) {
	result[0] = FABSF(result[0]);
    }
    if (source->NegateAbs) {
	result[0] = -result[0];
    }
}


/**
 * Fetch texel from texture.  Use partial derivatives when possible.
 */
static INLINE void
fetch_texel(GLcontext *ctx,
	    const struct gl_program_machine *machine,
	    const struct prog_instruction *inst,
	    const GLfloat texcoord[4], GLfloat lodBias,
	    GLfloat color[4])
{
    /* Note: we only have the right derivatives for fragment input attribs.
     */
    if (machine->NumDeriv > 0 &&
	inst->SrcReg[0].File == PROGRAM_INPUT &&
	inst->SrcReg[0].Index == FRAG_ATTRIB_TEX0 + inst->TexSrcUnit) {
	/* simple texture fetch for which we should have derivatives */
	GLuint attr = inst->SrcReg[0].Index;
	machine->FetchTexelDeriv(ctx, texcoord,
				 machine->DerivX[attr],
				 machine->DerivY[attr],
				 lodBias,
				 inst->TexSrcUnit, color);
    } else {
	machine->FetchTexelLod(ctx, texcoord, lodBias,
			       inst->TexSrcUnit, color);
    }
}


/**
 * Test value against zero and return GT, LT, EQ or UN if NaN.
 */
static INLINE GLuint
generate_cc(float value)
{
    if (value != value)
	return COND_UN;           /* NaN */
    if (value > 0.0F)
	return COND_GT;
    if (value < 0.0F)
	return COND_LT;
    return COND_EQ;
}


/**
 * Test if the ccMaskRule is satisfied by the given condition code.
 * Used to mask destination writes according to the current condition code.
 */
static INLINE GLboolean
test_cc(GLuint condCode, GLuint ccMaskRule)
{
    switch (ccMaskRule) {
	case COND_EQ:
	    return (condCode == COND_EQ);
	case COND_NE:
	    return (condCode != COND_EQ);
	case COND_LT:
	    return (condCode == COND_LT);
	case COND_GE:
	    return (condCode == COND_GT || condCode == COND_EQ);
	case COND_LE:
	    return (condCode == COND_LT || condCode == COND_EQ);
	case COND_GT:
	    return (condCode == COND_GT);
	case COND_TR:
	    return GL_TRUE;
	case COND_FL:
	    return GL_FALSE;
	default:
	    return GL_TRUE;
    }
}


/**
 * Evaluate the 4 condition codes against a predicate and return GL_TRUE
 * or GL_FALSE to indicate result.
 */
static INLINE GLboolean
eval_condition(const struct gl_program_machine *machine,
	       const struct prog_instruction *inst)
{
    const GLuint swizzle = inst->DstReg.CondSwizzle;
    const GLuint condMask = inst->DstReg.CondMask;
    if (test_cc(machine->CondCodes[GET_SWZ(swizzle, 0)], condMask) ||
	test_cc(machine->CondCodes[GET_SWZ(swizzle, 1)], condMask) ||
	test_cc(machine->CondCodes[GET_SWZ(swizzle, 2)], condMask) ||
	test_cc(machine->CondCodes[GET_SWZ(swizzle, 3)], condMask)) {
	return GL_TRUE;
    } else {
	return GL_FALSE;
    }
}



/**
 * Store 4 floats into a register.  Observe the instructions saturate and
 * set-condition-code flags.
 */
static void
store_vector4(const struct prog_instruction *inst,
	      struct gl_program_machine *machine, const GLfloat value[4])
{
    const struct prog_dst_register *dest = &(inst->DstReg);
    const GLboolean clamp = inst->SaturateMode == SATURATE_ZERO_ONE;
    GLfloat *dstReg;
    GLfloat clampedValue[4];
    GLuint writeMask = dest->WriteMask;

    switch (dest->File) {
	case PROGRAM_OUTPUT:
	    ASSERT(dest->Index < MAX_PROGRAM_OUTPUTS);
	    dstReg = machine->Outputs[dest->Index];
	    break;
	case PROGRAM_TEMPORARY:
	    ASSERT(dest->Index < MAX_PROGRAM_TEMPS);
	    dstReg = machine->Temporaries[dest->Index];
	    break;
	case PROGRAM_WRITE_ONLY:
	    return;
	default:
	    _mesa_problem(NULL, "bad register file in store_vector4(fp)");
	    return;
    }

#if 0
    if (value[0] > 1.0e10 ||
	IS_INF_OR_NAN(value[0]) ||
	IS_INF_OR_NAN(value[1]) ||
	IS_INF_OR_NAN(value[2]) || IS_INF_OR_NAN(value[3]))
	printf("store %g %g %g %g\n", value[0], value[1], value[2], value[3]);
#endif

    if (clamp) {
	clampedValue[0] = CLAMP(value[0], 0.0F, 1.0F);
	clampedValue[1] = CLAMP(value[1], 0.0F, 1.0F);
	clampedValue[2] = CLAMP(value[2], 0.0F, 1.0F);
	clampedValue[3] = CLAMP(value[3], 0.0F, 1.0F);
	value = clampedValue;
    }

    if (dest->CondMask != COND_TR) {
	/* condition codes may turn off some writes */
	if (writeMask & WRITEMASK_X) {
	    if (!test_cc(machine->CondCodes[GET_SWZ(dest->CondSwizzle, 0)],
			 dest->CondMask))
		writeMask &= ~WRITEMASK_X;
	}
	if (writeMask & WRITEMASK_Y) {
	    if (!test_cc(machine->CondCodes[GET_SWZ(dest->CondSwizzle, 1)],
			 dest->CondMask))
		writeMask &= ~WRITEMASK_Y;
	}
	if (writeMask & WRITEMASK_Z) {
	    if (!test_cc(machine->CondCodes[GET_SWZ(dest->CondSwizzle, 2)],
			 dest->CondMask))
		writeMask &= ~WRITEMASK_Z;
	}
	if (writeMask & WRITEMASK_W) {
	    if (!test_cc(machine->CondCodes[GET_SWZ(dest->CondSwizzle, 3)],
			 dest->CondMask))
		writeMask &= ~WRITEMASK_W;
	}
    }

    if (writeMask & WRITEMASK_X)
	dstReg[0] = value[0];
    if (writeMask & WRITEMASK_Y)
	dstReg[1] = value[1];
    if (writeMask & WRITEMASK_Z)
	dstReg[2] = value[2];
    if (writeMask & WRITEMASK_W)
	dstReg[3] = value[3];

    if (inst->CondUpdate) {
	if (writeMask & WRITEMASK_X)
	    machine->CondCodes[0] = generate_cc(value[0]);
	if (writeMask & WRITEMASK_Y)
	    machine->CondCodes[1] = generate_cc(value[1]);
	if (writeMask & WRITEMASK_Z)
	    machine->CondCodes[2] = generate_cc(value[2]);
	if (writeMask & WRITEMASK_W)
	    machine->CondCodes[3] = generate_cc(value[3]);
#if DEBUG_PROG
	printf("CondCodes=(%s,%s,%s,%s) for:\n",
	       _mesa_condcode_string(machine->CondCodes[0]),
	       _mesa_condcode_string(machine->CondCodes[1]),
	       _mesa_condcode_string(machine->CondCodes[2]),
	       _mesa_condcode_string(machine->CondCodes[3]));
#endif
    }
}

/*
 * The general interpreter above accepts the full ARB/NV/GLSL program model.
 * Software vertex shaders spend most of their time repeatedly resolving that
 * model's register files, however.  Straight-line GLSL emitted by slang is a
 * much smaller problem: resolve its source and destination registers once per
 * TNL batch, then retain only swizzles and write masks in the hot loop.
 */
struct gl_fast_source {
    const GLfloat *value;
    GLubyte component[4];
    GLubyte modifiers;
    GLubyte file;
    GLint index;
};

struct gl_fast_instruction {
    gl_inst_opcode opcode;
    struct gl_fast_source source[3];
    GLfloat *destination;
    GLuint writeMask;
    GLubyte destinationFile;
    GLint destinationIndex;
    GLuint condUpdate;
    GLuint condMask;
    GLuint condSwizzle;
    GLuint branchTarget;
};

struct gl_program_fast {
    struct gl_fast_instruction *instructions;
    struct gl_program_machine *machine;
    GLuint count;
    GLboolean batchSupported;
};

static GLboolean
fast_opcode_supported(gl_inst_opcode opcode)
{
    switch (opcode) {
	case OPCODE_ABS:
	case OPCODE_ADD:
	case OPCODE_BGNSUB:
	case OPCODE_CAL:
	case OPCODE_DP3:
	case OPCODE_DP4:
	case OPCODE_ELSE:
	case OPCODE_END:
	case OPCODE_ENDIF:
	case OPCODE_ENDSUB:
	case OPCODE_FLR:
	case OPCODE_FRC:
	case OPCODE_IF:
	case OPCODE_MAD:
	case OPCODE_MAX:
	case OPCODE_MIN:
	case OPCODE_MOV:
	case OPCODE_MUL:
	case OPCODE_NOP:
	case OPCODE_RCP:
	case OPCODE_RET:
	case OPCODE_SEQ:
	case OPCODE_SGE:
	case OPCODE_SLT:
	case OPCODE_SNE:
	case OPCODE_SUB:
	    return GL_TRUE;
	default:
	    return GL_FALSE;
    }
}

/* Control flow and condition-code updates are invocation-local and therefore
 * cannot share one lockstep program counter.  Straight-line arithmetic is the
 * common generated GLSL vertex-shader case and is safe to execute four
 * vertices at a time. */
static GLboolean
fast_batch_opcode_supported(gl_inst_opcode opcode)
{
    switch (opcode) {
	case OPCODE_ABS:
	case OPCODE_ADD:
	case OPCODE_DP3:
	case OPCODE_DP4:
	case OPCODE_END:
	case OPCODE_FLR:
	case OPCODE_FRC:
	case OPCODE_MAD:
	case OPCODE_MAX:
	case OPCODE_MIN:
	case OPCODE_MOV:
	case OPCODE_MUL:
	case OPCODE_NOP:
	case OPCODE_RCP:
	case OPCODE_SEQ:
	case OPCODE_SGE:
	case OPCODE_SLT:
	case OPCODE_SNE:
	case OPCODE_SUB:
	    return GL_TRUE;
	default:
	    return GL_FALSE;
    }
}

static GLboolean
fast_opcode_writes_result(gl_inst_opcode opcode)
{
    switch (opcode) {
	case OPCODE_BGNSUB:
	case OPCODE_CAL:
	case OPCODE_ELSE:
	case OPCODE_END:
	case OPCODE_ENDIF:
	case OPCODE_ENDSUB:
	case OPCODE_IF:
	case OPCODE_NOP:
	case OPCODE_RET:
	    return GL_FALSE;
	default:
	    return GL_TRUE;
    }
}

static GLboolean
fast_opcode_has_branch_target(gl_inst_opcode opcode)
{
    return opcode == OPCODE_CAL ||
	opcode == OPCODE_ELSE ||
	opcode == OPCODE_IF;
}

static GLfloat *
fast_destination_pointer(const struct prog_dst_register *destination,
			 struct gl_program_machine *machine)
{
    switch (destination->File) {
	case PROGRAM_TEMPORARY:
	    return machine->Temporaries[destination->Index];
	case PROGRAM_OUTPUT:
	    return machine->Outputs[destination->Index];
	default:
	    return NULL;
    }
}

struct gl_program_fast *
_mesa_create_fast_program(GLcontext *ctx,
			  const struct gl_program *program,
			  struct gl_program_machine *machine)
{
    struct gl_program_fast *fast;
    GLuint i;

    (void) ctx;
    if (!program || !machine || !program->NumInstructions)
	return NULL;
    {
	const char *disable = getenv("OSMESA_DISABLE_FAST_VERTEX_VM");
	if (disable && disable[0] != '\0' && disable[0] != '0')
	    return NULL;
    }

    fast = (struct gl_program_fast *) calloc(1, sizeof(*fast));
    if (!fast)
	return NULL;
    fast->instructions = (struct gl_fast_instruction *)
	calloc(program->NumInstructions, sizeof(*fast->instructions));
    if (!fast->instructions) {
	free(fast);
	return NULL;
    }
    fast->count = program->NumInstructions;
    fast->machine = machine;
    /* NV vertex programs define invocation register initialization
     * differently.  Keep them on the scalar VM; GLSL and ARB vertex
     * programs use the ARB target and are safe candidates for lockstep
     * execution. */
    fast->batchSupported = program->Target == GL_VERTEX_PROGRAM_ARB;
    {
	const char *disable = getenv("OSMESA_DISABLE_FAST_VERTEX_BATCH");
	if (disable && disable[0] != '\0' && disable[0] != '0')
	    fast->batchSupported = GL_FALSE;
    }

    machine->CurProgram = program;
    machine->EnvParams = ctx->VertexProgram.Parameters;
    for (i = 0; i < program->NumInstructions; ++i) {
	const struct prog_instruction *instruction = program->Instructions + i;
	struct gl_fast_instruction *out = fast->instructions + i;
	const GLuint sourceCount =
	    _mesa_num_inst_src_regs(instruction->Opcode);
	GLuint source;

	if (!fast_opcode_supported(instruction->Opcode) ||
	    instruction->SaturateMode != SATURATE_OFF ||
	    (instruction->Opcode == OPCODE_IF &&
	     instruction->SrcReg[0].File != PROGRAM_UNDEFINED) ||
	    (fast_opcode_has_branch_target(instruction->Opcode) &&
	     (instruction->BranchTarget < 0 ||
	      (GLuint) instruction->BranchTarget >=
	      program->NumInstructions)) ||
	    (fast_opcode_writes_result(instruction->Opcode) &&
	     instruction->DstReg.CondMask != COND_TR))
	    goto unsupported;

	out->opcode = instruction->Opcode;
	if (!fast_batch_opcode_supported(instruction->Opcode) ||
	    instruction->CondUpdate)
	    fast->batchSupported = GL_FALSE;
	out->destinationFile = instruction->DstReg.File;
	out->destinationIndex = instruction->DstReg.Index;
	out->condUpdate = instruction->CondUpdate;
	out->condMask = instruction->DstReg.CondMask;
	out->condSwizzle = instruction->DstReg.CondSwizzle;
	out->branchTarget = instruction->BranchTarget;
	if (fast_opcode_writes_result(instruction->Opcode)) {
	    out->destination =
		fast_destination_pointer(&instruction->DstReg, machine);
	    if (!out->destination)
		goto unsupported;
	    out->writeMask = instruction->DstReg.WriteMask;
	}
	for (source = 0; source < sourceCount; ++source) {
	    const struct prog_src_register *input =
		instruction->SrcReg + source;
	    struct gl_fast_source *resolved = out->source + source;
	    if (input->RelAddr)
		goto unsupported;
	    resolved->value = get_register_pointer(input, machine);
	    resolved->file = input->File;
	    resolved->index = input->Index;
	    if (!resolved->value)
		goto unsupported;
	    resolved->component[0] =
		(GLubyte) GET_SWZ(input->Swizzle, 0);
	    resolved->component[1] =
		(GLubyte) GET_SWZ(input->Swizzle, 1);
	    resolved->component[2] =
		(GLubyte) GET_SWZ(input->Swizzle, 2);
	    resolved->component[3] =
		(GLubyte) GET_SWZ(input->Swizzle, 3);
	    resolved->modifiers =
		(input->NegateBase ? 1u : 0u) |
		(input->Abs ? 2u : 0u) |
		(input->NegateAbs ? 4u : 0u);
	}
    }
    return fast;

unsupported:
    _mesa_destroy_fast_program(fast);
    return NULL;
}

void
_mesa_destroy_fast_program(struct gl_program_fast *program)
{
    if (!program)
	return;
    free(program->instructions);
    free(program);
}

static INLINE void
fast_fetch_vector4(const struct gl_fast_source *source, GLfloat result[4])
{
    const GLfloat *value = source->value;
    const GLuint modifiers = source->modifiers;

    result[0] = value[source->component[0]];
    result[1] = value[source->component[1]];
    result[2] = value[source->component[2]];
    result[3] = value[source->component[3]];
    if (!modifiers)
	return;
    if (modifiers & 1u) {
	result[0] = -result[0];
	result[1] = -result[1];
	result[2] = -result[2];
	result[3] = -result[3];
    }
    if (modifiers & 2u) {
	result[0] = FABSF(result[0]);
	result[1] = FABSF(result[1]);
	result[2] = FABSF(result[2]);
	result[3] = FABSF(result[3]);
    }
    if (modifiers & 4u) {
	result[0] = -result[0];
	result[1] = -result[1];
	result[2] = -result[2];
	result[3] = -result[3];
    }
}

static INLINE GLfloat
fast_fetch_vector1(const struct gl_fast_source *source)
{
    GLfloat result = source->value[source->component[0]];
    const GLuint modifiers = source->modifiers;
    if (modifiers & 1u)
	result = -result;
    if (modifiers & 2u)
	result = FABSF(result);
    if (modifiers & 4u)
	result = -result;
    return result;
}

static INLINE void
fast_store_vector4(const struct gl_fast_instruction *instruction,
		   struct gl_program_machine *machine,
		   const GLfloat value[4])
{
    GLfloat *destination = instruction->destination;
    const GLuint mask = instruction->writeMask;
    switch (mask) {
	case WRITEMASK_XYZW:
	    COPY_4V(destination, value);
	    break;
	case WRITEMASK_XYZ:
	    COPY_3V(destination, value);
	    break;
	case WRITEMASK_X:
	    destination[0] = value[0];
	    break;
	case WRITEMASK_Y:
	    destination[1] = value[1];
	    break;
	case WRITEMASK_Z:
	    destination[2] = value[2];
	    break;
	case WRITEMASK_W:
	    destination[3] = value[3];
	    break;
	default:
	    if (mask & WRITEMASK_X)
		destination[0] = value[0];
	    if (mask & WRITEMASK_Y)
		destination[1] = value[1];
	    if (mask & WRITEMASK_Z)
		destination[2] = value[2];
	    if (mask & WRITEMASK_W)
		destination[3] = value[3];
	    break;
    }
    if (instruction->condUpdate) {
	if (mask & WRITEMASK_X)
	    machine->CondCodes[0] = generate_cc(value[0]);
	if (mask & WRITEMASK_Y)
	    machine->CondCodes[1] = generate_cc(value[1]);
	if (mask & WRITEMASK_Z)
	    machine->CondCodes[2] = generate_cc(value[2]);
	if (mask & WRITEMASK_W)
	    machine->CondCodes[3] = generate_cc(value[3]);
    }
}

static INLINE GLboolean
fast_eval_condition(const struct gl_program_machine *machine,
		    const struct gl_fast_instruction *instruction)
{
    const GLuint swizzle = instruction->condSwizzle;
    const GLuint mask = instruction->condMask;

    return test_cc(machine->CondCodes[GET_SWZ(swizzle, 0)], mask) ||
	test_cc(machine->CondCodes[GET_SWZ(swizzle, 1)], mask) ||
	test_cc(machine->CondCodes[GET_SWZ(swizzle, 2)], mask) ||
	test_cc(machine->CondCodes[GET_SWZ(swizzle, 3)], mask);
}

GLboolean
_mesa_execute_fast_program(const struct gl_program_fast *program)
{
    struct gl_program_machine *machine = program->machine;
    GLuint pc;

    for (pc = 0; pc < program->count; ++pc) {
	const struct gl_fast_instruction *instruction =
	    program->instructions + pc;
	GLfloat a[4], b[4], c[4], result[4];

	switch (instruction->opcode) {
	    case OPCODE_ABS:
		fast_fetch_vector4(instruction->source, a);
		result[0] = FABSF(a[0]);
		result[1] = FABSF(a[1]);
		result[2] = FABSF(a[2]);
		result[3] = FABSF(a[3]);
		break;
	    case OPCODE_ADD:
		fast_fetch_vector4(instruction->source, a);
		fast_fetch_vector4(instruction->source + 1, b);
		result[0] = a[0] + b[0];
		result[1] = a[1] + b[1];
		result[2] = a[2] + b[2];
		result[3] = a[3] + b[3];
		break;
	    case OPCODE_BGNSUB:
	    case OPCODE_ENDIF:
	    case OPCODE_ENDSUB:
		continue;
	    case OPCODE_CAL:
		if (fast_eval_condition(machine, instruction)) {
		    if (machine->StackDepth >= MAX_PROGRAM_CALL_DEPTH)
			return GL_TRUE;
		    machine->CallStack[machine->StackDepth++] = pc + 1;
		    pc = instruction->branchTarget - 1;
		}
		continue;
	    case OPCODE_DP3:
		fast_fetch_vector4(instruction->source, a);
		fast_fetch_vector4(instruction->source + 1, b);
		result[0] = result[1] = result[2] = result[3] = DOT3(a, b);
		break;
	    case OPCODE_DP4:
		fast_fetch_vector4(instruction->source, a);
		fast_fetch_vector4(instruction->source + 1, b);
		result[0] = result[1] = result[2] = result[3] = DOT4(a, b);
		break;
	    case OPCODE_END:
		return GL_TRUE;
	    case OPCODE_ELSE:
		pc = instruction->branchTarget - 1;
		continue;
	    case OPCODE_FLR:
		fast_fetch_vector4(instruction->source, a);
		result[0] = FLOORF(a[0]);
		result[1] = FLOORF(a[1]);
		result[2] = FLOORF(a[2]);
		result[3] = FLOORF(a[3]);
		break;
	    case OPCODE_FRC:
		fast_fetch_vector4(instruction->source, a);
		result[0] = a[0] - FLOORF(a[0]);
		result[1] = a[1] - FLOORF(a[1]);
		result[2] = a[2] - FLOORF(a[2]);
		result[3] = a[3] - FLOORF(a[3]);
		break;
	    case OPCODE_IF:
		if (!fast_eval_condition(machine, instruction))
		    pc = instruction->branchTarget - 1;
		continue;
	    case OPCODE_MAD:
		fast_fetch_vector4(instruction->source, a);
		fast_fetch_vector4(instruction->source + 1, b);
		fast_fetch_vector4(instruction->source + 2, c);
		result[0] = a[0] * b[0] + c[0];
		result[1] = a[1] * b[1] + c[1];
		result[2] = a[2] * b[2] + c[2];
		result[3] = a[3] * b[3] + c[3];
		break;
	    case OPCODE_MAX:
		fast_fetch_vector4(instruction->source, a);
		fast_fetch_vector4(instruction->source + 1, b);
		result[0] = MAX2(a[0], b[0]);
		result[1] = MAX2(a[1], b[1]);
		result[2] = MAX2(a[2], b[2]);
		result[3] = MAX2(a[3], b[3]);
		break;
	    case OPCODE_MIN:
		fast_fetch_vector4(instruction->source, a);
		fast_fetch_vector4(instruction->source + 1, b);
		result[0] = MIN2(a[0], b[0]);
		result[1] = MIN2(a[1], b[1]);
		result[2] = MIN2(a[2], b[2]);
		result[3] = MIN2(a[3], b[3]);
		break;
	    case OPCODE_MOV:
		fast_fetch_vector4(instruction->source, result);
		break;
	    case OPCODE_MUL:
		fast_fetch_vector4(instruction->source, a);
		fast_fetch_vector4(instruction->source + 1, b);
		result[0] = a[0] * b[0];
		result[1] = a[1] * b[1];
		result[2] = a[2] * b[2];
		result[3] = a[3] * b[3];
		break;
	    case OPCODE_NOP:
		continue;
	    case OPCODE_RCP: {
		const GLfloat reciprocal =
		    1.0F / fast_fetch_vector1(instruction->source);
		result[0] = result[1] = result[2] = result[3] = reciprocal;
		break;
	    }
	    case OPCODE_RET:
		if (fast_eval_condition(machine, instruction)) {
		    if (machine->StackDepth == 0)
			return GL_TRUE;
		    pc = machine->CallStack[--machine->StackDepth] - 1;
		}
		continue;
	    case OPCODE_SEQ:
	    case OPCODE_SGE:
	    case OPCODE_SLT:
	    case OPCODE_SNE: {
		GLuint component;
		fast_fetch_vector4(instruction->source, a);
		fast_fetch_vector4(instruction->source + 1, b);
		for (component = 0; component < 4; ++component) {
		    switch (instruction->opcode) {
			case OPCODE_SEQ:
			    result[component] =
				(a[component] == b[component]) ? 1.0F : 0.0F;
			    break;
			case OPCODE_SGE:
			    result[component] =
				(a[component] >= b[component]) ? 1.0F : 0.0F;
			    break;
			case OPCODE_SLT:
			    result[component] =
				(a[component] < b[component]) ? 1.0F : 0.0F;
			    break;
			default:
			    result[component] =
				(a[component] != b[component]) ? 1.0F : 0.0F;
			    break;
		    }
		}
		break;
	    }
	    case OPCODE_SUB:
		fast_fetch_vector4(instruction->source, a);
		fast_fetch_vector4(instruction->source + 1, b);
		result[0] = a[0] - b[0];
		result[1] = a[1] - b[1];
		result[2] = a[2] - b[2];
		result[3] = a[3] - b[3];
		break;
	    default:
		return GL_FALSE;
	}
	fast_store_vector4(instruction, machine, result);
    }
    return GL_TRUE;
}

#define FAST_BATCH_WIDTH 4

/* Component-major storage lets the compiler operate on four independent
 * vertices with one host vector instruction.  The state is deliberately
 * local to one call: uniforms remain borrowed from the retained scalar
 * machine, while invocation-local registers never escape this function. */
struct gl_fast_batch_machine {
    GLfloat inputs[VERT_ATTRIB_MAX][4][FAST_BATCH_WIDTH];
    GLfloat temporaries[MAX_PROGRAM_TEMPS][4][FAST_BATCH_WIDTH];
    GLfloat outputs[MAX_PROGRAM_OUTPUTS][4][FAST_BATCH_WIDTH];
};

static INLINE void
fast_batch_fetch_vector4(const struct gl_fast_source *source,
			 const struct gl_fast_batch_machine *state,
			 GLfloat result[4][FAST_BATCH_WIDTH])
{
    GLuint component;
    GLuint lane;

    switch (source->file) {
	case PROGRAM_INPUT:
	    for (component = 0; component < 4; ++component) {
		const GLuint selected = source->component[component];
		for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
		    result[component][lane] =
			state->inputs[source->index][selected][lane];
	    }
	    break;
	case PROGRAM_TEMPORARY:
	    for (component = 0; component < 4; ++component) {
		const GLuint selected = source->component[component];
		for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
		    result[component][lane] =
			state->temporaries[source->index][selected][lane];
	    }
	    break;
	case PROGRAM_OUTPUT:
	    for (component = 0; component < 4; ++component) {
		const GLuint selected = source->component[component];
		for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
		    result[component][lane] =
			state->outputs[source->index][selected][lane];
	    }
	    break;
	default:
	    for (component = 0; component < 4; ++component) {
		const GLfloat value =
		    source->value[source->component[component]];
		for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
		    result[component][lane] = value;
	    }
	    break;
    }

    if (source->modifiers & 1u) {
	for (component = 0; component < 4; ++component)
	    for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
		result[component][lane] = -result[component][lane];
    }
    if (source->modifiers & 2u) {
	for (component = 0; component < 4; ++component)
	    for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
		result[component][lane] = FABSF(result[component][lane]);
    }
    if (source->modifiers & 4u) {
	for (component = 0; component < 4; ++component)
	    for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
		result[component][lane] = -result[component][lane];
    }
}

static INLINE void
fast_batch_store_vector4(const struct gl_fast_instruction *instruction,
			 struct gl_fast_batch_machine *state,
			 const GLfloat value[4][FAST_BATCH_WIDTH])
{
    GLfloat (*destination)[FAST_BATCH_WIDTH];
    GLuint component;
    GLuint lane;

    if (instruction->destinationFile == PROGRAM_TEMPORARY)
	destination = state->temporaries[instruction->destinationIndex];
    else if (instruction->destinationFile == PROGRAM_OUTPUT)
	destination = state->outputs[instruction->destinationIndex];
    else
	return;

    for (component = 0; component < 4; ++component) {
	if (!(instruction->writeMask & (1u << component)))
	    continue;
	for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
	    destination[component][lane] = value[component][lane];
    }
}

GLuint
_mesa_execute_fast_program_batch(
    const struct gl_program_fast *program,
    GLuint count,
    GLuint numInputs,
    const GLuint *inputAttributes,
    const GLuint *inputSizes,
    const GLuint *inputStrides,
    const GLubyte *const *inputData,
    GLuint numOutputs,
    const GLuint *outputAttributes,
    GLubyte *const *outputData,
    const GLuint *outputStrides)
{
    struct gl_fast_batch_machine state;
    const GLuint batchCount = count - count % FAST_BATCH_WIDTH;
    GLuint base;

    if (!program || !program->batchSupported || !batchCount ||
	(numInputs && (!inputAttributes || !inputSizes || !inputStrides ||
		       !inputData)) ||
	(numOutputs && (!outputAttributes || !outputData || !outputStrides)))
	return 0;

    for (base = 0; base < batchCount; base += FAST_BATCH_WIDTH) {
	GLuint input;
	GLuint output;
	GLuint pc;

	for (input = 0; input < numInputs; ++input) {
	    const GLuint attribute = inputAttributes[input];
	    const GLuint size = MIN2(inputSizes[input], 4);
	    GLuint lane;
	    GLuint component;
	    if (attribute >= VERT_ATTRIB_MAX)
		return base;
	    for (component = 0; component < 4; ++component) {
		for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane) {
		    const GLfloat *source = (const GLfloat *)
			(inputData[input] +
			 (base + lane) * inputStrides[input]);
		    state.inputs[attribute][component][lane] =
			component < size ? source[component] :
			(component == 3 ? 1.0F : 0.0F);
		}
	    }
	}

	for (pc = 0; pc < program->count; ++pc) {
	    const struct gl_fast_instruction *instruction =
		program->instructions + pc;
	    GLfloat a[4][FAST_BATCH_WIDTH];
	    GLfloat b[4][FAST_BATCH_WIDTH];
	    GLfloat c[4][FAST_BATCH_WIDTH];
	    GLfloat result[4][FAST_BATCH_WIDTH];
	    GLuint component;
	    GLuint lane;

	    switch (instruction->opcode) {
		case OPCODE_ABS:
		    fast_batch_fetch_vector4(instruction->source, &state, a);
		    for (component = 0; component < 4; ++component)
			for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
			    result[component][lane] =
				FABSF(a[component][lane]);
		    break;
		case OPCODE_ADD:
		    fast_batch_fetch_vector4(instruction->source, &state, a);
		    fast_batch_fetch_vector4(instruction->source + 1, &state, b);
		    for (component = 0; component < 4; ++component)
			for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
			    result[component][lane] =
				a[component][lane] + b[component][lane];
		    break;
		case OPCODE_DP3:
		case OPCODE_DP4: {
		    const GLuint components =
			instruction->opcode == OPCODE_DP3 ? 3 : 4;
		    fast_batch_fetch_vector4(instruction->source, &state, a);
		    fast_batch_fetch_vector4(instruction->source + 1, &state, b);
		    for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane) {
			GLfloat dot = 0.0F;
			for (component = 0; component < components; ++component)
			    dot += a[component][lane] * b[component][lane];
			for (component = 0; component < 4; ++component)
			    result[component][lane] = dot;
		    }
		    break;
		}
		case OPCODE_END:
		    pc = program->count;
		    continue;
		case OPCODE_FLR:
		    fast_batch_fetch_vector4(instruction->source, &state, a);
		    for (component = 0; component < 4; ++component)
			for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
			    result[component][lane] =
				FLOORF(a[component][lane]);
		    break;
		case OPCODE_FRC:
		    fast_batch_fetch_vector4(instruction->source, &state, a);
		    for (component = 0; component < 4; ++component)
			for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
			    result[component][lane] =
				a[component][lane] -
				FLOORF(a[component][lane]);
		    break;
		case OPCODE_MAD:
		    fast_batch_fetch_vector4(instruction->source, &state, a);
		    fast_batch_fetch_vector4(instruction->source + 1, &state, b);
		    fast_batch_fetch_vector4(instruction->source + 2, &state, c);
		    for (component = 0; component < 4; ++component)
			for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
			    result[component][lane] =
				a[component][lane] * b[component][lane] +
				c[component][lane];
		    break;
		case OPCODE_MAX:
		case OPCODE_MIN:
		    fast_batch_fetch_vector4(instruction->source, &state, a);
		    fast_batch_fetch_vector4(instruction->source + 1, &state, b);
		    for (component = 0; component < 4; ++component)
			for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
			    result[component][lane] =
				instruction->opcode == OPCODE_MAX ?
				MAX2(a[component][lane], b[component][lane]) :
				MIN2(a[component][lane], b[component][lane]);
		    break;
		case OPCODE_MOV:
		    fast_batch_fetch_vector4(instruction->source, &state, result);
		    break;
		case OPCODE_MUL:
		    fast_batch_fetch_vector4(instruction->source, &state, a);
		    fast_batch_fetch_vector4(instruction->source + 1, &state, b);
		    for (component = 0; component < 4; ++component)
			for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
			    result[component][lane] =
				a[component][lane] * b[component][lane];
		    break;
		case OPCODE_NOP:
		    continue;
		case OPCODE_RCP:
		    fast_batch_fetch_vector4(instruction->source, &state, a);
		    for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane) {
			const GLfloat reciprocal = 1.0F / a[0][lane];
			for (component = 0; component < 4; ++component)
			    result[component][lane] = reciprocal;
		    }
		    break;
		case OPCODE_SEQ:
		case OPCODE_SGE:
		case OPCODE_SLT:
		case OPCODE_SNE:
		    fast_batch_fetch_vector4(instruction->source, &state, a);
		    fast_batch_fetch_vector4(instruction->source + 1, &state, b);
		    for (component = 0; component < 4; ++component) {
			for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane) {
			    const GLfloat av = a[component][lane];
			    const GLfloat bv = b[component][lane];
			    GLboolean condition;
			    if (instruction->opcode == OPCODE_SEQ)
				condition = av == bv;
			    else if (instruction->opcode == OPCODE_SGE)
				condition = av >= bv;
			    else if (instruction->opcode == OPCODE_SLT)
				condition = av < bv;
			    else
				condition = av != bv;
			    result[component][lane] =
				condition ? 1.0F : 0.0F;
			}
		    }
		    break;
		case OPCODE_SUB:
		    fast_batch_fetch_vector4(instruction->source, &state, a);
		    fast_batch_fetch_vector4(instruction->source + 1, &state, b);
		    for (component = 0; component < 4; ++component)
			for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane)
			    result[component][lane] =
				a[component][lane] - b[component][lane];
		    break;
		default:
		    return base;
	    }
	    fast_batch_store_vector4(instruction, &state, result);
	}

	for (output = 0; output < numOutputs; ++output) {
	    const GLuint attribute = outputAttributes[output];
	    GLuint lane;
	    if (attribute >= MAX_PROGRAM_OUTPUTS)
		return base;
	    for (lane = 0; lane < FAST_BATCH_WIDTH; ++lane) {
		GLfloat *destination = (GLfloat *)
		    (outputData[output] +
		     (base + lane) * outputStrides[output]);
		destination[0] = state.outputs[attribute][0][lane];
		destination[1] = state.outputs[attribute][1][lane];
		destination[2] = state.outputs[attribute][2][lane];
		destination[3] = state.outputs[attribute][3][lane];
	    }
	}
    }
    return batchCount;
}

#undef FAST_BATCH_WIDTH

/**
 * Execute the given vertex/fragment program.
 *
 * \param ctx  rendering context
 * \param program  the program to execute
 * \param machine  machine state (must be initialized)
 * \return GL_TRUE if program completed or GL_FALSE if program executed KIL.
 */
GLboolean
_mesa_execute_program(GLcontext * ctx,
		      const struct gl_program *program,
		      struct gl_program_machine *machine)
{
    const GLuint numInst = program->NumInstructions;
    const GLuint maxExec = 10000;
    GLuint pc;
    GLuint numExec = 0;

    machine->CurProgram = program;

    if (DEBUG_PROG) {
	printf("execute program %u --------------------\n", program->Id);
    }

    if (program->Target == GL_VERTEX_PROGRAM_ARB) {
	machine->EnvParams = ctx->VertexProgram.Parameters;
    } else {
	machine->EnvParams = ctx->FragmentProgram.Parameters;
    }

    for (pc = 0; pc < numInst; pc++) {
	const struct prog_instruction *inst = program->Instructions + pc;

	if (DEBUG_PROG) {
	    _mesa_print_instruction(inst);
	}

	switch (inst->Opcode) {
	    case OPCODE_ABS: {
		GLfloat a[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		result[0] = FABSF(a[0]);
		result[1] = FABSF(a[1]);
		result[2] = FABSF(a[2]);
		result[3] = FABSF(a[3]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_ADD: {
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = a[0] + b[0];
		result[1] = a[1] + b[1];
		result[2] = a[2] + b[2];
		result[3] = a[3] + b[3];
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("ADD (%g %g %g %g) = (%g %g %g %g) + (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3]);
		}
	    }
	    break;
	    case OPCODE_ARL: {
		GLfloat t[4];
		fetch_vector4(&inst->SrcReg[0], machine, t);
		machine->AddressReg[0][0] = (GLint) FLOORF(t[0]);
	    }
	    break;
	    case OPCODE_BGNLOOP:
		/* no-op */
		break;
	    case OPCODE_ENDLOOP:
		/* subtract 1 here since pc is incremented by for(pc) loop */
		pc = inst->BranchTarget - 1;   /* go to matching BNGLOOP */
		break;
	    case OPCODE_BGNSUB:      /* begin subroutine */
		break;
	    case OPCODE_ENDSUB:      /* end subroutine */
		break;
	    case OPCODE_BRA:         /* branch (conditional) */
	    /* fall-through */
	    case OPCODE_BRK:         /* break out of loop (conditional) */
	    /* fall-through */
	    case OPCODE_CONT:        /* continue loop (conditional) */
		if (eval_condition(machine, inst)) {
		    /* take branch */
		    /* Subtract 1 here since we'll do pc++ at end of for-loop */
		    pc = inst->BranchTarget - 1;
		}
		break;
	    case OPCODE_CAL:         /* Call subroutine (conditional) */
		if (eval_condition(machine, inst)) {
		    /* call the subroutine */
		    if (machine->StackDepth >= MAX_PROGRAM_CALL_DEPTH) {
			return GL_TRUE;  /* Per GL_NV_vertex_program2 spec */
		    }
		    machine->CallStack[machine->StackDepth++] = pc + 1; /* next inst */
		    /* Subtract 1 here since we'll do pc++ at end of for-loop */
		    pc = inst->BranchTarget - 1;
		}
		break;
	    case OPCODE_CMP: {
		GLfloat a[4], b[4], c[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		fetch_vector4(&inst->SrcReg[2], machine, c);
		result[0] = a[0] < 0.0F ? b[0] : c[0];
		result[1] = a[1] < 0.0F ? b[1] : c[1];
		result[2] = a[2] < 0.0F ? b[2] : c[2];
		result[3] = a[3] < 0.0F ? b[3] : c[3];
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_COS: {
		GLfloat a[4], result[4];
		fetch_vector1(&inst->SrcReg[0], machine, a);
		result[0] = result[1] = result[2] = result[3]
						    = (GLfloat) cos(a[0]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_DDX: {       /* Partial derivative with respect to X */
		GLfloat result[4];
		fetch_vector4_deriv(ctx, &inst->SrcReg[0], machine,
				    'X', result);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_DDY: {       /* Partial derivative with respect to Y */
		GLfloat result[4];
		fetch_vector4_deriv(ctx, &inst->SrcReg[0], machine,
				    'Y', result);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_DP3: {
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = result[1] = result[2] = result[3] = DOT3(a, b);
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("DP3 %g = (%g %g %g) . (%g %g %g)\n",
			   result[0], a[0], a[1], a[2], b[0], b[1], b[2]);
		}
	    }
	    break;
	    case OPCODE_DP4: {
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = result[1] = result[2] = result[3] = DOT4(a, b);
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("DP4 %g = (%g, %g %g %g) . (%g, %g %g %g)\n",
			   result[0], a[0], a[1], a[2], a[3],
			   b[0], b[1], b[2], b[3]);
		}
	    }
	    break;
	    case OPCODE_DPH: {
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = result[1] = result[2] = result[3] =
							a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + b[3];
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_DST: {       /* Distance vector */
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = 1.0F;
		result[1] = a[1] * b[1];
		result[2] = a[2];
		result[3] = b[3];
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_EXP: {
		GLfloat t[4], q[4], floor_t0;
		fetch_vector1(&inst->SrcReg[0], machine, t);
		floor_t0 = FLOORF(t[0]);
		if (floor_t0 > FLT_MAX_EXP) {
		    SET_POS_INFINITY(q[0]);
		    SET_POS_INFINITY(q[2]);
		} else if (floor_t0 < FLT_MIN_EXP) {
		    q[0] = 0.0F;
		    q[2] = 0.0F;
		} else {
		    q[0] = LDEXPF(1.0, (int) floor_t0);
		    /* Note: GL_NV_vertex_program expects
		     * result.z = result.x * APPX(result.y)
		     * We do what the ARB extension says.
		     */
		    q[2] = pow(2.0, t[0]);
		}
		q[1] = t[0] - floor_t0;
		q[3] = 1.0F;
		store_vector4(inst, machine, q);
	    }
	    break;
	    case OPCODE_EX2: {       /* Exponential base 2 */
		GLfloat a[4], result[4];
		fetch_vector1(&inst->SrcReg[0], machine, a);
		result[0] = result[1] = result[2] = result[3] =
							(GLfloat) pow(2.0, a[0]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_FLR: {
		GLfloat a[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		result[0] = FLOORF(a[0]);
		result[1] = FLOORF(a[1]);
		result[2] = FLOORF(a[2]);
		result[3] = FLOORF(a[3]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_FRC: {
		GLfloat a[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		result[0] = a[0] - FLOORF(a[0]);
		result[1] = a[1] - FLOORF(a[1]);
		result[2] = a[2] - FLOORF(a[2]);
		result[3] = a[3] - FLOORF(a[3]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_IF: {
		GLboolean cond;
		/* eval condition */
		if (inst->SrcReg[0].File != PROGRAM_UNDEFINED) {
		    GLfloat a[4];
		    fetch_vector1(&inst->SrcReg[0], machine, a);
		    cond = (a[0] != 0.0);
		} else {
		    cond = eval_condition(machine, inst);
		}
		if (DEBUG_PROG) {
		    printf("IF: %d\n", cond);
		}
		/* do if/else */
		if (cond) {
		    /* do if-clause (just continue execution) */
		} else {
		    /* go to the instruction after ELSE or ENDIF */
		    assert(inst->BranchTarget >= 0);
		    pc = inst->BranchTarget - 1;
		}
	    }
	    break;
	    case OPCODE_ELSE:
		/* goto ENDIF */
		assert(inst->BranchTarget >= 0);
		pc = inst->BranchTarget - 1;
		break;
	    case OPCODE_ENDIF:
		/* nothing */
		break;
	    case OPCODE_INT: {       /* float to int */
		GLfloat a[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		result[0] = (GLfloat)(GLint) a[0];
		result[1] = (GLfloat)(GLint) a[1];
		result[2] = (GLfloat)(GLint) a[2];
		result[3] = (GLfloat)(GLint) a[3];
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_KIL_NV:      /* NV_f_p only (conditional) */
		if (eval_condition(machine, inst)) {
		    return GL_FALSE;
		}
		break;
	    case OPCODE_KIL: {       /* ARB_f_p only */
		GLfloat a[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		if (a[0] < 0.0F || a[1] < 0.0F || a[2] < 0.0F || a[3] < 0.0F) {
		    return GL_FALSE;
		}
	    }
	    break;
	    case OPCODE_LG2: {       /* log base 2 */
		GLfloat a[4], result[4];
		fetch_vector1(&inst->SrcReg[0], machine, a);
		result[0] = result[1] = result[2] = result[3] = LOG2(a[0]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_LIT: {
		const GLfloat epsilon = 1.0F / 256.0F;      /* from NV VP spec */
		GLfloat a[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		a[0] = MAX2(a[0], 0.0F);
		a[1] = MAX2(a[1], 0.0F);
		/* XXX ARB version clamps a[3], NV version doesn't */
		a[3] = CLAMP(a[3], -(128.0F - epsilon), (128.0F - epsilon));
		result[0] = 1.0F;
		result[1] = a[0];
		/* XXX we could probably just use pow() here */
		if (a[0] > 0.0F) {
		    if (a[1] == 0.0 && a[3] == 0.0)
			result[2] = 1.0;
		    else
			result[2] = EXPF(a[3] * LOGF(a[1]));
		} else {
		    result[2] = 0.0;
		}
		result[3] = 1.0F;
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("LIT (%g %g %g %g) : (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3]);
		}
	    }
	    break;
	    case OPCODE_LOG: {
		GLfloat t[4], q[4], abs_t0;
		fetch_vector1(&inst->SrcReg[0], machine, t);
		abs_t0 = FABSF(t[0]);
		if (abs_t0 != 0.0F) {
		    if (IS_INF_OR_NAN(abs_t0))
		    {
			SET_POS_INFINITY(q[0]);
			q[1] = 1.0F;
			SET_POS_INFINITY(q[2]);
		    } else {
			int exponent;
			GLfloat mantissa = FREXPF(t[0], &exponent);
			q[0] = (GLfloat)(exponent - 1);
			q[1] = (GLfloat)(2.0 * mantissa);  /* map [.5, 1) -> [1, 2) */
			q[2] = (GLfloat)(q[0] + LOG2(q[1]));
		    }
		} else {
		    SET_NEG_INFINITY(q[0]);
		    q[1] = 1.0F;
		    SET_NEG_INFINITY(q[2]);
		}
		q[3] = 1.0;
		store_vector4(inst, machine, q);
	    }
	    break;
	    case OPCODE_LRP: {
		GLfloat a[4], b[4], c[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		fetch_vector4(&inst->SrcReg[2], machine, c);
		result[0] = a[0] * b[0] + (1.0F - a[0]) * c[0];
		result[1] = a[1] * b[1] + (1.0F - a[1]) * c[1];
		result[2] = a[2] * b[2] + (1.0F - a[2]) * c[2];
		result[3] = a[3] * b[3] + (1.0F - a[3]) * c[3];
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("LRP (%g %g %g %g) = (%g %g %g %g), "
			   "(%g %g %g %g), (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3],
			   b[0], b[1], b[2], b[3], c[0], c[1], c[2], c[3]);
		}
	    }
	    break;
	    case OPCODE_MAD: {
		GLfloat a[4], b[4], c[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		fetch_vector4(&inst->SrcReg[2], machine, c);
		result[0] = a[0] * b[0] + c[0];
		result[1] = a[1] * b[1] + c[1];
		result[2] = a[2] * b[2] + c[2];
		result[3] = a[3] * b[3] + c[3];
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("MAD (%g %g %g %g) = (%g %g %g %g) * "
			   "(%g %g %g %g) + (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3],
			   b[0], b[1], b[2], b[3], c[0], c[1], c[2], c[3]);
		}
	    }
	    break;
	    case OPCODE_MAX: {
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = MAX2(a[0], b[0]);
		result[1] = MAX2(a[1], b[1]);
		result[2] = MAX2(a[2], b[2]);
		result[3] = MAX2(a[3], b[3]);
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("MAX (%g %g %g %g) = (%g %g %g %g), (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3]);
		}
	    }
	    break;
	    case OPCODE_MIN: {
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = MIN2(a[0], b[0]);
		result[1] = MIN2(a[1], b[1]);
		result[2] = MIN2(a[2], b[2]);
		result[3] = MIN2(a[3], b[3]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_MOV: {
		GLfloat result[4];
		fetch_vector4(&inst->SrcReg[0], machine, result);
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("MOV (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3]);
		}
	    }
	    break;
	    case OPCODE_MUL: {
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = a[0] * b[0];
		result[1] = a[1] * b[1];
		result[2] = a[2] * b[2];
		result[3] = a[3] * b[3];
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("MUL (%g %g %g %g) = (%g %g %g %g) * (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3]);
		}
	    }
	    break;
	    case OPCODE_NOISE1: {
		GLfloat a[4], result[4];
		fetch_vector1(&inst->SrcReg[0], machine, a);
		result[0] =
		    result[1] =
			result[2] = result[3] = _slang_library_noise1(a[0]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_NOISE2: {
		GLfloat a[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		result[0] =
		    result[1] =
			result[2] = result[3] = _slang_library_noise2(a[0], a[1]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_NOISE3: {
		GLfloat a[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		result[0] =
		    result[1] =
			result[2] =
			    result[3] = _slang_library_noise3(a[0], a[1], a[2]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_NOISE4: {
		GLfloat a[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		result[0] =
		    result[1] =
			result[2] =
			    result[3] = _slang_library_noise4(a[0], a[1], a[2], a[3]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_NOP:
		break;
	    case OPCODE_PK2H: {      /* pack two 16-bit floats in one 32-bit float */
		GLfloat a[4], result[4];
		GLhalfNV hx, hy;
		GLuint *rawResult = (GLuint *) result;
		GLuint twoHalves;
		fetch_vector4(&inst->SrcReg[0], machine, a);
		hx = _mesa_float_to_half(a[0]);
		hy = _mesa_float_to_half(a[1]);
		twoHalves = hx | (hy << 16);
		rawResult[0] = rawResult[1] = rawResult[2] = rawResult[3]
					      = twoHalves;
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_PK2US: {     /* pack two GLushorts into one 32-bit float */
		GLfloat a[4], result[4];
		GLuint usx, usy, *rawResult = (GLuint *) result;
		fetch_vector4(&inst->SrcReg[0], machine, a);
		a[0] = CLAMP(a[0], 0.0F, 1.0F);
		a[1] = CLAMP(a[1], 0.0F, 1.0F);
		usx = IROUND(a[0] * 65535.0F);
		usy = IROUND(a[1] * 65535.0F);
		rawResult[0] = rawResult[1] = rawResult[2] = rawResult[3]
					      = usx | (usy << 16);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_PK4B: {      /* pack four GLbytes into one 32-bit float */
		GLfloat a[4], result[4];
		GLuint ubx, uby, ubz, ubw, *rawResult = (GLuint *) result;
		fetch_vector4(&inst->SrcReg[0], machine, a);
		a[0] = CLAMP(a[0], -128.0F / 127.0F, 1.0F);
		a[1] = CLAMP(a[1], -128.0F / 127.0F, 1.0F);
		a[2] = CLAMP(a[2], -128.0F / 127.0F, 1.0F);
		a[3] = CLAMP(a[3], -128.0F / 127.0F, 1.0F);
		ubx = IROUND(127.0F * a[0] + 128.0F);
		uby = IROUND(127.0F * a[1] + 128.0F);
		ubz = IROUND(127.0F * a[2] + 128.0F);
		ubw = IROUND(127.0F * a[3] + 128.0F);
		rawResult[0] = rawResult[1] = rawResult[2] = rawResult[3]
					      = ubx | (uby << 8) | (ubz << 16) | (ubw << 24);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_PK4UB: {     /* pack four GLubytes into one 32-bit float */
		GLfloat a[4], result[4];
		GLuint ubx, uby, ubz, ubw, *rawResult = (GLuint *) result;
		fetch_vector4(&inst->SrcReg[0], machine, a);
		a[0] = CLAMP(a[0], 0.0F, 1.0F);
		a[1] = CLAMP(a[1], 0.0F, 1.0F);
		a[2] = CLAMP(a[2], 0.0F, 1.0F);
		a[3] = CLAMP(a[3], 0.0F, 1.0F);
		ubx = IROUND(255.0F * a[0]);
		uby = IROUND(255.0F * a[1]);
		ubz = IROUND(255.0F * a[2]);
		ubw = IROUND(255.0F * a[3]);
		rawResult[0] = rawResult[1] = rawResult[2] = rawResult[3]
					      = ubx | (uby << 8) | (ubz << 16) | (ubw << 24);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_POW: {
		GLfloat a[4], b[4], result[4];
		fetch_vector1(&inst->SrcReg[0], machine, a);
		fetch_vector1(&inst->SrcReg[1], machine, b);
		result[0] = result[1] = result[2] = result[3]
						    = (GLfloat) pow(a[0], b[0]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_RCP: {
		GLfloat a[4], result[4];
		fetch_vector1(&inst->SrcReg[0], machine, a);
		if (DEBUG_PROG) {
		    if (a[0] == 0)
			printf("RCP(0)\n");
		    else if (IS_INF_OR_NAN(a[0]))
			printf("RCP(inf)\n");
		}
		result[0] = result[1] = result[2] = result[3] = 1.0F / a[0];
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_RET:         /* return from subroutine (conditional) */
		if (eval_condition(machine, inst)) {
		    if (machine->StackDepth == 0) {
			return GL_TRUE;  /* Per GL_NV_vertex_program2 spec */
		    }
		    /* subtract one because of pc++ in the for loop */
		    pc = machine->CallStack[--machine->StackDepth] - 1;
		}
		break;
	    case OPCODE_RFL: {       /* reflection vector */
		GLfloat axis[4], dir[4], result[4], tmpX, tmpW;
		fetch_vector4(&inst->SrcReg[0], machine, axis);
		fetch_vector4(&inst->SrcReg[1], machine, dir);
		tmpW = DOT3(axis, axis);
		tmpX = (2.0F * DOT3(axis, dir)) / tmpW;
		result[0] = tmpX * axis[0] - dir[0];
		result[1] = tmpX * axis[1] - dir[1];
		result[2] = tmpX * axis[2] - dir[2];
		/* result[3] is never written! XXX enforce in parser! */
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_RSQ: {       /* 1 / sqrt() */
		GLfloat a[4], result[4];
		fetch_vector1(&inst->SrcReg[0], machine, a);
		a[0] = FABSF(a[0]);
		result[0] = result[1] = result[2] = result[3] = INV_SQRTF(a[0]);
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("RSQ %g = 1/sqrt(|%g|)\n", result[0], a[0]);
		}
	    }
	    break;
	    case OPCODE_SCS: {       /* sine and cos */
		GLfloat a[4], result[4];
		fetch_vector1(&inst->SrcReg[0], machine, a);
		result[0] = (GLfloat) cos(a[0]);
		result[1] = (GLfloat) sin(a[0]);
		result[2] = 0.0;    /* undefined! */
		result[3] = 0.0;    /* undefined! */
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_SEQ: {       /* set on equal */
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = (a[0] == b[0]) ? 1.0F : 0.0F;
		result[1] = (a[1] == b[1]) ? 1.0F : 0.0F;
		result[2] = (a[2] == b[2]) ? 1.0F : 0.0F;
		result[3] = (a[3] == b[3]) ? 1.0F : 0.0F;
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("SEQ (%g %g %g %g) = (%g %g %g %g) == (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3],
			   b[0], b[1], b[2], b[3]);
		}
	    }
	    break;
	    case OPCODE_SFL: {       /* set false, operands ignored */
		static const GLfloat result[4] = { 0.0F, 0.0F, 0.0F, 0.0F };
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_SGE: {       /* set on greater or equal */
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = (a[0] >= b[0]) ? 1.0F : 0.0F;
		result[1] = (a[1] >= b[1]) ? 1.0F : 0.0F;
		result[2] = (a[2] >= b[2]) ? 1.0F : 0.0F;
		result[3] = (a[3] >= b[3]) ? 1.0F : 0.0F;
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("SGE (%g %g %g %g) = (%g %g %g %g) >= (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3],
			   b[0], b[1], b[2], b[3]);
		}
	    }
	    break;
	    case OPCODE_SGT: {       /* set on greater */
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = (a[0] > b[0]) ? 1.0F : 0.0F;
		result[1] = (a[1] > b[1]) ? 1.0F : 0.0F;
		result[2] = (a[2] > b[2]) ? 1.0F : 0.0F;
		result[3] = (a[3] > b[3]) ? 1.0F : 0.0F;
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("SGT (%g %g %g %g) = (%g %g %g %g) > (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3],
			   b[0], b[1], b[2], b[3]);
		}
	    }
	    break;
	    case OPCODE_SIN: {
		GLfloat a[4], result[4];
		fetch_vector1(&inst->SrcReg[0], machine, a);
		result[0] = result[1] = result[2] = result[3]
						    = (GLfloat) sin(a[0]);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_SLE: {       /* set on less or equal */
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = (a[0] <= b[0]) ? 1.0F : 0.0F;
		result[1] = (a[1] <= b[1]) ? 1.0F : 0.0F;
		result[2] = (a[2] <= b[2]) ? 1.0F : 0.0F;
		result[3] = (a[3] <= b[3]) ? 1.0F : 0.0F;
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("SLE (%g %g %g %g) = (%g %g %g %g) <= (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3],
			   b[0], b[1], b[2], b[3]);
		}
	    }
	    break;
	    case OPCODE_SLT: {       /* set on less */
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = (a[0] < b[0]) ? 1.0F : 0.0F;
		result[1] = (a[1] < b[1]) ? 1.0F : 0.0F;
		result[2] = (a[2] < b[2]) ? 1.0F : 0.0F;
		result[3] = (a[3] < b[3]) ? 1.0F : 0.0F;
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("SLT (%g %g %g %g) = (%g %g %g %g) < (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3],
			   b[0], b[1], b[2], b[3]);
		}
	    }
	    break;
	    case OPCODE_SNE: {       /* set on not equal */
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = (a[0] != b[0]) ? 1.0F : 0.0F;
		result[1] = (a[1] != b[1]) ? 1.0F : 0.0F;
		result[2] = (a[2] != b[2]) ? 1.0F : 0.0F;
		result[3] = (a[3] != b[3]) ? 1.0F : 0.0F;
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("SNE (%g %g %g %g) = (%g %g %g %g) != (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3],
			   b[0], b[1], b[2], b[3]);
		}
	    }
	    break;
	    case OPCODE_STR: {       /* set true, operands ignored */
		static const GLfloat result[4] = { 1.0F, 1.0F, 1.0F, 1.0F };
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_SUB: {
		GLfloat a[4], b[4], result[4];
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = a[0] - b[0];
		result[1] = a[1] - b[1];
		result[2] = a[2] - b[2];
		result[3] = a[3] - b[3];
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("SUB (%g %g %g %g) = (%g %g %g %g) - (%g %g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3]);
		}
	    }
	    break;
	    case OPCODE_SWZ: {       /* extended swizzle */
		const struct prog_src_register *source = &inst->SrcReg[0];
		const GLfloat *src = get_register_pointer(source, machine);
		GLfloat result[4];
		GLuint i;
		for (i = 0; i < 4; i++) {
		    const GLuint swz = GET_SWZ(source->Swizzle, i);
		    if (swz == SWIZZLE_ZERO)
			result[i] = 0.0;
		    else if (swz == SWIZZLE_ONE)
			result[i] = 1.0;
		    else {
			ASSERT(swz >= 0);
			ASSERT(swz <= 3);
			result[i] = src[swz];
		    }
		    if (source->NegateBase & (1 << i))
			result[i] = -result[i];
		}
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_TEX:         /* Both ARB and NV frag prog */
		/* Simple texel lookup */
	    {
		GLfloat texcoord[4], color[4];
		fetch_vector4(&inst->SrcReg[0], machine, texcoord);

		fetch_texel(ctx, machine, inst, texcoord, 0.0, color);

		if (DEBUG_PROG) {
		    printf("TEX (%g, %g, %g, %g) = texture[%d][%g, %g, %g, %g]\n",
			   color[0], color[1], color[2], color[3],
			   inst->TexSrcUnit,
			   texcoord[0], texcoord[1], texcoord[2], texcoord[3]);
		}
		store_vector4(inst, machine, color);
	    }
	    break;
	    case OPCODE_TXB:         /* GL_ARB_fragment_program only */
		/* Texel lookup with LOD bias */
	    {
		const struct gl_texture_unit *texUnit
			= &ctx->Texture.Unit[inst->TexSrcUnit];
		GLfloat texcoord[4], color[4], lodBias;

		fetch_vector4(&inst->SrcReg[0], machine, texcoord);

		/* texcoord[3] is the bias to add to lambda */
		lodBias = texUnit->LodBias + texcoord[3];
		if (texUnit->_Current) {
		    lodBias += texUnit->_Current->LodBias;
		}

		fetch_texel(ctx, machine, inst, texcoord, lodBias, color);

		store_vector4(inst, machine, color);
	    }
	    break;
	    case OPCODE_TXD:         /* GL_NV_fragment_program only */
		/* Texture lookup w/ partial derivatives for LOD */
	    {
		GLfloat texcoord[4], dtdx[4], dtdy[4], color[4];
		fetch_vector4(&inst->SrcReg[0], machine, texcoord);
		fetch_vector4(&inst->SrcReg[1], machine, dtdx);
		fetch_vector4(&inst->SrcReg[2], machine, dtdy);
		machine->FetchTexelDeriv(ctx, texcoord, dtdx, dtdy,
					 0.0, /* lodBias */
					 inst->TexSrcUnit, color);
		store_vector4(inst, machine, color);
	    }
	    break;
	    case OPCODE_TXP:         /* GL_ARB_fragment_program only */
		/* Texture lookup w/ projective divide */
	    {
		GLfloat texcoord[4], color[4];

		fetch_vector4(&inst->SrcReg[0], machine, texcoord);
		/* Not so sure about this test - if texcoord[3] is
		 * zero, we'd probably be fine except for an ASSERT in
		 * IROUND_POS() which gets triggered by the inf values created.
		 */
		if (texcoord[3] != 0.0) {
		    texcoord[0] /= texcoord[3];
		    texcoord[1] /= texcoord[3];
		    texcoord[2] /= texcoord[3];
		}

		fetch_texel(ctx, machine, inst, texcoord, 0.0, color);

		store_vector4(inst, machine, color);
	    }
	    break;
	    case OPCODE_TXP_NV:      /* GL_NV_fragment_program only */
		/* Texture lookup w/ projective divide, as above, but do not
		 * do the divide by w if sampling from a cube map.
		 */
	    {
		GLfloat texcoord[4], color[4];

		fetch_vector4(&inst->SrcReg[0], machine, texcoord);
		if (inst->TexSrcTarget != TEXTURE_CUBE_INDEX &&
		    texcoord[3] != 0.0) {
		    texcoord[0] /= texcoord[3];
		    texcoord[1] /= texcoord[3];
		    texcoord[2] /= texcoord[3];
		}

		fetch_texel(ctx, machine, inst, texcoord, 0.0, color);

		store_vector4(inst, machine, color);
	    }
	    break;
	    case OPCODE_UP2H: {      /* unpack two 16-bit floats */
		GLfloat a[4] = {0.0}, result[4] = {0.0};
		const GLuint *rawBits = (const GLuint *) a;
		GLhalfNV hx, hy;
		fetch_vector1(&inst->SrcReg[0], machine, a);
		hx = rawBits[0] & 0xffff;
		hy = rawBits[0] >> 16;
		result[0] = result[2] = _mesa_half_to_float(hx);
		result[1] = result[3] = _mesa_half_to_float(hy);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_UP2US: {     /* unpack two GLushorts */
		GLfloat a[4] = {0.0}, result[4] = {0.0};
		const GLuint *rawBits = (const GLuint *) a;
		GLushort usx, usy;
		fetch_vector1(&inst->SrcReg[0], machine, a);
		usx = rawBits[0] & 0xffff;
		usy = rawBits[0] >> 16;
		result[0] = result[2] = usx * (1.0f / 65535.0f);
		result[1] = result[3] = usy * (1.0f / 65535.0f);
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_UP4B: {      /* unpack four GLbytes */
		GLfloat a[4] = {0.0}, result[4] = {0.0};
		const GLuint *rawBits = (const GLuint *) a;
		fetch_vector1(&inst->SrcReg[0], machine, a);
		result[0] = (((rawBits[0] >> 0) & 0xff) - 128) / 127.0F;
		result[1] = (((rawBits[0] >> 8) & 0xff) - 128) / 127.0F;
		result[2] = (((rawBits[0] >> 16) & 0xff) - 128) / 127.0F;
		result[3] = (((rawBits[0] >> 24) & 0xff) - 128) / 127.0F;
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_UP4UB: {     /* unpack four GLubytes */
		GLfloat a[4] = {0.0}, result[4] = {0.0};
		const GLuint *rawBits = (const GLuint *) a;
		fetch_vector1(&inst->SrcReg[0], machine, a);
		result[0] = ((rawBits[0] >> 0) & 0xff) / 255.0F;
		result[1] = ((rawBits[0] >> 8) & 0xff) / 255.0F;
		result[2] = ((rawBits[0] >> 16) & 0xff) / 255.0F;
		result[3] = ((rawBits[0] >> 24) & 0xff) / 255.0F;
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_XPD: {       /* cross product */
		GLfloat a[4] = {0.0}, b[4] = {0.0}, result[4] = {0.0};
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		result[0] = a[1] * b[2] - a[2] * b[1];
		result[1] = a[2] * b[0] - a[0] * b[2];
		result[2] = a[0] * b[1] - a[1] * b[0];
		result[3] = 1.0;
		store_vector4(inst, machine, result);
		if (DEBUG_PROG) {
		    printf("XPD (%g %g %g %g) = (%g %g %g) X (%g %g %g)\n",
			   result[0], result[1], result[2], result[3],
			   a[0], a[1], a[2], b[0], b[1], b[2]);
		}
	    }
	    break;
	    case OPCODE_X2D: {       /* 2-D matrix transform */
		GLfloat a[4] = {0.0}, b[4] = {0.0}, c[4] = {0.0}, result[4] = {0.0};
		fetch_vector4(&inst->SrcReg[0], machine, a);
		fetch_vector4(&inst->SrcReg[1], machine, b);
		fetch_vector4(&inst->SrcReg[2], machine, c);
		result[0] = a[0] + b[0] * c[0] + b[1] * c[1];
		result[1] = a[1] + b[0] * c[2] + b[1] * c[3];
		result[2] = a[2] + b[0] * c[0] + b[1] * c[1];
		result[3] = a[3] + b[0] * c[2] + b[1] * c[3];
		store_vector4(inst, machine, result);
	    }
	    break;
	    case OPCODE_PRINT: {
		 GLfloat a[4] = {0.0};
		 fetch_vector4(&inst->SrcReg[0], machine, a);
		 _mesa_printf("%s%g, %g, %g, %g\n", (const char *) inst->Data,
				 a[0], a[1], a[2], a[3]);
	    }
	    break;
	    case OPCODE_END:
		return GL_TRUE;
	    default:
		_mesa_problem(ctx, "Bad opcode %d in _mesa_execute_program",
			      inst->Opcode);
		assert(0);
		return GL_TRUE;        /* return value doesn't matter */

	}

	numExec++;
	if (numExec > maxExec) {
	    _mesa_problem(ctx, "Infinite loop detected in fragment program");
	    return GL_TRUE;
	}

    } /* for pc */

    return GL_TRUE;
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
