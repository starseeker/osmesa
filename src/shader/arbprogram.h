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
_mesa_EnableVertexAttribArrayARB(GLcontext *ctx, GLuint index);


extern void GLAPIENTRY
_mesa_DisableVertexAttribArrayARB(GLcontext *ctx, GLuint index);


extern void GLAPIENTRY
_mesa_GetVertexAttribdvARB(GLcontext *ctx, GLuint index, GLenum pname, GLdouble *params);


extern void GLAPIENTRY
_mesa_GetVertexAttribfvARB(GLcontext *ctx, GLuint index, GLenum pname, GLfloat *params);


extern void GLAPIENTRY
_mesa_GetVertexAttribivARB(GLcontext *ctx, GLuint index, GLenum pname, GLint *params);


extern void GLAPIENTRY
_mesa_GetVertexAttribPointervARB(GLcontext *ctx, GLuint index, GLenum pname, GLvoid **pointer);


extern GLboolean GLAPIENTRY
_mesa_IsProgramARB(GLcontext *ctx, GLuint id);


extern void GLAPIENTRY
_mesa_ProgramStringARB(GLcontext *ctx, GLenum target, GLenum format, GLsizei len,
		       const GLvoid *string);


extern void GLAPIENTRY
_mesa_ProgramEnvParameter4dARB(GLcontext *ctx, GLenum target, GLuint index,
			       GLdouble x, GLdouble y, GLdouble z, GLdouble w);


extern void GLAPIENTRY
_mesa_ProgramEnvParameter4dvARB(GLcontext *ctx, GLenum target, GLuint index,
				const GLdouble *params);


extern void GLAPIENTRY
_mesa_ProgramEnvParameter4fARB(GLcontext *ctx, GLenum target, GLuint index,
			       GLfloat x, GLfloat y, GLfloat z, GLfloat w);


extern void GLAPIENTRY
_mesa_ProgramEnvParameter4fvARB(GLcontext *ctx, GLenum target, GLuint index,
				const GLfloat *params);


extern void GLAPIENTRY
_mesa_ProgramEnvParameters4fvEXT(GLcontext *ctx, GLenum target, GLuint index, GLsizei count,
				 const GLfloat *params);


extern void GLAPIENTRY
_mesa_ProgramLocalParameter4dARB(GLcontext *ctx, GLenum target, GLuint index,
				 GLdouble x, GLdouble y,
				 GLdouble z, GLdouble w);


extern void GLAPIENTRY
_mesa_ProgramLocalParameter4dvARB(GLcontext *ctx, GLenum target, GLuint index,
				  const GLdouble *params);


extern void GLAPIENTRY
_mesa_ProgramLocalParameter4fARB(GLcontext *ctx, GLenum target, GLuint index,
				 GLfloat x, GLfloat y, GLfloat z, GLfloat w);


extern void GLAPIENTRY
_mesa_ProgramLocalParameter4fvARB(GLcontext *ctx, GLenum target, GLuint index,
				  const GLfloat *params);


extern void GLAPIENTRY
_mesa_ProgramLocalParameters4fvEXT(GLcontext *ctx, GLenum target, GLuint index, GLsizei count,
				   const GLfloat *params);


extern void GLAPIENTRY
_mesa_GetProgramEnvParameterdvARB(GLcontext *ctx, GLenum target, GLuint index,
				  GLdouble *params);


extern void GLAPIENTRY
_mesa_GetProgramEnvParameterfvARB(GLcontext *ctx, GLenum target, GLuint index,
				  GLfloat *params);


extern void GLAPIENTRY
_mesa_GetProgramLocalParameterdvARB(GLcontext *ctx, GLenum target, GLuint index,
				    GLdouble *params);


extern void GLAPIENTRY
_mesa_GetProgramLocalParameterfvARB(GLcontext *ctx, GLenum target, GLuint index,
				    GLfloat *params);


extern void GLAPIENTRY
_mesa_GetProgramivARB(GLcontext *ctx, GLenum target, GLenum pname, GLint *params);


extern void GLAPIENTRY
_mesa_GetProgramStringARB(GLcontext *ctx, GLenum target, GLenum pname, GLvoid *string);


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
