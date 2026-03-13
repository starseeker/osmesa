/*
 * Mesa 3-D graphics library
 * Version:  6.5.2
 *
 * Copyright (C) 1999-2006  Brian Paul   All Rights Reserved.
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


#ifndef ARBPROGRAM_H
#define ARBPROGRAM_H


extern void GLAPIENTRY
_mesa_EnableVertexAttribArrayARB(ctx, GLcontext *ctx, GLuint index);


extern void GLAPIENTRY
_mesa_DisableVertexAttribArrayARB(ctx, GLcontext *ctx, GLuint index);


extern void GLAPIENTRY
_mesa_GetVertexAttribdvARB(ctx, GLcontext *ctx, GLuint index, GLenum pname, GLdouble *params);


extern void GLAPIENTRY
_mesa_GetVertexAttribfvARB(ctx, GLcontext *ctx, GLuint index, GLenum pname, GLfloat *params);


extern void GLAPIENTRY
_mesa_GetVertexAttribivARB(ctx, GLcontext *ctx, GLuint index, GLenum pname, GLint *params);


extern void GLAPIENTRY
_mesa_GetVertexAttribPointervARB(ctx, GLcontext *ctx, GLuint index, GLenum pname, GLvoid **pointer);


extern GLboolean GLAPIENTRY
_mesa_IsProgramARB(ctx, GLcontext *ctx, GLuint id);


extern void GLAPIENTRY
_mesa_ProgramStringARB(ctx, GLcontext *ctx, GLenum target, GLenum format, GLsizei len,
		       const GLvoid *string);


extern void GLAPIENTRY
_mesa_ProgramEnvParameter4dARB(GLenum target, GLuint index,
			       GLdouble x, GLdouble y, GLdouble z, GLdouble w);


extern void GLAPIENTRY
_mesa_ProgramEnvParameter4dvARB(GLenum target, GLuint index,
				const GLdouble *params);


extern void GLAPIENTRY
_mesa_ProgramEnvParameter4fARB(ctx, GLcontext *ctx, GLenum target, GLuint index,
			       GLfloat x, GLfloat y, GLfloat z, GLfloat w);


extern void GLAPIENTRY
_mesa_ProgramEnvParameter4fvARB(GLenum target, GLuint index,
				const GLfloat *params);


extern void GLAPIENTRY
_mesa_ProgramEnvParameters4fvEXT(ctx, GLcontext *ctx, GLenum target, GLuint index, GLsizei count,
				 const GLfloat *params);


extern void GLAPIENTRY
_mesa_ProgramLocalParameter4dARB(GLenum target, GLuint index,
				 GLdouble x, GLdouble y,
				 GLdouble z, GLdouble w);


extern void GLAPIENTRY
_mesa_ProgramLocalParameter4dvARB(GLenum target, GLuint index,
				  const GLdouble *params);


extern void GLAPIENTRY
_mesa_ProgramLocalParameter4fARB(ctx, GLcontext *ctx, GLenum target, GLuint index,
				 GLfloat x, GLfloat y, GLfloat z, GLfloat w);


extern void GLAPIENTRY
_mesa_ProgramLocalParameter4fvARB(GLenum target, GLuint index,
				  const GLfloat *params);


extern void GLAPIENTRY
_mesa_ProgramLocalParameters4fvEXT(ctx, GLcontext *ctx, GLenum target, GLuint index, GLsizei count,
				   const GLfloat *params);


extern void GLAPIENTRY
_mesa_GetProgramEnvParameterdvARB(ctx, GLcontext *ctx, GLenum target, GLuint index,
				  GLdouble *params);


extern void GLAPIENTRY
_mesa_GetProgramEnvParameterfvARB(ctx, GLcontext *ctx, GLenum target, GLuint index,
				  GLfloat *params);


extern void GLAPIENTRY
_mesa_GetProgramLocalParameterdvARB(ctx, GLcontext *ctx, GLenum target, GLuint index,
				    GLdouble *params);


extern void GLAPIENTRY
_mesa_GetProgramLocalParameterfvARB(ctx, GLcontext *ctx, GLenum target, GLuint index,
				    GLfloat *params);


extern void GLAPIENTRY
_mesa_GetProgramivARB(ctx, GLcontext *ctx, GLenum target, GLenum pname, GLint *params);


extern void GLAPIENTRY
_mesa_GetProgramStringARB(ctx, GLcontext *ctx, GLenum target, GLenum pname, GLvoid *string);


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
