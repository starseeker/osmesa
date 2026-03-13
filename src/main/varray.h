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
_mesa_VertexPointer(GLcontext *ctx, GLint size, GLenum type, GLsizei stride, const GLvoid *ptr);

extern void GLAPIENTRY
_mesa_UnlockArraysEXT(GLcontext *ctx);

extern void GLAPIENTRY
_mesa_LockArraysEXT(GLcontext *ctx, GLint first, GLsizei count);


extern void GLAPIENTRY
_mesa_NormalPointer(GLcontext *ctx, GLenum type, GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_ColorPointer(GLcontext *ctx, GLint size, GLenum type, GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_IndexPointer(GLcontext *ctx, GLenum type, GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_TexCoordPointer(GLcontext *ctx, GLint size, GLenum type, GLsizei stride,
		      const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_EdgeFlagPointer(GLcontext *ctx, GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_VertexPointerEXT(GLcontext *ctx, GLint size, GLenum type, GLsizei stride,
		       GLsizei count, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_NormalPointerEXT(GLcontext *ctx, GLenum type, GLsizei stride, GLsizei count,
		       const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_ColorPointerEXT(GLcontext *ctx, GLint size, GLenum type, GLsizei stride, GLsizei count,
		      const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_IndexPointerEXT(GLcontext *ctx, GLenum type, GLsizei stride, GLsizei count,
		      const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_TexCoordPointerEXT(GLcontext *ctx, GLint size, GLenum type, GLsizei stride,
			 GLsizei count, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_EdgeFlagPointerEXT(GLcontext *ctx, GLsizei stride, GLsizei count, const GLboolean *ptr);


extern void GLAPIENTRY
_mesa_FogCoordPointerEXT(GLcontext *ctx, GLenum type, GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_SecondaryColorPointerEXT(GLcontext *ctx, GLint size, GLenum type,
			       GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_VertexAttribPointerNV(GLcontext *ctx, GLuint index, GLint size, GLenum type,
			    GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_VertexAttribPointerARB(GLcontext *ctx, GLuint index, GLint size, GLenum type,
			     GLboolean normalized,
			     GLsizei stride, const GLvoid *ptr);


extern void GLAPIENTRY
_mesa_InterleavedArrays(GLcontext *ctx, GLenum format, GLsizei stride, const GLvoid *pointer);


extern void GLAPIENTRY
_mesa_MultiDrawArraysEXT(GLcontext *ctx, GLenum mode, GLint *first,
			 GLsizei *count, GLsizei primcount);

extern void GLAPIENTRY
_mesa_MultiDrawElementsEXT(GLcontext *ctx, GLenum mode, const GLsizei *count, GLenum type,
			   const GLvoid **indices, GLsizei primcount);


extern void GLAPIENTRY
_mesa_MultiModeDrawArraysIBM(GLcontext *ctx, const GLenum * mode, const GLint * first,
			     const GLsizei * count,
			     GLsizei primcount, GLint modestride);


extern void GLAPIENTRY
_mesa_MultiModeDrawElementsIBM(GLcontext *ctx, const GLenum * mode, const GLsizei * count,
			       GLenum type, const GLvoid * const * indices,
			       GLsizei primcount, GLint modestride);


extern void
_mesa_init_varray(GLcontext *ctx);

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
