/*
 * Mesa 3-D graphics library
 * Version:  5.1
 *
 * Copyright (C) 1999-2003  Brian Paul   All Rights Reserved.
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
 *
 * Authors:
 *    Brian Paul
 */


#ifndef NVPROGRAM_H
#define NVPROGRAM_H


extern void GLAPIENTRY
_mesa_ExecuteProgramNV(GLcontext *ctx, GLenum target, GLuint id, const GLfloat *params);

extern GLboolean GLAPIENTRY
_mesa_AreProgramsResidentNV(GLcontext *ctx, GLsizei n, const GLuint *ids,
			    GLboolean *residences);

extern void GLAPIENTRY
_mesa_RequestResidentProgramsNV(GLcontext *ctx, GLsizei n, const GLuint *ids);

extern void GLAPIENTRY
_mesa_GetProgramParameterfvNV(GLcontext *ctx, GLenum target, GLuint index,
			      GLenum pname, GLfloat *params);

extern void GLAPIENTRY
_mesa_GetProgramParameterdvNV(GLcontext *ctx, GLenum target, GLuint index,
			      GLenum pname, GLdouble *params);

extern void GLAPIENTRY
_mesa_GetProgramivNV(GLcontext *ctx, GLuint id, GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetProgramStringNV(GLcontext *ctx, GLuint id, GLenum pname, GLubyte *program);

extern void GLAPIENTRY
_mesa_GetTrackMatrixivNV(GLcontext *ctx, GLenum target, GLuint address,
			 GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetVertexAttribdvNV(GLcontext *ctx, GLuint index, GLenum pname, GLdouble *params);

extern void GLAPIENTRY
_mesa_GetVertexAttribfvNV(GLcontext *ctx, GLuint index, GLenum pname, GLfloat *params);

extern void GLAPIENTRY
_mesa_GetVertexAttribivNV(GLcontext *ctx, GLuint index, GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetVertexAttribPointervNV(GLcontext *ctx, GLuint index, GLenum pname, GLvoid **pointer);

extern void GLAPIENTRY
_mesa_LoadProgramNV(GLcontext *ctx, GLenum target, GLuint id, GLsizei len,
		    const GLubyte *program);

extern void GLAPIENTRY
_mesa_ProgramParameter4dNV(GLcontext *ctx, GLenum target, GLuint index,
			   GLdouble x, GLdouble y, GLdouble z, GLdouble w);

extern void GLAPIENTRY
_mesa_ProgramParameter4dvNV(GLcontext *ctx, GLenum target, GLuint index,
			    const GLdouble *params);

extern void GLAPIENTRY
_mesa_ProgramParameter4fNV(GLcontext *ctx, GLenum target, GLuint index,
			   GLfloat x, GLfloat y, GLfloat z, GLfloat w);

extern void GLAPIENTRY
_mesa_ProgramParameter4fvNV(GLcontext *ctx, GLenum target, GLuint index,
			    const GLfloat *params);

extern void GLAPIENTRY
_mesa_ProgramParameters4dvNV(GLcontext *ctx, GLenum target, GLuint index,
			     GLuint num, const GLdouble *params);

extern void GLAPIENTRY
_mesa_ProgramParameters4fvNV(GLcontext *ctx, GLenum target, GLuint index,
			     GLuint num, const GLfloat *params);

extern void GLAPIENTRY
_mesa_TrackMatrixNV(GLcontext *ctx, GLenum target, GLuint address,
		    GLenum matrix, GLenum transform);


extern void GLAPIENTRY
_mesa_ProgramNamedParameter4fNV(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte *name,
				GLfloat x, GLfloat y, GLfloat z, GLfloat w);

extern void GLAPIENTRY
_mesa_ProgramNamedParameter4fvNV(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte *name,
				 const float v[]);

extern void GLAPIENTRY
_mesa_ProgramNamedParameter4dNV(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte *name,
				GLdouble x, GLdouble y, GLdouble z, GLdouble w);

extern void GLAPIENTRY
_mesa_ProgramNamedParameter4dvNV(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte *name,
				 const double v[]);

extern void GLAPIENTRY
_mesa_GetProgramNamedParameterfvNV(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte *name,
				   GLfloat *params);

extern void GLAPIENTRY
_mesa_GetProgramNamedParameterdvNV(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte *name,
				   GLdouble *params);


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
