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

#ifndef PROG_EXECUTE_H
#define PROG_EXECUTE_H


typedef void (*FetchTexelLodFunc)(GLcontext *ctx, const GLfloat texcoord[4],
				  GLfloat lambda, GLuint unit, GLfloat color[4]);

typedef void (*FetchTexelDerivFunc)(GLcontext *ctx, const GLfloat texcoord[4],
				    const GLfloat texdx[4],
				    const GLfloat texdy[4],
				    GLfloat lodBias,
				    GLuint unit, GLfloat color[4]);


/** The larger of VERT_RESULT_MAX, FRAG_RESULT_MAX */
#define MAX_PROGRAM_OUTPUTS VERT_RESULT_MAX


/**
 * Virtual machine state used during execution of vertex/fragment programs.
 */
struct gl_program_machine {
    const struct gl_program *CurProgram;

    /** Fragment Input attributes */
    GLfloat(*Attribs)[MAX_WIDTH][4];
    GLfloat(*DerivX)[4];
    GLfloat(*DerivY)[4];
    GLuint NumDeriv; /**< Max index into DerivX/Y arrays */
    GLuint CurElement; /**< Index into Attribs arrays */

    /** Vertex Input attribs */
    GLfloat VertAttribs[VERT_ATTRIB_MAX][4];

    GLfloat Temporaries[MAX_PROGRAM_TEMPS][4];
    GLfloat Outputs[MAX_PROGRAM_OUTPUTS][4];
    GLfloat(*EnvParams)[4];  /**< Vertex or Fragment env parameters */
    GLuint CondCodes[4];  /**< COND_* value for x/y/z/w */
    GLint AddressReg[MAX_PROGRAM_ADDRESS_REGS][4];

    GLuint CallStack[MAX_PROGRAM_CALL_DEPTH]; /**< For CAL/RET instructions */
    GLuint StackDepth; /**< Index/ptr to top of CallStack[] */

    /** Texture fetch functions */
    FetchTexelLodFunc FetchTexelLod;
    FetchTexelDerivFunc FetchTexelDeriv;
};

extern GLboolean
_mesa_execute_program(GLcontext *ctx,
		      const struct gl_program *program,
		      struct gl_program_machine *machine);

/**
 * Pre-resolved straight-line program used by the software vertex pipeline.
 * The object is intentionally opaque: it is valid only while the machine
 * passed to _mesa_create_fast_program remains at the same address.
 */
struct gl_program_fast;

extern struct gl_program_fast *
_mesa_create_fast_program(GLcontext *ctx,
			  const struct gl_program *program,
			  struct gl_program_machine *machine);

extern void
_mesa_destroy_fast_program(struct gl_program_fast *program);

extern GLboolean
_mesa_execute_fast_program(const struct gl_program_fast *program);

/**
 * Execute the largest four-vertex prefix of a straight-line fast program.
 *
 * Input and output strides are byte strides.  The returned count is the
 * number of vertices written; callers retain the scalar path for any tail or
 * for programs whose control flow cannot be executed in lockstep.
 */
extern GLuint
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
	const GLuint *outputStrides);


#endif /* PROG_EXECUTE_H */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
