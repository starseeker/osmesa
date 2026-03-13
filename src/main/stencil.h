/**
 * \file stencil.h
 * Stencil operations.
 */

/*
 * Mesa 3-D graphics library
 * Version:  7.1
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


#ifndef STENCIL_H
#define STENCIL_H


#include "mtypes.h"


extern void GLAPIENTRY
_mesa_ClearStencil(ctx, GLcontext *ctx, GLint s);


extern void GLAPIENTRY
_mesa_StencilFunc(ctx, GLcontext *ctx, GLenum func, GLint ref, GLuint mask);


extern void GLAPIENTRY
_mesa_StencilMask(ctx, GLcontext *ctx, GLuint mask);


extern void GLAPIENTRY
_mesa_StencilOp(ctx, GLcontext *ctx, GLenum fail, GLenum zfail, GLenum zpass);


extern void GLAPIENTRY
_mesa_ActiveStencilFaceEXT(ctx, GLcontext *ctx, GLenum face);


extern void GLAPIENTRY
_mesa_StencilOpSeparate(ctx, GLcontext *ctx, GLenum face, GLenum sfail, GLenum zfail, GLenum zpass);


extern void GLAPIENTRY
_mesa_StencilFuncSeparate(ctx, GLcontext *ctx, GLenum face, GLenum func, GLint ref, GLuint mask);


extern void GLAPIENTRY
_mesa_StencilFuncSeparateATI(ctx, GLcontext *ctx, GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask);

extern void GLAPIENTRY
_mesa_StencilMaskSeparate(ctx, GLcontext *ctx, GLenum face, GLuint mask);


extern void
_mesa_update_stencil(ctx, GLcontext *ctx);


extern void
_mesa_init_stencil(ctx, GLcontext *ctx);

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
