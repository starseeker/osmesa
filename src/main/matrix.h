/**
 * \file matrix.h
 * Matrix operations.
 */

/*
 * Mesa 3-D graphics library
 * Version:  3.5
 *
 * Copyright (C) 1999-2001  Brian Paul   All Rights Reserved.
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


#ifndef MATRIX_H
#define MATRIX_H


#include "mtypes.h"


extern void GLAPIENTRY
_mesa_Frustum(ctx, GLcontext *ctx, GLdouble left, GLdouble right,
	      GLdouble bottom, GLdouble top,
	      GLdouble nearval, GLdouble farval);

extern void GLAPIENTRY
_mesa_Ortho(ctx, GLcontext *ctx, GLdouble left, GLdouble right,
	    GLdouble bottom, GLdouble top,
	    GLdouble nearval, GLdouble farval);

extern void GLAPIENTRY
_mesa_PushMatrix(ctx, GLcontext *ctx);

extern void GLAPIENTRY
_mesa_PopMatrix(ctx, GLcontext *ctx);

extern void GLAPIENTRY
_mesa_LoadIdentity(ctx, GLcontext *ctx);

extern void GLAPIENTRY
_mesa_LoadMatrixf(ctx, GLcontext *ctx, const GLfloat *m);

extern void GLAPIENTRY
_mesa_LoadMatrixd(const GLdouble *m);

extern void GLAPIENTRY
_mesa_MatrixMode(ctx, GLcontext *ctx, GLenum mode);

extern void GLAPIENTRY
_mesa_MultMatrixf(ctx, GLcontext *ctx, const GLfloat *m);

extern void GLAPIENTRY
_mesa_MultMatrixd(const GLdouble *m);

extern void GLAPIENTRY
_mesa_Rotatef(ctx, GLcontext *ctx, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

extern void GLAPIENTRY
_mesa_Rotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);

extern void GLAPIENTRY
_mesa_Scalef(ctx, GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z);

extern void GLAPIENTRY
_mesa_Scaled(GLdouble x, GLdouble y, GLdouble z);

extern void GLAPIENTRY
_mesa_Translatef(ctx, GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z);

extern void GLAPIENTRY
_mesa_Translated(GLdouble x, GLdouble y, GLdouble z);

extern void GLAPIENTRY
_mesa_LoadTransposeMatrixfARB(const GLfloat *m);

extern void GLAPIENTRY
_mesa_LoadTransposeMatrixdARB(const GLdouble *m);

extern void GLAPIENTRY
_mesa_MultTransposeMatrixfARB(const GLfloat *m);

extern void GLAPIENTRY
_mesa_MultTransposeMatrixdARB(const GLdouble *m);

extern void GLAPIENTRY
_mesa_Viewport(ctx, GLcontext *ctx, GLint x, GLint y, GLsizei width, GLsizei height);

extern void
_mesa_set_viewport(ctx, GLcontext *ctx, GLint x, GLint y, GLsizei width, GLsizei height);

extern void GLAPIENTRY
_mesa_DepthRange(ctx, GLcontext *ctx, GLclampd nearval, GLclampd farval);


extern void
_mesa_init_matrix(ctx, GLcontext * ctx);

extern void
_mesa_init_transform(ctx, GLcontext *ctx);

extern void
_mesa_init_viewport(ctx, GLcontext *ctx);

extern void
_mesa_free_matrix_data(ctx, GLcontext *ctx);

extern void
_mesa_free_viewport_data(ctx, GLcontext *ctx);

extern void
_mesa_update_modelview_project(ctx, GLcontext *ctx, GLuint newstate);


#endif

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
