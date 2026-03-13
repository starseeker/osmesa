/*
 * Mesa 3-D graphics library
 * Version:  6.5.3
 *
 * Copyright (C) 2004-2007  Brian Paul   All Rights Reserved.
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


#ifndef SHADERS_H
#define SHADERS_H


#include "glheader.h"
#include "mtypes.h"


extern void GLAPIENTRY
_mesa_DeleteObjectARB(GLhandleARB obj);

extern GLhandleARB GLAPIENTRY
_mesa_GetHandleARB(ctx, GLcontext *ctx, GLenum pname);

extern void GLAPIENTRY
_mesa_DetachObjectARB(ctx, GLcontext *ctx, GLhandleARB program, GLhandleARB shader);

extern GLhandleARB GLAPIENTRY
_mesa_CreateShaderObjectARB(ctx, GLcontext *ctx, GLenum type);

extern void GLAPIENTRY
_mesa_ShaderSourceARB(ctx, GLcontext *ctx, GLhandleARB shaderObj, GLsizei count,
		      const GLcharARB ** string, const GLint * length);

extern void  GLAPIENTRY
_mesa_CompileShaderARB(ctx, GLcontext *ctx, GLhandleARB shaderObj);

extern GLhandleARB GLAPIENTRY
_mesa_CreateProgramObjectARB(ctx, GLcontext *ctx);

extern void GLAPIENTRY
_mesa_AttachObjectARB(ctx, GLcontext *ctx, GLhandleARB program, GLhandleARB shader);

extern void GLAPIENTRY
_mesa_LinkProgramARB(ctx, GLcontext *ctx, GLhandleARB programObj);

extern void GLAPIENTRY
_mesa_UseProgramObjectARB(ctx, GLcontext *ctx, GLhandleARB program);

extern void GLAPIENTRY
_mesa_ValidateProgramARB(ctx, GLcontext *ctx, GLhandleARB program);

extern void GLAPIENTRY
_mesa_Uniform1fARB(ctx, GLcontext *ctx, GLint location, GLfloat v0);

extern void GLAPIENTRY
_mesa_Uniform2fARB(ctx, GLcontext *ctx, GLint location, GLfloat v0, GLfloat v1);

extern void GLAPIENTRY
_mesa_Uniform3fARB(ctx, GLcontext *ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);

extern void GLAPIENTRY
_mesa_Uniform4fARB(ctx, GLcontext *ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2,
		   GLfloat v3);

extern void GLAPIENTRY
_mesa_Uniform1iARB(ctx, GLcontext *ctx, GLint location, GLint v0);

extern void GLAPIENTRY
_mesa_Uniform2iARB(ctx, GLcontext *ctx, GLint location, GLint v0, GLint v1);

extern void GLAPIENTRY
_mesa_Uniform3iARB(ctx, GLcontext *ctx, GLint location, GLint v0, GLint v1, GLint v2);

extern void GLAPIENTRY
_mesa_Uniform4iARB(ctx, GLcontext *ctx, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);

extern void GLAPIENTRY
_mesa_Uniform1fvARB(ctx, GLcontext *ctx, GLint location, GLsizei count, const GLfloat * value);

extern void GLAPIENTRY
_mesa_Uniform2fvARB(ctx, GLcontext *ctx, GLint location, GLsizei count, const GLfloat * value);

extern void GLAPIENTRY
_mesa_Uniform3fvARB(ctx, GLcontext *ctx, GLint location, GLsizei count, const GLfloat * value);

extern void GLAPIENTRY
_mesa_Uniform4fvARB(ctx, GLcontext *ctx, GLint location, GLsizei count, const GLfloat * value);

extern void GLAPIENTRY
_mesa_Uniform1ivARB(ctx, GLcontext *ctx, GLint location, GLsizei count, const GLint * value);

extern void GLAPIENTRY
_mesa_Uniform2ivARB(ctx, GLcontext *ctx, GLint location, GLsizei count, const GLint * value);

extern void GLAPIENTRY
_mesa_Uniform3ivARB(ctx, GLcontext *ctx, GLint location, GLsizei count, const GLint * value);

extern void GLAPIENTRY
_mesa_Uniform4ivARB(ctx, GLcontext *ctx, GLint location, GLsizei count, const GLint * value);

extern void GLAPIENTRY
_mesa_UniformMatrix2fvARB(ctx, GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose,
			  const GLfloat * value);

extern void GLAPIENTRY
_mesa_UniformMatrix3fvARB(ctx, GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose,
			  const GLfloat * value);

extern void GLAPIENTRY
_mesa_UniformMatrix4fvARB(ctx, GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose,
			  const GLfloat * value);

extern void GLAPIENTRY
_mesa_GetObjectParameterfvARB(GLhandleARB, GLenum, GLfloat *);

extern void GLAPIENTRY
_mesa_GetObjectParameterivARB(ctx, GLcontext *ctx, GLhandleARB object, GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetInfoLogARB(ctx, GLcontext *ctx, GLhandleARB object, GLsizei maxLength, GLsizei * length,
		    GLcharARB * infoLog);

extern void GLAPIENTRY
_mesa_GetAttachedObjectsARB(ctx, GLcontext *ctx, GLhandleARB container, GLsizei maxCount,
			    GLsizei * count, GLhandleARB * obj);

extern GLint GLAPIENTRY
_mesa_GetUniformLocationARB(ctx, GLcontext *ctx, GLhandleARB programObj, const GLcharARB *name);

extern void GLAPIENTRY
_mesa_GetActiveUniformARB(ctx, GLcontext *ctx, GLhandleARB program, GLuint index,
			  GLsizei maxLength, GLsizei * length, GLint * size,
			  GLenum * type, GLcharARB * name);

extern void GLAPIENTRY
_mesa_GetUniformfvARB(ctx, GLcontext *ctx, GLhandleARB program, GLint location, GLfloat * params);

extern void GLAPIENTRY
_mesa_GetUniformivARB(ctx, GLcontext *ctx, GLhandleARB program, GLint location, GLint * params);

extern void GLAPIENTRY
_mesa_GetShaderSourceARB(ctx, GLcontext *ctx, GLhandleARB shader, GLsizei maxLength,
			 GLsizei *length, GLcharARB *sourceOut);

#if FEATURE_ARB_vertex_shader

extern void GLAPIENTRY
_mesa_BindAttribLocationARB(ctx, GLcontext *ctx, GLhandleARB program, GLuint index,
			    const GLcharARB *name);

extern void GLAPIENTRY
_mesa_GetActiveAttribARB(ctx, GLcontext *ctx, GLhandleARB program, GLuint index,
			 GLsizei maxLength, GLsizei * length, GLint * size,
			 GLenum * type, GLcharARB * name);

extern GLint GLAPIENTRY
_mesa_GetAttribLocationARB(ctx, GLcontext *ctx, GLhandleARB program, const GLcharARB * name);

#endif /* FEATURE_ARB_vertex_shader */


/* 2.0 */
extern void GLAPIENTRY
_mesa_AttachShader(ctx, GLcontext *ctx, GLuint program, GLuint shader);

extern GLuint GLAPIENTRY
_mesa_CreateShader(ctx, GLcontext *ctx, GLenum type);

extern GLuint GLAPIENTRY
_mesa_CreateProgram(ctx, GLcontext *ctx);

extern void GLAPIENTRY
_mesa_DeleteProgram(GLuint program);

extern void GLAPIENTRY
_mesa_DeleteShader(GLuint shader);

extern void GLAPIENTRY
_mesa_DetachShader(ctx, GLcontext *ctx, GLuint program, GLuint shader);

extern void GLAPIENTRY
_mesa_GetAttachedShaders(ctx, GLcontext *ctx, GLuint program, GLsizei maxCount,
			 GLsizei *count, GLuint *obj);

extern void GLAPIENTRY
_mesa_GetProgramiv(ctx, GLcontext *ctx, GLuint program, GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetProgramInfoLog(ctx, GLcontext *ctx, GLuint program, GLsizei bufSize,
			GLsizei *length, GLchar *infoLog);

extern void GLAPIENTRY
_mesa_GetShaderiv(ctx, GLcontext *ctx, GLuint shader, GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetShaderInfoLog(ctx, GLcontext *ctx, GLuint shader, GLsizei bufSize,
		       GLsizei *length, GLchar *infoLog);

extern GLboolean GLAPIENTRY
_mesa_IsProgram(ctx, GLcontext *ctx, GLuint name);

extern GLboolean GLAPIENTRY
_mesa_IsShader(ctx, GLcontext *ctx, GLuint name);



/* 2.1 */
extern void GLAPIENTRY
_mesa_UniformMatrix2x3fv(ctx, GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose,
			 const GLfloat *value);

extern void GLAPIENTRY
_mesa_UniformMatrix3x2fv(ctx, GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose,
			 const GLfloat *value);

extern void GLAPIENTRY
_mesa_UniformMatrix2x4fv(ctx, GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose,
			 const GLfloat *value);

extern void GLAPIENTRY
_mesa_UniformMatrix4x2fv(ctx, GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose,
			 const GLfloat *value);

extern void GLAPIENTRY
_mesa_UniformMatrix3x4fv(ctx, GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose,
			 const GLfloat *value);

extern void GLAPIENTRY
_mesa_UniformMatrix4x3fv(ctx, GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose,
			 const GLfloat *value);


#endif /* SHADERS_H */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
