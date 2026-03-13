/*
 * Mesa 3-D graphics library
 * Version:  6.3
 *
 * Copyright (C) 1999-2004  Brian Paul   All Rights Reserved.
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
 *    Gareth Hughes
 */

#ifndef PRE_LOOPBACK
#define PRE_LOOPBACK( FUNC )
#endif

#include "dispatch.h"
#include "glapioffsets.h"

static void GLAPIENTRY TAG(ArrayElement)(GLcontext *ctx, GLint i)
{
    PRE_LOOPBACK(ArrayElement);
    CALL_ArrayElement(ctx->CurrentDispatch, (ctx, i));
}

static void GLAPIENTRY TAG(Color3f)(GLcontext *ctx, GLfloat r, GLfloat g, GLfloat b)
{
    PRE_LOOPBACK(Color3f);
    CALL_Color3f(ctx->CurrentDispatch, (ctx, r, g, b));
}

static void GLAPIENTRY TAG(Color3fv)(GLcontext *ctx, const GLfloat *v)
{
    PRE_LOOPBACK(Color3fv);
    CALL_Color3fv(ctx->CurrentDispatch, (ctx, v));
}

static void GLAPIENTRY TAG(Color4f)(GLcontext *ctx, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    PRE_LOOPBACK(Color4f);
    CALL_Color4f(ctx->CurrentDispatch, (ctx, r, g, b, a));
}

static void GLAPIENTRY TAG(Color4fv)(GLcontext *ctx, const GLfloat *v)
{
    PRE_LOOPBACK(Color4fv);
    CALL_Color4fv(ctx->CurrentDispatch, (ctx, v));
}

static void GLAPIENTRY TAG(EdgeFlag)(GLcontext *ctx, GLboolean e)
{
    PRE_LOOPBACK(EdgeFlag);
    CALL_EdgeFlag(ctx->CurrentDispatch, (ctx, e));
}

static void GLAPIENTRY TAG(EvalCoord1f)(GLcontext *ctx, GLfloat s)
{
    PRE_LOOPBACK(EvalCoord1f);
    CALL_EvalCoord1f(ctx->CurrentDispatch, (ctx, s));
}

static void GLAPIENTRY TAG(EvalCoord1fv)(GLcontext *ctx, const GLfloat *v)
{
    PRE_LOOPBACK(EvalCoord1fv);
    CALL_EvalCoord1fv(ctx->CurrentDispatch, (ctx, v));
}

static void GLAPIENTRY TAG(EvalCoord2f)(GLcontext *ctx, GLfloat s, GLfloat t)
{
    PRE_LOOPBACK(EvalCoord2f);
    CALL_EvalCoord2f(ctx->CurrentDispatch, (ctx, s, t));
}

static void GLAPIENTRY TAG(EvalCoord2fv)(GLcontext *ctx, const GLfloat *v)
{
    PRE_LOOPBACK(EvalCoord2fv);
    CALL_EvalCoord2fv(ctx->CurrentDispatch, (ctx, v));
}

static void GLAPIENTRY TAG(EvalPoint1)(GLcontext *ctx, GLint i)
{
    PRE_LOOPBACK(EvalPoint1);
    CALL_EvalPoint1(ctx->CurrentDispatch, (ctx, i));
}

static void GLAPIENTRY TAG(EvalPoint2)(GLcontext *ctx, GLint i, GLint j)
{
    PRE_LOOPBACK(EvalPoint2);
    CALL_EvalPoint2(ctx->CurrentDispatch, (ctx, i, j));
}

static void GLAPIENTRY TAG(FogCoordfEXT)(GLcontext *ctx, GLfloat f)
{
    PRE_LOOPBACK(FogCoordfEXT);
    CALL_FogCoordfEXT(ctx->CurrentDispatch, (ctx, f));
}

static void GLAPIENTRY TAG(FogCoordfvEXT)(GLcontext *ctx, const GLfloat *v)
{
    PRE_LOOPBACK(FogCoordfvEXT);
    CALL_FogCoordfvEXT(ctx->CurrentDispatch, (ctx, v));
}

static void GLAPIENTRY TAG(Indexf)(GLcontext *ctx, GLfloat f)
{
    PRE_LOOPBACK(Indexf);
    CALL_Indexf(ctx->CurrentDispatch, (ctx, f));
}

static void GLAPIENTRY TAG(Indexfv)(GLcontext *ctx, const GLfloat *v)
{
    PRE_LOOPBACK(Indexfv);
    CALL_Indexfv(ctx->CurrentDispatch, (ctx, v));
}

static void GLAPIENTRY TAG(Materialfv)(GLcontext *ctx, GLenum face, GLenum pname, const GLfloat *v)
{
    PRE_LOOPBACK(Materialfv);
    CALL_Materialfv(ctx->CurrentDispatch, (ctx, face, pname, v));
}

static void GLAPIENTRY TAG(MultiTexCoord1fARB)(GLcontext *ctx, GLenum target, GLfloat a)
{
    PRE_LOOPBACK(MultiTexCoord1fARB);
    CALL_MultiTexCoord1fARB(ctx->CurrentDispatch, (ctx, target, a));
}

static void GLAPIENTRY TAG(MultiTexCoord1fvARB)(GLcontext *ctx, GLenum target, const GLfloat *tc)
{
    PRE_LOOPBACK(MultiTexCoord1fvARB);
    CALL_MultiTexCoord1fvARB(ctx->CurrentDispatch, (ctx, target, tc));
}

static void GLAPIENTRY TAG(MultiTexCoord2fARB)(GLcontext *ctx, GLenum target, GLfloat s, GLfloat t)
{
    PRE_LOOPBACK(MultiTexCoord2fARB);
    CALL_MultiTexCoord2fARB(ctx->CurrentDispatch, (ctx, target, s, t));
}

static void GLAPIENTRY TAG(MultiTexCoord2fvARB)(GLcontext *ctx, GLenum target, const GLfloat *tc)
{
    PRE_LOOPBACK(MultiTexCoord2fvARB);
    CALL_MultiTexCoord2fvARB(ctx->CurrentDispatch, (ctx, target, tc));
}

static void GLAPIENTRY TAG(MultiTexCoord3fARB)(GLcontext *ctx, GLenum target, GLfloat s,
	GLfloat t, GLfloat r)
{
    PRE_LOOPBACK(MultiTexCoord3fARB);
    CALL_MultiTexCoord3fARB(ctx->CurrentDispatch, (ctx, target, s, t, r));
}

static void GLAPIENTRY TAG(MultiTexCoord3fvARB)(GLcontext *ctx, GLenum target, const GLfloat *tc)
{
    PRE_LOOPBACK(MultiTexCoord3fvARB);
    CALL_MultiTexCoord3fvARB(ctx->CurrentDispatch, (ctx, target, tc));
}

static void GLAPIENTRY TAG(MultiTexCoord4fARB)(GLcontext *ctx, GLenum target, GLfloat s,
	GLfloat t, GLfloat r, GLfloat q)
{
    PRE_LOOPBACK(MultiTexCoord4fARB);
    CALL_MultiTexCoord4fARB(ctx->CurrentDispatch, (ctx, target, s, t, r, q));
}

static void GLAPIENTRY TAG(MultiTexCoord4fvARB)(GLcontext *ctx, GLenum target, const GLfloat *tc)
{
    PRE_LOOPBACK(MultiTexCoord4fvARB);
    CALL_MultiTexCoord4fvARB(ctx->CurrentDispatch, (ctx, target, tc));
}

static void GLAPIENTRY TAG(Normal3f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z)
{
    PRE_LOOPBACK(Normal3f);
    CALL_Normal3f(ctx->CurrentDispatch, (ctx, x, y, z));
}

static void GLAPIENTRY TAG(Normal3fv)(GLcontext *ctx, const GLfloat *v)
{
    PRE_LOOPBACK(Normal3fv);
    CALL_Normal3fv(ctx->CurrentDispatch, (ctx, v));
}

static void GLAPIENTRY TAG(SecondaryColor3fEXT)(GLcontext *ctx, GLfloat r, GLfloat g, GLfloat b)
{
    PRE_LOOPBACK(SecondaryColor3fEXT);
    CALL_SecondaryColor3fEXT(ctx->CurrentDispatch, (ctx, r, g, b));
}

static void GLAPIENTRY TAG(SecondaryColor3fvEXT)(GLcontext *ctx, const GLfloat *v)
{
    PRE_LOOPBACK(SecondaryColor3fvEXT);
    CALL_SecondaryColor3fvEXT(ctx->CurrentDispatch, (ctx, v));
}

static void GLAPIENTRY TAG(TexCoord1f)(GLcontext *ctx, GLfloat s)
{
    PRE_LOOPBACK(TexCoord1f);
    CALL_TexCoord1f(ctx->CurrentDispatch, (ctx, s));
}

static void GLAPIENTRY TAG(TexCoord1fv)(GLcontext *ctx, const GLfloat *tc)
{
    PRE_LOOPBACK(TexCoord1fv);
    CALL_TexCoord1fv(ctx->CurrentDispatch, (ctx, tc));
}

static void GLAPIENTRY TAG(TexCoord2f)(GLcontext *ctx, GLfloat s, GLfloat t)
{
    PRE_LOOPBACK(TexCoord2f);
    CALL_TexCoord2f(ctx->CurrentDispatch, (ctx, s, t));
}

static void GLAPIENTRY TAG(TexCoord2fv)(GLcontext *ctx, const GLfloat *tc)
{
    PRE_LOOPBACK(TexCoord2fv);
    CALL_TexCoord2fv(ctx->CurrentDispatch, (ctx, tc));
}

static void GLAPIENTRY TAG(TexCoord3f)(GLcontext *ctx, GLfloat s, GLfloat t, GLfloat r)
{
    PRE_LOOPBACK(TexCoord3f);
    CALL_TexCoord3f(ctx->CurrentDispatch, (ctx, s, t, r));
}

static void GLAPIENTRY TAG(TexCoord3fv)(GLcontext *ctx, const GLfloat *tc)
{
    PRE_LOOPBACK(TexCoord3fv);
    CALL_TexCoord3fv(ctx->CurrentDispatch, (ctx, tc));
}

static void GLAPIENTRY TAG(TexCoord4f)(GLcontext *ctx, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
    PRE_LOOPBACK(TexCoord4f);
    CALL_TexCoord4f(ctx->CurrentDispatch, (ctx, s, t, r, q));
}

static void GLAPIENTRY TAG(TexCoord4fv)(GLcontext *ctx, const GLfloat *tc)
{
    PRE_LOOPBACK(TexCoord4fv);
    CALL_TexCoord4fv(ctx->CurrentDispatch, (ctx, tc));
}

static void GLAPIENTRY TAG(Vertex2f)(GLcontext *ctx, GLfloat x, GLfloat y)
{
    PRE_LOOPBACK(Vertex2f);
    CALL_Vertex2f(ctx->CurrentDispatch, (ctx, x, y));
}

static void GLAPIENTRY TAG(Vertex2fv)(GLcontext *ctx, const GLfloat *v)
{
    PRE_LOOPBACK(Vertex2fv);
    CALL_Vertex2fv(ctx->CurrentDispatch, (ctx, v));
}

static void GLAPIENTRY TAG(Vertex3f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z)
{
    PRE_LOOPBACK(Vertex3f);
    CALL_Vertex3f(ctx->CurrentDispatch, (ctx, x, y, z));
}

static void GLAPIENTRY TAG(Vertex3fv)(GLcontext *ctx, const GLfloat *v)
{
    PRE_LOOPBACK(Vertex3fv);
    CALL_Vertex3fv(ctx->CurrentDispatch, (ctx, v));
}

static void GLAPIENTRY TAG(Vertex4f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    PRE_LOOPBACK(Vertex4f);
    CALL_Vertex4f(ctx->CurrentDispatch, (ctx, x, y, z, w));
}

static void GLAPIENTRY TAG(Vertex4fv)(GLcontext *ctx, const GLfloat *v)
{
    PRE_LOOPBACK(Vertex4fv);
    CALL_Vertex4fv(ctx->CurrentDispatch, (ctx, v));
}

static void GLAPIENTRY TAG(CallList)(GLcontext *ctx, GLuint i)
{
    PRE_LOOPBACK(CallList);
    CALL_CallList(ctx->CurrentDispatch, (ctx, i));
}

static void GLAPIENTRY TAG(CallLists)(GLcontext *ctx, GLsizei sz, GLenum type, const GLvoid *v)
{
    PRE_LOOPBACK(CallLists);
    CALL_CallLists(ctx->CurrentDispatch, (ctx, sz, type, v));
}

static void GLAPIENTRY TAG(Begin)(GLcontext *ctx, GLenum mode)
{
    PRE_LOOPBACK(Begin);
    CALL_Begin(ctx->CurrentDispatch, (ctx, mode));
}

static void GLAPIENTRY TAG(End)(GLcontext *ctx)
{
    PRE_LOOPBACK(End);
    CALL_End(ctx->CurrentDispatch, (ctx));
}

static void GLAPIENTRY TAG(Rectf)(GLcontext *ctx, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    PRE_LOOPBACK(Rectf);
    CALL_Rectf(ctx->CurrentDispatch, (ctx, x1, y1, x2, y2));
}

static void GLAPIENTRY TAG(DrawArrays)(GLcontext *ctx, GLenum mode, GLint start, GLsizei count)
{
    PRE_LOOPBACK(DrawArrays);
    CALL_DrawArrays(ctx->CurrentDispatch, (ctx, mode, start, count));
}

static void GLAPIENTRY TAG(DrawElements)(GLcontext *ctx, GLenum mode, GLsizei count, GLenum type,
	const GLvoid *indices)
{
    PRE_LOOPBACK(DrawElements);
    CALL_DrawElements(ctx->CurrentDispatch, (ctx, mode, count, type, indices));
}

static void GLAPIENTRY TAG(DrawRangeElements)(GLcontext *ctx, GLenum mode, GLuint start,
	GLuint end, GLsizei count,
	GLenum type, const GLvoid *indices)
{
    PRE_LOOPBACK(DrawRangeElements);
    CALL_DrawRangeElements(ctx->CurrentDispatch, (ctx, mode, start, end, count, type, indices));
}

static void GLAPIENTRY TAG(EvalMesh1)(GLcontext *ctx, GLenum mode, GLint i1, GLint i2)
{
    PRE_LOOPBACK(EvalMesh1);
    CALL_EvalMesh1(ctx->CurrentDispatch, (ctx, mode, i1, i2));
}

static void GLAPIENTRY TAG(EvalMesh2)(GLcontext *ctx, GLenum mode, GLint i1, GLint i2,
				      GLint j1, GLint j2)
{
    PRE_LOOPBACK(EvalMesh2);
    CALL_EvalMesh2(ctx->CurrentDispatch, (ctx, mode, i1, i2, j1, j2));
}

static void GLAPIENTRY TAG(VertexAttrib1fNV)(GLcontext *ctx, GLuint index, GLfloat x)
{
    PRE_LOOPBACK(VertexAttrib1fNV);
    CALL_VertexAttrib1fNV(ctx->CurrentDispatch, (ctx, index, x));
}

static void GLAPIENTRY TAG(VertexAttrib1fvNV)(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    PRE_LOOPBACK(VertexAttrib1fvNV);
    CALL_VertexAttrib1fvNV(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY TAG(VertexAttrib2fNV)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y)
{
    PRE_LOOPBACK(VertexAttrib2fNV);
    CALL_VertexAttrib2fNV(ctx->CurrentDispatch, (ctx, index, x, y));
}

static void GLAPIENTRY TAG(VertexAttrib2fvNV)(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    PRE_LOOPBACK(VertexAttrib2fvNV);
    CALL_VertexAttrib2fvNV(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY TAG(VertexAttrib3fNV)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
    PRE_LOOPBACK(VertexAttrib3fNV);
    CALL_VertexAttrib3fNV(ctx->CurrentDispatch, (ctx, index, x, y, z));
}

static void GLAPIENTRY TAG(VertexAttrib3fvNV)(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    PRE_LOOPBACK(VertexAttrib3fvNV);
    CALL_VertexAttrib3fvNV(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY TAG(VertexAttrib4fNV)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    PRE_LOOPBACK(VertexAttrib4fNV);
    CALL_VertexAttrib4fNV(ctx->CurrentDispatch, (ctx, index, x, y, z, w));
}

static void GLAPIENTRY TAG(VertexAttrib4fvNV)(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    PRE_LOOPBACK(VertexAttrib4fvNV);
    CALL_VertexAttrib4fvNV(ctx->CurrentDispatch, (ctx, index, v));
}


static void GLAPIENTRY TAG(VertexAttrib1fARB)(GLcontext *ctx, GLuint index, GLfloat x)
{
    PRE_LOOPBACK(VertexAttrib1fARB);
    CALL_VertexAttrib1fARB(ctx->CurrentDispatch, (ctx, index, x));
}

static void GLAPIENTRY TAG(VertexAttrib1fvARB)(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    PRE_LOOPBACK(VertexAttrib1fvARB);
    CALL_VertexAttrib1fvARB(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY TAG(VertexAttrib2fARB)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y)
{
    PRE_LOOPBACK(VertexAttrib2fARB);
    CALL_VertexAttrib2fARB(ctx->CurrentDispatch, (ctx, index, x, y));
}

static void GLAPIENTRY TAG(VertexAttrib2fvARB)(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    PRE_LOOPBACK(VertexAttrib2fvARB);
    CALL_VertexAttrib2fvARB(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY TAG(VertexAttrib3fARB)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
    PRE_LOOPBACK(VertexAttrib3fARB);
    CALL_VertexAttrib3fARB(ctx->CurrentDispatch, (ctx, index, x, y, z));
}

static void GLAPIENTRY TAG(VertexAttrib3fvARB)(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    PRE_LOOPBACK(VertexAttrib3fvARB);
    CALL_VertexAttrib3fvARB(ctx->CurrentDispatch, (ctx, index, v));
}

static void GLAPIENTRY TAG(VertexAttrib4fARB)(GLcontext *ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    PRE_LOOPBACK(VertexAttrib4fARB);
    CALL_VertexAttrib4fARB(ctx->CurrentDispatch, (ctx, index, x, y, z, w));
}

static void GLAPIENTRY TAG(VertexAttrib4fvARB)(GLcontext *ctx, GLuint index, const GLfloat *v)
{
    PRE_LOOPBACK(VertexAttrib4fvARB);
    CALL_VertexAttrib4fvARB(ctx->CurrentDispatch, (ctx, index, v));
}


static GLvertexformat TAG(vtxfmt) = {
    TAG(ArrayElement),
    TAG(Color3f),
    TAG(Color3fv),
    TAG(Color4f),
    TAG(Color4fv),
    TAG(EdgeFlag),
    TAG(EvalCoord1f),
    TAG(EvalCoord1fv),
    TAG(EvalCoord2f),
    TAG(EvalCoord2fv),
    TAG(EvalPoint1),
    TAG(EvalPoint2),
    TAG(FogCoordfEXT),
    TAG(FogCoordfvEXT),
    TAG(Indexf),
    TAG(Indexfv),
    TAG(Materialfv),
    TAG(MultiTexCoord1fARB),
    TAG(MultiTexCoord1fvARB),
    TAG(MultiTexCoord2fARB),
    TAG(MultiTexCoord2fvARB),
    TAG(MultiTexCoord3fARB),
    TAG(MultiTexCoord3fvARB),
    TAG(MultiTexCoord4fARB),
    TAG(MultiTexCoord4fvARB),
    TAG(Normal3f),
    TAG(Normal3fv),
    TAG(SecondaryColor3fEXT),
    TAG(SecondaryColor3fvEXT),
    TAG(TexCoord1f),
    TAG(TexCoord1fv),
    TAG(TexCoord2f),
    TAG(TexCoord2fv),
    TAG(TexCoord3f),
    TAG(TexCoord3fv),
    TAG(TexCoord4f),
    TAG(TexCoord4fv),
    TAG(Vertex2f),
    TAG(Vertex2fv),
    TAG(Vertex3f),
    TAG(Vertex3fv),
    TAG(Vertex4f),
    TAG(Vertex4fv),
    TAG(CallList),
    TAG(CallLists),
    TAG(Begin),
    TAG(End),
    TAG(VertexAttrib1fNV),
    TAG(VertexAttrib1fvNV),
    TAG(VertexAttrib2fNV),
    TAG(VertexAttrib2fvNV),
    TAG(VertexAttrib3fNV),
    TAG(VertexAttrib3fvNV),
    TAG(VertexAttrib4fNV),
    TAG(VertexAttrib4fvNV),
    TAG(VertexAttrib1fARB),
    TAG(VertexAttrib1fvARB),
    TAG(VertexAttrib2fARB),
    TAG(VertexAttrib2fvARB),
    TAG(VertexAttrib3fARB),
    TAG(VertexAttrib3fvARB),
    TAG(VertexAttrib4fARB),
    TAG(VertexAttrib4fvARB),
    TAG(Rectf),
    TAG(DrawArrays),
    TAG(DrawElements),
    TAG(DrawRangeElements),
    TAG(EvalMesh1),
    TAG(EvalMesh2)
};

#undef TAG
#undef PRE_LOOPBACK

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
