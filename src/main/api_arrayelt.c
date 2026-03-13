/*
 * Mesa 3-D graphics library
 * Version:  6.5.1
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

/* Author:
 *    Keith Whitwell <keith@tungstengraphics.com>
 */

#include "glheader.h"
#include "api_arrayelt.h"
#include "context.h"
#include "imports.h"
#include "macros.h"
#include "glapioffsets.h"
#include "dispatch.h"

typedef void (GLAPIENTRY *array_func)(const void *);

typedef struct {
    const struct gl_client_array *array;
    int offset;
} AEarray;

typedef void (GLAPIENTRY *attrib_func)(GLuint indx, const void *data);

typedef struct {
    const struct gl_client_array *array;
    attrib_func func;
    GLuint index;
} AEattrib;

typedef struct {
    AEarray arrays[32];
    AEattrib attribs[VERT_ATTRIB_MAX + 1];
    GLuint NewState;

    struct gl_buffer_object *vbo[VERT_ATTRIB_MAX];
    GLuint nr_vbos;
    GLboolean mapped_vbos;

} AEcontext;

#define AE_CONTEXT(ctx) ((AEcontext *)(ctx)->aelt_context)


/*
 * Convert GL_BYTE, GL_UNSIGNED_BYTE, .. GL_DOUBLE into an integer
 * in the range [0, 7].  Luckily these type tokens are sequentially
 * numbered in gl.h, except for GL_DOUBLE.
 */
#define TYPE_IDX(t) ( (t) == GL_DOUBLE ? 7 : (t) & 7 )

static const int ColorFuncs[2][8] = {
    {
	_gloffset_Color3bv,
	_gloffset_Color3ubv,
	_gloffset_Color3sv,
	_gloffset_Color3usv,
	_gloffset_Color3iv,
	_gloffset_Color3uiv,
	_gloffset_Color3fv,
	_gloffset_Color3dv,
    },
    {
	_gloffset_Color4bv,
	_gloffset_Color4ubv,
	_gloffset_Color4sv,
	_gloffset_Color4usv,
	_gloffset_Color4iv,
	_gloffset_Color4uiv,
	_gloffset_Color4fv,
	_gloffset_Color4dv,
    },
};

static const int VertexFuncs[3][8] = {
    {
	-1,
	    -1,
	    _gloffset_Vertex2sv,
	    -1,
	    _gloffset_Vertex2iv,
	    -1,
	    _gloffset_Vertex2fv,
	    _gloffset_Vertex2dv,
	},
    {
	-1,
	    -1,
	    _gloffset_Vertex3sv,
	    -1,
	    _gloffset_Vertex3iv,
	    -1,
	    _gloffset_Vertex3fv,
	    _gloffset_Vertex3dv,
	},
    {
	-1,
	    -1,
	    _gloffset_Vertex4sv,
	    -1,
	    _gloffset_Vertex4iv,
	    -1,
	    _gloffset_Vertex4fv,
	    _gloffset_Vertex4dv,
	},
};

static const int IndexFuncs[8] = {
    -1,
	_gloffset_Indexubv,
	_gloffset_Indexsv,
	-1,
	_gloffset_Indexiv,
	-1,
	_gloffset_Indexfv,
	_gloffset_Indexdv,
    };

static const int NormalFuncs[8] = {
    _gloffset_Normal3bv,
    -1,
    _gloffset_Normal3sv,
    -1,
    _gloffset_Normal3iv,
    -1,
    _gloffset_Normal3fv,
    _gloffset_Normal3dv,
};

/* Note: _gloffset_* for these may not be a compile-time constant. */
static int SecondaryColorFuncs[8];
static int FogCoordFuncs[8];


/**
 ** GL_NV_vertex_program
 **/

/* GL_BYTE attributes */

static void GLAPIENTRY VertexAttrib1NbvNV(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, BYTE_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1bvNV(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NbvNV(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, BYTE_TO_FLOAT(v[0]), BYTE_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2bvNV(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NbvNV(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, BYTE_TO_FLOAT(v[0]),
					   BYTE_TO_FLOAT(v[1]),
					   BYTE_TO_FLOAT(v[2])));
}

static void GLAPIENTRY VertexAttrib3bvNV(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NbvNV(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, BYTE_TO_FLOAT(v[0]),
					   BYTE_TO_FLOAT(v[1]),
					   BYTE_TO_FLOAT(v[2]),
					   BYTE_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4bvNV(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_UNSIGNED_BYTE attributes */

static void GLAPIENTRY VertexAttrib1NubvNV(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, UBYTE_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1ubvNV(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NubvNV(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, UBYTE_TO_FLOAT(v[0]),
					   UBYTE_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2ubvNV(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NubvNV(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, UBYTE_TO_FLOAT(v[0]),
					   UBYTE_TO_FLOAT(v[1]),
					   UBYTE_TO_FLOAT(v[2])));
}
static void GLAPIENTRY VertexAttrib3ubvNV(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NubvNV(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, UBYTE_TO_FLOAT(v[0]),
					   UBYTE_TO_FLOAT(v[1]),
					   UBYTE_TO_FLOAT(v[2]),
					   UBYTE_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4ubvNV(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_SHORT attributes */

static void GLAPIENTRY VertexAttrib1NsvNV(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, SHORT_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1svNV(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NsvNV(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, SHORT_TO_FLOAT(v[0]),
					   SHORT_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2svNV(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NsvNV(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, SHORT_TO_FLOAT(v[0]),
					   SHORT_TO_FLOAT(v[1]),
					   SHORT_TO_FLOAT(v[2])));
}

static void GLAPIENTRY VertexAttrib3svNV(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NsvNV(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, SHORT_TO_FLOAT(v[0]),
					   SHORT_TO_FLOAT(v[1]),
					   SHORT_TO_FLOAT(v[2]),
					   SHORT_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4svNV(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_UNSIGNED_SHORT attributes */

static void GLAPIENTRY VertexAttrib1NusvNV(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, USHORT_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1usvNV(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NusvNV(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, USHORT_TO_FLOAT(v[0]),
					   USHORT_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2usvNV(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NusvNV(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, USHORT_TO_FLOAT(v[0]),
					   USHORT_TO_FLOAT(v[1]),
					   USHORT_TO_FLOAT(v[2])));
}

static void GLAPIENTRY VertexAttrib3usvNV(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NusvNV(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, USHORT_TO_FLOAT(v[0]),
					   USHORT_TO_FLOAT(v[1]),
					   USHORT_TO_FLOAT(v[2]),
					   USHORT_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4usvNV(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_INT attributes */

static void GLAPIENTRY VertexAttrib1NivNV(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, INT_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1ivNV(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NivNV(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, INT_TO_FLOAT(v[0]),
					   INT_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2ivNV(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NivNV(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, INT_TO_FLOAT(v[0]),
					   INT_TO_FLOAT(v[1]),
					   INT_TO_FLOAT(v[2])));
}

static void GLAPIENTRY VertexAttrib3ivNV(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NivNV(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, INT_TO_FLOAT(v[0]),
					   INT_TO_FLOAT(v[1]),
					   INT_TO_FLOAT(v[2]),
					   INT_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4ivNV(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_UNSIGNED_INT attributes */

static void GLAPIENTRY VertexAttrib1NuivNV(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, UINT_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1uivNV(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NuivNV(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, UINT_TO_FLOAT(v[0]),
					   UINT_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2uivNV(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NuivNV(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, UINT_TO_FLOAT(v[0]),
					   UINT_TO_FLOAT(v[1]),
					   UINT_TO_FLOAT(v[2])));
}

static void GLAPIENTRY VertexAttrib3uivNV(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NuivNV(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, UINT_TO_FLOAT(v[0]),
					   UINT_TO_FLOAT(v[1]),
					   UINT_TO_FLOAT(v[2]),
					   UINT_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4uivNV(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_FLOAT attributes */

static void GLAPIENTRY VertexAttrib1fvNV(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    CALL_VertexAttrib1fvNV(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib2fvNV(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    CALL_VertexAttrib2fvNV(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib3fvNV(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    CALL_VertexAttrib3fvNV(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib4fvNV(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    CALL_VertexAttrib4fvNV(ctx->CurrentDispatch, (ctx, index, v));
}

/* GL_DOUBLE attributes */

static void GLAPIENTRY VertexAttrib1dvNV(GLcontext *ctx, GLuint index, const GLdouble *v)
{
    CALL_VertexAttrib1dvNV(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib2dvNV(GLcontext *ctx, GLuint index, const GLdouble *v)
{
    CALL_VertexAttrib2dvNV(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib3dvNV(GLcontext *ctx, GLuint index, const GLdouble *v)
{
    CALL_VertexAttrib3dvNV(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib4dvNV(GLcontext *ctx, GLuint index, const GLdouble *v)
{
    CALL_VertexAttrib4dvNV(ctx->CurrentDispatch, (ctx, index, v));
}


/*
 * Array [size][type] of VertexAttrib functions
 */
static attrib_func AttribFuncsNV[2][4][8] = {
    {
	/* non-normalized */
	{
	    /* size 1 */
	    (attrib_func) VertexAttrib1bvNV,
	    (attrib_func) VertexAttrib1ubvNV,
	    (attrib_func) VertexAttrib1svNV,
	    (attrib_func) VertexAttrib1usvNV,
	    (attrib_func) VertexAttrib1ivNV,
	    (attrib_func) VertexAttrib1uivNV,
	    (attrib_func) VertexAttrib1fvNV,
	    (attrib_func) VertexAttrib1dvNV
	},
	{
	    /* size 2 */
	    (attrib_func) VertexAttrib2bvNV,
	    (attrib_func) VertexAttrib2ubvNV,
	    (attrib_func) VertexAttrib2svNV,
	    (attrib_func) VertexAttrib2usvNV,
	    (attrib_func) VertexAttrib2ivNV,
	    (attrib_func) VertexAttrib2uivNV,
	    (attrib_func) VertexAttrib2fvNV,
	    (attrib_func) VertexAttrib2dvNV
	},
	{
	    /* size 3 */
	    (attrib_func) VertexAttrib3bvNV,
	    (attrib_func) VertexAttrib3ubvNV,
	    (attrib_func) VertexAttrib3svNV,
	    (attrib_func) VertexAttrib3usvNV,
	    (attrib_func) VertexAttrib3ivNV,
	    (attrib_func) VertexAttrib3uivNV,
	    (attrib_func) VertexAttrib3fvNV,
	    (attrib_func) VertexAttrib3dvNV
	},
	{
	    /* size 4 */
	    (attrib_func) VertexAttrib4bvNV,
	    (attrib_func) VertexAttrib4ubvNV,
	    (attrib_func) VertexAttrib4svNV,
	    (attrib_func) VertexAttrib4usvNV,
	    (attrib_func) VertexAttrib4ivNV,
	    (attrib_func) VertexAttrib4uivNV,
	    (attrib_func) VertexAttrib4fvNV,
	    (attrib_func) VertexAttrib4dvNV
	}
    },
    {
	/* normalized (except for float/double) */
	{
	    /* size 1 */
	    (attrib_func) VertexAttrib1NbvNV,
	    (attrib_func) VertexAttrib1NubvNV,
	    (attrib_func) VertexAttrib1NsvNV,
	    (attrib_func) VertexAttrib1NusvNV,
	    (attrib_func) VertexAttrib1NivNV,
	    (attrib_func) VertexAttrib1NuivNV,
	    (attrib_func) VertexAttrib1fvNV,
	    (attrib_func) VertexAttrib1dvNV
	},
	{
	    /* size 2 */
	    (attrib_func) VertexAttrib2NbvNV,
	    (attrib_func) VertexAttrib2NubvNV,
	    (attrib_func) VertexAttrib2NsvNV,
	    (attrib_func) VertexAttrib2NusvNV,
	    (attrib_func) VertexAttrib2NivNV,
	    (attrib_func) VertexAttrib2NuivNV,
	    (attrib_func) VertexAttrib2fvNV,
	    (attrib_func) VertexAttrib2dvNV
	},
	{
	    /* size 3 */
	    (attrib_func) VertexAttrib3NbvNV,
	    (attrib_func) VertexAttrib3NubvNV,
	    (attrib_func) VertexAttrib3NsvNV,
	    (attrib_func) VertexAttrib3NusvNV,
	    (attrib_func) VertexAttrib3NivNV,
	    (attrib_func) VertexAttrib3NuivNV,
	    (attrib_func) VertexAttrib3fvNV,
	    (attrib_func) VertexAttrib3dvNV
	},
	{
	    /* size 4 */
	    (attrib_func) VertexAttrib4NbvNV,
	    (attrib_func) VertexAttrib4NubvNV,
	    (attrib_func) VertexAttrib4NsvNV,
	    (attrib_func) VertexAttrib4NusvNV,
	    (attrib_func) VertexAttrib4NivNV,
	    (attrib_func) VertexAttrib4NuivNV,
	    (attrib_func) VertexAttrib4fvNV,
	    (attrib_func) VertexAttrib4dvNV
	}
    }
};


/**
 ** GL_ARB_vertex_program
 **/

/* GL_BYTE attributes */

static void GLAPIENTRY VertexAttrib1NbvARB(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, BYTE_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1bvARB(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NbvARB(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, BYTE_TO_FLOAT(v[0]), BYTE_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2bvARB(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NbvARB(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, BYTE_TO_FLOAT(v[0]),
					    BYTE_TO_FLOAT(v[1]),
					    BYTE_TO_FLOAT(v[2])));
}

static void GLAPIENTRY VertexAttrib3bvARB(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NbvARB(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, BYTE_TO_FLOAT(v[0]),
					    BYTE_TO_FLOAT(v[1]),
					    BYTE_TO_FLOAT(v[2]),
					    BYTE_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4bvARB(GLcontext *ctx, GLuint index, const GLbyte *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_UNSIGNED_BYTE attributes */

static void GLAPIENTRY VertexAttrib1NubvARB(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, UBYTE_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1ubvARB(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NubvARB(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, UBYTE_TO_FLOAT(v[0]),
					    UBYTE_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2ubvARB(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NubvARB(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, UBYTE_TO_FLOAT(v[0]),
					    UBYTE_TO_FLOAT(v[1]),
					    UBYTE_TO_FLOAT(v[2])));
}
static void GLAPIENTRY VertexAttrib3ubvARB(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NubvARB(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, UBYTE_TO_FLOAT(v[0]),
					    UBYTE_TO_FLOAT(v[1]),
					    UBYTE_TO_FLOAT(v[2]),
					    UBYTE_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4ubvARB(GLcontext *ctx, GLuint index, const GLubyte *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_SHORT attributes */

static void GLAPIENTRY VertexAttrib1NsvARB(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, SHORT_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1svARB(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NsvARB(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, SHORT_TO_FLOAT(v[0]),
					    SHORT_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2svARB(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NsvARB(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, SHORT_TO_FLOAT(v[0]),
					    SHORT_TO_FLOAT(v[1]),
					    SHORT_TO_FLOAT(v[2])));
}

static void GLAPIENTRY VertexAttrib3svARB(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NsvARB(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, SHORT_TO_FLOAT(v[0]),
					    SHORT_TO_FLOAT(v[1]),
					    SHORT_TO_FLOAT(v[2]),
					    SHORT_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4svARB(GLcontext *ctx, GLuint index, const GLshort *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_UNSIGNED_SHORT attributes */

static void GLAPIENTRY VertexAttrib1NusvARB(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, USHORT_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1usvARB(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NusvARB(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, USHORT_TO_FLOAT(v[0]),
					    USHORT_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2usvARB(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NusvARB(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, USHORT_TO_FLOAT(v[0]),
					    USHORT_TO_FLOAT(v[1]),
					    USHORT_TO_FLOAT(v[2])));
}

static void GLAPIENTRY VertexAttrib3usvARB(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NusvARB(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, USHORT_TO_FLOAT(v[0]),
					    USHORT_TO_FLOAT(v[1]),
					    USHORT_TO_FLOAT(v[2]),
					    USHORT_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4usvARB(GLcontext *ctx, GLuint index, const GLushort *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_INT attributes */

static void GLAPIENTRY VertexAttrib1NivARB(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, INT_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1ivARB(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NivARB(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, INT_TO_FLOAT(v[0]),
					    INT_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2ivARB(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NivARB(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, INT_TO_FLOAT(v[0]),
					    INT_TO_FLOAT(v[1]),
					    INT_TO_FLOAT(v[2])));
}

static void GLAPIENTRY VertexAttrib3ivARB(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NivARB(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, INT_TO_FLOAT(v[0]),
					    INT_TO_FLOAT(v[1]),
					    INT_TO_FLOAT(v[2]),
					    INT_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4ivARB(GLcontext *ctx, GLuint index, const GLint *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_UNSIGNED_INT attributes */

static void GLAPIENTRY VertexAttrib1NuivARB(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, UINT_TO_FLOAT(v[0])));
}

static void GLAPIENTRY VertexAttrib1uivARB(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, v[0]));
}

static void GLAPIENTRY VertexAttrib2NuivARB(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, UINT_TO_FLOAT(v[0]),
					    UINT_TO_FLOAT(v[1])));
}

static void GLAPIENTRY VertexAttrib2uivARB(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1]));
}

static void GLAPIENTRY VertexAttrib3NuivARB(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, UINT_TO_FLOAT(v[0]),
					    UINT_TO_FLOAT(v[1]),
					    UINT_TO_FLOAT(v[2])));
}

static void GLAPIENTRY VertexAttrib3uivARB(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2]));
}

static void GLAPIENTRY VertexAttrib4NuivARB(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, UINT_TO_FLOAT(v[0]),
					    UINT_TO_FLOAT(v[1]),
					    UINT_TO_FLOAT(v[2]),
					    UINT_TO_FLOAT(v[3])));
}

static void GLAPIENTRY VertexAttrib4uivARB(GLcontext *ctx, GLuint index, const GLuint *v)
{
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, v[0], v[1], v[2], v[3]));
}

/* GL_FLOAT attributes */

static void GLAPIENTRY VertexAttrib1fvARB(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    CALL_VertexAttrib1fvARB(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib2fvARB(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    CALL_VertexAttrib2fvARB(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib3fvARB(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    CALL_VertexAttrib3fvARB(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib4fvARB(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    CALL_VertexAttrib4fvARB(ctx->CurrentDispatch, (ctx, index, v));
}

/* GL_DOUBLE attributes */

static void GLAPIENTRY VertexAttrib1dvARB(GLcontext *ctx, GLuint index, const GLdouble *v)
{
    CALL_VertexAttrib1dvARB(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib2dvARB(GLcontext *ctx, GLuint index, const GLdouble *v)
{
    CALL_VertexAttrib2dvARB(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib3dvARB(GLcontext *ctx, GLuint index, const GLdouble *v)
{
    CALL_VertexAttrib3dvARB(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY VertexAttrib4dvARB(GLcontext *ctx, GLuint index, const GLdouble *v)
{
    CALL_VertexAttrib4dvARB(ctx->CurrentDispatch, (ctx, index, v));
}


/*
 * Array [size][type] of VertexAttrib functions
 */
static attrib_func AttribFuncsARB[2][4][8] = {
    {
	/* non-normalized */
	{
	    /* size 1 */
	    (attrib_func) VertexAttrib1bvARB,
	    (attrib_func) VertexAttrib1ubvARB,
	    (attrib_func) VertexAttrib1svARB,
	    (attrib_func) VertexAttrib1usvARB,
	    (attrib_func) VertexAttrib1ivARB,
	    (attrib_func) VertexAttrib1uivARB,
	    (attrib_func) VertexAttrib1fvARB,
	    (attrib_func) VertexAttrib1dvARB
	},
	{
	    /* size 2 */
	    (attrib_func) VertexAttrib2bvARB,
	    (attrib_func) VertexAttrib2ubvARB,
	    (attrib_func) VertexAttrib2svARB,
	    (attrib_func) VertexAttrib2usvARB,
	    (attrib_func) VertexAttrib2ivARB,
	    (attrib_func) VertexAttrib2uivARB,
	    (attrib_func) VertexAttrib2fvARB,
	    (attrib_func) VertexAttrib2dvARB
	},
	{
	    /* size 3 */
	    (attrib_func) VertexAttrib3bvARB,
	    (attrib_func) VertexAttrib3ubvARB,
	    (attrib_func) VertexAttrib3svARB,
	    (attrib_func) VertexAttrib3usvARB,
	    (attrib_func) VertexAttrib3ivARB,
	    (attrib_func) VertexAttrib3uivARB,
	    (attrib_func) VertexAttrib3fvARB,
	    (attrib_func) VertexAttrib3dvARB
	},
	{
	    /* size 4 */
	    (attrib_func) VertexAttrib4bvARB,
	    (attrib_func) VertexAttrib4ubvARB,
	    (attrib_func) VertexAttrib4svARB,
	    (attrib_func) VertexAttrib4usvARB,
	    (attrib_func) VertexAttrib4ivARB,
	    (attrib_func) VertexAttrib4uivARB,
	    (attrib_func) VertexAttrib4fvARB,
	    (attrib_func) VertexAttrib4dvARB
	}
    },
    {
	/* normalized (except for float/double) */
	{
	    /* size 1 */
	    (attrib_func) VertexAttrib1NbvARB,
	    (attrib_func) VertexAttrib1NubvARB,
	    (attrib_func) VertexAttrib1NsvARB,
	    (attrib_func) VertexAttrib1NusvARB,
	    (attrib_func) VertexAttrib1NivARB,
	    (attrib_func) VertexAttrib1NuivARB,
	    (attrib_func) VertexAttrib1fvARB,
	    (attrib_func) VertexAttrib1dvARB
	},
	{
	    /* size 2 */
	    (attrib_func) VertexAttrib2NbvARB,
	    (attrib_func) VertexAttrib2NubvARB,
	    (attrib_func) VertexAttrib2NsvARB,
	    (attrib_func) VertexAttrib2NusvARB,
	    (attrib_func) VertexAttrib2NivARB,
	    (attrib_func) VertexAttrib2NuivARB,
	    (attrib_func) VertexAttrib2fvARB,
	    (attrib_func) VertexAttrib2dvARB
	},
	{
	    /* size 3 */
	    (attrib_func) VertexAttrib3NbvARB,
	    (attrib_func) VertexAttrib3NubvARB,
	    (attrib_func) VertexAttrib3NsvARB,
	    (attrib_func) VertexAttrib3NusvARB,
	    (attrib_func) VertexAttrib3NivARB,
	    (attrib_func) VertexAttrib3NuivARB,
	    (attrib_func) VertexAttrib3fvARB,
	    (attrib_func) VertexAttrib3dvARB
	},
	{
	    /* size 4 */
	    (attrib_func) VertexAttrib4NbvARB,
	    (attrib_func) VertexAttrib4NubvARB,
	    (attrib_func) VertexAttrib4NsvARB,
	    (attrib_func) VertexAttrib4NusvARB,
	    (attrib_func) VertexAttrib4NivARB,
	    (attrib_func) VertexAttrib4NuivARB,
	    (attrib_func) VertexAttrib4fvARB,
	    (attrib_func) VertexAttrib4dvARB
	}
    }
};

/**********************************************************************/


GLboolean _ae_create_context(GLcontext *ctx)
{
    if (ctx->aelt_context)
	return GL_TRUE;

    /* These _gloffset_* values may not be compile-time constants */
    SecondaryColorFuncs[0] = _gloffset_SecondaryColor3bvEXT;
    SecondaryColorFuncs[1] = _gloffset_SecondaryColor3ubvEXT;
    SecondaryColorFuncs[2] = _gloffset_SecondaryColor3svEXT;
    SecondaryColorFuncs[3] = _gloffset_SecondaryColor3usvEXT;
    SecondaryColorFuncs[4] = _gloffset_SecondaryColor3ivEXT;
    SecondaryColorFuncs[5] = _gloffset_SecondaryColor3uivEXT;
    SecondaryColorFuncs[6] = _gloffset_SecondaryColor3fvEXT;
    SecondaryColorFuncs[7] = _gloffset_SecondaryColor3dvEXT;

    FogCoordFuncs[0] = -1;
    FogCoordFuncs[1] = -1;
    FogCoordFuncs[2] = -1;
    FogCoordFuncs[3] = -1;
    FogCoordFuncs[4] = -1;
    FogCoordFuncs[5] = -1;
    FogCoordFuncs[6] = _gloffset_FogCoordfvEXT;
    FogCoordFuncs[7] = _gloffset_FogCoorddvEXT;

    ctx->aelt_context = calloc(1,sizeof(AEcontext));
    if (!ctx->aelt_context)
	return GL_FALSE;

    AE_CONTEXT(ctx)->NewState = ~0;
    return GL_TRUE;
}


void _ae_destroy_context(GLcontext *ctx)
{
    if (AE_CONTEXT(ctx)) {
	free(ctx->aelt_context);
	ctx->aelt_context = NULL;
    }
}

static void check_vbo(AEcontext *actx,
		      struct gl_buffer_object *vbo)
{
    if (vbo->Name && !vbo->Pointer) {
	GLuint i;
	for (i = 0; i < actx->nr_vbos; i++)
	    if (actx->vbo[i] == vbo)
		return;
	assert(actx->nr_vbos < VERT_ATTRIB_MAX);
	actx->vbo[actx->nr_vbos++] = vbo;
    }
}


/**
 * Make a list of per-vertex functions to call for each glArrayElement call.
 * These functions access the array data (i.e. glVertex, glColor, glNormal,
 * etc).
 * Note: this may be called during display list construction.
 */
static void _ae_update_state(GLcontext *ctx)
{
    AEcontext *actx = AE_CONTEXT(ctx);
    AEarray *aa = actx->arrays;
    AEattrib *at = actx->attribs;
    GLuint i;

    actx->nr_vbos = 0;

    /* conventional vertex arrays */
    if (ctx->Array.ArrayObj->Index.Enabled) {
	aa->array = &ctx->Array.ArrayObj->Index;
	aa->offset = IndexFuncs[TYPE_IDX(aa->array->Type)];
	check_vbo(actx, aa->array->BufferObj);
	aa++;
    }
    if (ctx->Array.ArrayObj->EdgeFlag.Enabled) {
	aa->array = &ctx->Array.ArrayObj->EdgeFlag;
	aa->offset = _gloffset_EdgeFlagv;
	check_vbo(actx, aa->array->BufferObj);
	aa++;
    }
    if (ctx->Array.ArrayObj->Normal.Enabled) {
	aa->array = &ctx->Array.ArrayObj->Normal;
	aa->offset = NormalFuncs[TYPE_IDX(aa->array->Type)];
	check_vbo(actx, aa->array->BufferObj);
	aa++;
    }
    if (ctx->Array.ArrayObj->Color.Enabled) {
	aa->array = &ctx->Array.ArrayObj->Color;
	aa->offset = ColorFuncs[aa->array->Size-3][TYPE_IDX(aa->array->Type)];
	check_vbo(actx, aa->array->BufferObj);
	aa++;
    }
    if (ctx->Array.ArrayObj->SecondaryColor.Enabled) {
	aa->array = &ctx->Array.ArrayObj->SecondaryColor;
	aa->offset = SecondaryColorFuncs[TYPE_IDX(aa->array->Type)];
	check_vbo(actx, aa->array->BufferObj);
	aa++;
    }
    if (ctx->Array.ArrayObj->FogCoord.Enabled) {
	aa->array = &ctx->Array.ArrayObj->FogCoord;
	aa->offset = FogCoordFuncs[TYPE_IDX(aa->array->Type)];
	check_vbo(actx, aa->array->BufferObj);
	aa++;
    }
    for (i = 0; i < ctx->Const.MaxTextureCoordUnits; i++) {
	struct gl_client_array *attribArray = &ctx->Array.ArrayObj->TexCoord[i];
	if (attribArray->Enabled) {
	    /* NOTE: we use generic glVertexAttribNV functions here.
	     * If we ever remove GL_NV_vertex_program this will have to change.
	     */
	    at->array = attribArray;
	    ASSERT(!at->array->Normalized);
	    at->func = AttribFuncsNV[at->array->Normalized]
		       [at->array->Size-1]
		       [TYPE_IDX(at->array->Type)];
	    at->index = VERT_ATTRIB_TEX0 + i;
	    check_vbo(actx, at->array->BufferObj);
	    at++;
	}
    }

    /* generic vertex attribute arrays */
    for (i = 1; i < VERT_ATTRIB_MAX; i++) {  /* skip zero! */
	struct gl_client_array *attribArray = &ctx->Array.ArrayObj->VertexAttrib[i];
	if (attribArray->Enabled) {
	    at->array = attribArray;
	    /* Note: we can't grab the _glapi_Dispatch->VertexAttrib1fvNV
	     * function pointer here (for float arrays) since the pointer may
	     * change from one execution of _ae_loopback_array_elt() to
	     * the next.  Doing so caused UT to break.
	     */
	    if (ctx->VertexProgram._Enabled
		&& ctx->VertexProgram.Current->IsNVProgram) {
		at->func = AttribFuncsNV[at->array->Normalized]
			   [at->array->Size-1]
			   [TYPE_IDX(at->array->Type)];
	    } else {
		at->func = AttribFuncsARB[at->array->Normalized]
			   [at->array->Size-1]
			   [TYPE_IDX(at->array->Type)];
	    }
	    at->index = i;
	    check_vbo(actx, at->array->BufferObj);
	    at++;
	}
    }

    /* finally, vertex position */
    if (ctx->Array.ArrayObj->VertexAttrib[0].Enabled) {
	/* Use glVertex(v) instead of glVertexAttrib(0, v) to be sure it's
	 * issued as the last (provoking) attribute).
	 */
	aa->array = &ctx->Array.ArrayObj->VertexAttrib[0];
	assert(aa->array->Size >= 2); /* XXX fix someday? */
	aa->offset = VertexFuncs[aa->array->Size-2][TYPE_IDX(aa->array->Type)];
	check_vbo(actx, aa->array->BufferObj);
	aa++;
    } else if (ctx->Array.ArrayObj->Vertex.Enabled) {
	aa->array = &ctx->Array.ArrayObj->Vertex;
	aa->offset = VertexFuncs[aa->array->Size-2][TYPE_IDX(aa->array->Type)];
	check_vbo(actx, aa->array->BufferObj);
	aa++;
    }

    check_vbo(actx, ctx->Array.ElementArrayBufferObj);

    ASSERT(at - actx->attribs <= VERT_ATTRIB_MAX);
    ASSERT(aa - actx->arrays < 32);
    at->func = NULL;  /* terminate the list */
    aa->offset = -1;  /* terminate the list */

    actx->NewState = 0;
}

void _ae_map_vbos(GLcontext *ctx)
{
    AEcontext *actx = AE_CONTEXT(ctx);
    GLuint i;

    if (actx->mapped_vbos)
	return;

    if (actx->NewState)
	_ae_update_state(ctx);

    for (i = 0; i < actx->nr_vbos; i++)
	ctx->Driver.MapBuffer(ctx,
			      GL_ARRAY_BUFFER_ARB,
			      GL_DYNAMIC_DRAW_ARB,
			      actx->vbo[i]);

    if (actx->nr_vbos)
	actx->mapped_vbos = GL_TRUE;
}

void _ae_unmap_vbos(GLcontext *ctx)
{
    AEcontext *actx = AE_CONTEXT(ctx);
    GLuint i;

    if (!actx->mapped_vbos)
	return;

    assert(!actx->NewState);

    for (i = 0; i < actx->nr_vbos; i++)
	ctx->Driver.UnmapBuffer(ctx,
				GL_ARRAY_BUFFER_ARB,
				actx->vbo[i]);

    actx->mapped_vbos = GL_FALSE;
}


/**
 * Called via glArrayElement() and glDrawArrays().
 * Issue the glNormal, glVertex, glColor, glVertexAttrib, etc functions
 * for all enabled vertex arrays (for elt-th element).
 * Note: this may be called during display list construction.
 */
void GLAPIENTRY _ae_loopback_array_elt(GLcontext *ctx, GLint elt)
{
    const AEcontext *actx = AE_CONTEXT(ctx);
    const AEarray *aa;
    const AEattrib *at;
    const struct _glapi_table * const disp = GET_DISPATCH();
    GLboolean do_map;

    if (actx->NewState) {
	assert(!actx->mapped_vbos);
	_ae_update_state(ctx);
    }

    do_map = actx->nr_vbos && !actx->mapped_vbos;

    /*
     */
    if (do_map)
	_ae_map_vbos(ctx);

    /* generic attributes */
    for (at = actx->attribs; at->func; at++) {
	const GLubyte *src
	    = ADD_POINTERS(at->array->BufferObj->Pointer, at->array->Ptr)
	      + elt * at->array->StrideB;
	at->func(at->index, src);
    }

    /* conventional arrays */
    for (aa = actx->arrays; aa->offset != -1 ; aa++) {
	const GLubyte *src
	    = ADD_POINTERS(aa->array->BufferObj->Pointer, aa->array->Ptr)
	      + elt * aa->array->StrideB;
	CALL_by_offset(disp, (array_func), aa->offset, ((const void *) src));
    }

    if (do_map)
	_ae_unmap_vbos(ctx);
}


void _ae_invalidate_state(GLcontext *ctx, GLuint new_state)
{
    AEcontext *actx = AE_CONTEXT(ctx);


    /* Only interested in this subset of mesa state.  Need to prune
     * this down as both tnl/ and the drivers can raise statechanges
     * for arcane reasons in the middle of seemingly atomic operations
     * like DrawElements, over which we'd like to keep a known set of
     * arrays and vbo's mapped.
     *
     * Luckily, neither the drivers nor tnl muck with the state that
     * concerns us here:
     */
    new_state &= _NEW_ARRAY | _NEW_PROGRAM;
    if (new_state) {
	assert(!actx->mapped_vbos);
	actx->NewState |= new_state;
    }
}

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
