/**
 * \file varray.h
 * Vertex arrays.
 *
 * \if subset
 * (No-op)
 *
 * \endif
 */

/*
 * Mesa 3-D graphics library
 * Version:  4.1
 *
 * Copyright (C) 1999-2002  Brian Paul   All Rights Reserved.
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


#ifndef VARRAY_H
#define VARRAY_H


#include "mtypes.h"

#if _HAVE_FULL_GL

extern void GLAPIENTRY
_mesa_VertexPointer(ctx, GLcontext *ctx, GLint size, GLenum type, GLsizei stride, const GLvoid *ptr);

extern void GLAPIENTRY
_mesa_UnlockArraysEXT(ctx, GLcontext *ctx);

extern void GLAPIENTRY
_mesa_LockArraysEXT(ctx, GLcontext *ctx, GLint first, GLsizei count);


extern void GLAPIENTRY
_mesa_NormalPointer(ctx, GLcontext *ctx, GLenum type, GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_ColorPointer(ctx, GLcontext *ctx, GLint size, GLenum type, GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_IndexPointer(ctx, GLcontext *ctx, GLenum type, GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_TexCoordPointer(ctx, GLcontext *ctx, GLint size, GLenum type, GLsizei stride,
		      const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_EdgeFlagPointer(ctx, GLcontext *ctx, GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_VertexPointerEXT(GLint size, GLenum type, GLsizei stride,
		       GLsizei count, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_NormalPointerEXT(GLenum type, GLsizei stride, GLsizei count,
		       const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_ColorPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count,
		      const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_IndexPointerEXT(GLenum type, GLsizei stride, GLsizei count,
		      const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_TexCoordPointerEXT(GLint size, GLenum type, GLsizei stride,
			 GLsizei count, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_EdgeFlagPointerEXT(GLsizei stride, GLsizei count, const GLboolean *ptr);


extern void GLAPIENTRY
_mesa_FogCoordPointerEXT(ctx, GLcontext *ctx, GLenum type, GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_SecondaryColorPointerEXT(ctx, GLcontext *ctx, GLint size, GLenum type,
			       GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_VertexAttribPointerNV(ctx, GLcontext *ctx, GLuint index, GLint size, GLenum type,
			    GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_VertexAttribPointerARB(ctx, GLcontext *ctx, GLuint index, GLint size, GLenum type,
			     GLboolean normalized,
			     GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_InterleavedArrays(ctx, GLcontext *ctx, GLenum format, GLsizei stride, const GLvoid *pointer);


extern void GLAPIENTRY
_mesa_MultiDrawArraysEXT(ctx, GLcontext *ctx, GLenum mode, GLint *first,
			 GLsizei *count, GLsizei primcount);

extern void GLAPIENTRY
_mesa_MultiDrawElementsEXT(ctx, GLcontext *ctx, GLenum mode, const GLsizei *count, GLenum type,
			   const GLvoid **indices, GLsizei primcount);


extern void GLAPIENTRY
_mesa_MultiModeDrawArraysIBM(ctx, GLcontext *ctx, const GLenum * mode, const GLint * first,
			     const GLsizei * count,
			     GLsizei primcount, GLint modestride);


extern void GLAPIENTRY
_mesa_MultiModeDrawElementsIBM(ctx, GLcontext *ctx, const GLenum * mode, const GLsizei * count,
			       GLenum type, const GLvoid * const * indices,
			       GLsizei primcount, GLint modestride);


extern void
_mesa_init_varray(ctx, GLcontext *ctx);

#else

/** No-op */
#define _mesa_init_varray(ctx, c)  ((void)0)

#endif

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
