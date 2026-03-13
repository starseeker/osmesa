/**************************************************************************

Copyright 2002 Tungsten Graphics Inc., Cedar Park, Texas.

All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
on the rights to use, copy, modify, merge, publish, distribute, sub
license, and/or sell copies of the Software, and to permit persons to whom
the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice (including the next
paragraph) shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
TUNGSTEN GRAPHICS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

#define ATTR1FV( A, V ) ATTR( A, 1, (V)[0], 0, 0, 1 )
#define ATTR2FV( A, V ) ATTR( A, 2, (V)[0], (V)[1], 0, 1 )
#define ATTR3FV( A, V ) ATTR( A, 3, (V)[0], (V)[1], (V)[2], 1 )
#define ATTR4FV( A, V ) ATTR( A, 4, (V)[0], (V)[1], (V)[2], (V)[3] )

#define ATTR1F( A, X )          ATTR( A, 1, X, 0, 0, 1 )
#define ATTR2F( A, X, Y )       ATTR( A, 2, X, Y, 0, 1 )
#define ATTR3F( A, X, Y, Z )    ATTR( A, 3, X, Y, Z, 1 )
#define ATTR4F( A, X, Y, Z, W ) ATTR( A, 4, X, Y, Z, W )

#define MAT_ATTR( A, N, V ) ATTR( A, N, (V)[0], (V)[1], (V)[2], (V)[3] )

static void GLAPIENTRY TAG(Vertex2f)(GLcontext *ctx, GLfloat x, GLfloat y)
{
    ATTR2F(VBO_ATTRIB_POS, x, y);
}

static void GLAPIENTRY TAG(Vertex2fv)(GLcontext *ctx, const GLfloat *v)
{
    ATTR2FV(VBO_ATTRIB_POS, v);
}

static void GLAPIENTRY TAG(Vertex3f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z)
{
    ATTR3F(VBO_ATTRIB_POS, x, y, z);
}

static void GLAPIENTRY TAG(Vertex3fv)(GLcontext *ctx, const GLfloat *v)
{
    ATTR3FV(VBO_ATTRIB_POS, v);
}

static void GLAPIENTRY TAG(Vertex4f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    ATTR4F(VBO_ATTRIB_POS, x, y, z, w);
}

static void GLAPIENTRY TAG(Vertex4fv)(GLcontext *ctx, const GLfloat *v)
{
    ATTR4FV(VBO_ATTRIB_POS, v);
}

static void GLAPIENTRY TAG(TexCoord1f)(GLcontext *ctx, GLfloat x)
{
    ATTR1F(VBO_ATTRIB_TEX0, x);
}

static void GLAPIENTRY TAG(TexCoord1fv)(GLcontext *ctx, const GLfloat *v)
{
    ATTR1FV(VBO_ATTRIB_TEX0, v);
}

static void GLAPIENTRY TAG(TexCoord2f)(GLcontext *ctx, GLfloat x, GLfloat y)
{
    ATTR2F(VBO_ATTRIB_TEX0, x, y);
}

static void GLAPIENTRY TAG(TexCoord2fv)(GLcontext *ctx, const GLfloat *v)
{
    ATTR2FV(VBO_ATTRIB_TEX0, v);
}

static void GLAPIENTRY TAG(TexCoord3f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z)
{
    ATTR3F(VBO_ATTRIB_TEX0, x, y, z);
}

static void GLAPIENTRY TAG(TexCoord3fv)(GLcontext *ctx, const GLfloat *v)
{
    ATTR3FV(VBO_ATTRIB_TEX0, v);
}

static void GLAPIENTRY TAG(TexCoord4f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    ATTR4F(VBO_ATTRIB_TEX0, x, y, z, w);
}

static void GLAPIENTRY TAG(TexCoord4fv)(GLcontext *ctx, const GLfloat *v)
{
    ATTR4FV(VBO_ATTRIB_TEX0, v);
}

static void GLAPIENTRY TAG(Normal3f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z)
{
    ATTR3F(VBO_ATTRIB_NORMAL, x, y, z);
}

static void GLAPIENTRY TAG(Normal3fv)(GLcontext *ctx, const GLfloat *v)
{
    ATTR3FV(VBO_ATTRIB_NORMAL, v);
}

static void GLAPIENTRY TAG(FogCoordfEXT)(GLcontext *ctx, GLfloat x)
{
    ATTR1F(VBO_ATTRIB_FOG, x);
}

static void GLAPIENTRY TAG(FogCoordfvEXT)(GLcontext *ctx, const GLfloat *v)
{
    ATTR1FV(VBO_ATTRIB_FOG, v);
}

static void GLAPIENTRY TAG(Color3f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z)
{
    ATTR3F(VBO_ATTRIB_COLOR0, x, y, z);
}

static void GLAPIENTRY TAG(Color3fv)(GLcontext *ctx, const GLfloat *v)
{
    ATTR3FV(VBO_ATTRIB_COLOR0, v);
}

static void GLAPIENTRY TAG(Color4f)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    ATTR4F(VBO_ATTRIB_COLOR0, x, y, z, w);
}

static void GLAPIENTRY TAG(Color4fv)(GLcontext *ctx, const GLfloat *v)
{
    ATTR4FV(VBO_ATTRIB_COLOR0, v);
}

static void GLAPIENTRY TAG(SecondaryColor3fEXT)(GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z)
{
    ATTR3F(VBO_ATTRIB_COLOR1, x, y, z);
}

static void GLAPIENTRY TAG(SecondaryColor3fvEXT)(GLcontext *ctx, const GLfloat *v)
{
    ATTR3FV(VBO_ATTRIB_COLOR1, v);
}


static void GLAPIENTRY TAG(EdgeFlag)(GLcontext *ctx, GLboolean b)
{
    ATTR1F(VBO_ATTRIB_EDGEFLAG, (GLfloat)b);
}

static void GLAPIENTRY TAG(Indexf)(GLcontext *ctx, GLfloat f)
{
    ATTR1F(VBO_ATTRIB_INDEX, f);
}

static void GLAPIENTRY TAG(Indexfv)(GLcontext *ctx, const GLfloat *f)
{
    ATTR1FV(VBO_ATTRIB_INDEX, f);
}


static void GLAPIENTRY TAG(MultiTexCoord1f)(GLcontext *ctx, GLenum target, GLfloat x)
{
    GLuint attr = (target & 0x7) + VBO_ATTRIB_TEX0;
    ATTR1F(attr, x);
}

static void GLAPIENTRY TAG(MultiTexCoord1fv)(GLcontext *ctx, GLenum target, const GLfloat *v)
{
    GLuint attr = (target & 0x7) + VBO_ATTRIB_TEX0;
    ATTR1FV(attr, v);
}

static void GLAPIENTRY TAG(MultiTexCoord2f)(GLcontext *ctx, GLenum target, GLfloat x, GLfloat y)
{
    GLuint attr = (target & 0x7) + VBO_ATTRIB_TEX0;
    ATTR2F(attr, x, y);
}

static void GLAPIENTRY TAG(MultiTexCoord2fv)(GLcontext *ctx, GLenum target, const GLfloat *v)
{
    GLuint attr = (target & 0x7) + VBO_ATTRIB_TEX0;
    ATTR2FV(attr, v);
}

static void GLAPIENTRY TAG(MultiTexCoord3f)(GLcontext *ctx, GLenum target, GLfloat x, GLfloat y,
	GLfloat z)
{
    GLuint attr = (target & 0x7) + VBO_ATTRIB_TEX0;
    ATTR3F(attr, x, y, z);
}

static void GLAPIENTRY TAG(MultiTexCoord3fv)(GLcontext *ctx, GLenum target, const GLfloat *v)
{
    GLuint attr = (target & 0x7) + VBO_ATTRIB_TEX0;
    ATTR3FV(attr, v);
}

static void GLAPIENTRY TAG(MultiTexCoord4f)(GLcontext *ctx, GLenum target, GLfloat x, GLfloat y,
	GLfloat z, GLfloat w)
{
    GLuint attr = (target & 0x7) + VBO_ATTRIB_TEX0;
    ATTR4F(attr, x, y, z, w);
}

static void GLAPIENTRY TAG(MultiTexCoord4fv)(GLcontext *ctx, GLenum target, const GLfloat *v)
{
    GLuint attr = (target & 0x7) + VBO_ATTRIB_TEX0;
    ATTR4FV(attr, v);
}


static void GLAPIENTRY TAG(VertexAttrib1fARB)(GLcontext *ctx, GLuint index, GLfloat x)
{
    if (index == 0)
	ATTR1F(0, x);
    else if (index < MAX_VERTEX_ATTRIBS)
	ATTR1F(VBO_ATTRIB_GENERIC0 + index, x);
    else
	ERROR();
}

static void GLAPIENTRY TAG(VertexAttrib1fvARB)(GLcontext *ctx, GLuint index,
	const GLfloat *v)
{
    if (index == 0)
	ATTR1FV(0, v);
    else if (index < MAX_VERTEX_ATTRIBS)
	ATTR1FV(VBO_ATTRIB_GENERIC0 + index, v);
    else
	ERROR();
}

static void GLAPIENTRY TAG(VertexAttrib2fARB)(GLcontext *ctx, GLuint index, GLfloat x,
	GLfloat y)
{
    if (index == 0)
	ATTR2F(0, x, y);
    else if (index < MAX_VERTEX_ATTRIBS)
	ATTR2F(VBO_ATTRIB_GENERIC0 + index, x, y);
    else
	ERROR();
}

static void GLAPIENTRY TAG(VertexAttrib2fvARB)(GLcontext *ctx, GLuint index,
	const GLfloat *v)
{
    if (index == 0)
	ATTR2FV(0, v);
    else if (index < MAX_VERTEX_ATTRIBS)
	ATTR2FV(VBO_ATTRIB_GENERIC0 + index, v);
    else
	ERROR();
}

static void GLAPIENTRY TAG(VertexAttrib3fARB)(GLcontext *ctx, GLuint index, GLfloat x,
	GLfloat y, GLfloat z)
{
    if (index == 0)
	ATTR3F(0, x, y, z);
    else if (index < MAX_VERTEX_ATTRIBS)
	ATTR3F(VBO_ATTRIB_GENERIC0 + index, x, y, z);
    else
	ERROR();
}

static void GLAPIENTRY TAG(VertexAttrib3fvARB)(GLcontext *ctx, GLuint index,
	const GLfloat *v)
{
    if (index == 0)
	ATTR3FV(0, v);
    else if (index < MAX_VERTEX_ATTRIBS)
	ATTR3FV(VBO_ATTRIB_GENERIC0 + index, v);
    else
	ERROR();
}

static void GLAPIENTRY TAG(VertexAttrib4fARB)(GLcontext *ctx, GLuint index, GLfloat x,
	GLfloat y, GLfloat z,
	GLfloat w)
{
    if (index == 0)
	ATTR4F(0, x, y, z, w);
    else if (index < MAX_VERTEX_ATTRIBS)
	ATTR4F(VBO_ATTRIB_GENERIC0 + index, x, y, z, w);
    else
	ERROR();
}

static void GLAPIENTRY TAG(VertexAttrib4fvARB)(GLcontext *ctx, GLuint index,
	const GLfloat *v)
{
    if (index == 0)
	ATTR4FV(0, v);
    else if (index < MAX_VERTEX_ATTRIBS)
	ATTR4FV(VBO_ATTRIB_GENERIC0 + index, v);
    else
	ERROR();
}


/* In addition to supporting NV_vertex_program, these entrypoints are
 * used by the display list and other code specifically because of
 * their property of aliasing with other attributes.  (See
 * vbo_save_loopback.c)
 */
static void GLAPIENTRY TAG(VertexAttrib1fNV)(GLcontext *ctx, GLuint index, GLfloat x)
{
    if (index < VBO_ATTRIB_MAX)
	ATTR1F(index, x);
}

static void GLAPIENTRY TAG(VertexAttrib1fvNV)(GLcontext *ctx, GLuint index,
	const GLfloat *v)
{
    if (index < VBO_ATTRIB_MAX)
	ATTR1FV(index, v);
}

static void GLAPIENTRY TAG(VertexAttrib2fNV)(GLcontext *ctx, GLuint index, GLfloat x,
	GLfloat y)
{
    if (index < VBO_ATTRIB_MAX)
	ATTR2F(index, x, y);
}

static void GLAPIENTRY TAG(VertexAttrib2fvNV)(GLcontext *ctx, GLuint index,
	const GLfloat *v)
{
    if (index < VBO_ATTRIB_MAX)
	ATTR2FV(index, v);
}

static void GLAPIENTRY TAG(VertexAttrib3fNV)(GLcontext *ctx, GLuint index, GLfloat x,
	GLfloat y, GLfloat z)
{
    if (index < VBO_ATTRIB_MAX)
	ATTR3F(index, x, y, z);
}

static void GLAPIENTRY TAG(VertexAttrib3fvNV)(GLcontext *ctx, GLuint index,
	const GLfloat *v)
{
    if (index < VBO_ATTRIB_MAX)
	ATTR3FV(index, v);
}

static void GLAPIENTRY TAG(VertexAttrib4fNV)(GLcontext *ctx, GLuint index, GLfloat x,
	GLfloat y, GLfloat z,
	GLfloat w)
{
    if (index < VBO_ATTRIB_MAX)
	ATTR4F(index, x, y, z, w);
}

static void GLAPIENTRY TAG(VertexAttrib4fvNV)(GLcontext *ctx, GLuint index,
	const GLfloat *v)
{
    if (index < VBO_ATTRIB_MAX)
	ATTR4FV(index, v);
}


#define MAT( ATTR, N, face, params )			\
do {							\
   if (face != GL_BACK)					\
      MAT_ATTR( ATTR, N, params ); /* front */		\
   if (face != GL_FRONT)				\
      MAT_ATTR( ATTR + 1, N, params ); /* back */	\
} while (0)


/* Colormaterial conflicts are dealt with later.
 */
static void GLAPIENTRY TAG(Materialfv)(GLcontext *ctx, GLenum face, GLenum pname,
				       const GLfloat *params)
{
    switch (pname) {
	case GL_EMISSION:
	    MAT(VBO_ATTRIB_MAT_FRONT_EMISSION, 4, face, params);
	    break;
	case GL_AMBIENT:
	    MAT(VBO_ATTRIB_MAT_FRONT_AMBIENT, 4, face, params);
	    break;
	case GL_DIFFUSE:
	    MAT(VBO_ATTRIB_MAT_FRONT_DIFFUSE, 4, face, params);
	    break;
	case GL_SPECULAR:
	    MAT(VBO_ATTRIB_MAT_FRONT_SPECULAR, 4, face, params);
	    break;
	case GL_SHININESS:
	    MAT(VBO_ATTRIB_MAT_FRONT_SHININESS, 1, face, params);
	    break;
	case GL_COLOR_INDEXES:
	    MAT(VBO_ATTRIB_MAT_FRONT_INDEXES, 3, face, params);
	    break;
	case GL_AMBIENT_AND_DIFFUSE:
	    MAT(VBO_ATTRIB_MAT_FRONT_AMBIENT, 4, face, params);
	    MAT(VBO_ATTRIB_MAT_FRONT_DIFFUSE, 4, face, params);
	    break;
	default:
	    ERROR();
	    return;
    }
}


#undef ATTR1FV
#undef ATTR2FV
#undef ATTR3FV
#undef ATTR4FV

#undef ATTR1F
#undef ATTR2F
#undef ATTR3F
#undef ATTR4F

#undef MAT
#undef MAT_ATTR

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
