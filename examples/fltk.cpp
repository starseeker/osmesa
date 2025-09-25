/*                     F L T K . C P P
 * BRL-CAD
 *
 * Published in 2025 by the United States Government.
 * This work is in the public domain, except as noted
 * below.
 */
/** @file fltk.cpp
 *
 * Self contained example of working with image data
 * in FLTK in C/C++
 *
 * TODO - look into
 * https://www.seriss.com/people/erco/fltk/#AnimateDrawing
 * https://www.seriss.com/people/erco/fltk/#OpenGlInterp
 */



// Code from the fontstash example is copyright Mikko Mononen:
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//      claim that you wrote the original software. If you use this software
//      in a product, an acknowledgment in the product documentation would be
//      appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//      misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.



// The Torus routine is extracted from GLUT, which per
// https://github.com/markkilgard/glut/blob/master/lib/glut/glut_shapes.c
// has the following license:
//
// (c) Copyright Mark J. Kilgard, 1994, 1997, 2001.
// (c) Copyright 1993, Silicon Graphics, Inc.
//
// ALL RIGHTS RESERVED
//
// Permission to use, copy, modify, and distribute this software
// for any purpose and without fee is hereby granted, provided
// that the above copyright notice appear in all copies and that
// both the copyright notice and this permission notice appear in
// supporting documentation, and that the name of Silicon
// Graphics, Inc. not be used in advertising or publicity
// pertaining to distribution of the software without specific,
// written prior permission.
//
// THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU
// "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR
// OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  IN NO
// EVENT SHALL SILICON GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE
// ELSE FOR ANY DIRECT, SPECIAL, INCIDENTAL, INDIRECT OR
// CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER,
// INCLUDING WITHOUT LIMITATION, LOSS OF PROFIT, LOSS OF USE,
// SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD PARTIES, WHETHER OR
// NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF THE POSSIBILITY
// OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE OR
// PERFORMANCE OF THIS SOFTWARE.
//
// US Government Users Restricted Rights
//
// Use, duplication, or disclosure by the Government is subject to
// restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
// (c)(1)(ii) of the Rights in Technical Data and Computer
// Software clause at DFARS 252.227-7013 and/or in similar or
// successor clauses in the FAR or the DOD or NASA FAR
// Supplement.  Unpublished-- rights reserved under the copyright
// laws of the United States.  Contractor/manufacturer is Silicon
// Graphics, Inc., 2011 N.  Shoreline Blvd., Mountain View, CA
// 94039-7311.
//
// OpenGL(TM) is a trademark of Silicon Graphics, Inc.

#include <random>
#include <iostream>
#include <cstring>
#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Window.H>

extern "C" {
#include "OSMesa/gl.h"
#include "OSMesa/osmesa.h"
#define FONTSTASH_IMPLEMENTATION
#include "fontstash/fontstash.h"
#define GLFONTSTASH_IMPLEMENTATION
#include "fontstash/glfontstash.h"
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

int
main(int argc, const char *argv[])
{
    int width = 800;
    int height = 600;

    OSMesaContext ctx = OSMesaCreateContextExt(OSMESA_RGBA, 16, 0, 0, NULL);
    if (!ctx) {
	printf("OSMesaCreateContext failed!\n");
	exit(1);
    }

    void *os_b = calloc(Fl::w() * Fl::h(), sizeof(GLubyte)*4);
    if (!os_b) {
	printf("buffer allocation failed!\n");
	exit(1);
    }
    if (!OSMesaMakeCurrent(ctx, os_b, GL_UNSIGNED_BYTE, Fl::w(), Fl::h())) {
	printf("OSMesaMakeCurrent failed!\n");
	exit(1);
    }

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat rand_mat[]  = {1, 0, 0, 1.0};

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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(20.0, 1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(-0.75, 0.5, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, rand_mat);
    Torus(0.275, 0.85, 20, 20);
    glPopMatrix();
    glPopMatrix();

    /* This is very important!!!
     * Make sure buffered commands are finished!!!
     */
    glFinish();

    size_t parea = Fl::w() * Fl::h();
    long dm_buff_size = parea * sizeof(GLubyte)*4;
    unsigned char *dmpixel = (unsigned char *)malloc(dm_buff_size*sizeof(char));

    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, dmpixel);

    // Image will be upside-down from FLTK's perspective, flip manually using an RGBA
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
	    memcpy(rgba, dmpixel + top, sizeof(rgba));
	    memcpy(dmpixel + top, dmpixel + bottom, sizeof(rgba));
	    memcpy(dmpixel + bottom, rgba, sizeof(rgba));
	}
    }

    Fl_Window *w = new Fl_Window(width, height, "OSMesa");
    w->begin();
    Fl_RGB_Image *img = new Fl_RGB_Image((const uchar *)dmpixel, width, height, 4);
    Fl_Box *b = new Fl_Box(0, 0, width, height);
    b->image(img);
    w->end();
    w->show();
    return Fl::run();
}


// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
