/**
 * \file texstate.h
 * Texture state management.
 */

/*
 * Mesa 3-D graphics library
 * Version:  6.5
 *
 * Copyright (C) 1999-2005  Brian Paul   All Rights Reserved.
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


#ifndef TEXSTATE_H
#define TEXSTATE_H


#include "mtypes.h"


extern void
_mesa_copy_texture_state(const GLcontext *src, GLcontext *dst);

extern void
_mesa_print_texunit_state(GLcontext *ctx, GLuint unit);


/**
 * \name Called from API
 */
/*@{*/

extern void GLAPIENTRY
_mesa_GetTexEnvfv(GLcontext *ctx, GLenum target, GLenum pname, GLfloat *params);

extern void GLAPIENTRY
_mesa_GetTexEnviv(GLcontext *ctx, GLenum target, GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetTexGendv(GLcontext *ctx, GLenum coord, GLenum pname, GLdouble *params);

extern void GLAPIENTRY
_mesa_GetTexGenfv(GLcontext *ctx, GLenum coord, GLenum pname, GLfloat *params);

extern void GLAPIENTRY
_mesa_GetTexGeniv(GLcontext *ctx, GLenum coord, GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetTexLevelParameterfv(GLcontext *ctx, GLenum target, GLint level,
			     GLenum pname, GLfloat *params);

extern void GLAPIENTRY
_mesa_GetTexLevelParameteriv(GLcontext *ctx, GLenum target, GLint level,
			     GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetTexParameterfv(GLcontext *ctx, GLenum target, GLenum pname, GLfloat *params);

extern void GLAPIENTRY
_mesa_GetTexParameteriv(GLcontext *ctx, GLenum target, GLenum pname, GLint *params);


extern void GLAPIENTRY
_mesa_TexEnvf(GLcontext *ctx, GLenum target, GLenum pname, GLfloat param);

extern void GLAPIENTRY
_mesa_TexEnvfv(GLcontext *ctx, GLenum target, GLenum pname, const GLfloat *param);

extern void GLAPIENTRY
_mesa_TexEnvi(GLcontext *ctx, GLenum target, GLenum pname, GLint param);

extern void GLAPIENTRY
_mesa_TexEnviv(GLcontext *ctx, GLenum target, GLenum pname, const GLint *param);


extern void GLAPIENTRY
_mesa_TexParameterfv(GLcontext *ctx, GLenum target, GLenum pname, const GLfloat *params);

extern void GLAPIENTRY
_mesa_TexParameterf(GLcontext *ctx, GLenum target, GLenum pname, GLfloat param);


extern void GLAPIENTRY
_mesa_TexParameteri(GLcontext *ctx, GLenum target, GLenum pname, GLint param);

extern void GLAPIENTRY
_mesa_TexParameteriv(GLcontext *ctx, GLenum target, GLenum pname, const GLint *params);


extern void GLAPIENTRY
_mesa_TexGend(GLcontext *ctx, GLenum coord, GLenum pname, GLdouble param);

extern void GLAPIENTRY
_mesa_TexGendv(GLcontext *ctx, GLenum coord, GLenum pname, const GLdouble *params);

extern void GLAPIENTRY
_mesa_TexGenf(GLcontext *ctx, GLenum coord, GLenum pname, GLfloat param);

extern void GLAPIENTRY
_mesa_TexGenfv(GLcontext *ctx, GLenum coord, GLenum pname, const GLfloat *params);

extern void GLAPIENTRY
_mesa_TexGeni(GLcontext *ctx, GLenum coord, GLenum pname, GLint param);

extern void GLAPIENTRY
_mesa_TexGeniv(GLcontext *ctx, GLenum coord, GLenum pname, const GLint *params);


/*
 * GL_ARB_multitexture
 */
extern void GLAPIENTRY
_mesa_ActiveTextureARB(GLcontext *ctx, GLenum texture);

extern void GLAPIENTRY
_mesa_ClientActiveTextureARB(GLcontext *ctx, GLenum texture);


/**
 * \name Initialization, state maintenance
 */
/*@{*/

extern void
_mesa_update_texture(GLcontext *ctx, GLuint new_state);

extern GLboolean
_mesa_init_texture(GLcontext *ctx);

extern void
_mesa_free_texture_data(GLcontext *ctx);

/*@}*/

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
