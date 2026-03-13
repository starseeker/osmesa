/* DO NOT EDIT - This file generated automatically by gl_table.py (from Mesa) script */

/*
 * Copyright (C) 1999-2003  Brian Paul   All Rights Reserved.
 * (C) Copyright IBM Corporation 2004
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL, IBM,
 * AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if !defined( _GLAPI_TABLE_H_ )
#  define _GLAPI_TABLE_H_


/* Forward declaration - full definition is in main/mtypes.h */
typedef struct __GLcontextRec GLcontext;
#ifndef GLAPIENTRYP
# ifndef GLAPIENTRY
#  define GLAPIENTRY
# endif

# define GLAPIENTRYP GLAPIENTRY *
#endif

typedef void (*_glapi_proc)(void); /* generic function pointer */

struct _glapi_table {
    void (GLAPIENTRYP NewList)(GLcontext *ctx, GLuint list, GLenum mode); /* 0 */
    void (GLAPIENTRYP EndList)(GLcontext *ctx); /* 1 */
    void (GLAPIENTRYP CallList)(GLcontext *ctx, GLuint list); /* 2 */
    void (GLAPIENTRYP CallLists)(GLcontext *ctx, GLsizei n, GLenum type, const GLvoid * lists); /* 3 */
    void (GLAPIENTRYP DeleteLists)(GLcontext *ctx, GLuint list, GLsizei range); /* 4 */
    GLuint(GLAPIENTRYP GenLists)(GLcontext *ctx, GLsizei range);  /* 5 */
    void (GLAPIENTRYP ListBase)(GLcontext *ctx, GLuint base); /* 6 */
    void (GLAPIENTRYP Begin)(GLcontext *ctx, GLenum mode); /* 7 */
    void (GLAPIENTRYP Bitmap)(GLcontext *ctx, GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap); /* 8 */
    void (GLAPIENTRYP Color3b)(GLcontext *ctx, GLbyte red, GLbyte green, GLbyte blue); /* 9 */
    void (GLAPIENTRYP Color3bv)(GLcontext *ctx, const GLbyte * v); /* 10 */
    void (GLAPIENTRYP Color3d)(GLcontext *ctx, GLdouble red, GLdouble green, GLdouble blue); /* 11 */
    void (GLAPIENTRYP Color3dv)(GLcontext *ctx, const GLdouble * v); /* 12 */
    void (GLAPIENTRYP Color3f)(GLcontext *ctx, GLfloat red, GLfloat green, GLfloat blue); /* 13 */
    void (GLAPIENTRYP Color3fv)(GLcontext *ctx, const GLfloat * v); /* 14 */
    void (GLAPIENTRYP Color3i)(GLcontext *ctx, GLint red, GLint green, GLint blue); /* 15 */
    void (GLAPIENTRYP Color3iv)(GLcontext *ctx, const GLint * v); /* 16 */
    void (GLAPIENTRYP Color3s)(GLcontext *ctx, GLshort red, GLshort green, GLshort blue); /* 17 */
    void (GLAPIENTRYP Color3sv)(GLcontext *ctx, const GLshort * v); /* 18 */
    void (GLAPIENTRYP Color3ub)(GLcontext *ctx, GLubyte red, GLubyte green, GLubyte blue); /* 19 */
    void (GLAPIENTRYP Color3ubv)(GLcontext *ctx, const GLubyte * v); /* 20 */
    void (GLAPIENTRYP Color3ui)(GLcontext *ctx, GLuint red, GLuint green, GLuint blue); /* 21 */
    void (GLAPIENTRYP Color3uiv)(GLcontext *ctx, const GLuint * v); /* 22 */
    void (GLAPIENTRYP Color3us)(GLcontext *ctx, GLushort red, GLushort green, GLushort blue); /* 23 */
    void (GLAPIENTRYP Color3usv)(GLcontext *ctx, const GLushort * v); /* 24 */
    void (GLAPIENTRYP Color4b)(GLcontext *ctx, GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha); /* 25 */
    void (GLAPIENTRYP Color4bv)(GLcontext *ctx, const GLbyte * v); /* 26 */
    void (GLAPIENTRYP Color4d)(GLcontext *ctx, GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha); /* 27 */
    void (GLAPIENTRYP Color4dv)(GLcontext *ctx, const GLdouble * v); /* 28 */
    void (GLAPIENTRYP Color4f)(GLcontext *ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha); /* 29 */
    void (GLAPIENTRYP Color4fv)(GLcontext *ctx, const GLfloat * v); /* 30 */
    void (GLAPIENTRYP Color4i)(GLcontext *ctx, GLint red, GLint green, GLint blue, GLint alpha); /* 31 */
    void (GLAPIENTRYP Color4iv)(GLcontext *ctx, const GLint * v); /* 32 */
    void (GLAPIENTRYP Color4s)(GLcontext *ctx, GLshort red, GLshort green, GLshort blue, GLshort alpha); /* 33 */
    void (GLAPIENTRYP Color4sv)(GLcontext *ctx, const GLshort * v); /* 34 */
    void (GLAPIENTRYP Color4ub)(GLcontext *ctx, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha); /* 35 */
    void (GLAPIENTRYP Color4ubv)(GLcontext *ctx, const GLubyte * v); /* 36 */
    void (GLAPIENTRYP Color4ui)(GLcontext *ctx, GLuint red, GLuint green, GLuint blue, GLuint alpha); /* 37 */
    void (GLAPIENTRYP Color4uiv)(GLcontext *ctx, const GLuint * v); /* 38 */
    void (GLAPIENTRYP Color4us)(GLcontext *ctx, GLushort red, GLushort green, GLushort blue, GLushort alpha); /* 39 */
    void (GLAPIENTRYP Color4usv)(GLcontext *ctx, const GLushort * v); /* 40 */
    void (GLAPIENTRYP EdgeFlag)(GLcontext *ctx, GLboolean flag); /* 41 */
    void (GLAPIENTRYP EdgeFlagv)(GLcontext *ctx, const GLboolean * flag); /* 42 */
    void (GLAPIENTRYP End)(GLcontext *ctx); /* 43 */
    void (GLAPIENTRYP Indexd)(GLcontext *ctx, GLdouble c); /* 44 */
    void (GLAPIENTRYP Indexdv)(GLcontext *ctx, const GLdouble * c); /* 45 */
    void (GLAPIENTRYP Indexf)(GLcontext *ctx, GLfloat c); /* 46 */
    void (GLAPIENTRYP Indexfv)(GLcontext *ctx, const GLfloat * c); /* 47 */
    void (GLAPIENTRYP Indexi)(GLcontext *ctx, GLint c); /* 48 */
    void (GLAPIENTRYP Indexiv)(GLcontext *ctx, const GLint * c); /* 49 */
    void (GLAPIENTRYP Indexs)(GLcontext *ctx, GLshort c); /* 50 */
    void (GLAPIENTRYP Indexsv)(GLcontext *ctx, const GLshort * c); /* 51 */
    void (GLAPIENTRYP Normal3b)(GLcontext *ctx, GLbyte nx, GLbyte ny, GLbyte nz); /* 52 */
    void (GLAPIENTRYP Normal3bv)(GLcontext *ctx, const GLbyte * v); /* 53 */
    void (GLAPIENTRYP Normal3d)(GLcontext *ctx, GLdouble nx, GLdouble ny, GLdouble nz); /* 54 */
    void (GLAPIENTRYP Normal3dv)(GLcontext *ctx, const GLdouble * v); /* 55 */
    void (GLAPIENTRYP Normal3f)(GLcontext *ctx, GLfloat nx, GLfloat ny, GLfloat nz); /* 56 */
    void (GLAPIENTRYP Normal3fv)(GLcontext *ctx, const GLfloat * v); /* 57 */
    void (GLAPIENTRYP Normal3i)(GLcontext *ctx, GLint nx, GLint ny, GLint nz); /* 58 */
    void (GLAPIENTRYP Normal3iv)(GLcontext *ctx, const GLint * v); /* 59 */
    void (GLAPIENTRYP Normal3s)(GLcontext *ctx, GLshort nx, GLshort ny, GLshort nz); /* 60 */
    void (GLAPIENTRYP Normal3sv)(GLcontext *ctx, const GLshort * v); /* 61 */
    void (GLAPIENTRYP RasterPos2d)(GLcontext *ctx, GLdouble x, GLdouble y); /* 62 */
    void (GLAPIENTRYP RasterPos2dv)(GLcontext *ctx, const GLdouble * v); /* 63 */
    void (GLAPIENTRYP RasterPos2f)(GLcontext *ctx, GLfloat x, GLfloat y); /* 64 */
    void (GLAPIENTRYP RasterPos2fv)(GLcontext *ctx, const GLfloat * v); /* 65 */
    void (GLAPIENTRYP RasterPos2i)(GLcontext *ctx, GLint x, GLint y); /* 66 */
    void (GLAPIENTRYP RasterPos2iv)(GLcontext *ctx, const GLint * v); /* 67 */
    void (GLAPIENTRYP RasterPos2s)(GLcontext *ctx, GLshort x, GLshort y); /* 68 */
    void (GLAPIENTRYP RasterPos2sv)(GLcontext *ctx, const GLshort * v); /* 69 */
    void (GLAPIENTRYP RasterPos3d)(GLcontext *ctx, GLdouble x, GLdouble y, GLdouble z); /* 70 */
    void (GLAPIENTRYP RasterPos3dv)(GLcontext *ctx, const GLdouble * v); /* 71 */
    void (GLAPIENTRYP RasterPos3f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z); /* 72 */
    void (GLAPIENTRYP RasterPos3fv)(GLcontext *ctx, const GLfloat * v); /* 73 */
    void (GLAPIENTRYP RasterPos3i)(GLcontext *ctx, GLint x, GLint y, GLint z); /* 74 */
    void (GLAPIENTRYP RasterPos3iv)(GLcontext *ctx, const GLint * v); /* 75 */
    void (GLAPIENTRYP RasterPos3s)(GLcontext *ctx, GLshort x, GLshort y, GLshort z); /* 76 */
    void (GLAPIENTRYP RasterPos3sv)(GLcontext *ctx, const GLshort * v); /* 77 */
    void (GLAPIENTRYP RasterPos4d)(GLcontext *ctx, GLdouble x, GLdouble y, GLdouble z, GLdouble w); /* 78 */
    void (GLAPIENTRYP RasterPos4dv)(GLcontext *ctx, const GLdouble * v); /* 79 */
    void (GLAPIENTRYP RasterPos4f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w); /* 80 */
    void (GLAPIENTRYP RasterPos4fv)(GLcontext *ctx, const GLfloat * v); /* 81 */
    void (GLAPIENTRYP RasterPos4i)(GLcontext *ctx, GLint x, GLint y, GLint z, GLint w); /* 82 */
    void (GLAPIENTRYP RasterPos4iv)(GLcontext *ctx, const GLint * v); /* 83 */
    void (GLAPIENTRYP RasterPos4s)(GLcontext *ctx, GLshort x, GLshort y, GLshort z, GLshort w); /* 84 */
    void (GLAPIENTRYP RasterPos4sv)(GLcontext *ctx, const GLshort * v); /* 85 */
    void (GLAPIENTRYP Rectd)(GLcontext *ctx, GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2); /* 86 */
    void (GLAPIENTRYP Rectdv)(GLcontext *ctx, const GLdouble * v1, const GLdouble * v2); /* 87 */
    void (GLAPIENTRYP Rectf)(GLcontext *ctx, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2); /* 88 */
    void (GLAPIENTRYP Rectfv)(GLcontext *ctx, const GLfloat * v1, const GLfloat * v2); /* 89 */
    void (GLAPIENTRYP Recti)(GLcontext *ctx, GLint x1, GLint y1, GLint x2, GLint y2); /* 90 */
    void (GLAPIENTRYP Rectiv)(GLcontext *ctx, const GLint * v1, const GLint * v2); /* 91 */
    void (GLAPIENTRYP Rects)(GLcontext *ctx, GLshort x1, GLshort y1, GLshort x2, GLshort y2); /* 92 */
    void (GLAPIENTRYP Rectsv)(GLcontext *ctx, const GLshort * v1, const GLshort * v2); /* 93 */
    void (GLAPIENTRYP TexCoord1d)(GLcontext *ctx, GLdouble s); /* 94 */
    void (GLAPIENTRYP TexCoord1dv)(GLcontext *ctx, const GLdouble * v); /* 95 */
    void (GLAPIENTRYP TexCoord1f)(GLcontext *ctx, GLfloat s); /* 96 */
    void (GLAPIENTRYP TexCoord1fv)(GLcontext *ctx, const GLfloat * v); /* 97 */
    void (GLAPIENTRYP TexCoord1i)(GLcontext *ctx, GLint s); /* 98 */
    void (GLAPIENTRYP TexCoord1iv)(GLcontext *ctx, const GLint * v); /* 99 */
    void (GLAPIENTRYP TexCoord1s)(GLcontext *ctx, GLshort s); /* 100 */
    void (GLAPIENTRYP TexCoord1sv)(GLcontext *ctx, const GLshort * v); /* 101 */
    void (GLAPIENTRYP TexCoord2d)(GLcontext *ctx, GLdouble s, GLdouble t); /* 102 */
    void (GLAPIENTRYP TexCoord2dv)(GLcontext *ctx, const GLdouble * v); /* 103 */
    void (GLAPIENTRYP TexCoord2f)(GLcontext *ctx, GLfloat s, GLfloat t); /* 104 */
    void (GLAPIENTRYP TexCoord2fv)(GLcontext *ctx, const GLfloat * v); /* 105 */
    void (GLAPIENTRYP TexCoord2i)(GLcontext *ctx, GLint s, GLint t); /* 106 */
    void (GLAPIENTRYP TexCoord2iv)(GLcontext *ctx, const GLint * v); /* 107 */
    void (GLAPIENTRYP TexCoord2s)(GLcontext *ctx, GLshort s, GLshort t); /* 108 */
    void (GLAPIENTRYP TexCoord2sv)(GLcontext *ctx, const GLshort * v); /* 109 */
    void (GLAPIENTRYP TexCoord3d)(GLcontext *ctx, GLdouble s, GLdouble t, GLdouble r); /* 110 */
    void (GLAPIENTRYP TexCoord3dv)(GLcontext *ctx, const GLdouble * v); /* 111 */
    void (GLAPIENTRYP TexCoord3f)(GLcontext *ctx, GLfloat s, GLfloat t, GLfloat r); /* 112 */
    void (GLAPIENTRYP TexCoord3fv)(GLcontext *ctx, const GLfloat * v); /* 113 */
    void (GLAPIENTRYP TexCoord3i)(GLcontext *ctx, GLint s, GLint t, GLint r); /* 114 */
    void (GLAPIENTRYP TexCoord3iv)(GLcontext *ctx, const GLint * v); /* 115 */
    void (GLAPIENTRYP TexCoord3s)(GLcontext *ctx, GLshort s, GLshort t, GLshort r); /* 116 */
    void (GLAPIENTRYP TexCoord3sv)(GLcontext *ctx, const GLshort * v); /* 117 */
    void (GLAPIENTRYP TexCoord4d)(GLcontext *ctx, GLdouble s, GLdouble t, GLdouble r, GLdouble q); /* 118 */
    void (GLAPIENTRYP TexCoord4dv)(GLcontext *ctx, const GLdouble * v); /* 119 */
    void (GLAPIENTRYP TexCoord4f)(GLcontext *ctx, GLfloat s, GLfloat t, GLfloat r, GLfloat q); /* 120 */
    void (GLAPIENTRYP TexCoord4fv)(GLcontext *ctx, const GLfloat * v); /* 121 */
    void (GLAPIENTRYP TexCoord4i)(GLcontext *ctx, GLint s, GLint t, GLint r, GLint q); /* 122 */
    void (GLAPIENTRYP TexCoord4iv)(GLcontext *ctx, const GLint * v); /* 123 */
    void (GLAPIENTRYP TexCoord4s)(GLcontext *ctx, GLshort s, GLshort t, GLshort r, GLshort q); /* 124 */
    void (GLAPIENTRYP TexCoord4sv)(GLcontext *ctx, const GLshort * v); /* 125 */
    void (GLAPIENTRYP Vertex2d)(GLcontext *ctx, GLdouble x, GLdouble y); /* 126 */
    void (GLAPIENTRYP Vertex2dv)(GLcontext *ctx, const GLdouble * v); /* 127 */
    void (GLAPIENTRYP Vertex2f)(GLcontext *ctx, GLfloat x, GLfloat y); /* 128 */
    void (GLAPIENTRYP Vertex2fv)(GLcontext *ctx, const GLfloat * v); /* 129 */
    void (GLAPIENTRYP Vertex2i)(GLcontext *ctx, GLint x, GLint y); /* 130 */
    void (GLAPIENTRYP Vertex2iv)(GLcontext *ctx, const GLint * v); /* 131 */
    void (GLAPIENTRYP Vertex2s)(GLcontext *ctx, GLshort x, GLshort y); /* 132 */
    void (GLAPIENTRYP Vertex2sv)(GLcontext *ctx, const GLshort * v); /* 133 */
    void (GLAPIENTRYP Vertex3d)(GLcontext *ctx, GLdouble x, GLdouble y, GLdouble z); /* 134 */
    void (GLAPIENTRYP Vertex3dv)(GLcontext *ctx, const GLdouble * v); /* 135 */
    void (GLAPIENTRYP Vertex3f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z); /* 136 */
    void (GLAPIENTRYP Vertex3fv)(GLcontext *ctx, const GLfloat * v); /* 137 */
    void (GLAPIENTRYP Vertex3i)(GLcontext *ctx, GLint x, GLint y, GLint z); /* 138 */
    void (GLAPIENTRYP Vertex3iv)(GLcontext *ctx, const GLint * v); /* 139 */
    void (GLAPIENTRYP Vertex3s)(GLcontext *ctx, GLshort x, GLshort y, GLshort z); /* 140 */
    void (GLAPIENTRYP Vertex3sv)(GLcontext *ctx, const GLshort * v); /* 141 */
    void (GLAPIENTRYP Vertex4d)(GLcontext *ctx, GLdouble x, GLdouble y, GLdouble z, GLdouble w); /* 142 */
    void (GLAPIENTRYP Vertex4dv)(GLcontext *ctx, const GLdouble * v); /* 143 */
    void (GLAPIENTRYP Vertex4f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w); /* 144 */
    void (GLAPIENTRYP Vertex4fv)(GLcontext *ctx, const GLfloat * v); /* 145 */
    void (GLAPIENTRYP Vertex4i)(GLcontext *ctx, GLint x, GLint y, GLint z, GLint w); /* 146 */
    void (GLAPIENTRYP Vertex4iv)(GLcontext *ctx, const GLint * v); /* 147 */
    void (GLAPIENTRYP Vertex4s)(GLcontext *ctx, GLshort x, GLshort y, GLshort z, GLshort w); /* 148 */
    void (GLAPIENTRYP Vertex4sv)(GLcontext *ctx, const GLshort * v); /* 149 */
    void (GLAPIENTRYP ClipPlane)(GLcontext *ctx, GLenum plane, const GLdouble * equation); /* 150 */
    void (GLAPIENTRYP ColorMaterial)(GLcontext *ctx, GLenum face, GLenum mode); /* 151 */
    void (GLAPIENTRYP CullFace)(GLcontext *ctx, GLenum mode); /* 152 */
    void (GLAPIENTRYP Fogf)(GLcontext *ctx, GLenum pname, GLfloat param); /* 153 */
    void (GLAPIENTRYP Fogfv)(GLcontext *ctx, GLenum pname, const GLfloat * params); /* 154 */
    void (GLAPIENTRYP Fogi)(GLcontext *ctx, GLenum pname, GLint param); /* 155 */
    void (GLAPIENTRYP Fogiv)(GLcontext *ctx, GLenum pname, const GLint * params); /* 156 */
    void (GLAPIENTRYP FrontFace)(GLcontext *ctx, GLenum mode); /* 157 */
    void (GLAPIENTRYP Hint)(GLcontext *ctx, GLenum target, GLenum mode); /* 158 */
    void (GLAPIENTRYP Lightf)(GLcontext *ctx, GLenum light, GLenum pname, GLfloat param); /* 159 */
    void (GLAPIENTRYP Lightfv)(GLcontext *ctx, GLenum light, GLenum pname, const GLfloat * params); /* 160 */
    void (GLAPIENTRYP Lighti)(GLcontext *ctx, GLenum light, GLenum pname, GLint param); /* 161 */
    void (GLAPIENTRYP Lightiv)(GLcontext *ctx, GLenum light, GLenum pname, const GLint * params); /* 162 */
    void (GLAPIENTRYP LightModelf)(GLcontext *ctx, GLenum pname, GLfloat param); /* 163 */
    void (GLAPIENTRYP LightModelfv)(GLcontext *ctx, GLenum pname, const GLfloat * params); /* 164 */
    void (GLAPIENTRYP LightModeli)(GLcontext *ctx, GLenum pname, GLint param); /* 165 */
    void (GLAPIENTRYP LightModeliv)(GLcontext *ctx, GLenum pname, const GLint * params); /* 166 */
    void (GLAPIENTRYP LineStipple)(GLcontext *ctx, GLint factor, GLushort pattern); /* 167 */
    void (GLAPIENTRYP LineWidth)(GLcontext *ctx, GLfloat width); /* 168 */
    void (GLAPIENTRYP Materialf)(GLcontext *ctx, GLenum face, GLenum pname, GLfloat param); /* 169 */
    void (GLAPIENTRYP Materialfv)(GLcontext *ctx, GLenum face, GLenum pname, const GLfloat * params); /* 170 */
    void (GLAPIENTRYP Materiali)(GLcontext *ctx, GLenum face, GLenum pname, GLint param); /* 171 */
    void (GLAPIENTRYP Materialiv)(GLcontext *ctx, GLenum face, GLenum pname, const GLint * params); /* 172 */
    void (GLAPIENTRYP PointSize)(GLcontext *ctx, GLfloat size); /* 173 */
    void (GLAPIENTRYP PolygonMode)(GLcontext *ctx, GLenum face, GLenum mode); /* 174 */
    void (GLAPIENTRYP PolygonStipple)(GLcontext *ctx, const GLubyte * mask); /* 175 */
    void (GLAPIENTRYP Scissor)(GLcontext *ctx, GLint x, GLint y, GLsizei width, GLsizei height); /* 176 */
    void (GLAPIENTRYP ShadeModel)(GLcontext *ctx, GLenum mode); /* 177 */
    void (GLAPIENTRYP TexParameterf)(GLcontext *ctx, GLenum target, GLenum pname, GLfloat param); /* 178 */
    void (GLAPIENTRYP TexParameterfv)(GLcontext *ctx, GLenum target, GLenum pname, const GLfloat * params); /* 179 */
    void (GLAPIENTRYP TexParameteri)(GLcontext *ctx, GLenum target, GLenum pname, GLint param); /* 180 */
    void (GLAPIENTRYP TexParameteriv)(GLcontext *ctx, GLenum target, GLenum pname, const GLint * params); /* 181 */
    void (GLAPIENTRYP TexImage1D)(GLcontext *ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels); /* 182 */
    void (GLAPIENTRYP TexImage2D)(GLcontext *ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels); /* 183 */
    void (GLAPIENTRYP TexEnvf)(GLcontext *ctx, GLenum target, GLenum pname, GLfloat param); /* 184 */
    void (GLAPIENTRYP TexEnvfv)(GLcontext *ctx, GLenum target, GLenum pname, const GLfloat * params); /* 185 */
    void (GLAPIENTRYP TexEnvi)(GLcontext *ctx, GLenum target, GLenum pname, GLint param); /* 186 */
    void (GLAPIENTRYP TexEnviv)(GLcontext *ctx, GLenum target, GLenum pname, const GLint * params); /* 187 */
    void (GLAPIENTRYP TexGend)(GLcontext *ctx, GLenum coord, GLenum pname, GLdouble param); /* 188 */
    void (GLAPIENTRYP TexGendv)(GLcontext *ctx, GLenum coord, GLenum pname, const GLdouble * params); /* 189 */
    void (GLAPIENTRYP TexGenf)(GLcontext *ctx, GLenum coord, GLenum pname, GLfloat param); /* 190 */
    void (GLAPIENTRYP TexGenfv)(GLcontext *ctx, GLenum coord, GLenum pname, const GLfloat * params); /* 191 */
    void (GLAPIENTRYP TexGeni)(GLcontext *ctx, GLenum coord, GLenum pname, GLint param); /* 192 */
    void (GLAPIENTRYP TexGeniv)(GLcontext *ctx, GLenum coord, GLenum pname, const GLint * params); /* 193 */
    void (GLAPIENTRYP FeedbackBuffer)(GLcontext *ctx, GLsizei size, GLenum type, GLfloat * buffer); /* 194 */
    void (GLAPIENTRYP SelectBuffer)(GLcontext *ctx, GLsizei size, GLuint * buffer); /* 195 */
    GLint(GLAPIENTRYP RenderMode)(GLcontext *ctx, GLenum mode);  /* 196 */
    void (GLAPIENTRYP InitNames)(GLcontext *ctx); /* 197 */
    void (GLAPIENTRYP LoadName)(GLcontext *ctx, GLuint name); /* 198 */
    void (GLAPIENTRYP PassThrough)(GLcontext *ctx, GLfloat token); /* 199 */
    void (GLAPIENTRYP PopName)(GLcontext *ctx); /* 200 */
    void (GLAPIENTRYP PushName)(GLcontext *ctx, GLuint name); /* 201 */
    void (GLAPIENTRYP DrawBuffer)(GLcontext *ctx, GLenum mode); /* 202 */
    void (GLAPIENTRYP Clear)(GLcontext *ctx, GLbitfield mask); /* 203 */
    void (GLAPIENTRYP ClearAccum)(GLcontext *ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha); /* 204 */
    void (GLAPIENTRYP ClearIndex)(GLcontext *ctx, GLfloat c); /* 205 */
    void (GLAPIENTRYP ClearColor)(GLcontext *ctx, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha); /* 206 */
    void (GLAPIENTRYP ClearStencil)(GLcontext *ctx, GLint s); /* 207 */
    void (GLAPIENTRYP ClearDepth)(GLcontext *ctx, GLclampd depth); /* 208 */
    void (GLAPIENTRYP StencilMask)(GLcontext *ctx, GLuint mask); /* 209 */
    void (GLAPIENTRYP ColorMask)(GLcontext *ctx, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha); /* 210 */
    void (GLAPIENTRYP DepthMask)(GLcontext *ctx, GLboolean flag); /* 211 */
    void (GLAPIENTRYP IndexMask)(GLcontext *ctx, GLuint mask); /* 212 */
    void (GLAPIENTRYP Accum)(GLcontext *ctx, GLenum op, GLfloat value); /* 213 */
    void (GLAPIENTRYP Disable)(GLcontext *ctx, GLenum cap); /* 214 */
    void (GLAPIENTRYP Enable)(GLcontext *ctx, GLenum cap); /* 215 */
    void (GLAPIENTRYP Finish)(GLcontext *ctx); /* 216 */
    void (GLAPIENTRYP Flush)(GLcontext *ctx); /* 217 */
    void (GLAPIENTRYP PopAttrib)(GLcontext *ctx); /* 218 */
    void (GLAPIENTRYP PushAttrib)(GLcontext *ctx, GLbitfield mask); /* 219 */
    void (GLAPIENTRYP Map1d)(GLcontext *ctx, GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points); /* 220 */
    void (GLAPIENTRYP Map1f)(GLcontext *ctx, GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points); /* 221 */
    void (GLAPIENTRYP Map2d)(GLcontext *ctx, GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points); /* 222 */
    void (GLAPIENTRYP Map2f)(GLcontext *ctx, GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points); /* 223 */
    void (GLAPIENTRYP MapGrid1d)(GLcontext *ctx, GLint un, GLdouble u1, GLdouble u2); /* 224 */
    void (GLAPIENTRYP MapGrid1f)(GLcontext *ctx, GLint un, GLfloat u1, GLfloat u2); /* 225 */
    void (GLAPIENTRYP MapGrid2d)(GLcontext *ctx, GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2); /* 226 */
    void (GLAPIENTRYP MapGrid2f)(GLcontext *ctx, GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2); /* 227 */
    void (GLAPIENTRYP EvalCoord1d)(GLcontext *ctx, GLdouble u); /* 228 */
    void (GLAPIENTRYP EvalCoord1dv)(GLcontext *ctx, const GLdouble * u); /* 229 */
    void (GLAPIENTRYP EvalCoord1f)(GLcontext *ctx, GLfloat u); /* 230 */
    void (GLAPIENTRYP EvalCoord1fv)(GLcontext *ctx, const GLfloat * u); /* 231 */
    void (GLAPIENTRYP EvalCoord2d)(GLcontext *ctx, GLdouble u, GLdouble v); /* 232 */
    void (GLAPIENTRYP EvalCoord2dv)(GLcontext *ctx, const GLdouble * u); /* 233 */
    void (GLAPIENTRYP EvalCoord2f)(GLcontext *ctx, GLfloat u, GLfloat v); /* 234 */
    void (GLAPIENTRYP EvalCoord2fv)(GLcontext *ctx, const GLfloat * u); /* 235 */
    void (GLAPIENTRYP EvalMesh1)(GLcontext *ctx, GLenum mode, GLint i1, GLint i2); /* 236 */
    void (GLAPIENTRYP EvalPoint1)(GLcontext *ctx, GLint i); /* 237 */
    void (GLAPIENTRYP EvalMesh2)(GLcontext *ctx, GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2); /* 238 */
    void (GLAPIENTRYP EvalPoint2)(GLcontext *ctx, GLint i, GLint j); /* 239 */
    void (GLAPIENTRYP AlphaFunc)(GLcontext *ctx, GLenum func, GLclampf ref); /* 240 */
    void (GLAPIENTRYP BlendFunc)(GLcontext *ctx, GLenum sfactor, GLenum dfactor); /* 241 */
    void (GLAPIENTRYP LogicOp)(GLcontext *ctx, GLenum opcode); /* 242 */
    void (GLAPIENTRYP StencilFunc)(GLcontext *ctx, GLenum func, GLint ref, GLuint mask); /* 243 */
    void (GLAPIENTRYP StencilOp)(GLcontext *ctx, GLenum fail, GLenum zfail, GLenum zpass); /* 244 */
    void (GLAPIENTRYP DepthFunc)(GLcontext *ctx, GLenum func); /* 245 */
    void (GLAPIENTRYP PixelZoom)(GLcontext *ctx, GLfloat xfactor, GLfloat yfactor); /* 246 */
    void (GLAPIENTRYP PixelTransferf)(GLcontext *ctx, GLenum pname, GLfloat param); /* 247 */
    void (GLAPIENTRYP PixelTransferi)(GLcontext *ctx, GLenum pname, GLint param); /* 248 */
    void (GLAPIENTRYP PixelStoref)(GLcontext *ctx, GLenum pname, GLfloat param); /* 249 */
    void (GLAPIENTRYP PixelStorei)(GLcontext *ctx, GLenum pname, GLint param); /* 250 */
    void (GLAPIENTRYP PixelMapfv)(GLcontext *ctx, GLenum map, GLsizei mapsize, const GLfloat * values); /* 251 */
    void (GLAPIENTRYP PixelMapuiv)(GLcontext *ctx, GLenum map, GLsizei mapsize, const GLuint * values); /* 252 */
    void (GLAPIENTRYP PixelMapusv)(GLcontext *ctx, GLenum map, GLsizei mapsize, const GLushort * values); /* 253 */
    void (GLAPIENTRYP ReadBuffer)(GLcontext *ctx, GLenum mode); /* 254 */
    void (GLAPIENTRYP CopyPixels)(GLcontext *ctx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum type); /* 255 */
    void (GLAPIENTRYP ReadPixels)(GLcontext *ctx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels); /* 256 */
    void (GLAPIENTRYP DrawPixels)(GLcontext *ctx, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels); /* 257 */
    void (GLAPIENTRYP GetBooleanv)(GLcontext *ctx, GLenum pname, GLboolean * params); /* 258 */
    void (GLAPIENTRYP GetClipPlane)(GLcontext *ctx, GLenum plane, GLdouble * equation); /* 259 */
    void (GLAPIENTRYP GetDoublev)(GLcontext *ctx, GLenum pname, GLdouble * params); /* 260 */
    GLenum(GLAPIENTRYP GetError)(GLcontext *ctx);  /* 261 */
    void (GLAPIENTRYP GetFloatv)(GLcontext *ctx, GLenum pname, GLfloat * params); /* 262 */
    void (GLAPIENTRYP GetIntegerv)(GLcontext *ctx, GLenum pname, GLint * params); /* 263 */
    void (GLAPIENTRYP GetLightfv)(GLcontext *ctx, GLenum light, GLenum pname, GLfloat * params); /* 264 */
    void (GLAPIENTRYP GetLightiv)(GLcontext *ctx, GLenum light, GLenum pname, GLint * params); /* 265 */
    void (GLAPIENTRYP GetMapdv)(GLcontext *ctx, GLenum target, GLenum query, GLdouble * v); /* 266 */
    void (GLAPIENTRYP GetMapfv)(GLcontext *ctx, GLenum target, GLenum query, GLfloat * v); /* 267 */
    void (GLAPIENTRYP GetMapiv)(GLcontext *ctx, GLenum target, GLenum query, GLint * v); /* 268 */
    void (GLAPIENTRYP GetMaterialfv)(GLcontext *ctx, GLenum face, GLenum pname, GLfloat * params); /* 269 */
    void (GLAPIENTRYP GetMaterialiv)(GLcontext *ctx, GLenum face, GLenum pname, GLint * params); /* 270 */
    void (GLAPIENTRYP GetPixelMapfv)(GLcontext *ctx, GLenum map, GLfloat * values); /* 271 */
    void (GLAPIENTRYP GetPixelMapuiv)(GLcontext *ctx, GLenum map, GLuint * values); /* 272 */
    void (GLAPIENTRYP GetPixelMapusv)(GLcontext *ctx, GLenum map, GLushort * values); /* 273 */
    void (GLAPIENTRYP GetPolygonStipple)(GLcontext *ctx, GLubyte * mask); /* 274 */
    const GLubyte * (GLAPIENTRYP GetString)(GLcontext *ctx, GLenum name); /* 275 */
    void (GLAPIENTRYP GetTexEnvfv)(GLcontext *ctx, GLenum target, GLenum pname, GLfloat * params); /* 276 */
    void (GLAPIENTRYP GetTexEnviv)(GLcontext *ctx, GLenum target, GLenum pname, GLint * params); /* 277 */
    void (GLAPIENTRYP GetTexGendv)(GLcontext *ctx, GLenum coord, GLenum pname, GLdouble * params); /* 278 */
    void (GLAPIENTRYP GetTexGenfv)(GLcontext *ctx, GLenum coord, GLenum pname, GLfloat * params); /* 279 */
    void (GLAPIENTRYP GetTexGeniv)(GLcontext *ctx, GLenum coord, GLenum pname, GLint * params); /* 280 */
    void (GLAPIENTRYP GetTexImage)(GLcontext *ctx, GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels); /* 281 */
    void (GLAPIENTRYP GetTexParameterfv)(GLcontext *ctx, GLenum target, GLenum pname, GLfloat * params); /* 282 */
    void (GLAPIENTRYP GetTexParameteriv)(GLcontext *ctx, GLenum target, GLenum pname, GLint * params); /* 283 */
    void (GLAPIENTRYP GetTexLevelParameterfv)(GLcontext *ctx, GLenum target, GLint level, GLenum pname, GLfloat * params); /* 284 */
    void (GLAPIENTRYP GetTexLevelParameteriv)(GLcontext *ctx, GLenum target, GLint level, GLenum pname, GLint * params); /* 285 */
    GLboolean(GLAPIENTRYP IsEnabled)(GLcontext *ctx, GLenum cap);  /* 286 */
    GLboolean(GLAPIENTRYP IsList)(GLcontext *ctx, GLuint list);  /* 287 */
    void (GLAPIENTRYP DepthRange)(GLcontext *ctx, GLclampd zNear, GLclampd zFar); /* 288 */
    void (GLAPIENTRYP Frustum)(GLcontext *ctx, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar); /* 289 */
    void (GLAPIENTRYP LoadIdentity)(GLcontext *ctx); /* 290 */
    void (GLAPIENTRYP LoadMatrixf)(GLcontext *ctx, const GLfloat * m); /* 291 */
    void (GLAPIENTRYP LoadMatrixd)(GLcontext *ctx, const GLdouble * m); /* 292 */
    void (GLAPIENTRYP MatrixMode)(GLcontext *ctx, GLenum mode); /* 293 */
    void (GLAPIENTRYP MultMatrixf)(GLcontext *ctx, const GLfloat * m); /* 294 */
    void (GLAPIENTRYP MultMatrixd)(GLcontext *ctx, const GLdouble * m); /* 295 */
    void (GLAPIENTRYP Ortho)(GLcontext *ctx, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar); /* 296 */
    void (GLAPIENTRYP PopMatrix)(GLcontext *ctx); /* 297 */
    void (GLAPIENTRYP PushMatrix)(GLcontext *ctx); /* 298 */
    void (GLAPIENTRYP Rotated)(GLcontext *ctx, GLdouble angle, GLdouble x, GLdouble y, GLdouble z); /* 299 */
    void (GLAPIENTRYP Rotatef)(GLcontext *ctx, GLfloat angle, GLfloat x, GLfloat y, GLfloat z); /* 300 */
    void (GLAPIENTRYP Scaled)(GLcontext *ctx, GLdouble x, GLdouble y, GLdouble z); /* 301 */
    void (GLAPIENTRYP Scalef)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z); /* 302 */
    void (GLAPIENTRYP Translated)(GLcontext *ctx, GLdouble x, GLdouble y, GLdouble z); /* 303 */
    void (GLAPIENTRYP Translatef)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z); /* 304 */
    void (GLAPIENTRYP Viewport)(GLcontext *ctx, GLint x, GLint y, GLsizei width, GLsizei height); /* 305 */
    void (GLAPIENTRYP ArrayElement)(GLcontext *ctx, GLint i); /* 306 */
    void (GLAPIENTRYP BindTexture)(GLcontext *ctx, GLenum target, GLuint texture); /* 307 */
    void (GLAPIENTRYP ColorPointer)(GLcontext *ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer); /* 308 */
    void (GLAPIENTRYP DisableClientState)(GLcontext *ctx, GLenum array); /* 309 */
    void (GLAPIENTRYP DrawArrays)(GLcontext *ctx, GLenum mode, GLint first, GLsizei count); /* 310 */
    void (GLAPIENTRYP DrawElements)(GLcontext *ctx, GLenum mode, GLsizei count, GLenum type, const GLvoid * indices); /* 311 */
    void (GLAPIENTRYP EdgeFlagPointer)(GLcontext *ctx, GLsizei stride, const GLvoid * pointer); /* 312 */
    void (GLAPIENTRYP EnableClientState)(GLcontext *ctx, GLenum array); /* 313 */
    void (GLAPIENTRYP IndexPointer)(GLcontext *ctx, GLenum type, GLsizei stride, const GLvoid * pointer); /* 314 */
    void (GLAPIENTRYP Indexub)(GLcontext *ctx, GLubyte c); /* 315 */
    void (GLAPIENTRYP Indexubv)(GLcontext *ctx, const GLubyte * c); /* 316 */
    void (GLAPIENTRYP InterleavedArrays)(GLcontext *ctx, GLenum format, GLsizei stride, const GLvoid * pointer); /* 317 */
    void (GLAPIENTRYP NormalPointer)(GLcontext *ctx, GLenum type, GLsizei stride, const GLvoid * pointer); /* 318 */
    void (GLAPIENTRYP PolygonOffset)(GLcontext *ctx, GLfloat factor, GLfloat units); /* 319 */
    void (GLAPIENTRYP TexCoordPointer)(GLcontext *ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer); /* 320 */
    void (GLAPIENTRYP VertexPointer)(GLcontext *ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer); /* 321 */
    GLboolean(GLAPIENTRYP AreTexturesResident)(GLcontext *ctx, GLsizei n, const GLuint * textures, GLboolean * residences);  /* 322 */
    void (GLAPIENTRYP CopyTexImage1D)(GLcontext *ctx, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border); /* 323 */
    void (GLAPIENTRYP CopyTexImage2D)(GLcontext *ctx, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border); /* 324 */
    void (GLAPIENTRYP CopyTexSubImage1D)(GLcontext *ctx, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width); /* 325 */
    void (GLAPIENTRYP CopyTexSubImage2D)(GLcontext *ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height); /* 326 */
    void (GLAPIENTRYP DeleteTextures)(GLcontext *ctx, GLsizei n, const GLuint * textures); /* 327 */
    void (GLAPIENTRYP GenTextures)(GLcontext *ctx, GLsizei n, GLuint * textures); /* 328 */
    void (GLAPIENTRYP GetPointerv)(GLcontext *ctx, GLenum pname, GLvoid ** params); /* 329 */
    GLboolean(GLAPIENTRYP IsTexture)(GLcontext *ctx, GLuint texture);  /* 330 */
    void (GLAPIENTRYP PrioritizeTextures)(GLcontext *ctx, GLsizei n, const GLuint * textures, const GLclampf * priorities); /* 331 */
    void (GLAPIENTRYP TexSubImage1D)(GLcontext *ctx, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels); /* 332 */
    void (GLAPIENTRYP TexSubImage2D)(GLcontext *ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels); /* 333 */
    void (GLAPIENTRYP PopClientAttrib)(GLcontext *ctx); /* 334 */
    void (GLAPIENTRYP PushClientAttrib)(GLcontext *ctx, GLbitfield mask); /* 335 */
    void (GLAPIENTRYP BlendColor)(GLcontext *ctx, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha); /* 336 */
    void (GLAPIENTRYP BlendEquation)(GLcontext *ctx, GLenum mode); /* 337 */
    void (GLAPIENTRYP DrawRangeElements)(GLcontext *ctx, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices); /* 338 */
    void (GLAPIENTRYP ColorTable)(GLcontext *ctx, GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * table); /* 339 */
    void (GLAPIENTRYP ColorTableParameterfv)(GLcontext *ctx, GLenum target, GLenum pname, const GLfloat * params); /* 340 */
    void (GLAPIENTRYP ColorTableParameteriv)(GLcontext *ctx, GLenum target, GLenum pname, const GLint * params); /* 341 */
    void (GLAPIENTRYP CopyColorTable)(GLcontext *ctx, GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width); /* 342 */
    void (GLAPIENTRYP GetColorTable)(GLcontext *ctx, GLenum target, GLenum format, GLenum type, GLvoid * table); /* 343 */
    void (GLAPIENTRYP GetColorTableParameterfv)(GLcontext *ctx, GLenum target, GLenum pname, GLfloat * params); /* 344 */
    void (GLAPIENTRYP GetColorTableParameteriv)(GLcontext *ctx, GLenum target, GLenum pname, GLint * params); /* 345 */
    void (GLAPIENTRYP ColorSubTable)(GLcontext *ctx, GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid * data); /* 346 */
    void (GLAPIENTRYP CopyColorSubTable)(GLcontext *ctx, GLenum target, GLsizei start, GLint x, GLint y, GLsizei width); /* 347 */
    void (GLAPIENTRYP ConvolutionFilter1D)(GLcontext *ctx, GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * image); /* 348 */
    void (GLAPIENTRYP ConvolutionFilter2D)(GLcontext *ctx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * image); /* 349 */
    void (GLAPIENTRYP ConvolutionParameterf)(GLcontext *ctx, GLenum target, GLenum pname, GLfloat params); /* 350 */
    void (GLAPIENTRYP ConvolutionParameterfv)(GLcontext *ctx, GLenum target, GLenum pname, const GLfloat * params); /* 351 */
    void (GLAPIENTRYP ConvolutionParameteri)(GLcontext *ctx, GLenum target, GLenum pname, GLint params); /* 352 */
    void (GLAPIENTRYP ConvolutionParameteriv)(GLcontext *ctx, GLenum target, GLenum pname, const GLint * params); /* 353 */
    void (GLAPIENTRYP CopyConvolutionFilter1D)(GLcontext *ctx, GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width); /* 354 */
    void (GLAPIENTRYP CopyConvolutionFilter2D)(GLcontext *ctx, GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height); /* 355 */
    void (GLAPIENTRYP GetConvolutionFilter)(GLcontext *ctx, GLenum target, GLenum format, GLenum type, GLvoid * image); /* 356 */
    void (GLAPIENTRYP GetConvolutionParameterfv)(GLcontext *ctx, GLenum target, GLenum pname, GLfloat * params); /* 357 */
    void (GLAPIENTRYP GetConvolutionParameteriv)(GLcontext *ctx, GLenum target, GLenum pname, GLint * params); /* 358 */
    void (GLAPIENTRYP GetSeparableFilter)(GLcontext *ctx, GLenum target, GLenum format, GLenum type, GLvoid * row, GLvoid * column, GLvoid * span); /* 359 */
    void (GLAPIENTRYP SeparableFilter2D)(GLcontext *ctx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * row, const GLvoid * column); /* 360 */
    void (GLAPIENTRYP GetHistogram)(GLcontext *ctx, GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values); /* 361 */
    void (GLAPIENTRYP GetHistogramParameterfv)(GLcontext *ctx, GLenum target, GLenum pname, GLfloat * params); /* 362 */
    void (GLAPIENTRYP GetHistogramParameteriv)(GLcontext *ctx, GLenum target, GLenum pname, GLint * params); /* 363 */
    void (GLAPIENTRYP GetMinmax)(GLcontext *ctx, GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values); /* 364 */
    void (GLAPIENTRYP GetMinmaxParameterfv)(GLcontext *ctx, GLenum target, GLenum pname, GLfloat * params); /* 365 */
    void (GLAPIENTRYP GetMinmaxParameteriv)(GLcontext *ctx, GLenum target, GLenum pname, GLint * params); /* 366 */
    void (GLAPIENTRYP Histogram)(GLcontext *ctx, GLenum target, GLsizei width, GLenum internalformat, GLboolean sink); /* 367 */
    void (GLAPIENTRYP Minmax)(GLcontext *ctx, GLenum target, GLenum internalformat, GLboolean sink); /* 368 */
    void (GLAPIENTRYP ResetHistogram)(GLcontext *ctx, GLenum target); /* 369 */
    void (GLAPIENTRYP ResetMinmax)(GLcontext *ctx, GLenum target); /* 370 */
    void (GLAPIENTRYP TexImage3D)(GLcontext *ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels); /* 371 */
    void (GLAPIENTRYP TexSubImage3D)(GLcontext *ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels); /* 372 */
    void (GLAPIENTRYP CopyTexSubImage3D)(GLcontext *ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height); /* 373 */
    void (GLAPIENTRYP ActiveTextureARB)(GLcontext *ctx, GLenum texture); /* 374 */
    void (GLAPIENTRYP ClientActiveTextureARB)(GLcontext *ctx, GLenum texture); /* 375 */
    void (GLAPIENTRYP MultiTexCoord1dARB)(GLcontext *ctx, GLenum target, GLdouble s); /* 376 */
    void (GLAPIENTRYP MultiTexCoord1dvARB)(GLcontext *ctx, GLenum target, const GLdouble * v); /* 377 */
    void (GLAPIENTRYP MultiTexCoord1fARB)(GLcontext *ctx, GLenum target, GLfloat s); /* 378 */
    void (GLAPIENTRYP MultiTexCoord1fvARB)(GLcontext *ctx, GLenum target, const GLfloat * v); /* 379 */
    void (GLAPIENTRYP MultiTexCoord1iARB)(GLcontext *ctx, GLenum target, GLint s); /* 380 */
    void (GLAPIENTRYP MultiTexCoord1ivARB)(GLcontext *ctx, GLenum target, const GLint * v); /* 381 */
    void (GLAPIENTRYP MultiTexCoord1sARB)(GLcontext *ctx, GLenum target, GLshort s); /* 382 */
    void (GLAPIENTRYP MultiTexCoord1svARB)(GLcontext *ctx, GLenum target, const GLshort * v); /* 383 */
    void (GLAPIENTRYP MultiTexCoord2dARB)(GLcontext *ctx, GLenum target, GLdouble s, GLdouble t); /* 384 */
    void (GLAPIENTRYP MultiTexCoord2dvARB)(GLcontext *ctx, GLenum target, const GLdouble * v); /* 385 */
    void (GLAPIENTRYP MultiTexCoord2fARB)(GLcontext *ctx, GLenum target, GLfloat s, GLfloat t); /* 386 */
    void (GLAPIENTRYP MultiTexCoord2fvARB)(GLcontext *ctx, GLenum target, const GLfloat * v); /* 387 */
    void (GLAPIENTRYP MultiTexCoord2iARB)(GLcontext *ctx, GLenum target, GLint s, GLint t); /* 388 */
    void (GLAPIENTRYP MultiTexCoord2ivARB)(GLcontext *ctx, GLenum target, const GLint * v); /* 389 */
    void (GLAPIENTRYP MultiTexCoord2sARB)(GLcontext *ctx, GLenum target, GLshort s, GLshort t); /* 390 */
    void (GLAPIENTRYP MultiTexCoord2svARB)(GLcontext *ctx, GLenum target, const GLshort * v); /* 391 */
    void (GLAPIENTRYP MultiTexCoord3dARB)(GLcontext *ctx, GLenum target, GLdouble s, GLdouble t, GLdouble r); /* 392 */
    void (GLAPIENTRYP MultiTexCoord3dvARB)(GLcontext *ctx, GLenum target, const GLdouble * v); /* 393 */
    void (GLAPIENTRYP MultiTexCoord3fARB)(GLcontext *ctx, GLenum target, GLfloat s, GLfloat t, GLfloat r); /* 394 */
    void (GLAPIENTRYP MultiTexCoord3fvARB)(GLcontext *ctx, GLenum target, const GLfloat * v); /* 395 */
    void (GLAPIENTRYP MultiTexCoord3iARB)(GLcontext *ctx, GLenum target, GLint s, GLint t, GLint r); /* 396 */
    void (GLAPIENTRYP MultiTexCoord3ivARB)(GLcontext *ctx, GLenum target, const GLint * v); /* 397 */
    void (GLAPIENTRYP MultiTexCoord3sARB)(GLcontext *ctx, GLenum target, GLshort s, GLshort t, GLshort r); /* 398 */
    void (GLAPIENTRYP MultiTexCoord3svARB)(GLcontext *ctx, GLenum target, const GLshort * v); /* 399 */
    void (GLAPIENTRYP MultiTexCoord4dARB)(GLcontext *ctx, GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q); /* 400 */
    void (GLAPIENTRYP MultiTexCoord4dvARB)(GLcontext *ctx, GLenum target, const GLdouble * v); /* 401 */
    void (GLAPIENTRYP MultiTexCoord4fARB)(GLcontext *ctx, GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q); /* 402 */
    void (GLAPIENTRYP MultiTexCoord4fvARB)(GLcontext *ctx, GLenum target, const GLfloat * v); /* 403 */
    void (GLAPIENTRYP MultiTexCoord4iARB)(GLcontext *ctx, GLenum target, GLint s, GLint t, GLint r, GLint q); /* 404 */
    void (GLAPIENTRYP MultiTexCoord4ivARB)(GLcontext *ctx, GLenum target, const GLint * v); /* 405 */
    void (GLAPIENTRYP MultiTexCoord4sARB)(GLcontext *ctx, GLenum target, GLshort s, GLshort t, GLshort r, GLshort q); /* 406 */
    void (GLAPIENTRYP MultiTexCoord4svARB)(GLcontext *ctx, GLenum target, const GLshort * v); /* 407 */
    void (GLAPIENTRYP AttachShader)(GLcontext *ctx, GLuint program, GLuint shader); /* 408 */
    GLuint(GLAPIENTRYP CreateProgram)(GLcontext *ctx);  /* 409 */
    GLuint(GLAPIENTRYP CreateShader)(GLcontext *ctx, GLenum type);  /* 410 */
    void (GLAPIENTRYP DeleteProgram)(GLcontext *ctx, GLuint program); /* 411 */
    void (GLAPIENTRYP DeleteShader)(GLcontext *ctx, GLuint program); /* 412 */
    void (GLAPIENTRYP DetachShader)(GLcontext *ctx, GLuint program, GLuint shader); /* 413 */
    void (GLAPIENTRYP GetAttachedShaders)(GLcontext *ctx, GLuint program, GLsizei maxCount, GLsizei * count, GLuint * obj); /* 414 */
    void (GLAPIENTRYP GetProgramInfoLog)(GLcontext *ctx, GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog); /* 415 */
    void (GLAPIENTRYP GetProgramiv)(GLcontext *ctx, GLuint program, GLenum pname, GLint * params); /* 416 */
    void (GLAPIENTRYP GetShaderInfoLog)(GLcontext *ctx, GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog); /* 417 */
    void (GLAPIENTRYP GetShaderiv)(GLcontext *ctx, GLuint shader, GLenum pname, GLint * params); /* 418 */
    GLboolean(GLAPIENTRYP IsProgram)(GLcontext *ctx, GLuint program);  /* 419 */
    GLboolean(GLAPIENTRYP IsShader)(GLcontext *ctx, GLuint shader);  /* 420 */
    void (GLAPIENTRYP StencilFuncSeparate)(GLcontext *ctx, GLenum face, GLenum func, GLint ref, GLuint mask); /* 421 */
    void (GLAPIENTRYP StencilMaskSeparate)(GLcontext *ctx, GLenum face, GLuint mask); /* 422 */
    void (GLAPIENTRYP StencilOpSeparate)(GLcontext *ctx, GLenum face, GLenum sfail, GLenum zfail, GLenum zpass); /* 423 */
    void (GLAPIENTRYP UniformMatrix2x3fv)(GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value); /* 424 */
    void (GLAPIENTRYP UniformMatrix2x4fv)(GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value); /* 425 */
    void (GLAPIENTRYP UniformMatrix3x2fv)(GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value); /* 426 */
    void (GLAPIENTRYP UniformMatrix3x4fv)(GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value); /* 427 */
    void (GLAPIENTRYP UniformMatrix4x2fv)(GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value); /* 428 */
    void (GLAPIENTRYP UniformMatrix4x3fv)(GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value); /* 429 */
    void (GLAPIENTRYP LoadTransposeMatrixdARB)(GLcontext *ctx, const GLdouble * m); /* 430 */
    void (GLAPIENTRYP LoadTransposeMatrixfARB)(GLcontext *ctx, const GLfloat * m); /* 431 */
    void (GLAPIENTRYP MultTransposeMatrixdARB)(GLcontext *ctx, const GLdouble * m); /* 432 */
    void (GLAPIENTRYP MultTransposeMatrixfARB)(GLcontext *ctx, const GLfloat * m); /* 433 */
    void (GLAPIENTRYP SampleCoverageARB)(GLcontext *ctx, GLclampf value, GLboolean invert); /* 434 */
    void (GLAPIENTRYP CompressedTexImage1DARB)(GLcontext *ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid * data); /* 435 */
    void (GLAPIENTRYP CompressedTexImage2DARB)(GLcontext *ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data); /* 436 */
    void (GLAPIENTRYP CompressedTexImage3DARB)(GLcontext *ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data); /* 437 */
    void (GLAPIENTRYP CompressedTexSubImage1DARB)(GLcontext *ctx, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data); /* 438 */
    void (GLAPIENTRYP CompressedTexSubImage2DARB)(GLcontext *ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data); /* 439 */
    void (GLAPIENTRYP CompressedTexSubImage3DARB)(GLcontext *ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data); /* 440 */
    void (GLAPIENTRYP GetCompressedTexImageARB)(GLcontext *ctx, GLenum target, GLint level, GLvoid * img); /* 441 */
    void (GLAPIENTRYP DisableVertexAttribArrayARB)(GLcontext *ctx, GLuint index); /* 442 */
    void (GLAPIENTRYP EnableVertexAttribArrayARB)(GLcontext *ctx, GLuint index); /* 443 */
    void (GLAPIENTRYP GetProgramEnvParameterdvARB)(GLcontext *ctx, GLenum target, GLuint index, GLdouble * params); /* 444 */
    void (GLAPIENTRYP GetProgramEnvParameterfvARB)(GLcontext *ctx, GLenum target, GLuint index, GLfloat * params); /* 445 */
    void (GLAPIENTRYP GetProgramLocalParameterdvARB)(GLcontext *ctx, GLenum target, GLuint index, GLdouble * params); /* 446 */
    void (GLAPIENTRYP GetProgramLocalParameterfvARB)(GLcontext *ctx, GLenum target, GLuint index, GLfloat * params); /* 447 */
    void (GLAPIENTRYP GetProgramStringARB)(GLcontext *ctx, GLenum target, GLenum pname, GLvoid * string); /* 448 */
    void (GLAPIENTRYP GetProgramivARB)(GLcontext *ctx, GLenum target, GLenum pname, GLint * params); /* 449 */
    void (GLAPIENTRYP GetVertexAttribdvARB)(GLcontext *ctx, GLuint index, GLenum pname, GLdouble * params); /* 450 */
    void (GLAPIENTRYP GetVertexAttribfvARB)(GLcontext *ctx, GLuint index, GLenum pname, GLfloat * params); /* 451 */
    void (GLAPIENTRYP GetVertexAttribivARB)(GLcontext *ctx, GLuint index, GLenum pname, GLint * params); /* 452 */
    void (GLAPIENTRYP ProgramEnvParameter4dARB)(GLcontext *ctx, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w); /* 453 */
    void (GLAPIENTRYP ProgramEnvParameter4dvARB)(GLcontext *ctx, GLenum target, GLuint index, const GLdouble * params); /* 454 */
    void (GLAPIENTRYP ProgramEnvParameter4fARB)(GLcontext *ctx, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w); /* 455 */
    void (GLAPIENTRYP ProgramEnvParameter4fvARB)(GLcontext *ctx, GLenum target, GLuint index, const GLfloat * params); /* 456 */
    void (GLAPIENTRYP ProgramLocalParameter4dARB)(GLcontext *ctx, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w); /* 457 */
    void (GLAPIENTRYP ProgramLocalParameter4dvARB)(GLcontext *ctx, GLenum target, GLuint index, const GLdouble * params); /* 458 */
    void (GLAPIENTRYP ProgramLocalParameter4fARB)(GLcontext *ctx, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w); /* 459 */
    void (GLAPIENTRYP ProgramLocalParameter4fvARB)(GLcontext *ctx, GLenum target, GLuint index, const GLfloat * params); /* 460 */
    void (GLAPIENTRYP ProgramStringARB)(GLcontext *ctx, GLenum target, GLenum format, GLsizei len, const GLvoid * string); /* 461 */
    void (GLAPIENTRYP VertexAttrib1dARB)(GLcontext *ctx, GLuint index, GLdouble x); /* 462 */
    void (GLAPIENTRYP VertexAttrib1dvARB)(GLcontext *ctx, GLuint index, const GLdouble * v); /* 463 */
    void (GLAPIENTRYP VertexAttrib1fARB)(GLcontext *ctx, GLuint index, GLfloat x); /* 464 */
    void (GLAPIENTRYP VertexAttrib1fvARB)(GLcontext *ctx, GLuint index, const GLfloat * v); /* 465 */
    void (GLAPIENTRYP VertexAttrib1sARB)(GLcontext *ctx, GLuint index, GLshort x); /* 466 */
    void (GLAPIENTRYP VertexAttrib1svARB)(GLcontext *ctx, GLuint index, const GLshort * v); /* 467 */
    void (GLAPIENTRYP VertexAttrib2dARB)(GLcontext *ctx, GLuint index, GLdouble x, GLdouble y); /* 468 */
    void (GLAPIENTRYP VertexAttrib2dvARB)(GLcontext *ctx, GLuint index, const GLdouble * v); /* 469 */
    void (GLAPIENTRYP VertexAttrib2fARB)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y); /* 470 */
    void (GLAPIENTRYP VertexAttrib2fvARB)(GLcontext *ctx, GLuint index, const GLfloat * v); /* 471 */
    void (GLAPIENTRYP VertexAttrib2sARB)(GLcontext *ctx, GLuint index, GLshort x, GLshort y); /* 472 */
    void (GLAPIENTRYP VertexAttrib2svARB)(GLcontext *ctx, GLuint index, const GLshort * v); /* 473 */
    void (GLAPIENTRYP VertexAttrib3dARB)(GLcontext *ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z); /* 474 */
    void (GLAPIENTRYP VertexAttrib3dvARB)(GLcontext *ctx, GLuint index, const GLdouble * v); /* 475 */
    void (GLAPIENTRYP VertexAttrib3fARB)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z); /* 476 */
    void (GLAPIENTRYP VertexAttrib3fvARB)(GLcontext *ctx, GLuint index, const GLfloat * v); /* 477 */
    void (GLAPIENTRYP VertexAttrib3sARB)(GLcontext *ctx, GLuint index, GLshort x, GLshort y, GLshort z); /* 478 */
    void (GLAPIENTRYP VertexAttrib3svARB)(GLcontext *ctx, GLuint index, const GLshort * v); /* 479 */
    void (GLAPIENTRYP VertexAttrib4NbvARB)(GLcontext *ctx, GLuint index, const GLbyte * v); /* 480 */
    void (GLAPIENTRYP VertexAttrib4NivARB)(GLcontext *ctx, GLuint index, const GLint * v); /* 481 */
    void (GLAPIENTRYP VertexAttrib4NsvARB)(GLcontext *ctx, GLuint index, const GLshort * v); /* 482 */
    void (GLAPIENTRYP VertexAttrib4NubARB)(GLcontext *ctx, GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w); /* 483 */
    void (GLAPIENTRYP VertexAttrib4NubvARB)(GLcontext *ctx, GLuint index, const GLubyte * v); /* 484 */
    void (GLAPIENTRYP VertexAttrib4NuivARB)(GLcontext *ctx, GLuint index, const GLuint * v); /* 485 */
    void (GLAPIENTRYP VertexAttrib4NusvARB)(GLcontext *ctx, GLuint index, const GLushort * v); /* 486 */
    void (GLAPIENTRYP VertexAttrib4bvARB)(GLcontext *ctx, GLuint index, const GLbyte * v); /* 487 */
    void (GLAPIENTRYP VertexAttrib4dARB)(GLcontext *ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w); /* 488 */
    void (GLAPIENTRYP VertexAttrib4dvARB)(GLcontext *ctx, GLuint index, const GLdouble * v); /* 489 */
    void (GLAPIENTRYP VertexAttrib4fARB)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w); /* 490 */
    void (GLAPIENTRYP VertexAttrib4fvARB)(GLcontext *ctx, GLuint index, const GLfloat * v); /* 491 */
    void (GLAPIENTRYP VertexAttrib4ivARB)(GLcontext *ctx, GLuint index, const GLint * v); /* 492 */
    void (GLAPIENTRYP VertexAttrib4sARB)(GLcontext *ctx, GLuint index, GLshort x, GLshort y, GLshort z, GLshort w); /* 493 */
    void (GLAPIENTRYP VertexAttrib4svARB)(GLcontext *ctx, GLuint index, const GLshort * v); /* 494 */
    void (GLAPIENTRYP VertexAttrib4ubvARB)(GLcontext *ctx, GLuint index, const GLubyte * v); /* 495 */
    void (GLAPIENTRYP VertexAttrib4uivARB)(GLcontext *ctx, GLuint index, const GLuint * v); /* 496 */
    void (GLAPIENTRYP VertexAttrib4usvARB)(GLcontext *ctx, GLuint index, const GLushort * v); /* 497 */
    void (GLAPIENTRYP VertexAttribPointerARB)(GLcontext *ctx, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer); /* 498 */
    void (GLAPIENTRYP BindBufferARB)(GLcontext *ctx, GLenum target, GLuint buffer); /* 499 */
    void (GLAPIENTRYP BufferDataARB)(GLcontext *ctx, GLenum target, GLsizeiptrARB size, const GLvoid * data, GLenum usage); /* 500 */
    void (GLAPIENTRYP BufferSubDataARB)(GLcontext *ctx, GLenum target, GLintptrARB offset, GLsizeiptrARB size, const GLvoid * data); /* 501 */
    void (GLAPIENTRYP DeleteBuffersARB)(GLcontext *ctx, GLsizei n, const GLuint * buffer); /* 502 */
    void (GLAPIENTRYP GenBuffersARB)(GLcontext *ctx, GLsizei n, GLuint * buffer); /* 503 */
    void (GLAPIENTRYP GetBufferParameterivARB)(GLcontext *ctx, GLenum target, GLenum pname, GLint * params); /* 504 */
    void (GLAPIENTRYP GetBufferPointervARB)(GLcontext *ctx, GLenum target, GLenum pname, GLvoid ** params); /* 505 */
    void (GLAPIENTRYP GetBufferSubDataARB)(GLcontext *ctx, GLenum target, GLintptrARB offset, GLsizeiptrARB size, GLvoid * data); /* 506 */
    GLboolean(GLAPIENTRYP IsBufferARB)(GLcontext *ctx, GLuint buffer);  /* 507 */
    GLvoid * (GLAPIENTRYP MapBufferARB)(GLcontext *ctx, GLenum target, GLenum access); /* 508 */
    GLboolean(GLAPIENTRYP UnmapBufferARB)(GLcontext *ctx, GLenum target);  /* 509 */
    void (GLAPIENTRYP BeginQueryARB)(GLcontext *ctx, GLenum target, GLuint id); /* 510 */
    void (GLAPIENTRYP DeleteQueriesARB)(GLcontext *ctx, GLsizei n, const GLuint * ids); /* 511 */
    void (GLAPIENTRYP EndQueryARB)(GLcontext *ctx, GLenum target); /* 512 */
    void (GLAPIENTRYP GenQueriesARB)(GLcontext *ctx, GLsizei n, GLuint * ids); /* 513 */
    void (GLAPIENTRYP GetQueryObjectivARB)(GLcontext *ctx, GLuint id, GLenum pname, GLint * params); /* 514 */
    void (GLAPIENTRYP GetQueryObjectuivARB)(GLcontext *ctx, GLuint id, GLenum pname, GLuint * params); /* 515 */
    void (GLAPIENTRYP GetQueryivARB)(GLcontext *ctx, GLenum target, GLenum pname, GLint * params); /* 516 */
    GLboolean(GLAPIENTRYP IsQueryARB)(GLcontext *ctx, GLuint id);  /* 517 */
    void (GLAPIENTRYP AttachObjectARB)(GLcontext *ctx, GLhandleARB containerObj, GLhandleARB obj); /* 518 */
    void (GLAPIENTRYP CompileShaderARB)(GLcontext *ctx, GLhandleARB shader); /* 519 */
    GLhandleARB(GLAPIENTRYP CreateProgramObjectARB)(GLcontext *ctx);  /* 520 */
    GLhandleARB(GLAPIENTRYP CreateShaderObjectARB)(GLcontext *ctx, GLenum shaderType);  /* 521 */
    void (GLAPIENTRYP DeleteObjectARB)(GLcontext *ctx, GLhandleARB obj); /* 522 */
    void (GLAPIENTRYP DetachObjectARB)(GLcontext *ctx, GLhandleARB containerObj, GLhandleARB attachedObj); /* 523 */
    void (GLAPIENTRYP GetActiveUniformARB)(GLcontext *ctx, GLhandleARB program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLcharARB * name); /* 524 */
    void (GLAPIENTRYP GetAttachedObjectsARB)(GLcontext *ctx, GLhandleARB containerObj, GLsizei maxLength, GLsizei * length, GLhandleARB * infoLog); /* 525 */
    GLhandleARB(GLAPIENTRYP GetHandleARB)(GLcontext *ctx, GLenum pname);  /* 526 */
    void (GLAPIENTRYP GetInfoLogARB)(GLcontext *ctx, GLhandleARB obj, GLsizei maxLength, GLsizei * length, GLcharARB * infoLog); /* 527 */
    void (GLAPIENTRYP GetObjectParameterfvARB)(GLcontext *ctx, GLhandleARB obj, GLenum pname, GLfloat * params); /* 528 */
    void (GLAPIENTRYP GetObjectParameterivARB)(GLcontext *ctx, GLhandleARB obj, GLenum pname, GLint * params); /* 529 */
    void (GLAPIENTRYP GetShaderSourceARB)(GLcontext *ctx, GLhandleARB shader, GLsizei bufSize, GLsizei * length, GLcharARB * source); /* 530 */
    GLint(GLAPIENTRYP GetUniformLocationARB)(GLcontext *ctx, GLhandleARB program, const GLcharARB * name);  /* 531 */
    void (GLAPIENTRYP GetUniformfvARB)(GLcontext *ctx, GLhandleARB program, GLint location, GLfloat * params); /* 532 */
    void (GLAPIENTRYP GetUniformivARB)(GLcontext *ctx, GLhandleARB program, GLint location, GLint * params); /* 533 */
    void (GLAPIENTRYP LinkProgramARB)(GLcontext *ctx, GLhandleARB program); /* 534 */
    void (GLAPIENTRYP ShaderSourceARB)(GLcontext *ctx, GLhandleARB shader, GLsizei count, const GLcharARB ** string, const GLint * length); /* 535 */
    void (GLAPIENTRYP Uniform1fARB)(GLcontext *ctx, GLint location, GLfloat v0); /* 536 */
    void (GLAPIENTRYP Uniform1fvARB)(GLcontext *ctx, GLint location, GLsizei count, const GLfloat * value); /* 537 */
    void (GLAPIENTRYP Uniform1iARB)(GLcontext *ctx, GLint location, GLint v0); /* 538 */
    void (GLAPIENTRYP Uniform1ivARB)(GLcontext *ctx, GLint location, GLsizei count, const GLint * value); /* 539 */
    void (GLAPIENTRYP Uniform2fARB)(GLcontext *ctx, GLint location, GLfloat v0, GLfloat v1); /* 540 */
    void (GLAPIENTRYP Uniform2fvARB)(GLcontext *ctx, GLint location, GLsizei count, const GLfloat * value); /* 541 */
    void (GLAPIENTRYP Uniform2iARB)(GLcontext *ctx, GLint location, GLint v0, GLint v1); /* 542 */
    void (GLAPIENTRYP Uniform2ivARB)(GLcontext *ctx, GLint location, GLsizei count, const GLint * value); /* 543 */
    void (GLAPIENTRYP Uniform3fARB)(GLcontext *ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2); /* 544 */
    void (GLAPIENTRYP Uniform3fvARB)(GLcontext *ctx, GLint location, GLsizei count, const GLfloat * value); /* 545 */
    void (GLAPIENTRYP Uniform3iARB)(GLcontext *ctx, GLint location, GLint v0, GLint v1, GLint v2); /* 546 */
    void (GLAPIENTRYP Uniform3ivARB)(GLcontext *ctx, GLint location, GLsizei count, const GLint * value); /* 547 */
    void (GLAPIENTRYP Uniform4fARB)(GLcontext *ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3); /* 548 */
    void (GLAPIENTRYP Uniform4fvARB)(GLcontext *ctx, GLint location, GLsizei count, const GLfloat * value); /* 549 */
    void (GLAPIENTRYP Uniform4iARB)(GLcontext *ctx, GLint location, GLint v0, GLint v1, GLint v2, GLint v3); /* 550 */
    void (GLAPIENTRYP Uniform4ivARB)(GLcontext *ctx, GLint location, GLsizei count, const GLint * value); /* 551 */
    void (GLAPIENTRYP UniformMatrix2fvARB)(GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value); /* 552 */
    void (GLAPIENTRYP UniformMatrix3fvARB)(GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value); /* 553 */
    void (GLAPIENTRYP UniformMatrix4fvARB)(GLcontext *ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value); /* 554 */
    void (GLAPIENTRYP UseProgramObjectARB)(GLcontext *ctx, GLhandleARB program); /* 555 */
    void (GLAPIENTRYP ValidateProgramARB)(GLcontext *ctx, GLhandleARB program); /* 556 */
    void (GLAPIENTRYP BindAttribLocationARB)(GLcontext *ctx, GLhandleARB program, GLuint index, const GLcharARB * name); /* 557 */
    void (GLAPIENTRYP GetActiveAttribARB)(GLcontext *ctx, GLhandleARB program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLcharARB * name); /* 558 */
    GLint(GLAPIENTRYP GetAttribLocationARB)(GLcontext *ctx, GLhandleARB program, const GLcharARB * name);  /* 559 */
    void (GLAPIENTRYP DrawBuffersARB)(GLcontext *ctx, GLsizei n, const GLenum * bufs); /* 560 */
    void (GLAPIENTRYP PolygonOffsetEXT)(GLcontext *ctx, GLfloat factor, GLfloat bias); /* 561 */
    void (GLAPIENTRYP GetPixelTexGenParameterfvSGIS)(GLcontext *ctx, GLenum pname, GLfloat * params); /* 562 */
    void (GLAPIENTRYP GetPixelTexGenParameterivSGIS)(GLcontext *ctx, GLenum pname, GLint * params); /* 563 */
    void (GLAPIENTRYP PixelTexGenParameterfSGIS)(GLcontext *ctx, GLenum pname, GLfloat param); /* 564 */
    void (GLAPIENTRYP PixelTexGenParameterfvSGIS)(GLcontext *ctx, GLenum pname, const GLfloat * params); /* 565 */
    void (GLAPIENTRYP PixelTexGenParameteriSGIS)(GLcontext *ctx, GLenum pname, GLint param); /* 566 */
    void (GLAPIENTRYP PixelTexGenParameterivSGIS)(GLcontext *ctx, GLenum pname, const GLint * params); /* 567 */
    void (GLAPIENTRYP SampleMaskSGIS)(GLcontext *ctx, GLclampf value, GLboolean invert); /* 568 */
    void (GLAPIENTRYP SamplePatternSGIS)(GLcontext *ctx, GLenum pattern); /* 569 */
    void (GLAPIENTRYP ColorPointerEXT)(GLcontext *ctx, GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer); /* 570 */
    void (GLAPIENTRYP EdgeFlagPointerEXT)(GLcontext *ctx, GLsizei stride, GLsizei count, const GLboolean * pointer); /* 571 */
    void (GLAPIENTRYP IndexPointerEXT)(GLcontext *ctx, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer); /* 572 */
    void (GLAPIENTRYP NormalPointerEXT)(GLcontext *ctx, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer); /* 573 */
    void (GLAPIENTRYP TexCoordPointerEXT)(GLcontext *ctx, GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer); /* 574 */
    void (GLAPIENTRYP VertexPointerEXT)(GLcontext *ctx, GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer); /* 575 */
    void (GLAPIENTRYP PointParameterfEXT)(GLcontext *ctx, GLenum pname, GLfloat param); /* 576 */
    void (GLAPIENTRYP PointParameterfvEXT)(GLcontext *ctx, GLenum pname, const GLfloat * params); /* 577 */
    void (GLAPIENTRYP LockArraysEXT)(GLcontext *ctx, GLint first, GLsizei count); /* 578 */
    void (GLAPIENTRYP UnlockArraysEXT)(GLcontext *ctx); /* 579 */
    void (GLAPIENTRYP CullParameterdvEXT)(GLcontext *ctx, GLenum pname, GLdouble * params); /* 580 */
    void (GLAPIENTRYP CullParameterfvEXT)(GLcontext *ctx, GLenum pname, GLfloat * params); /* 581 */
    void (GLAPIENTRYP SecondaryColor3bEXT)(GLcontext *ctx, GLbyte red, GLbyte green, GLbyte blue); /* 582 */
    void (GLAPIENTRYP SecondaryColor3bvEXT)(GLcontext *ctx, const GLbyte * v); /* 583 */
    void (GLAPIENTRYP SecondaryColor3dEXT)(GLcontext *ctx, GLdouble red, GLdouble green, GLdouble blue); /* 584 */
    void (GLAPIENTRYP SecondaryColor3dvEXT)(GLcontext *ctx, const GLdouble * v); /* 585 */
    void (GLAPIENTRYP SecondaryColor3fEXT)(GLcontext *ctx, GLfloat red, GLfloat green, GLfloat blue); /* 586 */
    void (GLAPIENTRYP SecondaryColor3fvEXT)(GLcontext *ctx, const GLfloat * v); /* 587 */
    void (GLAPIENTRYP SecondaryColor3iEXT)(GLcontext *ctx, GLint red, GLint green, GLint blue); /* 588 */
    void (GLAPIENTRYP SecondaryColor3ivEXT)(GLcontext *ctx, const GLint * v); /* 589 */
    void (GLAPIENTRYP SecondaryColor3sEXT)(GLcontext *ctx, GLshort red, GLshort green, GLshort blue); /* 590 */
    void (GLAPIENTRYP SecondaryColor3svEXT)(GLcontext *ctx, const GLshort * v); /* 591 */
    void (GLAPIENTRYP SecondaryColor3ubEXT)(GLcontext *ctx, GLubyte red, GLubyte green, GLubyte blue); /* 592 */
    void (GLAPIENTRYP SecondaryColor3ubvEXT)(GLcontext *ctx, const GLubyte * v); /* 593 */
    void (GLAPIENTRYP SecondaryColor3uiEXT)(GLcontext *ctx, GLuint red, GLuint green, GLuint blue); /* 594 */
    void (GLAPIENTRYP SecondaryColor3uivEXT)(GLcontext *ctx, const GLuint * v); /* 595 */
    void (GLAPIENTRYP SecondaryColor3usEXT)(GLcontext *ctx, GLushort red, GLushort green, GLushort blue); /* 596 */
    void (GLAPIENTRYP SecondaryColor3usvEXT)(GLcontext *ctx, const GLushort * v); /* 597 */
    void (GLAPIENTRYP SecondaryColorPointerEXT)(GLcontext *ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer); /* 598 */
    void (GLAPIENTRYP MultiDrawArraysEXT)(GLcontext *ctx, GLenum mode, GLint * first, GLsizei * count, GLsizei primcount); /* 599 */
    void (GLAPIENTRYP MultiDrawElementsEXT)(GLcontext *ctx, GLenum mode, const GLsizei * count, GLenum type, const GLvoid ** indices, GLsizei primcount); /* 600 */
    void (GLAPIENTRYP FogCoordPointerEXT)(GLcontext *ctx, GLenum type, GLsizei stride, const GLvoid * pointer); /* 601 */
    void (GLAPIENTRYP FogCoorddEXT)(GLcontext *ctx, GLdouble coord); /* 602 */
    void (GLAPIENTRYP FogCoorddvEXT)(GLcontext *ctx, const GLdouble * coord); /* 603 */
    void (GLAPIENTRYP FogCoordfEXT)(GLcontext *ctx, GLfloat coord); /* 604 */
    void (GLAPIENTRYP FogCoordfvEXT)(GLcontext *ctx, const GLfloat * coord); /* 605 */
    void (GLAPIENTRYP PixelTexGenSGIX)(GLcontext *ctx, GLenum mode); /* 606 */
    void (GLAPIENTRYP BlendFuncSeparateEXT)(GLcontext *ctx, GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha); /* 607 */
    void (GLAPIENTRYP FlushVertexArrayRangeNV)(GLcontext *ctx); /* 608 */
    void (GLAPIENTRYP VertexArrayRangeNV)(GLcontext *ctx, GLsizei length, const GLvoid * pointer); /* 609 */
    void (GLAPIENTRYP CombinerInputNV)(GLcontext *ctx, GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage); /* 610 */
    void (GLAPIENTRYP CombinerOutputNV)(GLcontext *ctx, GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum); /* 611 */
    void (GLAPIENTRYP CombinerParameterfNV)(GLcontext *ctx, GLenum pname, GLfloat param); /* 612 */
    void (GLAPIENTRYP CombinerParameterfvNV)(GLcontext *ctx, GLenum pname, const GLfloat * params); /* 613 */
    void (GLAPIENTRYP CombinerParameteriNV)(GLcontext *ctx, GLenum pname, GLint param); /* 614 */
    void (GLAPIENTRYP CombinerParameterivNV)(GLcontext *ctx, GLenum pname, const GLint * params); /* 615 */
    void (GLAPIENTRYP FinalCombinerInputNV)(GLcontext *ctx, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage); /* 616 */
    void (GLAPIENTRYP GetCombinerInputParameterfvNV)(GLcontext *ctx, GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat * params); /* 617 */
    void (GLAPIENTRYP GetCombinerInputParameterivNV)(GLcontext *ctx, GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint * params); /* 618 */
    void (GLAPIENTRYP GetCombinerOutputParameterfvNV)(GLcontext *ctx, GLenum stage, GLenum portion, GLenum pname, GLfloat * params); /* 619 */
    void (GLAPIENTRYP GetCombinerOutputParameterivNV)(GLcontext *ctx, GLenum stage, GLenum portion, GLenum pname, GLint * params); /* 620 */
    void (GLAPIENTRYP GetFinalCombinerInputParameterfvNV)(GLcontext *ctx, GLenum variable, GLenum pname, GLfloat * params); /* 621 */
    void (GLAPIENTRYP GetFinalCombinerInputParameterivNV)(GLcontext *ctx, GLenum variable, GLenum pname, GLint * params); /* 622 */
    void (GLAPIENTRYP ResizeBuffersMESA)(GLcontext *ctx); /* 623 */
    void (GLAPIENTRYP WindowPos2dMESA)(GLcontext *ctx, GLdouble x, GLdouble y); /* 624 */
    void (GLAPIENTRYP WindowPos2dvMESA)(GLcontext *ctx, const GLdouble * v); /* 625 */
    void (GLAPIENTRYP WindowPos2fMESA)(GLcontext *ctx, GLfloat x, GLfloat y); /* 626 */
    void (GLAPIENTRYP WindowPos2fvMESA)(GLcontext *ctx, const GLfloat * v); /* 627 */
    void (GLAPIENTRYP WindowPos2iMESA)(GLcontext *ctx, GLint x, GLint y); /* 628 */
    void (GLAPIENTRYP WindowPos2ivMESA)(GLcontext *ctx, const GLint * v); /* 629 */
    void (GLAPIENTRYP WindowPos2sMESA)(GLcontext *ctx, GLshort x, GLshort y); /* 630 */
    void (GLAPIENTRYP WindowPos2svMESA)(GLcontext *ctx, const GLshort * v); /* 631 */
    void (GLAPIENTRYP WindowPos3dMESA)(GLcontext *ctx, GLdouble x, GLdouble y, GLdouble z); /* 632 */
    void (GLAPIENTRYP WindowPos3dvMESA)(GLcontext *ctx, const GLdouble * v); /* 633 */
    void (GLAPIENTRYP WindowPos3fMESA)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z); /* 634 */
    void (GLAPIENTRYP WindowPos3fvMESA)(GLcontext *ctx, const GLfloat * v); /* 635 */
    void (GLAPIENTRYP WindowPos3iMESA)(GLcontext *ctx, GLint x, GLint y, GLint z); /* 636 */
    void (GLAPIENTRYP WindowPos3ivMESA)(GLcontext *ctx, const GLint * v); /* 637 */
    void (GLAPIENTRYP WindowPos3sMESA)(GLcontext *ctx, GLshort x, GLshort y, GLshort z); /* 638 */
    void (GLAPIENTRYP WindowPos3svMESA)(GLcontext *ctx, const GLshort * v); /* 639 */
    void (GLAPIENTRYP WindowPos4dMESA)(GLcontext *ctx, GLdouble x, GLdouble y, GLdouble z, GLdouble w); /* 640 */
    void (GLAPIENTRYP WindowPos4dvMESA)(GLcontext *ctx, const GLdouble * v); /* 641 */
    void (GLAPIENTRYP WindowPos4fMESA)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w); /* 642 */
    void (GLAPIENTRYP WindowPos4fvMESA)(GLcontext *ctx, const GLfloat * v); /* 643 */
    void (GLAPIENTRYP WindowPos4iMESA)(GLcontext *ctx, GLint x, GLint y, GLint z, GLint w); /* 644 */
    void (GLAPIENTRYP WindowPos4ivMESA)(GLcontext *ctx, const GLint * v); /* 645 */
    void (GLAPIENTRYP WindowPos4sMESA)(GLcontext *ctx, GLshort x, GLshort y, GLshort z, GLshort w); /* 646 */
    void (GLAPIENTRYP WindowPos4svMESA)(GLcontext *ctx, const GLshort * v); /* 647 */
    void (GLAPIENTRYP MultiModeDrawArraysIBM)(GLcontext *ctx, const GLenum * mode, const GLint * first, const GLsizei * count, GLsizei primcount, GLint modestride); /* 648 */
    void (GLAPIENTRYP MultiModeDrawElementsIBM)(GLcontext *ctx, const GLenum * mode, const GLsizei * count, GLenum type, const GLvoid * const * indices, GLsizei primcount, GLint modestride); /* 649 */
    void (GLAPIENTRYP DeleteFencesNV)(GLcontext *ctx, GLsizei n, const GLuint * fences); /* 650 */
    void (GLAPIENTRYP FinishFenceNV)(GLcontext *ctx, GLuint fence); /* 651 */
    void (GLAPIENTRYP GenFencesNV)(GLcontext *ctx, GLsizei n, GLuint * fences); /* 652 */
    void (GLAPIENTRYP GetFenceivNV)(GLcontext *ctx, GLuint fence, GLenum pname, GLint * params); /* 653 */
    GLboolean(GLAPIENTRYP IsFenceNV)(GLcontext *ctx, GLuint fence);  /* 654 */
    void (GLAPIENTRYP SetFenceNV)(GLcontext *ctx, GLuint fence, GLenum condition); /* 655 */
    GLboolean(GLAPIENTRYP TestFenceNV)(GLcontext *ctx, GLuint fence);  /* 656 */
    GLboolean(GLAPIENTRYP AreProgramsResidentNV)(GLcontext *ctx, GLsizei n, const GLuint * ids, GLboolean * residences);  /* 657 */
    void (GLAPIENTRYP BindProgramNV)(GLcontext *ctx, GLenum target, GLuint program); /* 658 */
    void (GLAPIENTRYP DeleteProgramsNV)(GLcontext *ctx, GLsizei n, const GLuint * programs); /* 659 */
    void (GLAPIENTRYP ExecuteProgramNV)(GLcontext *ctx, GLenum target, GLuint id, const GLfloat * params); /* 660 */
    void (GLAPIENTRYP GenProgramsNV)(GLcontext *ctx, GLsizei n, GLuint * programs); /* 661 */
    void (GLAPIENTRYP GetProgramParameterdvNV)(GLcontext *ctx, GLenum target, GLuint index, GLenum pname, GLdouble * params); /* 662 */
    void (GLAPIENTRYP GetProgramParameterfvNV)(GLcontext *ctx, GLenum target, GLuint index, GLenum pname, GLfloat * params); /* 663 */
    void (GLAPIENTRYP GetProgramStringNV)(GLcontext *ctx, GLuint id, GLenum pname, GLubyte * program); /* 664 */
    void (GLAPIENTRYP GetProgramivNV)(GLcontext *ctx, GLuint id, GLenum pname, GLint * params); /* 665 */
    void (GLAPIENTRYP GetTrackMatrixivNV)(GLcontext *ctx, GLenum target, GLuint address, GLenum pname, GLint * params); /* 666 */
    void (GLAPIENTRYP GetVertexAttribPointervNV)(GLcontext *ctx, GLuint index, GLenum pname, GLvoid ** pointer); /* 667 */
    void (GLAPIENTRYP GetVertexAttribdvNV)(GLcontext *ctx, GLuint index, GLenum pname, GLdouble * params); /* 668 */
    void (GLAPIENTRYP GetVertexAttribfvNV)(GLcontext *ctx, GLuint index, GLenum pname, GLfloat * params); /* 669 */
    void (GLAPIENTRYP GetVertexAttribivNV)(GLcontext *ctx, GLuint index, GLenum pname, GLint * params); /* 670 */
    GLboolean(GLAPIENTRYP IsProgramNV)(GLcontext *ctx, GLuint program);  /* 671 */
    void (GLAPIENTRYP LoadProgramNV)(GLcontext *ctx, GLenum target, GLuint id, GLsizei len, const GLubyte * program); /* 672 */
    void (GLAPIENTRYP ProgramParameter4dNV)(GLcontext *ctx, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w); /* 673 */
    void (GLAPIENTRYP ProgramParameter4dvNV)(GLcontext *ctx, GLenum target, GLuint index, const GLdouble * params); /* 674 */
    void (GLAPIENTRYP ProgramParameter4fNV)(GLcontext *ctx, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w); /* 675 */
    void (GLAPIENTRYP ProgramParameter4fvNV)(GLcontext *ctx, GLenum target, GLuint index, const GLfloat * params); /* 676 */
    void (GLAPIENTRYP ProgramParameters4dvNV)(GLcontext *ctx, GLenum target, GLuint index, GLuint num, const GLdouble * params); /* 677 */
    void (GLAPIENTRYP ProgramParameters4fvNV)(GLcontext *ctx, GLenum target, GLuint index, GLuint num, const GLfloat * params); /* 678 */
    void (GLAPIENTRYP RequestResidentProgramsNV)(GLcontext *ctx, GLsizei n, const GLuint * ids); /* 679 */
    void (GLAPIENTRYP TrackMatrixNV)(GLcontext *ctx, GLenum target, GLuint address, GLenum matrix, GLenum transform); /* 680 */
    void (GLAPIENTRYP VertexAttrib1dNV)(GLcontext *ctx, GLuint index, GLdouble x); /* 681 */
    void (GLAPIENTRYP VertexAttrib1dvNV)(GLcontext *ctx, GLuint index, const GLdouble * v); /* 682 */
    void (GLAPIENTRYP VertexAttrib1fNV)(GLcontext *ctx, GLuint index, GLfloat x); /* 683 */
    void (GLAPIENTRYP VertexAttrib1fvNV)(GLcontext *ctx, GLuint index, const GLfloat * v); /* 684 */
    void (GLAPIENTRYP VertexAttrib1sNV)(GLcontext *ctx, GLuint index, GLshort x); /* 685 */
    void (GLAPIENTRYP VertexAttrib1svNV)(GLcontext *ctx, GLuint index, const GLshort * v); /* 686 */
    void (GLAPIENTRYP VertexAttrib2dNV)(GLcontext *ctx, GLuint index, GLdouble x, GLdouble y); /* 687 */
    void (GLAPIENTRYP VertexAttrib2dvNV)(GLcontext *ctx, GLuint index, const GLdouble * v); /* 688 */
    void (GLAPIENTRYP VertexAttrib2fNV)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y); /* 689 */
    void (GLAPIENTRYP VertexAttrib2fvNV)(GLcontext *ctx, GLuint index, const GLfloat * v); /* 690 */
    void (GLAPIENTRYP VertexAttrib2sNV)(GLcontext *ctx, GLuint index, GLshort x, GLshort y); /* 691 */
    void (GLAPIENTRYP VertexAttrib2svNV)(GLcontext *ctx, GLuint index, const GLshort * v); /* 692 */
    void (GLAPIENTRYP VertexAttrib3dNV)(GLcontext *ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z); /* 693 */
    void (GLAPIENTRYP VertexAttrib3dvNV)(GLcontext *ctx, GLuint index, const GLdouble * v); /* 694 */
    void (GLAPIENTRYP VertexAttrib3fNV)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z); /* 695 */
    void (GLAPIENTRYP VertexAttrib3fvNV)(GLcontext *ctx, GLuint index, const GLfloat * v); /* 696 */
    void (GLAPIENTRYP VertexAttrib3sNV)(GLcontext *ctx, GLuint index, GLshort x, GLshort y, GLshort z); /* 697 */
    void (GLAPIENTRYP VertexAttrib3svNV)(GLcontext *ctx, GLuint index, const GLshort * v); /* 698 */
    void (GLAPIENTRYP VertexAttrib4dNV)(GLcontext *ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w); /* 699 */
    void (GLAPIENTRYP VertexAttrib4dvNV)(GLcontext *ctx, GLuint index, const GLdouble * v); /* 700 */
    void (GLAPIENTRYP VertexAttrib4fNV)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w); /* 701 */
    void (GLAPIENTRYP VertexAttrib4fvNV)(GLcontext *ctx, GLuint index, const GLfloat * v); /* 702 */
    void (GLAPIENTRYP VertexAttrib4sNV)(GLcontext *ctx, GLuint index, GLshort x, GLshort y, GLshort z, GLshort w); /* 703 */
    void (GLAPIENTRYP VertexAttrib4svNV)(GLcontext *ctx, GLuint index, const GLshort * v); /* 704 */
    void (GLAPIENTRYP VertexAttrib4ubNV)(GLcontext *ctx, GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w); /* 705 */
    void (GLAPIENTRYP VertexAttrib4ubvNV)(GLcontext *ctx, GLuint index, const GLubyte * v); /* 706 */
    void (GLAPIENTRYP VertexAttribPointerNV)(GLcontext *ctx, GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer); /* 707 */
    void (GLAPIENTRYP VertexAttribs1dvNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLdouble * v); /* 708 */
    void (GLAPIENTRYP VertexAttribs1fvNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLfloat * v); /* 709 */
    void (GLAPIENTRYP VertexAttribs1svNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLshort * v); /* 710 */
    void (GLAPIENTRYP VertexAttribs2dvNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLdouble * v); /* 711 */
    void (GLAPIENTRYP VertexAttribs2fvNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLfloat * v); /* 712 */
    void (GLAPIENTRYP VertexAttribs2svNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLshort * v); /* 713 */
    void (GLAPIENTRYP VertexAttribs3dvNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLdouble * v); /* 714 */
    void (GLAPIENTRYP VertexAttribs3fvNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLfloat * v); /* 715 */
    void (GLAPIENTRYP VertexAttribs3svNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLshort * v); /* 716 */
    void (GLAPIENTRYP VertexAttribs4dvNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLdouble * v); /* 717 */
    void (GLAPIENTRYP VertexAttribs4fvNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLfloat * v); /* 718 */
    void (GLAPIENTRYP VertexAttribs4svNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLshort * v); /* 719 */
    void (GLAPIENTRYP VertexAttribs4ubvNV)(GLcontext *ctx, GLuint index, GLsizei n, const GLubyte * v); /* 720 */
    void (GLAPIENTRYP AlphaFragmentOp1ATI)(GLcontext *ctx, GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod); /* 721 */
    void (GLAPIENTRYP AlphaFragmentOp2ATI)(GLcontext *ctx, GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod); /* 722 */
    void (GLAPIENTRYP AlphaFragmentOp3ATI)(GLcontext *ctx, GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod); /* 723 */
    void (GLAPIENTRYP BeginFragmentShaderATI)(GLcontext *ctx); /* 724 */
    void (GLAPIENTRYP BindFragmentShaderATI)(GLcontext *ctx, GLuint id); /* 725 */
    void (GLAPIENTRYP ColorFragmentOp1ATI)(GLcontext *ctx, GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod); /* 726 */
    void (GLAPIENTRYP ColorFragmentOp2ATI)(GLcontext *ctx, GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod); /* 727 */
    void (GLAPIENTRYP ColorFragmentOp3ATI)(GLcontext *ctx, GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod); /* 728 */
    void (GLAPIENTRYP DeleteFragmentShaderATI)(GLcontext *ctx, GLuint id); /* 729 */
    void (GLAPIENTRYP EndFragmentShaderATI)(GLcontext *ctx); /* 730 */
    GLuint(GLAPIENTRYP GenFragmentShadersATI)(GLcontext *ctx, GLuint range);  /* 731 */
    void (GLAPIENTRYP PassTexCoordATI)(GLcontext *ctx, GLuint dst, GLuint coord, GLenum swizzle); /* 732 */
    void (GLAPIENTRYP SampleMapATI)(GLcontext *ctx, GLuint dst, GLuint interp, GLenum swizzle); /* 733 */
    void (GLAPIENTRYP SetFragmentShaderConstantATI)(GLcontext *ctx, GLuint dst, const GLfloat * value); /* 734 */
    void (GLAPIENTRYP PointParameteriNV)(GLcontext *ctx, GLenum pname, GLint param); /* 735 */
    void (GLAPIENTRYP PointParameterivNV)(GLcontext *ctx, GLenum pname, const GLint * params); /* 736 */
    void (GLAPIENTRYP ActiveStencilFaceEXT)(GLcontext *ctx, GLenum face); /* 737 */
    void (GLAPIENTRYP BindVertexArrayAPPLE)(GLcontext *ctx, GLuint array); /* 738 */
    void (GLAPIENTRYP DeleteVertexArraysAPPLE)(GLcontext *ctx, GLsizei n, const GLuint * arrays); /* 739 */
    void (GLAPIENTRYP GenVertexArraysAPPLE)(GLcontext *ctx, GLsizei n, GLuint * arrays); /* 740 */
    GLboolean(GLAPIENTRYP IsVertexArrayAPPLE)(GLcontext *ctx, GLuint array);  /* 741 */
    void (GLAPIENTRYP GetProgramNamedParameterdvNV)(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte * name, GLdouble * params); /* 742 */
    void (GLAPIENTRYP GetProgramNamedParameterfvNV)(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte * name, GLfloat * params); /* 743 */
    void (GLAPIENTRYP ProgramNamedParameter4dNV)(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte * name, GLdouble x, GLdouble y, GLdouble z, GLdouble w); /* 744 */
    void (GLAPIENTRYP ProgramNamedParameter4dvNV)(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte * name, const GLdouble * v); /* 745 */
    void (GLAPIENTRYP ProgramNamedParameter4fNV)(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w); /* 746 */
    void (GLAPIENTRYP ProgramNamedParameter4fvNV)(GLcontext *ctx, GLuint id, GLsizei len, const GLubyte * name, const GLfloat * v); /* 747 */
    void (GLAPIENTRYP DepthBoundsEXT)(GLcontext *ctx, GLclampd zmin, GLclampd zmax); /* 748 */
    void (GLAPIENTRYP BlendEquationSeparateEXT)(GLcontext *ctx, GLenum modeRGB, GLenum modeA); /* 749 */
    void (GLAPIENTRYP BindFramebufferEXT)(GLcontext *ctx, GLenum target, GLuint framebuffer); /* 750 */
    void (GLAPIENTRYP BindRenderbufferEXT)(GLcontext *ctx, GLenum target, GLuint renderbuffer); /* 751 */
    GLenum(GLAPIENTRYP CheckFramebufferStatusEXT)(GLcontext *ctx, GLenum target);  /* 752 */
    void (GLAPIENTRYP DeleteFramebuffersEXT)(GLcontext *ctx, GLsizei n, const GLuint * framebuffers); /* 753 */
    void (GLAPIENTRYP DeleteRenderbuffersEXT)(GLcontext *ctx, GLsizei n, const GLuint * renderbuffers); /* 754 */
    void (GLAPIENTRYP FramebufferRenderbufferEXT)(GLcontext *ctx, GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer); /* 755 */
    void (GLAPIENTRYP FramebufferTexture1DEXT)(GLcontext *ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level); /* 756 */
    void (GLAPIENTRYP FramebufferTexture2DEXT)(GLcontext *ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level); /* 757 */
    void (GLAPIENTRYP FramebufferTexture3DEXT)(GLcontext *ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset); /* 758 */
    void (GLAPIENTRYP GenFramebuffersEXT)(GLcontext *ctx, GLsizei n, GLuint * framebuffers); /* 759 */
    void (GLAPIENTRYP GenRenderbuffersEXT)(GLcontext *ctx, GLsizei n, GLuint * renderbuffers); /* 760 */
    void (GLAPIENTRYP GenerateMipmapEXT)(GLcontext *ctx, GLenum target); /* 761 */
    void (GLAPIENTRYP GetFramebufferAttachmentParameterivEXT)(GLcontext *ctx, GLenum target, GLenum attachment, GLenum pname, GLint * params); /* 762 */
    void (GLAPIENTRYP GetRenderbufferParameterivEXT)(GLcontext *ctx, GLenum target, GLenum pname, GLint * params); /* 763 */
    GLboolean(GLAPIENTRYP IsFramebufferEXT)(GLcontext *ctx, GLuint framebuffer);  /* 764 */
    GLboolean(GLAPIENTRYP IsRenderbufferEXT)(GLcontext *ctx, GLuint renderbuffer);  /* 765 */
    void (GLAPIENTRYP RenderbufferStorageEXT)(GLcontext *ctx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height); /* 766 */
    void (GLAPIENTRYP BlitFramebufferEXT)(GLcontext *ctx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter); /* 767 */
    void (GLAPIENTRYP StencilFuncSeparateATI)(GLcontext *ctx, GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask); /* 768 */
    void (GLAPIENTRYP ProgramEnvParameters4fvEXT)(GLcontext *ctx, GLenum target, GLuint index, GLsizei count, const GLfloat * params); /* 769 */
    void (GLAPIENTRYP ProgramLocalParameters4fvEXT)(GLcontext *ctx, GLenum target, GLuint index, GLsizei count, const GLfloat * params); /* 770 */
    void (GLAPIENTRYP GetQueryObjecti64vEXT)(GLcontext *ctx, GLuint id, GLenum pname, GLint64EXT * params); /* 771 */
    void (GLAPIENTRYP GetQueryObjectui64vEXT)(GLcontext *ctx, GLuint id, GLenum pname, GLuint64EXT * params); /* 772 */
};

#endif /* !defined( _GLAPI_TABLE_H_ ) */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
