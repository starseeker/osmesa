/*
 * OSMesa explicit-context API - glctx.h
 *
 * This header provides a zero-TLS alternative to the standard OpenGL API.
 * Every GL function is exposed as an inline wrapper that calls directly
 * through the dispatch table of the supplied OSMesaContext without
 * accessing any global or thread-local state.
 *
 * Usage:
 *
 *   #include "OSMesa/glctx.h"
 *
 *   OSMesaContext ctx = OSMesaCreateContext(OSMESA_RGBA, NULL);
 *   // ... OSMesaMakeCurrent to bind a buffer ...
 *
 *   // Call GL functions with an explicit context - no global state touched:
 *   osCtxClearColor(ctx, 0.0f, 0.0f, 0.0f, 1.0f);
 *   osCtxClear(ctx, GL_COLOR_BUFFER_BIT);
 *
 * All wrappers are named  osCtx<GLFunctionName>  and take an OSMesaContext
 * as their first argument, followed by the normal GL parameters.
 *
 * Generated from src/glapi/glapitable.h.
 */

#ifndef OSMESA_GLCTX_H
#define OSMESA_GLCTX_H

#include "OSMesa/osmesa.h"

/* Full dispatch table definition needed for member access in wrappers */
#include "OSMesa/glapitable.h"

#ifndef INLINE
#  ifdef __GNUC__
#    define INLINE __inline__
#  elif defined(_MSC_VER)
#    define INLINE __inline
#  else
#    define INLINE
#  endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

static INLINE void osCtxNewList(OSMesaContext _osCtx, GLuint list, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->NewList(_gl, list, mode);
}

static INLINE void osCtxEndList(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EndList(_gl);
}

static INLINE void osCtxCallList(OSMesaContext _osCtx, GLuint list)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CallList(_gl, list);
}

static INLINE void osCtxCallLists(OSMesaContext _osCtx, GLsizei n, GLenum type, const GLvoid * lists)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CallLists(_gl, n, type, lists);
}

static INLINE void osCtxDeleteLists(OSMesaContext _osCtx, GLuint list, GLsizei range)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteLists(_gl, list, range);
}

static INLINE void osCtxListBase(OSMesaContext _osCtx, GLuint base)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ListBase(_gl, base);
}

static INLINE void osCtxBegin(OSMesaContext _osCtx, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Begin(_gl, mode);
}

static INLINE void osCtxBitmap(OSMesaContext _osCtx, GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Bitmap(_gl, width, height, xorig, yorig, xmove, ymove, bitmap);
}

static INLINE void osCtxColor3b(OSMesaContext _osCtx, GLbyte red, GLbyte green, GLbyte blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3b(_gl, red, green, blue);
}

static INLINE void osCtxColor3bv(OSMesaContext _osCtx, const GLbyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3bv(_gl, v);
}

static INLINE void osCtxColor3d(OSMesaContext _osCtx, GLdouble red, GLdouble green, GLdouble blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3d(_gl, red, green, blue);
}

static INLINE void osCtxColor3dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3dv(_gl, v);
}

static INLINE void osCtxColor3f(OSMesaContext _osCtx, GLfloat red, GLfloat green, GLfloat blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3f(_gl, red, green, blue);
}

static INLINE void osCtxColor3fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3fv(_gl, v);
}

static INLINE void osCtxColor3i(OSMesaContext _osCtx, GLint red, GLint green, GLint blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3i(_gl, red, green, blue);
}

static INLINE void osCtxColor3iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3iv(_gl, v);
}

static INLINE void osCtxColor3s(OSMesaContext _osCtx, GLshort red, GLshort green, GLshort blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3s(_gl, red, green, blue);
}

static INLINE void osCtxColor3sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3sv(_gl, v);
}

static INLINE void osCtxColor3ub(OSMesaContext _osCtx, GLubyte red, GLubyte green, GLubyte blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3ub(_gl, red, green, blue);
}

static INLINE void osCtxColor3ubv(OSMesaContext _osCtx, const GLubyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3ubv(_gl, v);
}

static INLINE void osCtxColor3ui(OSMesaContext _osCtx, GLuint red, GLuint green, GLuint blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3ui(_gl, red, green, blue);
}

static INLINE void osCtxColor3uiv(OSMesaContext _osCtx, const GLuint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3uiv(_gl, v);
}

static INLINE void osCtxColor3us(OSMesaContext _osCtx, GLushort red, GLushort green, GLushort blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3us(_gl, red, green, blue);
}

static INLINE void osCtxColor3usv(OSMesaContext _osCtx, const GLushort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color3usv(_gl, v);
}

static INLINE void osCtxColor4b(OSMesaContext _osCtx, GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4b(_gl, red, green, blue, alpha);
}

static INLINE void osCtxColor4bv(OSMesaContext _osCtx, const GLbyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4bv(_gl, v);
}

static INLINE void osCtxColor4d(OSMesaContext _osCtx, GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4d(_gl, red, green, blue, alpha);
}

static INLINE void osCtxColor4dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4dv(_gl, v);
}

static INLINE void osCtxColor4f(OSMesaContext _osCtx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4f(_gl, red, green, blue, alpha);
}

static INLINE void osCtxColor4fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4fv(_gl, v);
}

static INLINE void osCtxColor4i(OSMesaContext _osCtx, GLint red, GLint green, GLint blue, GLint alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4i(_gl, red, green, blue, alpha);
}

static INLINE void osCtxColor4iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4iv(_gl, v);
}

static INLINE void osCtxColor4s(OSMesaContext _osCtx, GLshort red, GLshort green, GLshort blue, GLshort alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4s(_gl, red, green, blue, alpha);
}

static INLINE void osCtxColor4sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4sv(_gl, v);
}

static INLINE void osCtxColor4ub(OSMesaContext _osCtx, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4ub(_gl, red, green, blue, alpha);
}

static INLINE void osCtxColor4ubv(OSMesaContext _osCtx, const GLubyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4ubv(_gl, v);
}

static INLINE void osCtxColor4ui(OSMesaContext _osCtx, GLuint red, GLuint green, GLuint blue, GLuint alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4ui(_gl, red, green, blue, alpha);
}

static INLINE void osCtxColor4uiv(OSMesaContext _osCtx, const GLuint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4uiv(_gl, v);
}

static INLINE void osCtxColor4us(OSMesaContext _osCtx, GLushort red, GLushort green, GLushort blue, GLushort alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4us(_gl, red, green, blue, alpha);
}

static INLINE void osCtxColor4usv(OSMesaContext _osCtx, const GLushort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Color4usv(_gl, v);
}

static INLINE void osCtxEdgeFlag(OSMesaContext _osCtx, GLboolean flag)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EdgeFlag(_gl, flag);
}

static INLINE void osCtxEdgeFlagv(OSMesaContext _osCtx, const GLboolean * flag)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EdgeFlagv(_gl, flag);
}

static INLINE void osCtxEnd(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->End(_gl);
}

static INLINE void osCtxIndexd(OSMesaContext _osCtx, GLdouble c)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Indexd(_gl, c);
}

static INLINE void osCtxIndexdv(OSMesaContext _osCtx, const GLdouble * c)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Indexdv(_gl, c);
}

static INLINE void osCtxIndexf(OSMesaContext _osCtx, GLfloat c)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Indexf(_gl, c);
}

static INLINE void osCtxIndexfv(OSMesaContext _osCtx, const GLfloat * c)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Indexfv(_gl, c);
}

static INLINE void osCtxIndexi(OSMesaContext _osCtx, GLint c)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Indexi(_gl, c);
}

static INLINE void osCtxIndexiv(OSMesaContext _osCtx, const GLint * c)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Indexiv(_gl, c);
}

static INLINE void osCtxIndexs(OSMesaContext _osCtx, GLshort c)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Indexs(_gl, c);
}

static INLINE void osCtxIndexsv(OSMesaContext _osCtx, const GLshort * c)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Indexsv(_gl, c);
}

static INLINE void osCtxNormal3b(OSMesaContext _osCtx, GLbyte nx, GLbyte ny, GLbyte nz)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Normal3b(_gl, nx, ny, nz);
}

static INLINE void osCtxNormal3bv(OSMesaContext _osCtx, const GLbyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Normal3bv(_gl, v);
}

static INLINE void osCtxNormal3d(OSMesaContext _osCtx, GLdouble nx, GLdouble ny, GLdouble nz)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Normal3d(_gl, nx, ny, nz);
}

static INLINE void osCtxNormal3dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Normal3dv(_gl, v);
}

static INLINE void osCtxNormal3f(OSMesaContext _osCtx, GLfloat nx, GLfloat ny, GLfloat nz)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Normal3f(_gl, nx, ny, nz);
}

static INLINE void osCtxNormal3fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Normal3fv(_gl, v);
}

static INLINE void osCtxNormal3i(OSMesaContext _osCtx, GLint nx, GLint ny, GLint nz)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Normal3i(_gl, nx, ny, nz);
}

static INLINE void osCtxNormal3iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Normal3iv(_gl, v);
}

static INLINE void osCtxNormal3s(OSMesaContext _osCtx, GLshort nx, GLshort ny, GLshort nz)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Normal3s(_gl, nx, ny, nz);
}

static INLINE void osCtxNormal3sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Normal3sv(_gl, v);
}

static INLINE void osCtxRasterPos2d(OSMesaContext _osCtx, GLdouble x, GLdouble y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos2d(_gl, x, y);
}

static INLINE void osCtxRasterPos2dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos2dv(_gl, v);
}

static INLINE void osCtxRasterPos2f(OSMesaContext _osCtx, GLfloat x, GLfloat y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos2f(_gl, x, y);
}

static INLINE void osCtxRasterPos2fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos2fv(_gl, v);
}

static INLINE void osCtxRasterPos2i(OSMesaContext _osCtx, GLint x, GLint y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos2i(_gl, x, y);
}

static INLINE void osCtxRasterPos2iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos2iv(_gl, v);
}

static INLINE void osCtxRasterPos2s(OSMesaContext _osCtx, GLshort x, GLshort y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos2s(_gl, x, y);
}

static INLINE void osCtxRasterPos2sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos2sv(_gl, v);
}

static INLINE void osCtxRasterPos3d(OSMesaContext _osCtx, GLdouble x, GLdouble y, GLdouble z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos3d(_gl, x, y, z);
}

static INLINE void osCtxRasterPos3dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos3dv(_gl, v);
}

static INLINE void osCtxRasterPos3f(OSMesaContext _osCtx, GLfloat x, GLfloat y, GLfloat z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos3f(_gl, x, y, z);
}

static INLINE void osCtxRasterPos3fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos3fv(_gl, v);
}

static INLINE void osCtxRasterPos3i(OSMesaContext _osCtx, GLint x, GLint y, GLint z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos3i(_gl, x, y, z);
}

static INLINE void osCtxRasterPos3iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos3iv(_gl, v);
}

static INLINE void osCtxRasterPos3s(OSMesaContext _osCtx, GLshort x, GLshort y, GLshort z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos3s(_gl, x, y, z);
}

static INLINE void osCtxRasterPos3sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos3sv(_gl, v);
}

static INLINE void osCtxRasterPos4d(OSMesaContext _osCtx, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos4d(_gl, x, y, z, w);
}

static INLINE void osCtxRasterPos4dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos4dv(_gl, v);
}

static INLINE void osCtxRasterPos4f(OSMesaContext _osCtx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos4f(_gl, x, y, z, w);
}

static INLINE void osCtxRasterPos4fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos4fv(_gl, v);
}

static INLINE void osCtxRasterPos4i(OSMesaContext _osCtx, GLint x, GLint y, GLint z, GLint w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos4i(_gl, x, y, z, w);
}

static INLINE void osCtxRasterPos4iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos4iv(_gl, v);
}

static INLINE void osCtxRasterPos4s(OSMesaContext _osCtx, GLshort x, GLshort y, GLshort z, GLshort w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos4s(_gl, x, y, z, w);
}

static INLINE void osCtxRasterPos4sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RasterPos4sv(_gl, v);
}

static INLINE void osCtxRectd(OSMesaContext _osCtx, GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Rectd(_gl, x1, y1, x2, y2);
}

static INLINE void osCtxRectdv(OSMesaContext _osCtx, const GLdouble * v1, const GLdouble * v2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Rectdv(_gl, v1, v2);
}

static INLINE void osCtxRectf(OSMesaContext _osCtx, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Rectf(_gl, x1, y1, x2, y2);
}

static INLINE void osCtxRectfv(OSMesaContext _osCtx, const GLfloat * v1, const GLfloat * v2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Rectfv(_gl, v1, v2);
}

static INLINE void osCtxRecti(OSMesaContext _osCtx, GLint x1, GLint y1, GLint x2, GLint y2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Recti(_gl, x1, y1, x2, y2);
}

static INLINE void osCtxRectiv(OSMesaContext _osCtx, const GLint * v1, const GLint * v2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Rectiv(_gl, v1, v2);
}

static INLINE void osCtxRects(OSMesaContext _osCtx, GLshort x1, GLshort y1, GLshort x2, GLshort y2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Rects(_gl, x1, y1, x2, y2);
}

static INLINE void osCtxRectsv(OSMesaContext _osCtx, const GLshort * v1, const GLshort * v2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Rectsv(_gl, v1, v2);
}

static INLINE void osCtxTexCoord1d(OSMesaContext _osCtx, GLdouble s)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord1d(_gl, s);
}

static INLINE void osCtxTexCoord1dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord1dv(_gl, v);
}

static INLINE void osCtxTexCoord1f(OSMesaContext _osCtx, GLfloat s)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord1f(_gl, s);
}

static INLINE void osCtxTexCoord1fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord1fv(_gl, v);
}

static INLINE void osCtxTexCoord1i(OSMesaContext _osCtx, GLint s)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord1i(_gl, s);
}

static INLINE void osCtxTexCoord1iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord1iv(_gl, v);
}

static INLINE void osCtxTexCoord1s(OSMesaContext _osCtx, GLshort s)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord1s(_gl, s);
}

static INLINE void osCtxTexCoord1sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord1sv(_gl, v);
}

static INLINE void osCtxTexCoord2d(OSMesaContext _osCtx, GLdouble s, GLdouble t)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord2d(_gl, s, t);
}

static INLINE void osCtxTexCoord2dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord2dv(_gl, v);
}

static INLINE void osCtxTexCoord2f(OSMesaContext _osCtx, GLfloat s, GLfloat t)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord2f(_gl, s, t);
}

static INLINE void osCtxTexCoord2fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord2fv(_gl, v);
}

static INLINE void osCtxTexCoord2i(OSMesaContext _osCtx, GLint s, GLint t)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord2i(_gl, s, t);
}

static INLINE void osCtxTexCoord2iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord2iv(_gl, v);
}

static INLINE void osCtxTexCoord2s(OSMesaContext _osCtx, GLshort s, GLshort t)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord2s(_gl, s, t);
}

static INLINE void osCtxTexCoord2sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord2sv(_gl, v);
}

static INLINE void osCtxTexCoord3d(OSMesaContext _osCtx, GLdouble s, GLdouble t, GLdouble r)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord3d(_gl, s, t, r);
}

static INLINE void osCtxTexCoord3dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord3dv(_gl, v);
}

static INLINE void osCtxTexCoord3f(OSMesaContext _osCtx, GLfloat s, GLfloat t, GLfloat r)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord3f(_gl, s, t, r);
}

static INLINE void osCtxTexCoord3fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord3fv(_gl, v);
}

static INLINE void osCtxTexCoord3i(OSMesaContext _osCtx, GLint s, GLint t, GLint r)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord3i(_gl, s, t, r);
}

static INLINE void osCtxTexCoord3iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord3iv(_gl, v);
}

static INLINE void osCtxTexCoord3s(OSMesaContext _osCtx, GLshort s, GLshort t, GLshort r)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord3s(_gl, s, t, r);
}

static INLINE void osCtxTexCoord3sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord3sv(_gl, v);
}

static INLINE void osCtxTexCoord4d(OSMesaContext _osCtx, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord4d(_gl, s, t, r, q);
}

static INLINE void osCtxTexCoord4dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord4dv(_gl, v);
}

static INLINE void osCtxTexCoord4f(OSMesaContext _osCtx, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord4f(_gl, s, t, r, q);
}

static INLINE void osCtxTexCoord4fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord4fv(_gl, v);
}

static INLINE void osCtxTexCoord4i(OSMesaContext _osCtx, GLint s, GLint t, GLint r, GLint q)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord4i(_gl, s, t, r, q);
}

static INLINE void osCtxTexCoord4iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord4iv(_gl, v);
}

static INLINE void osCtxTexCoord4s(OSMesaContext _osCtx, GLshort s, GLshort t, GLshort r, GLshort q)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord4s(_gl, s, t, r, q);
}

static INLINE void osCtxTexCoord4sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoord4sv(_gl, v);
}

static INLINE void osCtxVertex2d(OSMesaContext _osCtx, GLdouble x, GLdouble y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex2d(_gl, x, y);
}

static INLINE void osCtxVertex2dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex2dv(_gl, v);
}

static INLINE void osCtxVertex2f(OSMesaContext _osCtx, GLfloat x, GLfloat y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex2f(_gl, x, y);
}

static INLINE void osCtxVertex2fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex2fv(_gl, v);
}

static INLINE void osCtxVertex2i(OSMesaContext _osCtx, GLint x, GLint y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex2i(_gl, x, y);
}

static INLINE void osCtxVertex2iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex2iv(_gl, v);
}

static INLINE void osCtxVertex2s(OSMesaContext _osCtx, GLshort x, GLshort y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex2s(_gl, x, y);
}

static INLINE void osCtxVertex2sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex2sv(_gl, v);
}

static INLINE void osCtxVertex3d(OSMesaContext _osCtx, GLdouble x, GLdouble y, GLdouble z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex3d(_gl, x, y, z);
}

static INLINE void osCtxVertex3dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex3dv(_gl, v);
}

static INLINE void osCtxVertex3f(OSMesaContext _osCtx, GLfloat x, GLfloat y, GLfloat z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex3f(_gl, x, y, z);
}

static INLINE void osCtxVertex3fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex3fv(_gl, v);
}

static INLINE void osCtxVertex3i(OSMesaContext _osCtx, GLint x, GLint y, GLint z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex3i(_gl, x, y, z);
}

static INLINE void osCtxVertex3iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex3iv(_gl, v);
}

static INLINE void osCtxVertex3s(OSMesaContext _osCtx, GLshort x, GLshort y, GLshort z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex3s(_gl, x, y, z);
}

static INLINE void osCtxVertex3sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex3sv(_gl, v);
}

static INLINE void osCtxVertex4d(OSMesaContext _osCtx, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex4d(_gl, x, y, z, w);
}

static INLINE void osCtxVertex4dv(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex4dv(_gl, v);
}

static INLINE void osCtxVertex4f(OSMesaContext _osCtx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex4f(_gl, x, y, z, w);
}

static INLINE void osCtxVertex4fv(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex4fv(_gl, v);
}

static INLINE void osCtxVertex4i(OSMesaContext _osCtx, GLint x, GLint y, GLint z, GLint w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex4i(_gl, x, y, z, w);
}

static INLINE void osCtxVertex4iv(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex4iv(_gl, v);
}

static INLINE void osCtxVertex4s(OSMesaContext _osCtx, GLshort x, GLshort y, GLshort z, GLshort w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex4s(_gl, x, y, z, w);
}

static INLINE void osCtxVertex4sv(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Vertex4sv(_gl, v);
}

static INLINE void osCtxClipPlane(OSMesaContext _osCtx, GLenum plane, const GLdouble * equation)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ClipPlane(_gl, plane, equation);
}

static INLINE void osCtxColorMaterial(OSMesaContext _osCtx, GLenum face, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ColorMaterial(_gl, face, mode);
}

static INLINE void osCtxCullFace(OSMesaContext _osCtx, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CullFace(_gl, mode);
}

static INLINE void osCtxFogf(OSMesaContext _osCtx, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Fogf(_gl, pname, param);
}

static INLINE void osCtxFogfv(OSMesaContext _osCtx, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Fogfv(_gl, pname, params);
}

static INLINE void osCtxFogi(OSMesaContext _osCtx, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Fogi(_gl, pname, param);
}

static INLINE void osCtxFogiv(OSMesaContext _osCtx, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Fogiv(_gl, pname, params);
}

static INLINE void osCtxFrontFace(OSMesaContext _osCtx, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FrontFace(_gl, mode);
}

static INLINE void osCtxHint(OSMesaContext _osCtx, GLenum target, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Hint(_gl, target, mode);
}

static INLINE void osCtxLightf(OSMesaContext _osCtx, GLenum light, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Lightf(_gl, light, pname, param);
}

static INLINE void osCtxLightfv(OSMesaContext _osCtx, GLenum light, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Lightfv(_gl, light, pname, params);
}

static INLINE void osCtxLighti(OSMesaContext _osCtx, GLenum light, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Lighti(_gl, light, pname, param);
}

static INLINE void osCtxLightiv(OSMesaContext _osCtx, GLenum light, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Lightiv(_gl, light, pname, params);
}

static INLINE void osCtxLightModelf(OSMesaContext _osCtx, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LightModelf(_gl, pname, param);
}

static INLINE void osCtxLightModelfv(OSMesaContext _osCtx, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LightModelfv(_gl, pname, params);
}

static INLINE void osCtxLightModeli(OSMesaContext _osCtx, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LightModeli(_gl, pname, param);
}

static INLINE void osCtxLightModeliv(OSMesaContext _osCtx, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LightModeliv(_gl, pname, params);
}

static INLINE void osCtxLineStipple(OSMesaContext _osCtx, GLint factor, GLushort pattern)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LineStipple(_gl, factor, pattern);
}

static INLINE void osCtxLineWidth(OSMesaContext _osCtx, GLfloat width)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LineWidth(_gl, width);
}

static INLINE void osCtxMaterialf(OSMesaContext _osCtx, GLenum face, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Materialf(_gl, face, pname, param);
}

static INLINE void osCtxMaterialfv(OSMesaContext _osCtx, GLenum face, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Materialfv(_gl, face, pname, params);
}

static INLINE void osCtxMateriali(OSMesaContext _osCtx, GLenum face, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Materiali(_gl, face, pname, param);
}

static INLINE void osCtxMaterialiv(OSMesaContext _osCtx, GLenum face, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Materialiv(_gl, face, pname, params);
}

static INLINE void osCtxPointSize(OSMesaContext _osCtx, GLfloat size)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PointSize(_gl, size);
}

static INLINE void osCtxPolygonMode(OSMesaContext _osCtx, GLenum face, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PolygonMode(_gl, face, mode);
}

static INLINE void osCtxPolygonStipple(OSMesaContext _osCtx, const GLubyte * mask)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PolygonStipple(_gl, mask);
}

static INLINE void osCtxScissor(OSMesaContext _osCtx, GLint x, GLint y, GLsizei width, GLsizei height)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Scissor(_gl, x, y, width, height);
}

static INLINE void osCtxShadeModel(OSMesaContext _osCtx, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ShadeModel(_gl, mode);
}

static INLINE void osCtxTexParameterf(OSMesaContext _osCtx, GLenum target, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexParameterf(_gl, target, pname, param);
}

static INLINE void osCtxTexParameterfv(OSMesaContext _osCtx, GLenum target, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexParameterfv(_gl, target, pname, params);
}

static INLINE void osCtxTexParameteri(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexParameteri(_gl, target, pname, param);
}

static INLINE void osCtxTexParameteriv(OSMesaContext _osCtx, GLenum target, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexParameteriv(_gl, target, pname, params);
}

static INLINE void osCtxTexImage1D(OSMesaContext _osCtx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexImage1D(_gl, target, level, internalformat, width, border, format, type, pixels);
}

static INLINE void osCtxTexImage2D(OSMesaContext _osCtx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexImage2D(_gl, target, level, internalformat, width, height, border, format, type, pixels);
}

static INLINE void osCtxTexEnvf(OSMesaContext _osCtx, GLenum target, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexEnvf(_gl, target, pname, param);
}

static INLINE void osCtxTexEnvfv(OSMesaContext _osCtx, GLenum target, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexEnvfv(_gl, target, pname, params);
}

static INLINE void osCtxTexEnvi(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexEnvi(_gl, target, pname, param);
}

static INLINE void osCtxTexEnviv(OSMesaContext _osCtx, GLenum target, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexEnviv(_gl, target, pname, params);
}

static INLINE void osCtxTexGend(OSMesaContext _osCtx, GLenum coord, GLenum pname, GLdouble param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexGend(_gl, coord, pname, param);
}

static INLINE void osCtxTexGendv(OSMesaContext _osCtx, GLenum coord, GLenum pname, const GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexGendv(_gl, coord, pname, params);
}

static INLINE void osCtxTexGenf(OSMesaContext _osCtx, GLenum coord, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexGenf(_gl, coord, pname, param);
}

static INLINE void osCtxTexGenfv(OSMesaContext _osCtx, GLenum coord, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexGenfv(_gl, coord, pname, params);
}

static INLINE void osCtxTexGeni(OSMesaContext _osCtx, GLenum coord, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexGeni(_gl, coord, pname, param);
}

static INLINE void osCtxTexGeniv(OSMesaContext _osCtx, GLenum coord, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexGeniv(_gl, coord, pname, params);
}

static INLINE void osCtxFeedbackBuffer(OSMesaContext _osCtx, GLsizei size, GLenum type, GLfloat * buffer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FeedbackBuffer(_gl, size, type, buffer);
}

static INLINE void osCtxSelectBuffer(OSMesaContext _osCtx, GLsizei size, GLuint * buffer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SelectBuffer(_gl, size, buffer);
}

static INLINE void osCtxInitNames(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->InitNames(_gl);
}

static INLINE void osCtxLoadName(OSMesaContext _osCtx, GLuint name)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LoadName(_gl, name);
}

static INLINE void osCtxPassThrough(OSMesaContext _osCtx, GLfloat token)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PassThrough(_gl, token);
}

static INLINE void osCtxPopName(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PopName(_gl);
}

static INLINE void osCtxPushName(OSMesaContext _osCtx, GLuint name)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PushName(_gl, name);
}

static INLINE void osCtxDrawBuffer(OSMesaContext _osCtx, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DrawBuffer(_gl, mode);
}

static INLINE void osCtxClear(OSMesaContext _osCtx, GLbitfield mask)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Clear(_gl, mask);
}

static INLINE void osCtxClearAccum(OSMesaContext _osCtx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ClearAccum(_gl, red, green, blue, alpha);
}

static INLINE void osCtxClearIndex(OSMesaContext _osCtx, GLfloat c)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ClearIndex(_gl, c);
}

static INLINE void osCtxClearColor(OSMesaContext _osCtx, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ClearColor(_gl, red, green, blue, alpha);
}

static INLINE void osCtxClearStencil(OSMesaContext _osCtx, GLint s)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ClearStencil(_gl, s);
}

static INLINE void osCtxClearDepth(OSMesaContext _osCtx, GLclampd depth)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ClearDepth(_gl, depth);
}

static INLINE void osCtxStencilMask(OSMesaContext _osCtx, GLuint mask)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->StencilMask(_gl, mask);
}

static INLINE void osCtxColorMask(OSMesaContext _osCtx, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ColorMask(_gl, red, green, blue, alpha);
}

static INLINE void osCtxDepthMask(OSMesaContext _osCtx, GLboolean flag)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DepthMask(_gl, flag);
}

static INLINE void osCtxIndexMask(OSMesaContext _osCtx, GLuint mask)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->IndexMask(_gl, mask);
}

static INLINE void osCtxAccum(OSMesaContext _osCtx, GLenum op, GLfloat value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Accum(_gl, op, value);
}

static INLINE void osCtxDisable(OSMesaContext _osCtx, GLenum cap)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Disable(_gl, cap);
}

static INLINE void osCtxEnable(OSMesaContext _osCtx, GLenum cap)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Enable(_gl, cap);
}

static INLINE void osCtxFinish(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Finish(_gl);
}

static INLINE void osCtxFlush(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Flush(_gl);
}

static INLINE void osCtxPopAttrib(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PopAttrib(_gl);
}

static INLINE void osCtxPushAttrib(OSMesaContext _osCtx, GLbitfield mask)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PushAttrib(_gl, mask);
}

static INLINE void osCtxMap1d(OSMesaContext _osCtx, GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Map1d(_gl, target, u1, u2, stride, order, points);
}

static INLINE void osCtxMap1f(OSMesaContext _osCtx, GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Map1f(_gl, target, u1, u2, stride, order, points);
}

static INLINE void osCtxMap2d(OSMesaContext _osCtx, GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Map2d(_gl, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

static INLINE void osCtxMap2f(OSMesaContext _osCtx, GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Map2f(_gl, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

static INLINE void osCtxMapGrid1d(OSMesaContext _osCtx, GLint un, GLdouble u1, GLdouble u2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MapGrid1d(_gl, un, u1, u2);
}

static INLINE void osCtxMapGrid1f(OSMesaContext _osCtx, GLint un, GLfloat u1, GLfloat u2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MapGrid1f(_gl, un, u1, u2);
}

static INLINE void osCtxMapGrid2d(OSMesaContext _osCtx, GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MapGrid2d(_gl, un, u1, u2, vn, v1, v2);
}

static INLINE void osCtxMapGrid2f(OSMesaContext _osCtx, GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MapGrid2f(_gl, un, u1, u2, vn, v1, v2);
}

static INLINE void osCtxEvalCoord1d(OSMesaContext _osCtx, GLdouble u)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalCoord1d(_gl, u);
}

static INLINE void osCtxEvalCoord1dv(OSMesaContext _osCtx, const GLdouble * u)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalCoord1dv(_gl, u);
}

static INLINE void osCtxEvalCoord1f(OSMesaContext _osCtx, GLfloat u)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalCoord1f(_gl, u);
}

static INLINE void osCtxEvalCoord1fv(OSMesaContext _osCtx, const GLfloat * u)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalCoord1fv(_gl, u);
}

static INLINE void osCtxEvalCoord2d(OSMesaContext _osCtx, GLdouble u, GLdouble v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalCoord2d(_gl, u, v);
}

static INLINE void osCtxEvalCoord2dv(OSMesaContext _osCtx, const GLdouble * u)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalCoord2dv(_gl, u);
}

static INLINE void osCtxEvalCoord2f(OSMesaContext _osCtx, GLfloat u, GLfloat v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalCoord2f(_gl, u, v);
}

static INLINE void osCtxEvalCoord2fv(OSMesaContext _osCtx, const GLfloat * u)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalCoord2fv(_gl, u);
}

static INLINE void osCtxEvalMesh1(OSMesaContext _osCtx, GLenum mode, GLint i1, GLint i2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalMesh1(_gl, mode, i1, i2);
}

static INLINE void osCtxEvalPoint1(OSMesaContext _osCtx, GLint i)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalPoint1(_gl, i);
}

static INLINE void osCtxEvalMesh2(OSMesaContext _osCtx, GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalMesh2(_gl, mode, i1, i2, j1, j2);
}

static INLINE void osCtxEvalPoint2(OSMesaContext _osCtx, GLint i, GLint j)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EvalPoint2(_gl, i, j);
}

static INLINE void osCtxAlphaFunc(OSMesaContext _osCtx, GLenum func, GLclampf ref)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->AlphaFunc(_gl, func, ref);
}

static INLINE void osCtxBlendFunc(OSMesaContext _osCtx, GLenum sfactor, GLenum dfactor)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BlendFunc(_gl, sfactor, dfactor);
}

static INLINE void osCtxLogicOp(OSMesaContext _osCtx, GLenum opcode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LogicOp(_gl, opcode);
}

static INLINE void osCtxStencilFunc(OSMesaContext _osCtx, GLenum func, GLint ref, GLuint mask)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->StencilFunc(_gl, func, ref, mask);
}

static INLINE void osCtxStencilOp(OSMesaContext _osCtx, GLenum fail, GLenum zfail, GLenum zpass)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->StencilOp(_gl, fail, zfail, zpass);
}

static INLINE void osCtxDepthFunc(OSMesaContext _osCtx, GLenum func)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DepthFunc(_gl, func);
}

static INLINE void osCtxPixelZoom(OSMesaContext _osCtx, GLfloat xfactor, GLfloat yfactor)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelZoom(_gl, xfactor, yfactor);
}

static INLINE void osCtxPixelTransferf(OSMesaContext _osCtx, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelTransferf(_gl, pname, param);
}

static INLINE void osCtxPixelTransferi(OSMesaContext _osCtx, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelTransferi(_gl, pname, param);
}

static INLINE void osCtxPixelStoref(OSMesaContext _osCtx, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelStoref(_gl, pname, param);
}

static INLINE void osCtxPixelStorei(OSMesaContext _osCtx, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelStorei(_gl, pname, param);
}

static INLINE void osCtxPixelMapfv(OSMesaContext _osCtx, GLenum map, GLsizei mapsize, const GLfloat * values)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelMapfv(_gl, map, mapsize, values);
}

static INLINE void osCtxPixelMapuiv(OSMesaContext _osCtx, GLenum map, GLsizei mapsize, const GLuint * values)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelMapuiv(_gl, map, mapsize, values);
}

static INLINE void osCtxPixelMapusv(OSMesaContext _osCtx, GLenum map, GLsizei mapsize, const GLushort * values)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelMapusv(_gl, map, mapsize, values);
}

static INLINE void osCtxReadBuffer(OSMesaContext _osCtx, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ReadBuffer(_gl, mode);
}

static INLINE void osCtxCopyPixels(OSMesaContext _osCtx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum type)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CopyPixels(_gl, x, y, width, height, type);
}

static INLINE void osCtxReadPixels(OSMesaContext _osCtx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ReadPixels(_gl, x, y, width, height, format, type, pixels);
}

static INLINE void osCtxDrawPixels(OSMesaContext _osCtx, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DrawPixels(_gl, width, height, format, type, pixels);
}

static INLINE void osCtxGetBooleanv(OSMesaContext _osCtx, GLenum pname, GLboolean * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetBooleanv(_gl, pname, params);
}

static INLINE void osCtxGetClipPlane(OSMesaContext _osCtx, GLenum plane, GLdouble * equation)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetClipPlane(_gl, plane, equation);
}

static INLINE void osCtxGetDoublev(OSMesaContext _osCtx, GLenum pname, GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetDoublev(_gl, pname, params);
}

static INLINE void osCtxGetFloatv(OSMesaContext _osCtx, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetFloatv(_gl, pname, params);
}

static INLINE void osCtxGetIntegerv(OSMesaContext _osCtx, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetIntegerv(_gl, pname, params);
}

static INLINE void osCtxGetLightfv(OSMesaContext _osCtx, GLenum light, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetLightfv(_gl, light, pname, params);
}

static INLINE void osCtxGetLightiv(OSMesaContext _osCtx, GLenum light, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetLightiv(_gl, light, pname, params);
}

static INLINE void osCtxGetMapdv(OSMesaContext _osCtx, GLenum target, GLenum query, GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetMapdv(_gl, target, query, v);
}

static INLINE void osCtxGetMapfv(OSMesaContext _osCtx, GLenum target, GLenum query, GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetMapfv(_gl, target, query, v);
}

static INLINE void osCtxGetMapiv(OSMesaContext _osCtx, GLenum target, GLenum query, GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetMapiv(_gl, target, query, v);
}

static INLINE void osCtxGetMaterialfv(OSMesaContext _osCtx, GLenum face, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetMaterialfv(_gl, face, pname, params);
}

static INLINE void osCtxGetMaterialiv(OSMesaContext _osCtx, GLenum face, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetMaterialiv(_gl, face, pname, params);
}

static INLINE void osCtxGetPixelMapfv(OSMesaContext _osCtx, GLenum map, GLfloat * values)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetPixelMapfv(_gl, map, values);
}

static INLINE void osCtxGetPixelMapuiv(OSMesaContext _osCtx, GLenum map, GLuint * values)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetPixelMapuiv(_gl, map, values);
}

static INLINE void osCtxGetPixelMapusv(OSMesaContext _osCtx, GLenum map, GLushort * values)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetPixelMapusv(_gl, map, values);
}

static INLINE void osCtxGetPolygonStipple(OSMesaContext _osCtx, GLubyte * mask)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetPolygonStipple(_gl, mask);
}

static INLINE const GLubyte * osCtxGetString(OSMesaContext _osCtx, GLenum name)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    return _tbl->GetString(_gl, name);
}

static INLINE void osCtxGetTexEnvfv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetTexEnvfv(_gl, target, pname, params);
}

static INLINE void osCtxGetTexEnviv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetTexEnviv(_gl, target, pname, params);
}

static INLINE void osCtxGetTexGendv(OSMesaContext _osCtx, GLenum coord, GLenum pname, GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetTexGendv(_gl, coord, pname, params);
}

static INLINE void osCtxGetTexGenfv(OSMesaContext _osCtx, GLenum coord, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetTexGenfv(_gl, coord, pname, params);
}

static INLINE void osCtxGetTexGeniv(OSMesaContext _osCtx, GLenum coord, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetTexGeniv(_gl, coord, pname, params);
}

static INLINE void osCtxGetTexImage(OSMesaContext _osCtx, GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetTexImage(_gl, target, level, format, type, pixels);
}

static INLINE void osCtxGetTexParameterfv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetTexParameterfv(_gl, target, pname, params);
}

static INLINE void osCtxGetTexParameteriv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetTexParameteriv(_gl, target, pname, params);
}

static INLINE void osCtxGetTexLevelParameterfv(OSMesaContext _osCtx, GLenum target, GLint level, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetTexLevelParameterfv(_gl, target, level, pname, params);
}

static INLINE void osCtxGetTexLevelParameteriv(OSMesaContext _osCtx, GLenum target, GLint level, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetTexLevelParameteriv(_gl, target, level, pname, params);
}

static INLINE void osCtxDepthRange(OSMesaContext _osCtx, GLclampd zNear, GLclampd zFar)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DepthRange(_gl, zNear, zFar);
}

static INLINE void osCtxFrustum(OSMesaContext _osCtx, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Frustum(_gl, left, right, bottom, top, zNear, zFar);
}

static INLINE void osCtxLoadIdentity(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LoadIdentity(_gl);
}

static INLINE void osCtxLoadMatrixf(OSMesaContext _osCtx, const GLfloat * m)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LoadMatrixf(_gl, m);
}

static INLINE void osCtxLoadMatrixd(OSMesaContext _osCtx, const GLdouble * m)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LoadMatrixd(_gl, m);
}

static INLINE void osCtxMatrixMode(OSMesaContext _osCtx, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MatrixMode(_gl, mode);
}

static INLINE void osCtxMultMatrixf(OSMesaContext _osCtx, const GLfloat * m)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultMatrixf(_gl, m);
}

static INLINE void osCtxMultMatrixd(OSMesaContext _osCtx, const GLdouble * m)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultMatrixd(_gl, m);
}

static INLINE void osCtxOrtho(OSMesaContext _osCtx, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Ortho(_gl, left, right, bottom, top, zNear, zFar);
}

static INLINE void osCtxPopMatrix(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PopMatrix(_gl);
}

static INLINE void osCtxPushMatrix(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PushMatrix(_gl);
}

static INLINE void osCtxRotated(OSMesaContext _osCtx, GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Rotated(_gl, angle, x, y, z);
}

static INLINE void osCtxRotatef(OSMesaContext _osCtx, GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Rotatef(_gl, angle, x, y, z);
}

static INLINE void osCtxScaled(OSMesaContext _osCtx, GLdouble x, GLdouble y, GLdouble z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Scaled(_gl, x, y, z);
}

static INLINE void osCtxScalef(OSMesaContext _osCtx, GLfloat x, GLfloat y, GLfloat z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Scalef(_gl, x, y, z);
}

static INLINE void osCtxTranslated(OSMesaContext _osCtx, GLdouble x, GLdouble y, GLdouble z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Translated(_gl, x, y, z);
}

static INLINE void osCtxTranslatef(OSMesaContext _osCtx, GLfloat x, GLfloat y, GLfloat z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Translatef(_gl, x, y, z);
}

static INLINE void osCtxViewport(OSMesaContext _osCtx, GLint x, GLint y, GLsizei width, GLsizei height)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Viewport(_gl, x, y, width, height);
}

static INLINE void osCtxArrayElement(OSMesaContext _osCtx, GLint i)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ArrayElement(_gl, i);
}

static INLINE void osCtxBindTexture(OSMesaContext _osCtx, GLenum target, GLuint texture)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BindTexture(_gl, target, texture);
}

static INLINE void osCtxColorPointer(OSMesaContext _osCtx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ColorPointer(_gl, size, type, stride, pointer);
}

static INLINE void osCtxDisableClientState(OSMesaContext _osCtx, GLenum array)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DisableClientState(_gl, array);
}

static INLINE void osCtxDrawArrays(OSMesaContext _osCtx, GLenum mode, GLint first, GLsizei count)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DrawArrays(_gl, mode, first, count);
}

static INLINE void osCtxDrawElements(OSMesaContext _osCtx, GLenum mode, GLsizei count, GLenum type, const GLvoid * indices)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DrawElements(_gl, mode, count, type, indices);
}

static INLINE void osCtxEdgeFlagPointer(OSMesaContext _osCtx, GLsizei stride, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EdgeFlagPointer(_gl, stride, pointer);
}

static INLINE void osCtxEnableClientState(OSMesaContext _osCtx, GLenum array)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EnableClientState(_gl, array);
}

static INLINE void osCtxIndexPointer(OSMesaContext _osCtx, GLenum type, GLsizei stride, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->IndexPointer(_gl, type, stride, pointer);
}

static INLINE void osCtxIndexub(OSMesaContext _osCtx, GLubyte c)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Indexub(_gl, c);
}

static INLINE void osCtxIndexubv(OSMesaContext _osCtx, const GLubyte * c)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Indexubv(_gl, c);
}

static INLINE void osCtxInterleavedArrays(OSMesaContext _osCtx, GLenum format, GLsizei stride, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->InterleavedArrays(_gl, format, stride, pointer);
}

static INLINE void osCtxNormalPointer(OSMesaContext _osCtx, GLenum type, GLsizei stride, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->NormalPointer(_gl, type, stride, pointer);
}

static INLINE void osCtxPolygonOffset(OSMesaContext _osCtx, GLfloat factor, GLfloat units)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PolygonOffset(_gl, factor, units);
}

static INLINE void osCtxTexCoordPointer(OSMesaContext _osCtx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoordPointer(_gl, size, type, stride, pointer);
}

static INLINE void osCtxVertexPointer(OSMesaContext _osCtx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexPointer(_gl, size, type, stride, pointer);
}

static INLINE void osCtxCopyTexImage1D(OSMesaContext _osCtx, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CopyTexImage1D(_gl, target, level, internalformat, x, y, width, border);
}

static INLINE void osCtxCopyTexImage2D(OSMesaContext _osCtx, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CopyTexImage2D(_gl, target, level, internalformat, x, y, width, height, border);
}

static INLINE void osCtxCopyTexSubImage1D(OSMesaContext _osCtx, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CopyTexSubImage1D(_gl, target, level, xoffset, x, y, width);
}

static INLINE void osCtxCopyTexSubImage2D(OSMesaContext _osCtx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CopyTexSubImage2D(_gl, target, level, xoffset, yoffset, x, y, width, height);
}

static INLINE void osCtxDeleteTextures(OSMesaContext _osCtx, GLsizei n, const GLuint * textures)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteTextures(_gl, n, textures);
}

static INLINE void osCtxGenTextures(OSMesaContext _osCtx, GLsizei n, GLuint * textures)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GenTextures(_gl, n, textures);
}

static INLINE void osCtxGetPointerv(OSMesaContext _osCtx, GLenum pname, GLvoid ** params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetPointerv(_gl, pname, params);
}

static INLINE void osCtxPrioritizeTextures(OSMesaContext _osCtx, GLsizei n, const GLuint * textures, const GLclampf * priorities)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PrioritizeTextures(_gl, n, textures, priorities);
}

static INLINE void osCtxTexSubImage1D(OSMesaContext _osCtx, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexSubImage1D(_gl, target, level, xoffset, width, format, type, pixels);
}

static INLINE void osCtxTexSubImage2D(OSMesaContext _osCtx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexSubImage2D(_gl, target, level, xoffset, yoffset, width, height, format, type, pixels);
}

static INLINE void osCtxPopClientAttrib(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PopClientAttrib(_gl);
}

static INLINE void osCtxPushClientAttrib(OSMesaContext _osCtx, GLbitfield mask)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PushClientAttrib(_gl, mask);
}

static INLINE void osCtxBlendColor(OSMesaContext _osCtx, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BlendColor(_gl, red, green, blue, alpha);
}

static INLINE void osCtxBlendEquation(OSMesaContext _osCtx, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BlendEquation(_gl, mode);
}

static INLINE void osCtxDrawRangeElements(OSMesaContext _osCtx, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DrawRangeElements(_gl, mode, start, end, count, type, indices);
}

static INLINE void osCtxColorTable(OSMesaContext _osCtx, GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * table)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ColorTable(_gl, target, internalformat, width, format, type, table);
}

static INLINE void osCtxColorTableParameterfv(OSMesaContext _osCtx, GLenum target, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ColorTableParameterfv(_gl, target, pname, params);
}

static INLINE void osCtxColorTableParameteriv(OSMesaContext _osCtx, GLenum target, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ColorTableParameteriv(_gl, target, pname, params);
}

static INLINE void osCtxCopyColorTable(OSMesaContext _osCtx, GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CopyColorTable(_gl, target, internalformat, x, y, width);
}

static INLINE void osCtxGetColorTable(OSMesaContext _osCtx, GLenum target, GLenum format, GLenum type, GLvoid * table)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetColorTable(_gl, target, format, type, table);
}

static INLINE void osCtxGetColorTableParameterfv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetColorTableParameterfv(_gl, target, pname, params);
}

static INLINE void osCtxGetColorTableParameteriv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetColorTableParameteriv(_gl, target, pname, params);
}

static INLINE void osCtxColorSubTable(OSMesaContext _osCtx, GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid * data)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ColorSubTable(_gl, target, start, count, format, type, data);
}

static INLINE void osCtxCopyColorSubTable(OSMesaContext _osCtx, GLenum target, GLsizei start, GLint x, GLint y, GLsizei width)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CopyColorSubTable(_gl, target, start, x, y, width);
}

static INLINE void osCtxConvolutionFilter1D(OSMesaContext _osCtx, GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * image)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ConvolutionFilter1D(_gl, target, internalformat, width, format, type, image);
}

static INLINE void osCtxConvolutionFilter2D(OSMesaContext _osCtx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * image)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ConvolutionFilter2D(_gl, target, internalformat, width, height, format, type, image);
}

static INLINE void osCtxConvolutionParameterf(OSMesaContext _osCtx, GLenum target, GLenum pname, GLfloat params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ConvolutionParameterf(_gl, target, pname, params);
}

static INLINE void osCtxConvolutionParameterfv(OSMesaContext _osCtx, GLenum target, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ConvolutionParameterfv(_gl, target, pname, params);
}

static INLINE void osCtxConvolutionParameteri(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ConvolutionParameteri(_gl, target, pname, params);
}

static INLINE void osCtxConvolutionParameteriv(OSMesaContext _osCtx, GLenum target, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ConvolutionParameteriv(_gl, target, pname, params);
}

static INLINE void osCtxCopyConvolutionFilter1D(OSMesaContext _osCtx, GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CopyConvolutionFilter1D(_gl, target, internalformat, x, y, width);
}

static INLINE void osCtxCopyConvolutionFilter2D(OSMesaContext _osCtx, GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CopyConvolutionFilter2D(_gl, target, internalformat, x, y, width, height);
}

static INLINE void osCtxGetConvolutionFilter(OSMesaContext _osCtx, GLenum target, GLenum format, GLenum type, GLvoid * image)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetConvolutionFilter(_gl, target, format, type, image);
}

static INLINE void osCtxGetConvolutionParameterfv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetConvolutionParameterfv(_gl, target, pname, params);
}

static INLINE void osCtxGetConvolutionParameteriv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetConvolutionParameteriv(_gl, target, pname, params);
}

static INLINE void osCtxGetSeparableFilter(OSMesaContext _osCtx, GLenum target, GLenum format, GLenum type, GLvoid * row, GLvoid * column, GLvoid * span)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetSeparableFilter(_gl, target, format, type, row, column, span);
}

static INLINE void osCtxSeparableFilter2D(OSMesaContext _osCtx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * row, const GLvoid * column)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SeparableFilter2D(_gl, target, internalformat, width, height, format, type, row, column);
}

static INLINE void osCtxGetHistogram(OSMesaContext _osCtx, GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetHistogram(_gl, target, reset, format, type, values);
}

static INLINE void osCtxGetHistogramParameterfv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetHistogramParameterfv(_gl, target, pname, params);
}

static INLINE void osCtxGetHistogramParameteriv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetHistogramParameteriv(_gl, target, pname, params);
}

static INLINE void osCtxGetMinmax(OSMesaContext _osCtx, GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetMinmax(_gl, target, reset, format, type, values);
}

static INLINE void osCtxGetMinmaxParameterfv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetMinmaxParameterfv(_gl, target, pname, params);
}

static INLINE void osCtxGetMinmaxParameteriv(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetMinmaxParameteriv(_gl, target, pname, params);
}

static INLINE void osCtxHistogram(OSMesaContext _osCtx, GLenum target, GLsizei width, GLenum internalformat, GLboolean sink)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Histogram(_gl, target, width, internalformat, sink);
}

static INLINE void osCtxMinmax(OSMesaContext _osCtx, GLenum target, GLenum internalformat, GLboolean sink)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Minmax(_gl, target, internalformat, sink);
}

static INLINE void osCtxResetHistogram(OSMesaContext _osCtx, GLenum target)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ResetHistogram(_gl, target);
}

static INLINE void osCtxResetMinmax(OSMesaContext _osCtx, GLenum target)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ResetMinmax(_gl, target);
}

static INLINE void osCtxTexImage3D(OSMesaContext _osCtx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexImage3D(_gl, target, level, internalformat, width, height, depth, border, format, type, pixels);
}

static INLINE void osCtxTexSubImage3D(OSMesaContext _osCtx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexSubImage3D(_gl, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

static INLINE void osCtxCopyTexSubImage3D(OSMesaContext _osCtx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CopyTexSubImage3D(_gl, target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

static INLINE void osCtxActiveTextureARB(OSMesaContext _osCtx, GLenum texture)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ActiveTextureARB(_gl, texture);
}

static INLINE void osCtxClientActiveTextureARB(OSMesaContext _osCtx, GLenum texture)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ClientActiveTextureARB(_gl, texture);
}

static INLINE void osCtxMultiTexCoord1dARB(OSMesaContext _osCtx, GLenum target, GLdouble s)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord1dARB(_gl, target, s);
}

static INLINE void osCtxMultiTexCoord1dvARB(OSMesaContext _osCtx, GLenum target, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord1dvARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord1fARB(OSMesaContext _osCtx, GLenum target, GLfloat s)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord1fARB(_gl, target, s);
}

static INLINE void osCtxMultiTexCoord1fvARB(OSMesaContext _osCtx, GLenum target, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord1fvARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord1iARB(OSMesaContext _osCtx, GLenum target, GLint s)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord1iARB(_gl, target, s);
}

static INLINE void osCtxMultiTexCoord1ivARB(OSMesaContext _osCtx, GLenum target, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord1ivARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord1sARB(OSMesaContext _osCtx, GLenum target, GLshort s)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord1sARB(_gl, target, s);
}

static INLINE void osCtxMultiTexCoord1svARB(OSMesaContext _osCtx, GLenum target, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord1svARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord2dARB(OSMesaContext _osCtx, GLenum target, GLdouble s, GLdouble t)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord2dARB(_gl, target, s, t);
}

static INLINE void osCtxMultiTexCoord2dvARB(OSMesaContext _osCtx, GLenum target, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord2dvARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord2fARB(OSMesaContext _osCtx, GLenum target, GLfloat s, GLfloat t)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord2fARB(_gl, target, s, t);
}

static INLINE void osCtxMultiTexCoord2fvARB(OSMesaContext _osCtx, GLenum target, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord2fvARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord2iARB(OSMesaContext _osCtx, GLenum target, GLint s, GLint t)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord2iARB(_gl, target, s, t);
}

static INLINE void osCtxMultiTexCoord2ivARB(OSMesaContext _osCtx, GLenum target, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord2ivARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord2sARB(OSMesaContext _osCtx, GLenum target, GLshort s, GLshort t)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord2sARB(_gl, target, s, t);
}

static INLINE void osCtxMultiTexCoord2svARB(OSMesaContext _osCtx, GLenum target, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord2svARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord3dARB(OSMesaContext _osCtx, GLenum target, GLdouble s, GLdouble t, GLdouble r)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord3dARB(_gl, target, s, t, r);
}

static INLINE void osCtxMultiTexCoord3dvARB(OSMesaContext _osCtx, GLenum target, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord3dvARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord3fARB(OSMesaContext _osCtx, GLenum target, GLfloat s, GLfloat t, GLfloat r)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord3fARB(_gl, target, s, t, r);
}

static INLINE void osCtxMultiTexCoord3fvARB(OSMesaContext _osCtx, GLenum target, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord3fvARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord3iARB(OSMesaContext _osCtx, GLenum target, GLint s, GLint t, GLint r)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord3iARB(_gl, target, s, t, r);
}

static INLINE void osCtxMultiTexCoord3ivARB(OSMesaContext _osCtx, GLenum target, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord3ivARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord3sARB(OSMesaContext _osCtx, GLenum target, GLshort s, GLshort t, GLshort r)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord3sARB(_gl, target, s, t, r);
}

static INLINE void osCtxMultiTexCoord3svARB(OSMesaContext _osCtx, GLenum target, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord3svARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord4dARB(OSMesaContext _osCtx, GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord4dARB(_gl, target, s, t, r, q);
}

static INLINE void osCtxMultiTexCoord4dvARB(OSMesaContext _osCtx, GLenum target, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord4dvARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord4fARB(OSMesaContext _osCtx, GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord4fARB(_gl, target, s, t, r, q);
}

static INLINE void osCtxMultiTexCoord4fvARB(OSMesaContext _osCtx, GLenum target, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord4fvARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord4iARB(OSMesaContext _osCtx, GLenum target, GLint s, GLint t, GLint r, GLint q)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord4iARB(_gl, target, s, t, r, q);
}

static INLINE void osCtxMultiTexCoord4ivARB(OSMesaContext _osCtx, GLenum target, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord4ivARB(_gl, target, v);
}

static INLINE void osCtxMultiTexCoord4sARB(OSMesaContext _osCtx, GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord4sARB(_gl, target, s, t, r, q);
}

static INLINE void osCtxMultiTexCoord4svARB(OSMesaContext _osCtx, GLenum target, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiTexCoord4svARB(_gl, target, v);
}

static INLINE void osCtxAttachShader(OSMesaContext _osCtx, GLuint program, GLuint shader)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->AttachShader(_gl, program, shader);
}

static INLINE void osCtxDeleteProgram(OSMesaContext _osCtx, GLuint program)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteProgram(_gl, program);
}

static INLINE void osCtxDeleteShader(OSMesaContext _osCtx, GLuint program)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteShader(_gl, program);
}

static INLINE void osCtxDetachShader(OSMesaContext _osCtx, GLuint program, GLuint shader)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DetachShader(_gl, program, shader);
}

static INLINE void osCtxGetAttachedShaders(OSMesaContext _osCtx, GLuint program, GLsizei maxCount, GLsizei * count, GLuint * obj)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetAttachedShaders(_gl, program, maxCount, count, obj);
}

static INLINE void osCtxGetProgramInfoLog(OSMesaContext _osCtx, GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramInfoLog(_gl, program, bufSize, length, infoLog);
}

static INLINE void osCtxGetProgramiv(OSMesaContext _osCtx, GLuint program, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramiv(_gl, program, pname, params);
}

static INLINE void osCtxGetShaderInfoLog(OSMesaContext _osCtx, GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetShaderInfoLog(_gl, shader, bufSize, length, infoLog);
}

static INLINE void osCtxGetShaderiv(OSMesaContext _osCtx, GLuint shader, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetShaderiv(_gl, shader, pname, params);
}

static INLINE void osCtxStencilFuncSeparate(OSMesaContext _osCtx, GLenum face, GLenum func, GLint ref, GLuint mask)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->StencilFuncSeparate(_gl, face, func, ref, mask);
}

static INLINE void osCtxStencilMaskSeparate(OSMesaContext _osCtx, GLenum face, GLuint mask)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->StencilMaskSeparate(_gl, face, mask);
}

static INLINE void osCtxStencilOpSeparate(OSMesaContext _osCtx, GLenum face, GLenum sfail, GLenum zfail, GLenum zpass)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->StencilOpSeparate(_gl, face, sfail, zfail, zpass);
}

static INLINE void osCtxUniformMatrix2x3fv(OSMesaContext _osCtx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->UniformMatrix2x3fv(_gl, location, count, transpose, value);
}

static INLINE void osCtxUniformMatrix2x4fv(OSMesaContext _osCtx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->UniformMatrix2x4fv(_gl, location, count, transpose, value);
}

static INLINE void osCtxUniformMatrix3x2fv(OSMesaContext _osCtx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->UniformMatrix3x2fv(_gl, location, count, transpose, value);
}

static INLINE void osCtxUniformMatrix3x4fv(OSMesaContext _osCtx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->UniformMatrix3x4fv(_gl, location, count, transpose, value);
}

static INLINE void osCtxUniformMatrix4x2fv(OSMesaContext _osCtx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->UniformMatrix4x2fv(_gl, location, count, transpose, value);
}

static INLINE void osCtxUniformMatrix4x3fv(OSMesaContext _osCtx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->UniformMatrix4x3fv(_gl, location, count, transpose, value);
}

static INLINE void osCtxLoadTransposeMatrixdARB(OSMesaContext _osCtx, const GLdouble * m)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LoadTransposeMatrixdARB(_gl, m);
}

static INLINE void osCtxLoadTransposeMatrixfARB(OSMesaContext _osCtx, const GLfloat * m)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LoadTransposeMatrixfARB(_gl, m);
}

static INLINE void osCtxMultTransposeMatrixdARB(OSMesaContext _osCtx, const GLdouble * m)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultTransposeMatrixdARB(_gl, m);
}

static INLINE void osCtxMultTransposeMatrixfARB(OSMesaContext _osCtx, const GLfloat * m)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultTransposeMatrixfARB(_gl, m);
}

static INLINE void osCtxSampleCoverageARB(OSMesaContext _osCtx, GLclampf value, GLboolean invert)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SampleCoverageARB(_gl, value, invert);
}

static INLINE void osCtxCompressedTexImage1DARB(OSMesaContext _osCtx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid * data)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CompressedTexImage1DARB(_gl, target, level, internalformat, width, border, imageSize, data);
}

static INLINE void osCtxCompressedTexImage2DARB(OSMesaContext _osCtx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CompressedTexImage2DARB(_gl, target, level, internalformat, width, height, border, imageSize, data);
}

static INLINE void osCtxCompressedTexImage3DARB(OSMesaContext _osCtx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CompressedTexImage3DARB(_gl, target, level, internalformat, width, height, depth, border, imageSize, data);
}

static INLINE void osCtxCompressedTexSubImage1DARB(OSMesaContext _osCtx, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CompressedTexSubImage1DARB(_gl, target, level, xoffset, width, format, imageSize, data);
}

static INLINE void osCtxCompressedTexSubImage2DARB(OSMesaContext _osCtx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CompressedTexSubImage2DARB(_gl, target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

static INLINE void osCtxCompressedTexSubImage3DARB(OSMesaContext _osCtx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CompressedTexSubImage3DARB(_gl, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

static INLINE void osCtxGetCompressedTexImageARB(OSMesaContext _osCtx, GLenum target, GLint level, GLvoid * img)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetCompressedTexImageARB(_gl, target, level, img);
}

static INLINE void osCtxDisableVertexAttribArrayARB(OSMesaContext _osCtx, GLuint index)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DisableVertexAttribArrayARB(_gl, index);
}

static INLINE void osCtxEnableVertexAttribArrayARB(OSMesaContext _osCtx, GLuint index)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EnableVertexAttribArrayARB(_gl, index);
}

static INLINE void osCtxGetProgramEnvParameterdvARB(OSMesaContext _osCtx, GLenum target, GLuint index, GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramEnvParameterdvARB(_gl, target, index, params);
}

static INLINE void osCtxGetProgramEnvParameterfvARB(OSMesaContext _osCtx, GLenum target, GLuint index, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramEnvParameterfvARB(_gl, target, index, params);
}

static INLINE void osCtxGetProgramLocalParameterdvARB(OSMesaContext _osCtx, GLenum target, GLuint index, GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramLocalParameterdvARB(_gl, target, index, params);
}

static INLINE void osCtxGetProgramLocalParameterfvARB(OSMesaContext _osCtx, GLenum target, GLuint index, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramLocalParameterfvARB(_gl, target, index, params);
}

static INLINE void osCtxGetProgramStringARB(OSMesaContext _osCtx, GLenum target, GLenum pname, GLvoid * string)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramStringARB(_gl, target, pname, string);
}

static INLINE void osCtxGetProgramivARB(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramivARB(_gl, target, pname, params);
}

static INLINE void osCtxGetVertexAttribdvARB(OSMesaContext _osCtx, GLuint index, GLenum pname, GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetVertexAttribdvARB(_gl, index, pname, params);
}

static INLINE void osCtxGetVertexAttribfvARB(OSMesaContext _osCtx, GLuint index, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetVertexAttribfvARB(_gl, index, pname, params);
}

static INLINE void osCtxGetVertexAttribivARB(OSMesaContext _osCtx, GLuint index, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetVertexAttribivARB(_gl, index, pname, params);
}

static INLINE void osCtxProgramEnvParameter4dARB(OSMesaContext _osCtx, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramEnvParameter4dARB(_gl, target, index, x, y, z, w);
}

static INLINE void osCtxProgramEnvParameter4dvARB(OSMesaContext _osCtx, GLenum target, GLuint index, const GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramEnvParameter4dvARB(_gl, target, index, params);
}

static INLINE void osCtxProgramEnvParameter4fARB(OSMesaContext _osCtx, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramEnvParameter4fARB(_gl, target, index, x, y, z, w);
}

static INLINE void osCtxProgramEnvParameter4fvARB(OSMesaContext _osCtx, GLenum target, GLuint index, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramEnvParameter4fvARB(_gl, target, index, params);
}

static INLINE void osCtxProgramLocalParameter4dARB(OSMesaContext _osCtx, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramLocalParameter4dARB(_gl, target, index, x, y, z, w);
}

static INLINE void osCtxProgramLocalParameter4dvARB(OSMesaContext _osCtx, GLenum target, GLuint index, const GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramLocalParameter4dvARB(_gl, target, index, params);
}

static INLINE void osCtxProgramLocalParameter4fARB(OSMesaContext _osCtx, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramLocalParameter4fARB(_gl, target, index, x, y, z, w);
}

static INLINE void osCtxProgramLocalParameter4fvARB(OSMesaContext _osCtx, GLenum target, GLuint index, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramLocalParameter4fvARB(_gl, target, index, params);
}

static INLINE void osCtxProgramStringARB(OSMesaContext _osCtx, GLenum target, GLenum format, GLsizei len, const GLvoid * string)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramStringARB(_gl, target, format, len, string);
}

static INLINE void osCtxVertexAttrib1dARB(OSMesaContext _osCtx, GLuint index, GLdouble x)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1dARB(_gl, index, x);
}

static INLINE void osCtxVertexAttrib1dvARB(OSMesaContext _osCtx, GLuint index, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1dvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib1fARB(OSMesaContext _osCtx, GLuint index, GLfloat x)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1fARB(_gl, index, x);
}

static INLINE void osCtxVertexAttrib1fvARB(OSMesaContext _osCtx, GLuint index, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1fvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib1sARB(OSMesaContext _osCtx, GLuint index, GLshort x)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1sARB(_gl, index, x);
}

static INLINE void osCtxVertexAttrib1svARB(OSMesaContext _osCtx, GLuint index, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1svARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib2dARB(OSMesaContext _osCtx, GLuint index, GLdouble x, GLdouble y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2dARB(_gl, index, x, y);
}

static INLINE void osCtxVertexAttrib2dvARB(OSMesaContext _osCtx, GLuint index, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2dvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib2fARB(OSMesaContext _osCtx, GLuint index, GLfloat x, GLfloat y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2fARB(_gl, index, x, y);
}

static INLINE void osCtxVertexAttrib2fvARB(OSMesaContext _osCtx, GLuint index, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2fvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib2sARB(OSMesaContext _osCtx, GLuint index, GLshort x, GLshort y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2sARB(_gl, index, x, y);
}

static INLINE void osCtxVertexAttrib2svARB(OSMesaContext _osCtx, GLuint index, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2svARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib3dARB(OSMesaContext _osCtx, GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3dARB(_gl, index, x, y, z);
}

static INLINE void osCtxVertexAttrib3dvARB(OSMesaContext _osCtx, GLuint index, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3dvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib3fARB(OSMesaContext _osCtx, GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3fARB(_gl, index, x, y, z);
}

static INLINE void osCtxVertexAttrib3fvARB(OSMesaContext _osCtx, GLuint index, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3fvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib3sARB(OSMesaContext _osCtx, GLuint index, GLshort x, GLshort y, GLshort z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3sARB(_gl, index, x, y, z);
}

static INLINE void osCtxVertexAttrib3svARB(OSMesaContext _osCtx, GLuint index, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3svARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4NbvARB(OSMesaContext _osCtx, GLuint index, const GLbyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4NbvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4NivARB(OSMesaContext _osCtx, GLuint index, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4NivARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4NsvARB(OSMesaContext _osCtx, GLuint index, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4NsvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4NubARB(OSMesaContext _osCtx, GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4NubARB(_gl, index, x, y, z, w);
}

static INLINE void osCtxVertexAttrib4NubvARB(OSMesaContext _osCtx, GLuint index, const GLubyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4NubvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4NuivARB(OSMesaContext _osCtx, GLuint index, const GLuint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4NuivARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4NusvARB(OSMesaContext _osCtx, GLuint index, const GLushort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4NusvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4bvARB(OSMesaContext _osCtx, GLuint index, const GLbyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4bvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4dARB(OSMesaContext _osCtx, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4dARB(_gl, index, x, y, z, w);
}

static INLINE void osCtxVertexAttrib4dvARB(OSMesaContext _osCtx, GLuint index, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4dvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4fARB(OSMesaContext _osCtx, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4fARB(_gl, index, x, y, z, w);
}

static INLINE void osCtxVertexAttrib4fvARB(OSMesaContext _osCtx, GLuint index, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4fvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4ivARB(OSMesaContext _osCtx, GLuint index, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4ivARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4sARB(OSMesaContext _osCtx, GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4sARB(_gl, index, x, y, z, w);
}

static INLINE void osCtxVertexAttrib4svARB(OSMesaContext _osCtx, GLuint index, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4svARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4ubvARB(OSMesaContext _osCtx, GLuint index, const GLubyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4ubvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4uivARB(OSMesaContext _osCtx, GLuint index, const GLuint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4uivARB(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4usvARB(OSMesaContext _osCtx, GLuint index, const GLushort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4usvARB(_gl, index, v);
}

static INLINE void osCtxVertexAttribPointerARB(OSMesaContext _osCtx, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribPointerARB(_gl, index, size, type, normalized, stride, pointer);
}

static INLINE void osCtxBindBufferARB(OSMesaContext _osCtx, GLenum target, GLuint buffer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BindBufferARB(_gl, target, buffer);
}

static INLINE void osCtxBufferDataARB(OSMesaContext _osCtx, GLenum target, GLsizeiptrARB size, const GLvoid * data, GLenum usage)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BufferDataARB(_gl, target, size, data, usage);
}

static INLINE void osCtxBufferSubDataARB(OSMesaContext _osCtx, GLenum target, GLintptrARB offset, GLsizeiptrARB size, const GLvoid * data)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BufferSubDataARB(_gl, target, offset, size, data);
}

static INLINE void osCtxDeleteBuffersARB(OSMesaContext _osCtx, GLsizei n, const GLuint * buffer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteBuffersARB(_gl, n, buffer);
}

static INLINE void osCtxGenBuffersARB(OSMesaContext _osCtx, GLsizei n, GLuint * buffer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GenBuffersARB(_gl, n, buffer);
}

static INLINE void osCtxGetBufferParameterivARB(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetBufferParameterivARB(_gl, target, pname, params);
}

static INLINE void osCtxGetBufferPointervARB(OSMesaContext _osCtx, GLenum target, GLenum pname, GLvoid ** params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetBufferPointervARB(_gl, target, pname, params);
}

static INLINE void osCtxGetBufferSubDataARB(OSMesaContext _osCtx, GLenum target, GLintptrARB offset, GLsizeiptrARB size, GLvoid * data)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetBufferSubDataARB(_gl, target, offset, size, data);
}

static INLINE GLvoid * osCtxMapBufferARB(OSMesaContext _osCtx, GLenum target, GLenum access)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    return _tbl->MapBufferARB(_gl, target, access);
}

static INLINE void osCtxBeginQueryARB(OSMesaContext _osCtx, GLenum target, GLuint id)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BeginQueryARB(_gl, target, id);
}

static INLINE void osCtxDeleteQueriesARB(OSMesaContext _osCtx, GLsizei n, const GLuint * ids)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteQueriesARB(_gl, n, ids);
}

static INLINE void osCtxEndQueryARB(OSMesaContext _osCtx, GLenum target)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EndQueryARB(_gl, target);
}

static INLINE void osCtxGenQueriesARB(OSMesaContext _osCtx, GLsizei n, GLuint * ids)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GenQueriesARB(_gl, n, ids);
}

static INLINE void osCtxGetQueryObjectivARB(OSMesaContext _osCtx, GLuint id, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetQueryObjectivARB(_gl, id, pname, params);
}

static INLINE void osCtxGetQueryObjectuivARB(OSMesaContext _osCtx, GLuint id, GLenum pname, GLuint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetQueryObjectuivARB(_gl, id, pname, params);
}

static INLINE void osCtxGetQueryivARB(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetQueryivARB(_gl, target, pname, params);
}

static INLINE void osCtxAttachObjectARB(OSMesaContext _osCtx, GLhandleARB containerObj, GLhandleARB obj)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->AttachObjectARB(_gl, containerObj, obj);
}

static INLINE void osCtxCompileShaderARB(OSMesaContext _osCtx, GLhandleARB shader)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CompileShaderARB(_gl, shader);
}

static INLINE void osCtxDeleteObjectARB(OSMesaContext _osCtx, GLhandleARB obj)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteObjectARB(_gl, obj);
}

static INLINE void osCtxDetachObjectARB(OSMesaContext _osCtx, GLhandleARB containerObj, GLhandleARB attachedObj)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DetachObjectARB(_gl, containerObj, attachedObj);
}

static INLINE void osCtxGetActiveUniformARB(OSMesaContext _osCtx, GLhandleARB program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLcharARB * name)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetActiveUniformARB(_gl, program, index, bufSize, length, size, type, name);
}

static INLINE void osCtxGetAttachedObjectsARB(OSMesaContext _osCtx, GLhandleARB containerObj, GLsizei maxLength, GLsizei * length, GLhandleARB * infoLog)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetAttachedObjectsARB(_gl, containerObj, maxLength, length, infoLog);
}

static INLINE void osCtxGetInfoLogARB(OSMesaContext _osCtx, GLhandleARB obj, GLsizei maxLength, GLsizei * length, GLcharARB * infoLog)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetInfoLogARB(_gl, obj, maxLength, length, infoLog);
}

static INLINE void osCtxGetObjectParameterfvARB(OSMesaContext _osCtx, GLhandleARB obj, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetObjectParameterfvARB(_gl, obj, pname, params);
}

static INLINE void osCtxGetObjectParameterivARB(OSMesaContext _osCtx, GLhandleARB obj, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetObjectParameterivARB(_gl, obj, pname, params);
}

static INLINE void osCtxGetShaderSourceARB(OSMesaContext _osCtx, GLhandleARB shader, GLsizei bufSize, GLsizei * length, GLcharARB * source)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetShaderSourceARB(_gl, shader, bufSize, length, source);
}

static INLINE void osCtxGetUniformfvARB(OSMesaContext _osCtx, GLhandleARB program, GLint location, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetUniformfvARB(_gl, program, location, params);
}

static INLINE void osCtxGetUniformivARB(OSMesaContext _osCtx, GLhandleARB program, GLint location, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetUniformivARB(_gl, program, location, params);
}

static INLINE void osCtxLinkProgramARB(OSMesaContext _osCtx, GLhandleARB program)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LinkProgramARB(_gl, program);
}

static INLINE void osCtxShaderSourceARB(OSMesaContext _osCtx, GLhandleARB shader, GLsizei count, const GLcharARB ** string, const GLint * length)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ShaderSourceARB(_gl, shader, count, string, length);
}

static INLINE void osCtxUniform1fARB(OSMesaContext _osCtx, GLint location, GLfloat v0)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform1fARB(_gl, location, v0);
}

static INLINE void osCtxUniform1fvARB(OSMesaContext _osCtx, GLint location, GLsizei count, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform1fvARB(_gl, location, count, value);
}

static INLINE void osCtxUniform1iARB(OSMesaContext _osCtx, GLint location, GLint v0)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform1iARB(_gl, location, v0);
}

static INLINE void osCtxUniform1ivARB(OSMesaContext _osCtx, GLint location, GLsizei count, const GLint * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform1ivARB(_gl, location, count, value);
}

static INLINE void osCtxUniform2fARB(OSMesaContext _osCtx, GLint location, GLfloat v0, GLfloat v1)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform2fARB(_gl, location, v0, v1);
}

static INLINE void osCtxUniform2fvARB(OSMesaContext _osCtx, GLint location, GLsizei count, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform2fvARB(_gl, location, count, value);
}

static INLINE void osCtxUniform2iARB(OSMesaContext _osCtx, GLint location, GLint v0, GLint v1)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform2iARB(_gl, location, v0, v1);
}

static INLINE void osCtxUniform2ivARB(OSMesaContext _osCtx, GLint location, GLsizei count, const GLint * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform2ivARB(_gl, location, count, value);
}

static INLINE void osCtxUniform3fARB(OSMesaContext _osCtx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform3fARB(_gl, location, v0, v1, v2);
}

static INLINE void osCtxUniform3fvARB(OSMesaContext _osCtx, GLint location, GLsizei count, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform3fvARB(_gl, location, count, value);
}

static INLINE void osCtxUniform3iARB(OSMesaContext _osCtx, GLint location, GLint v0, GLint v1, GLint v2)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform3iARB(_gl, location, v0, v1, v2);
}

static INLINE void osCtxUniform3ivARB(OSMesaContext _osCtx, GLint location, GLsizei count, const GLint * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform3ivARB(_gl, location, count, value);
}

static INLINE void osCtxUniform4fARB(OSMesaContext _osCtx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform4fARB(_gl, location, v0, v1, v2, v3);
}

static INLINE void osCtxUniform4fvARB(OSMesaContext _osCtx, GLint location, GLsizei count, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform4fvARB(_gl, location, count, value);
}

static INLINE void osCtxUniform4iARB(OSMesaContext _osCtx, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform4iARB(_gl, location, v0, v1, v2, v3);
}

static INLINE void osCtxUniform4ivARB(OSMesaContext _osCtx, GLint location, GLsizei count, const GLint * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->Uniform4ivARB(_gl, location, count, value);
}

static INLINE void osCtxUniformMatrix2fvARB(OSMesaContext _osCtx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->UniformMatrix2fvARB(_gl, location, count, transpose, value);
}

static INLINE void osCtxUniformMatrix3fvARB(OSMesaContext _osCtx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->UniformMatrix3fvARB(_gl, location, count, transpose, value);
}

static INLINE void osCtxUniformMatrix4fvARB(OSMesaContext _osCtx, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->UniformMatrix4fvARB(_gl, location, count, transpose, value);
}

static INLINE void osCtxUseProgramObjectARB(OSMesaContext _osCtx, GLhandleARB program)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->UseProgramObjectARB(_gl, program);
}

static INLINE void osCtxValidateProgramARB(OSMesaContext _osCtx, GLhandleARB program)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ValidateProgramARB(_gl, program);
}

static INLINE void osCtxBindAttribLocationARB(OSMesaContext _osCtx, GLhandleARB program, GLuint index, const GLcharARB * name)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BindAttribLocationARB(_gl, program, index, name);
}

static INLINE void osCtxGetActiveAttribARB(OSMesaContext _osCtx, GLhandleARB program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLcharARB * name)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetActiveAttribARB(_gl, program, index, bufSize, length, size, type, name);
}

static INLINE void osCtxDrawBuffersARB(OSMesaContext _osCtx, GLsizei n, const GLenum * bufs)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DrawBuffersARB(_gl, n, bufs);
}

static INLINE void osCtxPolygonOffsetEXT(OSMesaContext _osCtx, GLfloat factor, GLfloat bias)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PolygonOffsetEXT(_gl, factor, bias);
}

static INLINE void osCtxGetPixelTexGenParameterfvSGIS(OSMesaContext _osCtx, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetPixelTexGenParameterfvSGIS(_gl, pname, params);
}

static INLINE void osCtxGetPixelTexGenParameterivSGIS(OSMesaContext _osCtx, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetPixelTexGenParameterivSGIS(_gl, pname, params);
}

static INLINE void osCtxPixelTexGenParameterfSGIS(OSMesaContext _osCtx, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelTexGenParameterfSGIS(_gl, pname, param);
}

static INLINE void osCtxPixelTexGenParameterfvSGIS(OSMesaContext _osCtx, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelTexGenParameterfvSGIS(_gl, pname, params);
}

static INLINE void osCtxPixelTexGenParameteriSGIS(OSMesaContext _osCtx, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelTexGenParameteriSGIS(_gl, pname, param);
}

static INLINE void osCtxPixelTexGenParameterivSGIS(OSMesaContext _osCtx, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelTexGenParameterivSGIS(_gl, pname, params);
}

static INLINE void osCtxSampleMaskSGIS(OSMesaContext _osCtx, GLclampf value, GLboolean invert)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SampleMaskSGIS(_gl, value, invert);
}

static INLINE void osCtxSamplePatternSGIS(OSMesaContext _osCtx, GLenum pattern)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SamplePatternSGIS(_gl, pattern);
}

static INLINE void osCtxColorPointerEXT(OSMesaContext _osCtx, GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ColorPointerEXT(_gl, size, type, stride, count, pointer);
}

static INLINE void osCtxEdgeFlagPointerEXT(OSMesaContext _osCtx, GLsizei stride, GLsizei count, const GLboolean * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EdgeFlagPointerEXT(_gl, stride, count, pointer);
}

static INLINE void osCtxIndexPointerEXT(OSMesaContext _osCtx, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->IndexPointerEXT(_gl, type, stride, count, pointer);
}

static INLINE void osCtxNormalPointerEXT(OSMesaContext _osCtx, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->NormalPointerEXT(_gl, type, stride, count, pointer);
}

static INLINE void osCtxTexCoordPointerEXT(OSMesaContext _osCtx, GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TexCoordPointerEXT(_gl, size, type, stride, count, pointer);
}

static INLINE void osCtxVertexPointerEXT(OSMesaContext _osCtx, GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexPointerEXT(_gl, size, type, stride, count, pointer);
}

static INLINE void osCtxPointParameterfEXT(OSMesaContext _osCtx, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PointParameterfEXT(_gl, pname, param);
}

static INLINE void osCtxPointParameterfvEXT(OSMesaContext _osCtx, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PointParameterfvEXT(_gl, pname, params);
}

static INLINE void osCtxLockArraysEXT(OSMesaContext _osCtx, GLint first, GLsizei count)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LockArraysEXT(_gl, first, count);
}

static INLINE void osCtxUnlockArraysEXT(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->UnlockArraysEXT(_gl);
}

static INLINE void osCtxCullParameterdvEXT(OSMesaContext _osCtx, GLenum pname, GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CullParameterdvEXT(_gl, pname, params);
}

static INLINE void osCtxCullParameterfvEXT(OSMesaContext _osCtx, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CullParameterfvEXT(_gl, pname, params);
}

static INLINE void osCtxSecondaryColor3bEXT(OSMesaContext _osCtx, GLbyte red, GLbyte green, GLbyte blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3bEXT(_gl, red, green, blue);
}

static INLINE void osCtxSecondaryColor3bvEXT(OSMesaContext _osCtx, const GLbyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3bvEXT(_gl, v);
}

static INLINE void osCtxSecondaryColor3dEXT(OSMesaContext _osCtx, GLdouble red, GLdouble green, GLdouble blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3dEXT(_gl, red, green, blue);
}

static INLINE void osCtxSecondaryColor3dvEXT(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3dvEXT(_gl, v);
}

static INLINE void osCtxSecondaryColor3fEXT(OSMesaContext _osCtx, GLfloat red, GLfloat green, GLfloat blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3fEXT(_gl, red, green, blue);
}

static INLINE void osCtxSecondaryColor3fvEXT(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3fvEXT(_gl, v);
}

static INLINE void osCtxSecondaryColor3iEXT(OSMesaContext _osCtx, GLint red, GLint green, GLint blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3iEXT(_gl, red, green, blue);
}

static INLINE void osCtxSecondaryColor3ivEXT(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3ivEXT(_gl, v);
}

static INLINE void osCtxSecondaryColor3sEXT(OSMesaContext _osCtx, GLshort red, GLshort green, GLshort blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3sEXT(_gl, red, green, blue);
}

static INLINE void osCtxSecondaryColor3svEXT(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3svEXT(_gl, v);
}

static INLINE void osCtxSecondaryColor3ubEXT(OSMesaContext _osCtx, GLubyte red, GLubyte green, GLubyte blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3ubEXT(_gl, red, green, blue);
}

static INLINE void osCtxSecondaryColor3ubvEXT(OSMesaContext _osCtx, const GLubyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3ubvEXT(_gl, v);
}

static INLINE void osCtxSecondaryColor3uiEXT(OSMesaContext _osCtx, GLuint red, GLuint green, GLuint blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3uiEXT(_gl, red, green, blue);
}

static INLINE void osCtxSecondaryColor3uivEXT(OSMesaContext _osCtx, const GLuint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3uivEXT(_gl, v);
}

static INLINE void osCtxSecondaryColor3usEXT(OSMesaContext _osCtx, GLushort red, GLushort green, GLushort blue)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3usEXT(_gl, red, green, blue);
}

static INLINE void osCtxSecondaryColor3usvEXT(OSMesaContext _osCtx, const GLushort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColor3usvEXT(_gl, v);
}

static INLINE void osCtxSecondaryColorPointerEXT(OSMesaContext _osCtx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SecondaryColorPointerEXT(_gl, size, type, stride, pointer);
}

static INLINE void osCtxMultiDrawArraysEXT(OSMesaContext _osCtx, GLenum mode, GLint * first, GLsizei * count, GLsizei primcount)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiDrawArraysEXT(_gl, mode, first, count, primcount);
}

static INLINE void osCtxMultiDrawElementsEXT(OSMesaContext _osCtx, GLenum mode, const GLsizei * count, GLenum type, const GLvoid ** indices, GLsizei primcount)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiDrawElementsEXT(_gl, mode, count, type, indices, primcount);
}

static INLINE void osCtxFogCoordPointerEXT(OSMesaContext _osCtx, GLenum type, GLsizei stride, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FogCoordPointerEXT(_gl, type, stride, pointer);
}

static INLINE void osCtxFogCoorddEXT(OSMesaContext _osCtx, GLdouble coord)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FogCoorddEXT(_gl, coord);
}

static INLINE void osCtxFogCoorddvEXT(OSMesaContext _osCtx, const GLdouble * coord)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FogCoorddvEXT(_gl, coord);
}

static INLINE void osCtxFogCoordfEXT(OSMesaContext _osCtx, GLfloat coord)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FogCoordfEXT(_gl, coord);
}

static INLINE void osCtxFogCoordfvEXT(OSMesaContext _osCtx, const GLfloat * coord)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FogCoordfvEXT(_gl, coord);
}

static INLINE void osCtxPixelTexGenSGIX(OSMesaContext _osCtx, GLenum mode)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PixelTexGenSGIX(_gl, mode);
}

static INLINE void osCtxBlendFuncSeparateEXT(OSMesaContext _osCtx, GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BlendFuncSeparateEXT(_gl, sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

static INLINE void osCtxFlushVertexArrayRangeNV(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FlushVertexArrayRangeNV(_gl);
}

static INLINE void osCtxVertexArrayRangeNV(OSMesaContext _osCtx, GLsizei length, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexArrayRangeNV(_gl, length, pointer);
}

static INLINE void osCtxCombinerInputNV(OSMesaContext _osCtx, GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CombinerInputNV(_gl, stage, portion, variable, input, mapping, componentUsage);
}

static INLINE void osCtxCombinerOutputNV(OSMesaContext _osCtx, GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CombinerOutputNV(_gl, stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDotProduct, muxSum);
}

static INLINE void osCtxCombinerParameterfNV(OSMesaContext _osCtx, GLenum pname, GLfloat param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CombinerParameterfNV(_gl, pname, param);
}

static INLINE void osCtxCombinerParameterfvNV(OSMesaContext _osCtx, GLenum pname, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CombinerParameterfvNV(_gl, pname, params);
}

static INLINE void osCtxCombinerParameteriNV(OSMesaContext _osCtx, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CombinerParameteriNV(_gl, pname, param);
}

static INLINE void osCtxCombinerParameterivNV(OSMesaContext _osCtx, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->CombinerParameterivNV(_gl, pname, params);
}

static INLINE void osCtxFinalCombinerInputNV(OSMesaContext _osCtx, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FinalCombinerInputNV(_gl, variable, input, mapping, componentUsage);
}

static INLINE void osCtxGetCombinerInputParameterfvNV(OSMesaContext _osCtx, GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetCombinerInputParameterfvNV(_gl, stage, portion, variable, pname, params);
}

static INLINE void osCtxGetCombinerInputParameterivNV(OSMesaContext _osCtx, GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetCombinerInputParameterivNV(_gl, stage, portion, variable, pname, params);
}

static INLINE void osCtxGetCombinerOutputParameterfvNV(OSMesaContext _osCtx, GLenum stage, GLenum portion, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetCombinerOutputParameterfvNV(_gl, stage, portion, pname, params);
}

static INLINE void osCtxGetCombinerOutputParameterivNV(OSMesaContext _osCtx, GLenum stage, GLenum portion, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetCombinerOutputParameterivNV(_gl, stage, portion, pname, params);
}

static INLINE void osCtxGetFinalCombinerInputParameterfvNV(OSMesaContext _osCtx, GLenum variable, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetFinalCombinerInputParameterfvNV(_gl, variable, pname, params);
}

static INLINE void osCtxGetFinalCombinerInputParameterivNV(OSMesaContext _osCtx, GLenum variable, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetFinalCombinerInputParameterivNV(_gl, variable, pname, params);
}

static INLINE void osCtxResizeBuffersMESA(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ResizeBuffersMESA(_gl);
}

static INLINE void osCtxWindowPos2dMESA(OSMesaContext _osCtx, GLdouble x, GLdouble y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos2dMESA(_gl, x, y);
}

static INLINE void osCtxWindowPos2dvMESA(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos2dvMESA(_gl, v);
}

static INLINE void osCtxWindowPos2fMESA(OSMesaContext _osCtx, GLfloat x, GLfloat y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos2fMESA(_gl, x, y);
}

static INLINE void osCtxWindowPos2fvMESA(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos2fvMESA(_gl, v);
}

static INLINE void osCtxWindowPos2iMESA(OSMesaContext _osCtx, GLint x, GLint y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos2iMESA(_gl, x, y);
}

static INLINE void osCtxWindowPos2ivMESA(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos2ivMESA(_gl, v);
}

static INLINE void osCtxWindowPos2sMESA(OSMesaContext _osCtx, GLshort x, GLshort y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos2sMESA(_gl, x, y);
}

static INLINE void osCtxWindowPos2svMESA(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos2svMESA(_gl, v);
}

static INLINE void osCtxWindowPos3dMESA(OSMesaContext _osCtx, GLdouble x, GLdouble y, GLdouble z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos3dMESA(_gl, x, y, z);
}

static INLINE void osCtxWindowPos3dvMESA(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos3dvMESA(_gl, v);
}

static INLINE void osCtxWindowPos3fMESA(OSMesaContext _osCtx, GLfloat x, GLfloat y, GLfloat z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos3fMESA(_gl, x, y, z);
}

static INLINE void osCtxWindowPos3fvMESA(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos3fvMESA(_gl, v);
}

static INLINE void osCtxWindowPos3iMESA(OSMesaContext _osCtx, GLint x, GLint y, GLint z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos3iMESA(_gl, x, y, z);
}

static INLINE void osCtxWindowPos3ivMESA(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos3ivMESA(_gl, v);
}

static INLINE void osCtxWindowPos3sMESA(OSMesaContext _osCtx, GLshort x, GLshort y, GLshort z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos3sMESA(_gl, x, y, z);
}

static INLINE void osCtxWindowPos3svMESA(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos3svMESA(_gl, v);
}

static INLINE void osCtxWindowPos4dMESA(OSMesaContext _osCtx, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos4dMESA(_gl, x, y, z, w);
}

static INLINE void osCtxWindowPos4dvMESA(OSMesaContext _osCtx, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos4dvMESA(_gl, v);
}

static INLINE void osCtxWindowPos4fMESA(OSMesaContext _osCtx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos4fMESA(_gl, x, y, z, w);
}

static INLINE void osCtxWindowPos4fvMESA(OSMesaContext _osCtx, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos4fvMESA(_gl, v);
}

static INLINE void osCtxWindowPos4iMESA(OSMesaContext _osCtx, GLint x, GLint y, GLint z, GLint w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos4iMESA(_gl, x, y, z, w);
}

static INLINE void osCtxWindowPos4ivMESA(OSMesaContext _osCtx, const GLint * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos4ivMESA(_gl, v);
}

static INLINE void osCtxWindowPos4sMESA(OSMesaContext _osCtx, GLshort x, GLshort y, GLshort z, GLshort w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos4sMESA(_gl, x, y, z, w);
}

static INLINE void osCtxWindowPos4svMESA(OSMesaContext _osCtx, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->WindowPos4svMESA(_gl, v);
}

static INLINE void osCtxMultiModeDrawArraysIBM(OSMesaContext _osCtx, const GLenum * mode, const GLint * first, const GLsizei * count, GLsizei primcount, GLint modestride)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiModeDrawArraysIBM(_gl, mode, first, count, primcount, modestride);
}

static INLINE void osCtxMultiModeDrawElementsIBM(OSMesaContext _osCtx, const GLenum * mode, const GLsizei * count, GLenum type, const GLvoid * const * indices, GLsizei primcount, GLint modestride)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->MultiModeDrawElementsIBM(_gl, mode, count, type, indices, primcount, modestride);
}

static INLINE void osCtxDeleteFencesNV(OSMesaContext _osCtx, GLsizei n, const GLuint * fences)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteFencesNV(_gl, n, fences);
}

static INLINE void osCtxFinishFenceNV(OSMesaContext _osCtx, GLuint fence)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FinishFenceNV(_gl, fence);
}

static INLINE void osCtxGenFencesNV(OSMesaContext _osCtx, GLsizei n, GLuint * fences)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GenFencesNV(_gl, n, fences);
}

static INLINE void osCtxGetFenceivNV(OSMesaContext _osCtx, GLuint fence, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetFenceivNV(_gl, fence, pname, params);
}

static INLINE void osCtxSetFenceNV(OSMesaContext _osCtx, GLuint fence, GLenum condition)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SetFenceNV(_gl, fence, condition);
}

static INLINE void osCtxBindProgramNV(OSMesaContext _osCtx, GLenum target, GLuint program)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BindProgramNV(_gl, target, program);
}

static INLINE void osCtxDeleteProgramsNV(OSMesaContext _osCtx, GLsizei n, const GLuint * programs)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteProgramsNV(_gl, n, programs);
}

static INLINE void osCtxExecuteProgramNV(OSMesaContext _osCtx, GLenum target, GLuint id, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ExecuteProgramNV(_gl, target, id, params);
}

static INLINE void osCtxGenProgramsNV(OSMesaContext _osCtx, GLsizei n, GLuint * programs)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GenProgramsNV(_gl, n, programs);
}

static INLINE void osCtxGetProgramParameterdvNV(OSMesaContext _osCtx, GLenum target, GLuint index, GLenum pname, GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramParameterdvNV(_gl, target, index, pname, params);
}

static INLINE void osCtxGetProgramParameterfvNV(OSMesaContext _osCtx, GLenum target, GLuint index, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramParameterfvNV(_gl, target, index, pname, params);
}

static INLINE void osCtxGetProgramStringNV(OSMesaContext _osCtx, GLuint id, GLenum pname, GLubyte * program)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramStringNV(_gl, id, pname, program);
}

static INLINE void osCtxGetProgramivNV(OSMesaContext _osCtx, GLuint id, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramivNV(_gl, id, pname, params);
}

static INLINE void osCtxGetTrackMatrixivNV(OSMesaContext _osCtx, GLenum target, GLuint address, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetTrackMatrixivNV(_gl, target, address, pname, params);
}

static INLINE void osCtxGetVertexAttribPointervNV(OSMesaContext _osCtx, GLuint index, GLenum pname, GLvoid ** pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetVertexAttribPointervNV(_gl, index, pname, pointer);
}

static INLINE void osCtxGetVertexAttribdvNV(OSMesaContext _osCtx, GLuint index, GLenum pname, GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetVertexAttribdvNV(_gl, index, pname, params);
}

static INLINE void osCtxGetVertexAttribfvNV(OSMesaContext _osCtx, GLuint index, GLenum pname, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetVertexAttribfvNV(_gl, index, pname, params);
}

static INLINE void osCtxGetVertexAttribivNV(OSMesaContext _osCtx, GLuint index, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetVertexAttribivNV(_gl, index, pname, params);
}

static INLINE void osCtxLoadProgramNV(OSMesaContext _osCtx, GLenum target, GLuint id, GLsizei len, const GLubyte * program)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->LoadProgramNV(_gl, target, id, len, program);
}

static INLINE void osCtxProgramParameter4dNV(OSMesaContext _osCtx, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramParameter4dNV(_gl, target, index, x, y, z, w);
}

static INLINE void osCtxProgramParameter4dvNV(OSMesaContext _osCtx, GLenum target, GLuint index, const GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramParameter4dvNV(_gl, target, index, params);
}

static INLINE void osCtxProgramParameter4fNV(OSMesaContext _osCtx, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramParameter4fNV(_gl, target, index, x, y, z, w);
}

static INLINE void osCtxProgramParameter4fvNV(OSMesaContext _osCtx, GLenum target, GLuint index, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramParameter4fvNV(_gl, target, index, params);
}

static INLINE void osCtxProgramParameters4dvNV(OSMesaContext _osCtx, GLenum target, GLuint index, GLuint num, const GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramParameters4dvNV(_gl, target, index, num, params);
}

static INLINE void osCtxProgramParameters4fvNV(OSMesaContext _osCtx, GLenum target, GLuint index, GLuint num, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramParameters4fvNV(_gl, target, index, num, params);
}

static INLINE void osCtxRequestResidentProgramsNV(OSMesaContext _osCtx, GLsizei n, const GLuint * ids)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RequestResidentProgramsNV(_gl, n, ids);
}

static INLINE void osCtxTrackMatrixNV(OSMesaContext _osCtx, GLenum target, GLuint address, GLenum matrix, GLenum transform)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->TrackMatrixNV(_gl, target, address, matrix, transform);
}

static INLINE void osCtxVertexAttrib1dNV(OSMesaContext _osCtx, GLuint index, GLdouble x)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1dNV(_gl, index, x);
}

static INLINE void osCtxVertexAttrib1dvNV(OSMesaContext _osCtx, GLuint index, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1dvNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib1fNV(OSMesaContext _osCtx, GLuint index, GLfloat x)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1fNV(_gl, index, x);
}

static INLINE void osCtxVertexAttrib1fvNV(OSMesaContext _osCtx, GLuint index, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1fvNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib1sNV(OSMesaContext _osCtx, GLuint index, GLshort x)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1sNV(_gl, index, x);
}

static INLINE void osCtxVertexAttrib1svNV(OSMesaContext _osCtx, GLuint index, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib1svNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib2dNV(OSMesaContext _osCtx, GLuint index, GLdouble x, GLdouble y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2dNV(_gl, index, x, y);
}

static INLINE void osCtxVertexAttrib2dvNV(OSMesaContext _osCtx, GLuint index, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2dvNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib2fNV(OSMesaContext _osCtx, GLuint index, GLfloat x, GLfloat y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2fNV(_gl, index, x, y);
}

static INLINE void osCtxVertexAttrib2fvNV(OSMesaContext _osCtx, GLuint index, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2fvNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib2sNV(OSMesaContext _osCtx, GLuint index, GLshort x, GLshort y)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2sNV(_gl, index, x, y);
}

static INLINE void osCtxVertexAttrib2svNV(OSMesaContext _osCtx, GLuint index, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib2svNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib3dNV(OSMesaContext _osCtx, GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3dNV(_gl, index, x, y, z);
}

static INLINE void osCtxVertexAttrib3dvNV(OSMesaContext _osCtx, GLuint index, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3dvNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib3fNV(OSMesaContext _osCtx, GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3fNV(_gl, index, x, y, z);
}

static INLINE void osCtxVertexAttrib3fvNV(OSMesaContext _osCtx, GLuint index, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3fvNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib3sNV(OSMesaContext _osCtx, GLuint index, GLshort x, GLshort y, GLshort z)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3sNV(_gl, index, x, y, z);
}

static INLINE void osCtxVertexAttrib3svNV(OSMesaContext _osCtx, GLuint index, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib3svNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4dNV(OSMesaContext _osCtx, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4dNV(_gl, index, x, y, z, w);
}

static INLINE void osCtxVertexAttrib4dvNV(OSMesaContext _osCtx, GLuint index, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4dvNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4fNV(OSMesaContext _osCtx, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4fNV(_gl, index, x, y, z, w);
}

static INLINE void osCtxVertexAttrib4fvNV(OSMesaContext _osCtx, GLuint index, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4fvNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4sNV(OSMesaContext _osCtx, GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4sNV(_gl, index, x, y, z, w);
}

static INLINE void osCtxVertexAttrib4svNV(OSMesaContext _osCtx, GLuint index, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4svNV(_gl, index, v);
}

static INLINE void osCtxVertexAttrib4ubNV(OSMesaContext _osCtx, GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4ubNV(_gl, index, x, y, z, w);
}

static INLINE void osCtxVertexAttrib4ubvNV(OSMesaContext _osCtx, GLuint index, const GLubyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttrib4ubvNV(_gl, index, v);
}

static INLINE void osCtxVertexAttribPointerNV(OSMesaContext _osCtx, GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribPointerNV(_gl, index, size, type, stride, pointer);
}

static INLINE void osCtxVertexAttribs1dvNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs1dvNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs1fvNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs1fvNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs1svNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs1svNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs2dvNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs2dvNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs2fvNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs2fvNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs2svNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs2svNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs3dvNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs3dvNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs3fvNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs3fvNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs3svNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs3svNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs4dvNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs4dvNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs4fvNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs4fvNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs4svNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLshort * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs4svNV(_gl, index, n, v);
}

static INLINE void osCtxVertexAttribs4ubvNV(OSMesaContext _osCtx, GLuint index, GLsizei n, const GLubyte * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->VertexAttribs4ubvNV(_gl, index, n, v);
}

static INLINE void osCtxAlphaFragmentOp1ATI(OSMesaContext _osCtx, GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->AlphaFragmentOp1ATI(_gl, op, dst, dstMod, arg1, arg1Rep, arg1Mod);
}

static INLINE void osCtxAlphaFragmentOp2ATI(OSMesaContext _osCtx, GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->AlphaFragmentOp2ATI(_gl, op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod);
}

static INLINE void osCtxAlphaFragmentOp3ATI(OSMesaContext _osCtx, GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->AlphaFragmentOp3ATI(_gl, op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod);
}

static INLINE void osCtxBeginFragmentShaderATI(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BeginFragmentShaderATI(_gl);
}

static INLINE void osCtxBindFragmentShaderATI(OSMesaContext _osCtx, GLuint id)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BindFragmentShaderATI(_gl, id);
}

static INLINE void osCtxColorFragmentOp1ATI(OSMesaContext _osCtx, GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ColorFragmentOp1ATI(_gl, op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod);
}

static INLINE void osCtxColorFragmentOp2ATI(OSMesaContext _osCtx, GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ColorFragmentOp2ATI(_gl, op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod);
}

static INLINE void osCtxColorFragmentOp3ATI(OSMesaContext _osCtx, GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ColorFragmentOp3ATI(_gl, op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod);
}

static INLINE void osCtxDeleteFragmentShaderATI(OSMesaContext _osCtx, GLuint id)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteFragmentShaderATI(_gl, id);
}

static INLINE void osCtxEndFragmentShaderATI(OSMesaContext _osCtx)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->EndFragmentShaderATI(_gl);
}

static INLINE void osCtxPassTexCoordATI(OSMesaContext _osCtx, GLuint dst, GLuint coord, GLenum swizzle)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PassTexCoordATI(_gl, dst, coord, swizzle);
}

static INLINE void osCtxSampleMapATI(OSMesaContext _osCtx, GLuint dst, GLuint interp, GLenum swizzle)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SampleMapATI(_gl, dst, interp, swizzle);
}

static INLINE void osCtxSetFragmentShaderConstantATI(OSMesaContext _osCtx, GLuint dst, const GLfloat * value)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->SetFragmentShaderConstantATI(_gl, dst, value);
}

static INLINE void osCtxPointParameteriNV(OSMesaContext _osCtx, GLenum pname, GLint param)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PointParameteriNV(_gl, pname, param);
}

static INLINE void osCtxPointParameterivNV(OSMesaContext _osCtx, GLenum pname, const GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->PointParameterivNV(_gl, pname, params);
}

static INLINE void osCtxActiveStencilFaceEXT(OSMesaContext _osCtx, GLenum face)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ActiveStencilFaceEXT(_gl, face);
}

static INLINE void osCtxBindVertexArrayAPPLE(OSMesaContext _osCtx, GLuint array)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BindVertexArrayAPPLE(_gl, array);
}

static INLINE void osCtxDeleteVertexArraysAPPLE(OSMesaContext _osCtx, GLsizei n, const GLuint * arrays)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteVertexArraysAPPLE(_gl, n, arrays);
}

static INLINE void osCtxGenVertexArraysAPPLE(OSMesaContext _osCtx, GLsizei n, GLuint * arrays)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GenVertexArraysAPPLE(_gl, n, arrays);
}

static INLINE void osCtxGetProgramNamedParameterdvNV(OSMesaContext _osCtx, GLuint id, GLsizei len, const GLubyte * name, GLdouble * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramNamedParameterdvNV(_gl, id, len, name, params);
}

static INLINE void osCtxGetProgramNamedParameterfvNV(OSMesaContext _osCtx, GLuint id, GLsizei len, const GLubyte * name, GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetProgramNamedParameterfvNV(_gl, id, len, name, params);
}

static INLINE void osCtxProgramNamedParameter4dNV(OSMesaContext _osCtx, GLuint id, GLsizei len, const GLubyte * name, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramNamedParameter4dNV(_gl, id, len, name, x, y, z, w);
}

static INLINE void osCtxProgramNamedParameter4dvNV(OSMesaContext _osCtx, GLuint id, GLsizei len, const GLubyte * name, const GLdouble * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramNamedParameter4dvNV(_gl, id, len, name, v);
}

static INLINE void osCtxProgramNamedParameter4fNV(OSMesaContext _osCtx, GLuint id, GLsizei len, const GLubyte * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramNamedParameter4fNV(_gl, id, len, name, x, y, z, w);
}

static INLINE void osCtxProgramNamedParameter4fvNV(OSMesaContext _osCtx, GLuint id, GLsizei len, const GLubyte * name, const GLfloat * v)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramNamedParameter4fvNV(_gl, id, len, name, v);
}

static INLINE void osCtxDepthBoundsEXT(OSMesaContext _osCtx, GLclampd zmin, GLclampd zmax)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DepthBoundsEXT(_gl, zmin, zmax);
}

static INLINE void osCtxBlendEquationSeparateEXT(OSMesaContext _osCtx, GLenum modeRGB, GLenum modeA)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BlendEquationSeparateEXT(_gl, modeRGB, modeA);
}

static INLINE void osCtxBindFramebufferEXT(OSMesaContext _osCtx, GLenum target, GLuint framebuffer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BindFramebufferEXT(_gl, target, framebuffer);
}

static INLINE void osCtxBindRenderbufferEXT(OSMesaContext _osCtx, GLenum target, GLuint renderbuffer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BindRenderbufferEXT(_gl, target, renderbuffer);
}

static INLINE void osCtxDeleteFramebuffersEXT(OSMesaContext _osCtx, GLsizei n, const GLuint * framebuffers)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteFramebuffersEXT(_gl, n, framebuffers);
}

static INLINE void osCtxDeleteRenderbuffersEXT(OSMesaContext _osCtx, GLsizei n, const GLuint * renderbuffers)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->DeleteRenderbuffersEXT(_gl, n, renderbuffers);
}

static INLINE void osCtxFramebufferRenderbufferEXT(OSMesaContext _osCtx, GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FramebufferRenderbufferEXT(_gl, target, attachment, renderbuffertarget, renderbuffer);
}

static INLINE void osCtxFramebufferTexture1DEXT(OSMesaContext _osCtx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FramebufferTexture1DEXT(_gl, target, attachment, textarget, texture, level);
}

static INLINE void osCtxFramebufferTexture2DEXT(OSMesaContext _osCtx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FramebufferTexture2DEXT(_gl, target, attachment, textarget, texture, level);
}

static INLINE void osCtxFramebufferTexture3DEXT(OSMesaContext _osCtx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->FramebufferTexture3DEXT(_gl, target, attachment, textarget, texture, level, zoffset);
}

static INLINE void osCtxGenFramebuffersEXT(OSMesaContext _osCtx, GLsizei n, GLuint * framebuffers)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GenFramebuffersEXT(_gl, n, framebuffers);
}

static INLINE void osCtxGenRenderbuffersEXT(OSMesaContext _osCtx, GLsizei n, GLuint * renderbuffers)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GenRenderbuffersEXT(_gl, n, renderbuffers);
}

static INLINE void osCtxGenerateMipmapEXT(OSMesaContext _osCtx, GLenum target)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GenerateMipmapEXT(_gl, target);
}

static INLINE void osCtxGetFramebufferAttachmentParameterivEXT(OSMesaContext _osCtx, GLenum target, GLenum attachment, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetFramebufferAttachmentParameterivEXT(_gl, target, attachment, pname, params);
}

static INLINE void osCtxGetRenderbufferParameterivEXT(OSMesaContext _osCtx, GLenum target, GLenum pname, GLint * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetRenderbufferParameterivEXT(_gl, target, pname, params);
}

static INLINE void osCtxRenderbufferStorageEXT(OSMesaContext _osCtx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->RenderbufferStorageEXT(_gl, target, internalformat, width, height);
}

static INLINE void osCtxBlitFramebufferEXT(OSMesaContext _osCtx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->BlitFramebufferEXT(_gl, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

static INLINE void osCtxStencilFuncSeparateATI(OSMesaContext _osCtx, GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->StencilFuncSeparateATI(_gl, frontfunc, backfunc, ref, mask);
}

static INLINE void osCtxProgramEnvParameters4fvEXT(OSMesaContext _osCtx, GLenum target, GLuint index, GLsizei count, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramEnvParameters4fvEXT(_gl, target, index, count, params);
}

static INLINE void osCtxProgramLocalParameters4fvEXT(OSMesaContext _osCtx, GLenum target, GLuint index, GLsizei count, const GLfloat * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->ProgramLocalParameters4fvEXT(_gl, target, index, count, params);
}

static INLINE void osCtxGetQueryObjecti64vEXT(OSMesaContext _osCtx, GLuint id, GLenum pname, GLint64EXT * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetQueryObjecti64vEXT(_gl, id, pname, params);
}

static INLINE void osCtxGetQueryObjectui64vEXT(OSMesaContext _osCtx, GLuint id, GLenum pname, GLuint64EXT * params)
{
    GLcontext *_gl = OSMesaGetGLcontext(_osCtx);
    struct _glapi_table *_tbl = OSMesaGetDispatch(_osCtx);
    _tbl->GetQueryObjectui64vEXT(_gl, id, pname, params);
}

#ifdef __cplusplus
}
#endif

#endif /* OSMESA_GLCTX_H */
