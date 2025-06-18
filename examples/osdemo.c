/*
 * Demo of off-screen Mesa rendering
 *
 * See OSMesa/osmesa.h for documentation of the OSMesa functions.
 *
 * This program (except for extracted routines as noted below) is in the public
 * domain.
 *
 * Brian Paul
 *
 * PPM output provided by Joerg Schmalzl.
 * ASCII PPM output added by Brian Paul.
 *
 * The original osdemo code was adjusted to output a PNG file rather than PPM,
 * and uses Milo Yip's svpng to do so - see svpng.h
 *
 *
 *
 * The Sphere and Cylinder routines are extracted from GLU, which has
 * the following license:
 *
 * SGI FREE SOFTWARE LICENSE B (Version 2.0, Sept. 18, 2008)
 * Copyright (C) 1991-2000 Silicon Graphics, Inc. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice including the dates of first publication and
 * either this permission notice or a reference to
 * http://oss.sgi.com/projects/FreeB/
 * shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * SILICON GRAPHICS, INC. BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of Silicon Graphics, Inc.
 * shall not be used in advertising or otherwise to promote the sale, use or
 * other dealings in this Software without prior written authorization from
 * Silicon Graphics, Inc.
 *
 *
 *
 * The Torus routine is extracted from GLUT, which per
 * https://github.com/markkilgard/glut/blob/master/lib/glut/glut_shapes.c
 * has the following license:
 *
 * (c) Copyright Mark J. Kilgard, 1994, 1997, 2001.
 * (c) Copyright 1993, Silicon Graphics, Inc.
 *
 * ALL RIGHTS RESERVED
 *
 * Permission to use, copy, modify, and distribute this software
 * for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that
 * both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of Silicon
 * Graphics, Inc. not be used in advertising or publicity
 * pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU
 * "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR
 * OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  IN NO
 * EVENT SHALL SILICON GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE
 * ELSE FOR ANY DIRECT, SPECIAL, INCIDENTAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER,
 * INCLUDING WITHOUT LIMITATION, LOSS OF PROFIT, LOSS OF USE,
 * SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD PARTIES, WHETHER OR
 * NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 *
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer
 * Software clause at DFARS 252.227-7013 and/or in similar or
 * successor clauses in the FAR or the DOD or NASA FAR
 * Supplement.  Unpublished-- rights reserved under the copyright
 * laws of the United States.  Contractor/manufacturer is Silicon
 * Graphics, Inc., 2011 N.  Shoreline Blvd., Mountain View, CA
 * 94039-7311.
 *
 * OpenGL(TM) is a trademark of Silicon Graphics, Inc.
 *
 *
 * Usage: osdemo [filename]
 */

#define _USE_MATH_DEFINES /* for M_PI */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OSMesa/gl.h"
#include "OSMesa/osmesa.h"
#include "svpng.h"

#define CACHE_SIZE 240

static void
gluSphere(GLdouble radius, GLint slices, GLint stacks)
{
    GLfloat sinCache1a[CACHE_SIZE];
    GLfloat cosCache1a[CACHE_SIZE];
    GLfloat sinCache2a[CACHE_SIZE];
    GLfloat cosCache2a[CACHE_SIZE];
    GLfloat sinCache1b[CACHE_SIZE];
    GLfloat cosCache1b[CACHE_SIZE];
    GLfloat sinCache2b[CACHE_SIZE];
    GLfloat cosCache2b[CACHE_SIZE];

    if (slices >= CACHE_SIZE) slices = CACHE_SIZE-1;
    if (stacks >= CACHE_SIZE) stacks = CACHE_SIZE-1;
    if (slices < 2 || stacks < 1 || radius < 0.0) {
	return;
    }

    for (GLint i = 0; i < slices; i++) {
	GLfloat angle = 2 * M_PI * i / slices;
	sinCache1a[i] = sin(angle);
	cosCache1a[i] = cos(angle);
	sinCache2a[i] = sinCache1a[i];
	cosCache2a[i] = cosCache1a[i];
    }

    for (GLint j = 0; j <= stacks; j++) {
	GLfloat angle = M_PI * j / stacks;
	sinCache2b[j] = sin(angle);
	cosCache2b[j] = cos(angle);
	sinCache1b[j] = radius * sin(angle);
	cosCache1b[j] = radius * cos(angle);
    }
    /* Make sure it comes to a point */
    sinCache1b[0] = 0;
    sinCache1b[stacks] = 0;

    sinCache1a[slices] = sinCache1a[0];
    cosCache1a[slices] = cosCache1a[0];
    sinCache2a[slices] = sinCache2a[0];
    cosCache2a[slices] = cosCache2a[0];

    /* Do ends of sphere as TRIANGLE_FAN's */

    /* Low end first (j == 0 iteration) */
    GLfloat sintemp2 = sinCache1b[1];
    GLfloat zHigh = cosCache1b[1];
    GLfloat sintemp3 = sinCache2b[1];
    GLfloat costemp3 = cosCache2b[1];
    glNormal3f(sinCache2a[0] * sinCache2b[0],
	    cosCache2a[0] * sinCache2b[0],
	    cosCache2b[0]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, radius);
    for (GLint i = slices; i >= 0; i--) {
	glNormal3f(sinCache2a[i] * sintemp3,
		cosCache2a[i] * sintemp3,
		costemp3);
	glVertex3f(sintemp2 * sinCache1a[i],
		sintemp2 * cosCache1a[i], zHigh);
    }
    glEnd();

    /* High end next (j == stacks-1 iteration) */
    sintemp2 = sinCache1b[stacks-1];
    zHigh = cosCache1b[stacks-1];
    sintemp3 = sinCache2b[stacks-1];
    costemp3 = cosCache2b[stacks-1];
    glNormal3f(sinCache2a[stacks] * sinCache2b[stacks],
	    cosCache2a[stacks] * sinCache2b[stacks],
	    cosCache2b[stacks]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, -radius);
    for (GLint i = 0; i <= slices; i++) {
	glNormal3f(sinCache2a[i] * sintemp3,
		cosCache2a[i] * sintemp3,
		costemp3);
	glVertex3f(sintemp2 * sinCache1a[i],
		sintemp2 * cosCache1a[i], zHigh);
    }
    glEnd();
    for (GLint j = 1; j < stacks - 1; j++) {
	GLfloat zLow = cosCache1b[j];
	zHigh = cosCache1b[j+1];
	GLfloat sintemp1 = sinCache1b[j];
	sintemp2 = sinCache1b[j+1];
	sintemp3 = sinCache2b[j+1];
	costemp3 = cosCache2b[j+1];
	GLfloat sintemp4 = sinCache2b[j];
	GLfloat costemp4 = cosCache2b[j];

	glBegin(GL_QUAD_STRIP);
	for (GLint i = 0; i <= slices; i++) {
	    glNormal3f(sinCache2a[i] * sintemp3,
		    cosCache2a[i] * sintemp3,
		    costemp3);
	    glVertex3f(sintemp2 * sinCache1a[i],
		    sintemp2 * cosCache1a[i], zHigh);
	    glNormal3f(sinCache2a[i] * sintemp4,
		    cosCache2a[i] * sintemp4,
		    costemp4);
	    glVertex3f(sintemp1 * sinCache1a[i],
		    sintemp1 * cosCache1a[i], zLow);
	}
	glEnd();
    }
}

static void
Sphere(float radius, int slices, int stacks)
{
    gluSphere(radius, slices, stacks);
}

static void
gluCylinder(GLdouble baseRadius, GLdouble topRadius,
	GLdouble height, GLint slices, GLint stacks)
{
    GLfloat sinCache[CACHE_SIZE];
    GLfloat cosCache[CACHE_SIZE];
    GLfloat sinCache2[CACHE_SIZE];
    GLfloat cosCache2[CACHE_SIZE];

    if (slices >= CACHE_SIZE)
       	slices = CACHE_SIZE-1;

    if (slices < 2 || stacks < 1 || baseRadius < 0.0 || topRadius < 0.0 || height < 0.0)
	return;

    /* Compute length (needed for normal calculations) */
    GLfloat deltaRadius = baseRadius - topRadius;
    GLfloat length = sqrt(deltaRadius*deltaRadius + height*height);
    if (length == 0.0)
	return;

    GLfloat zNormal = deltaRadius / length;
    GLfloat xyNormalRatio = height / length;

    for (GLint i = 0; i < slices; i++) {
	GLfloat angle = 2 * M_PI * i / slices;
	sinCache2[i] = xyNormalRatio * sin(angle);
	cosCache2[i] = xyNormalRatio * cos(angle);
	sinCache[i] = sin(angle);
	cosCache[i] = cos(angle);
    }

    sinCache[slices] = sinCache[0];
    cosCache[slices] = cosCache[0];
    sinCache2[slices] = sinCache2[0];
    cosCache2[slices] = cosCache2[0];

    /* Note:
     ** An argument could be made for using a TRIANGLE_FAN for the end
     ** of the cylinder of either radii is 0.0 (a cone).  However, a
     ** TRIANGLE_FAN would not work in smooth shading mode (the common
     ** case) because the normal for the apex is different for every
     ** triangle (and TRIANGLE_FAN doesn't let me respecify that normal).
     ** Now, my choice is GL_TRIANGLES, or leave the GL_QUAD_STRIP and
     ** just let the GL trivially reject one of the two triangles of the
     ** QUAD.  GL_QUAD_STRIP is probably faster, so I will leave this code
     ** alone.
     */
    for (GLint j = 0; j < stacks; j++) {
	GLfloat zLow = j * height / stacks;
	GLfloat zHigh = (j + 1) * height / stacks;
	GLfloat radiusLow = baseRadius - deltaRadius * ((float) j / stacks);
	GLfloat radiusHigh = baseRadius - deltaRadius * ((float) (j + 1) / stacks);

	glBegin(GL_QUAD_STRIP);
	for (GLint i = 0; i <= slices; i++) {
	    glNormal3f(sinCache2[i], cosCache2[i], zNormal);
	    glVertex3f(radiusLow * sinCache[i],
		    radiusLow * cosCache[i], zLow);
	    glVertex3f(radiusHigh * sinCache[i],
		    radiusHigh * cosCache[i], zHigh);
	}
	glEnd();
    }
}

static void
Cone(float base, float height, int slices, int stacks)
{
    gluCylinder(base, 0.0, height, slices, stacks);
}


    static void
Torus(float innerRadius, float outerRadius, int sides, int rings)
{
    /* from GLUT... */
    int i, j;
    GLfloat theta, phi, theta1;
    GLfloat cosTheta, sinTheta;
    GLfloat cosTheta1, sinTheta1;
    const GLfloat ringDelta = 2.0 * M_PI / rings;
    const GLfloat sideDelta = 2.0 * M_PI / sides;

    theta = 0.0;
    cosTheta = 1.0;
    sinTheta = 0.0;
    for (i = rings - 1; i >= 0; i--) {
	theta1 = theta + ringDelta;
	cosTheta1 = cos(theta1);
	sinTheta1 = sin(theta1);
	glBegin(GL_QUAD_STRIP);
	phi = 0.0;
	for (j = sides; j >= 0; j--) {
	    GLfloat cosPhi, sinPhi, dist;

	    phi += sideDelta;
	    cosPhi = cos(phi);
	    sinPhi = sin(phi);
	    dist = outerRadius + innerRadius * cosPhi;

	    glNormal3f(cosTheta1 * cosPhi, -sinTheta1 * cosPhi, sinPhi);
	    glVertex3f(cosTheta1 * dist, -sinTheta1 * dist, innerRadius * sinPhi);
	    glNormal3f(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi);
	    glVertex3f(cosTheta * dist, -sinTheta * dist,  innerRadius * sinPhi);
	}
	glEnd();
	theta = theta1;
	cosTheta = cosTheta1;
	sinTheta = sinTheta1;
    }
}


void
render_image(void)
{
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat red_mat[]   = { 1.0, 0.2, 0.2, 1.0 };
    GLfloat green_mat[] = { 0.2, 1.0, 0.2, 1.0 };
    GLfloat blue_mat[]  = { 0.2, 0.2, 1.0, 1.0 };


    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.5, 2.5, -2.5, 2.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();
    glRotatef(20.0, 1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(-0.75, 0.5, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red_mat );
    Torus(0.275, 0.85, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75, -0.5, 0.0);
    glRotatef(270.0, 1.0, 0.0, 0.0);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green_mat );
    Cone(1.0, 2.0, 16, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75, 0.0, -1.0);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue_mat );
    Sphere(1.0, 20, 20);
    glPopMatrix();

    glPopMatrix();

    /* This is very important!!!
     * Make sure buffered commands are finished!!!
     */
    glFinish();
}

void
sph(double angle)
{
    GLfloat blue_mat[]  = { 1, 1, 0, 1 };

    glPushMatrix();
    glTranslatef(0.75, 0.0, 0);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue_mat );
    Sphere(1.0, 20, 20);
    glPopMatrix();

    glFinish();
}

static void
write_png(const char *filename, GLubyte *buffer, int width, int height)
{
    const int binary = 0;
    FILE *f = fopen( filename, "wb" );

    if (f) {
	// Image will be upside-down from SDL's perspective, flip manually using an RGBA
	// variation of the math from:
	// https://github.com/vallentin/GLCollection/blob/master/screenshot.cpp
	//
	// Apparently this is necessary, since OpenGL doesn't provide a built-in way
	// to handle this:
	// https://www.opengl.org/archives/resources/features/KilgardTechniques/oglpitfall/
	for (int y = 0; y < height / 2; ++y) {
	    for (int x = 0; x < width; ++x) {
		int top = (x + y * width) * 4;
		int bottom = (x + (height - y - 1) * width) * 4;
		char rgba[4];
		memcpy(rgba, buffer + top, sizeof(rgba));
		memcpy(buffer + top, buffer + bottom, sizeof(rgba));
		memcpy(buffer + bottom, rgba, sizeof(rgba));
	    }
	}
	svpng(f, width, height, buffer, 1);

	fclose(f);
    }
}

int
main(int argc, const char *argv[])
{
    OSMesaContext ctx;
    void *buffer;
    int Width = 400;
    int Height = 400;
    const char *filename = NULL;

    if (argc < 2) {
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "  osdemo filename [width height]\n");
	return 0;
    }

    filename = argv[1];
    if (argc == 4) {
	Width = atoi(argv[2]);
	Height = atoi(argv[3]);
    }

    ctx = OSMesaCreateContextExt( OSMESA_RGBA, 16, 0, 0, NULL );
    if (!ctx) {
	printf("OSMesaCreateContext failed!\n");
	return 0;
    }

    buffer = calloc(Width * Height, sizeof(GLubyte)*4);
    if (!buffer) {
	printf("Alloc image buffer failed!\n");
	return 0;
    }

    if (!OSMesaMakeCurrent( ctx, buffer, GL_UNSIGNED_BYTE, Width, Height )) {
	printf("OSMesaMakeCurrent failed!\n");
	return 0;
    }

    {
	int z, s, a;
	glGetIntegerv(GL_DEPTH_BITS, &z);
	glGetIntegerv(GL_STENCIL_BITS, &s);
	glGetIntegerv(GL_ACCUM_RED_BITS, &a);
	printf("Depth=%d Stencil=%d Accum=%d\n", z, s, a);
    }

    render_image();

    if (filename != NULL) {
	write_png(filename, buffer, Width, Height);
    }
    else {
	printf("Need filename\n");
    }

    printf("all done\n");

    free( buffer );

    OSMesaDestroyContext( ctx );

    return 0;
}

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8 cino=N-s
 */
