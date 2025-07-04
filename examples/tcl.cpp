/*                     T C L _ I M G . C P P
 * BRL-CAD
 *
 * Published in 2020 by the United States Government.
 * This work is in the public domain, except as noted
 * below.
 */
/** @file tcl_img.cpp
 *
 * Self contained example of working with image data
 * in Tcl/Tk in C/C++
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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



extern "C" {
#include "tcl.h"
#include "tk.h"
#include "OSMesa/gl.h"
#include "OSMesa/osmesa.h"
#define FONTSTASH_IMPLEMENTATION
#include "fontstash/fontstash.h"
#define GLFONTSTASH_IMPLEMENTATION
#include "fontstash/glfontstash.h"
}


const char *DM_PHOTO = ".dm0.photo";
const char *DM_CANVAS = ".dm0";

TCL_DECLARE_MUTEX(dilock)
TCL_DECLARE_MUTEX(fblock)
TCL_DECLARE_MUTEX(threadMutex)
TCL_DECLARE_MUTEX(DmMutex)

struct font_info {
    int fontNormal = FONS_INVALID;
    int fontItalic = FONS_INVALID;
    int fontBold = FONS_INVALID;
    int fontJapanese = FONS_INVALID;
    FONScontext* fs = NULL;
};

/* Container holding image generation information - need to be able
 * to pass these to the update command */
struct img_data {
    // These flags should be mutex guarded.
    int dm_render_needed;
    int dm_render_running;
    int dm_render_ready;

    int fb_render_running;
    int fb_render_ready;

    // Parent application sets this when it's time to shut
    // down all rendering
    int shutdown;

    // Main thread id - used to send a rendering event back to
    // the parent thread.
    Tcl_ThreadId parent_id;

    // Tcl interp can only be used by the thread that created it, and the
    // Tk_Photo calls require an interpreter.  Thus we keep track of which
    // interpreter is the parent interp in the primary data container, as this
    // interp (and ONLY this interp) is requried to do Tk_Photo processing when
    // triggered from thread events sent back to the parent.  Those callbacks
    // don't by default encode knowledge about the parent's Tcl_Interp, so we
    // store it where we know we can access it.
    Tcl_Interp *parent_interp;

    // DM thread id
    Tcl_ThreadId dm_id;

    // FB thread_id
    Tcl_ThreadId fb_id;

    // Screen width and height.  Maximum possible
    // buffer size needed.
    int screen_width;
    int screen_height;

    // Font info
    struct font_info f;

    // Image info.  Reflects the currently requested parent image
    // size - the render thread may have a different size during
    // rendering, as it "snapshots" these numbers to have a stable
    // buffer size when actually writing pixels.
    int dm_width;
    int dm_height;

    // Actual allocated sizes of image buffer
    int dm_bwidth;
    int dm_bheight;

    // Used for image generation - these are presisted across renders so the
    // image contents will vary as expected.
    std::default_random_engine *gen;
    std::uniform_int_distribution<int> *colors;
    std::uniform_int_distribution<int> *vals;

    // The rendering memory used to actually generate the DM scene contents.
    OSMesaContext ctx;
    void *os_b;
    int x;
    double t;

    long dm_buff_size;
    unsigned char *dmpixel;

    // The rendering memory used to actually generate the framebuffer contents.
    long fb_buff_size;
    int fb_width;
    int fb_height;
    unsigned char *fbpixel;
};

// Event container passed to routines triggered by events.
struct RenderEvent {
    Tcl_Event event;            /* Must be first */
    struct img_data *idata;
};

// Event container passed to routines triggered by events.
struct FbRenderEvent {
    Tcl_Event event;            /* Must be first */
    struct img_data *idata;
};

// Even for events where we don't intend to actually run a proc,
// we need to tell Tcl it successfully processed them.  For that
// we define a no-op callback proc.
static int
noop_proc(Tcl_Event *evPtr, int mask)
{
    // Return one to signify a successful completion of the process execution
    return 1;
}

// The actual Tk_Photo updating must be done by the creater of the
// Tcl_Interp - which is the parent thread.  The interp below must
// thus be the PARENT's interp, and we have passed it through the
// various structures to be available here.
//
// TODO - see if we can use the Tk_PhotoPutZoomedBlock API to keep the image in
// sync with the window size as we're moving; even if it's not a fully crisp
// rendering, then catch up once a properly sized rendering is done...
static int
UpdateProc(Tcl_Event *evPtr, int mask)
{
    struct RenderEvent *DmEventPtr = (RenderEvent *) evPtr;
    struct img_data *idata = DmEventPtr->idata;
    Tcl_Interp *interp = idata->parent_interp;

    Tcl_MutexLock(&dilock);
    Tcl_MutexLock(&fblock);

    // Render processing now - reset the ready flag
    Tcl_MutexLock(&threadMutex);
    idata->dm_render_ready = 0;
    Tcl_MutexUnlock(&threadMutex);

    int width = idata->dm_bwidth;
    int height = idata->dm_bheight;

    // If we're mid-render, don't update - that means another render
    // got triggered after this proc got started, and another update
    // event will eventually be triggered.
    if (idata->dm_render_running) {
	Tcl_MutexUnlock(&dilock);
	Tcl_MutexUnlock(&fblock);
	return 1;
    }

    std::cout << "Window updating!\n";

    // Let Tcl/Tk know the photo data has changed, so it can update the visuals
    // accordingly
    Tk_PhotoImageBlock dm_data;
    Tk_PhotoHandle dm_img = Tk_FindPhoto(interp, DM_PHOTO);
    Tk_PhotoGetImage(dm_img, &dm_data);
    if (dm_data.width != width || dm_data.height != height) {
	Tk_PhotoSetSize(interp, dm_img, width, height);
	Tk_PhotoGetImage(dm_img, &dm_data);
    }


    // Tk_PhotoPutBlock appears to be making a copy of the data, so we should
    // be able to point to our thread's rendered data to feed it in for
    // copying without worrying that Tk might alter it.
    dm_data.pixelPtr = idata->dmpixel;
    Tk_PhotoPutBlock(interp, dm_img, &dm_data, 0, 0, dm_data.width, dm_data.height, TK_PHOTO_COMPOSITE_SET);

    // Now overlay the framebuffer.
    Tk_PhotoImageBlock fb_data;
    Tk_PhotoGetImage(dm_img, &fb_data);
    fb_data.width = idata->fb_width;
    fb_data.height = idata->fb_height;
    fb_data.pitch = fb_data.width * 4;
    fb_data.pixelPtr = idata->fbpixel;
    Tk_PhotoPutBlock(interp, dm_img, &fb_data, 0, 0, idata->fb_width, idata->fb_height, TK_PHOTO_COMPOSITE_OVERLAY);

    Tcl_MutexUnlock(&dilock);
    Tcl_MutexUnlock(&fblock);

    // Return one to signify a successful completion of the process execution
    return 1;
}

int
image_update_data(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{
    struct img_data *idata = (struct img_data *)clientData;

    if (argc == 3) {
	// Unpack the current width and height.  If these don't match what idata has
	// or thinks its working on, update the image size.
	// (Note: checking errno, although it may not truly be necessary if we
	// trust Tk to always give us valid coordinates...)
	char *p_end;
	errno = 0;
	long width = strtol(argv[1], &p_end, 10);
	if (errno == ERANGE || (errno != 0 && width == 0) || p_end == argv[1]) {
	    std::cerr << "Invalid width: " << argv[1] << "\n";
	    return TCL_ERROR;
	}
	errno = 0;
	long height = strtol(argv[2], &p_end, 10);
	if (errno == ERANGE || (errno != 0 && height == 0) || p_end == argv[1]) {
	    std::cerr << "Invalid height: " << argv[2] << "\n";
	    return TCL_ERROR;
	}

	Tcl_MutexLock(&dilock);
	idata->dm_width = width;
	idata->dm_height = height;
	Tcl_MutexUnlock(&dilock);

	Tk_PhotoImageBlock dm_data;
	Tk_PhotoHandle dm_img = Tk_FindPhoto(interp, DM_PHOTO);
	Tk_PhotoGetImage(dm_img, &dm_data);
	if (dm_data.width != idata->dm_width || dm_data.height != idata->dm_height) {
	    Tk_PhotoSetSize(interp, dm_img, idata->dm_width, idata->dm_height);
	}
    }

    // Generate an event for the manager thread to let it know we need work
    Tcl_MutexLock(&threadMutex);
    struct RenderEvent *threadEventPtr = (struct RenderEvent *)ckalloc(sizeof(RenderEvent));
    threadEventPtr->idata = idata;
    threadEventPtr->event.proc = noop_proc;
    Tcl_ThreadQueueEvent(idata->dm_id, (Tcl_Event *) threadEventPtr, TCL_QUEUE_TAIL);
    Tcl_ThreadAlert(idata->dm_id);
    Tcl_MutexUnlock(&threadMutex);

    return TCL_OK;
}

// Given an X,Y coordinate in a TkPhoto image and a desired offset in
// X and Y, return the index value into the pixelPtr array N such that
// N is the integer value of the R color at that X,Y coordiante, N+1
// is the G value, N+2 is the B value and N+3 is the Alpha value.
// If either desired offset is beyond the width and height boundaries,
// cap the return at the minimum/maximum allowed value.
static int
img_xy_index(int width, int height, int x, int y, int dx, int dy)
{
    int nx = ((x + dx) > width)  ? width  : ((x + dx) < 0) ? 0 : x + dx;
    int ny = ((y + dy) > height) ? height : ((y + dy) < 0) ? 0 : y + dy;
    return (ny * width * 4) + nx * 4;
}

/* This is a test of directly manipulating the Tk_Photo data itself, without
 * copying in a buffer.  Probably not something we want to do for real... */
int
image_paint_xy(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{
    if (argc != 3) {
	std::cerr << "Unexpected argc: " << argc << "\n";
	return TCL_ERROR;
    }

    struct img_data *idata = (struct img_data *)clientData;

    // If we're mid-render, don't draw - we're about to get superceded by
    // another frame.
    if (idata->dm_render_running) {
	return TCL_OK;
    }

    // Unpack the coordinates (checking errno, although it may not truly be
    // necessary if we trust Tk to always give us valid coordinates...)
    char *p_end;
    errno = 0;
    long xcoor = strtol(argv[1], &p_end, 10);
    if (errno == ERANGE || (errno != 0 && xcoor == 0) || p_end == argv[1]) {
	std::cerr << "Invalid image_paint_xy X coordinate: " << argv[1] << "\n";
	return TCL_ERROR;
    }
    errno = 0;
    long ycoor = strtol(argv[2], &p_end, 10);
    if (errno == ERANGE || (errno != 0 && ycoor == 0) || p_end == argv[1]) {
	std::cerr << "Invalid image_paint_xy Y coordinate: " << argv[2] << "\n";
	return TCL_ERROR;
    }

    // Look up the internals of the image - we're going to directly manipulate
    // the values of the image to simulate a display manager or framebuffer
    // changing the visual via rendering.
    Tk_PhotoImageBlock dm_data;
    Tk_PhotoHandle dm_img = Tk_FindPhoto(interp, DM_PHOTO);
    Tk_PhotoGetImage(dm_img, &dm_data);


    for (int i = -2; i < 3; i++) {
	for (int j = -2; j < 3; j++) {
	    int pindex = img_xy_index(dm_data.width, dm_data.height, xcoor, ycoor, i, j);
	    if (pindex >= idata->dm_buff_size - 1) {
		continue;
	    }
	    // Set to opaque white
	    dm_data.pixelPtr[pindex] = 255;
	    dm_data.pixelPtr[pindex+1] = 255;
	    dm_data.pixelPtr[pindex+2] = 255;
	    dm_data.pixelPtr[pindex+3] = 255;
	}
    }

    // Let Tcl/Tk know the photo data has changed, so it can update the visuals accordingly.
    Tk_PhotoPutBlock(interp, dm_img, &dm_data, 0, 0, dm_data.width, dm_data.height, TK_PHOTO_COMPOSITE_SET);

    return TCL_OK;
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
DrawText(struct font_info *f, int width, int height)
{
    FONScontext *fs = f->fs;
    glDisable(GL_LIGHTING);

    float sx, sy, dx, dy, lh = 0;
    unsigned int white,black,brown,blue;
    // Update and render
    glViewport(0, 0, width, height);
    glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,width,height,0,-1,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glColor4ub(255,255,255,255);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

    white = glfonsRGBA(255,255,255,255);
    brown = glfonsRGBA(192,128,0,128);
    blue = glfonsRGBA(0,192,255,255);
    black = glfonsRGBA(0,0,0,255);

    sx = 50; sy = 50;

    dx = sx; dy = sy;

    //dash(dx,dy);

    fonsClearState(fs);

    fonsSetSize(fs, 124.0f);
    fonsSetFont(fs, f->fontNormal);
    fonsVertMetrics(fs, NULL, NULL, &lh);
    dx = sx;
    dy += lh;
    //dash(dx,dy);

    fonsSetSize(fs, 124.0f);
    fonsSetFont(fs, f->fontNormal);
    fonsSetColor(fs, white);
    dx = fonsDrawText(fs, dx,dy,"The quick ",NULL);

    fonsSetSize(fs, 48.0f);
    fonsSetFont(fs, f->fontItalic);
    fonsSetColor(fs, brown);
    dx = fonsDrawText(fs, dx,dy,"brown ",NULL);

    fonsSetSize(fs, 24.0f);
    fonsSetFont(fs, f->fontNormal);
    fonsSetColor(fs, white);
    dx = fonsDrawText(fs, dx,dy,"fox ",NULL);

    fonsVertMetrics(fs, NULL, NULL, &lh);
    dx = sx;
    dy += lh*1.2f;
    //dash(dx,dy);
    fonsSetFont(fs, f->fontItalic);
    dx = fonsDrawText(fs, dx,dy,"jumps over ",NULL);
    fonsSetFont(fs, f->fontBold);
    dx = fonsDrawText(fs, dx,dy,"the lazy ",NULL);
    fonsSetFont(fs, f->fontNormal);
    dx = fonsDrawText(fs, dx,dy,"dog.",NULL);

    dx = sx;
    dy += lh*1.2f;
    //dash(dx,dy);
    fonsSetSize(fs, 12.0f);
    fonsSetFont(fs, f->fontNormal);
    fonsSetColor(fs, blue);
    fonsDrawText(fs, dx,dy,"Now is the time for all good men to come to the aid of the party.",NULL);

    fonsVertMetrics(fs, NULL,NULL,&lh);
    dx = sx;
    dy += lh*1.2f*2;
    //dash(dx,dy);
    fonsSetSize(fs, 18.0f);
    fonsSetFont(fs, f->fontItalic);
    fonsSetColor(fs, white);
    fonsDrawText(fs, dx,dy,"Ég get etið gler án þess að meiða mig.",NULL);

    fonsVertMetrics(fs, NULL,NULL,&lh);
    dx = sx;
    dy += lh*1.2f;
    //dash(dx,dy);
    fonsSetFont(fs, f->fontJapanese);
    fonsDrawText(fs, dx,dy,"私はガラスを食べられます。それは私を傷つけません。",NULL);

    // Font alignment
    fonsSetSize(fs, 18.0f);
    fonsSetFont(fs, f->fontNormal);
    fonsSetColor(fs, white);

    dx = 50; dy = 350;
    //line(dx-10,dy,dx+250,dy);
    fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_TOP);
    dx = fonsDrawText(fs, dx,dy,"Top",NULL);
    dx += 10;
    fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_MIDDLE);
    dx = fonsDrawText(fs, dx,dy,"Middle",NULL);
    dx += 10;
    fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE);
    dx = fonsDrawText(fs, dx,dy,"Baseline",NULL);
    dx += 10;
    fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BOTTOM);
    fonsDrawText(fs, dx,dy,"Bottom",NULL);

    dx = 150; dy = 400;
    //line(dx,dy-30,dx,dy+80.0f);
    fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE);
    fonsDrawText(fs, dx,dy,"Left",NULL);
    dy += 30;
    fonsSetAlign(fs, FONS_ALIGN_CENTER | FONS_ALIGN_BASELINE);
    fonsDrawText(fs, dx,dy,"Center",NULL);
    dy += 30;
    fonsSetAlign(fs, FONS_ALIGN_RIGHT | FONS_ALIGN_BASELINE);
    fonsDrawText(fs, dx,dy,"Right",NULL);

    // Blur
    dx = 500; dy = 350;
    fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE);

    fonsSetSize(fs, 60.0f);
    fonsSetFont(fs, f->fontItalic);
    fonsSetColor(fs, white);
    fonsSetSpacing(fs, 5.0f);
    fonsSetBlur(fs, 10.0f);
    fonsDrawText(fs, dx,dy,"Blurry...",NULL);

    dy += 50.0f;

    fonsSetSize(fs, 18.0f);
    fonsSetFont(fs, f->fontBold);
    fonsSetColor(fs, black);
    fonsSetSpacing(fs, 0.0f);
    fonsSetBlur(fs, 3.0f);
    fonsDrawText(fs, dx,dy+2,"DROP THAT SHADOW",NULL);

    fonsSetColor(fs, white);
    fonsSetBlur(fs, 0);
    fonsDrawText(fs, dx,dy,"DROP THAT SHADOW",NULL);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

static Tcl_ThreadCreateType
Dm_Render(ClientData clientData)
{
    // Unpack the shared data object
    struct img_data *idata = (struct img_data *)clientData;

    // Lock updating of the idata values until we've gotten this run's key
    // information - we don't want this changing mid-render.
    Tcl_MutexLock(&dilock);

    // Anything before this point will be convered by this render.  (This
    // flag may get set after this render starts by additional events, but
    // to this point this rendering will handle it.)
    idata->dm_render_needed = 0;

    // We're now in process - don't start another frame until this one
    // is complete.
    idata->dm_render_running = 1;

    // Until we're done, make sure nobody thinks we are ready
    idata->dm_render_ready = 0;

    // Lock in this width and height - that's what we've got memory for,
    // so that's what the remainder of this rendering pass will use.
    idata->dm_bwidth = idata->dm_width;
    idata->dm_bheight = idata->dm_height;

    // Have the key values now, we can unlock and allow interactivity in
    // the parent.  We'll finish this rendering pass before paying any
    // further attention to parent settings, but the parent may now set
    // them for future consideration.
    Tcl_MutexUnlock(&dilock);

    //////////////////////////////////////////////////////////////////////////////
    // Rendering operation - this is where the work of a DM/FB render pass
    // would occur in a real application
    //////////////////////////////////////////////////////////////////////////////

    // Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    float r = (*idata->colors)((*idata->gen));
    float g = (*idata->colors)((*idata->gen));
    float b = (*idata->colors)((*idata->gen));
    GLfloat rand_mat[]  = { r, g, b, 1.0 };


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
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, rand_mat );
    Torus(0.275, 0.85, 20, 20);
    glPopMatrix();
    glPopMatrix();

    // TODO - there seems to be some problem triggered by fonsDrawText
    DrawText(&idata->f, idata->dm_width, idata->dm_height);

    /* This is very important!!!
     * Make sure buffered commands are finished!!!
     */
    glFinish();

    glReadPixels(0, 0, idata->dm_width, idata->dm_height, GL_RGBA, GL_UNSIGNED_BYTE, idata->dmpixel);


    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    //std::cout << "DM update: " << r << "," << g << "," << b << "\n";

    // Update done - let the parent structure know.  We don't clear the
    // render_needed flag here, since the parent window may have changed
    // between the start and the end of this render and if it has we need
    // to start over.
    Tcl_MutexLock(&dilock);
    idata->dm_render_running = 0;
    Tcl_MutexLock(&threadMutex);
    idata->dm_render_ready = 1;
    Tcl_MutexUnlock(&threadMutex);
    Tcl_MutexUnlock(&dilock);

    // Generate an event for the manager thread to let it know we're done
    Tcl_MutexLock(&threadMutex);
    struct RenderEvent *threadEventPtr = (struct RenderEvent *)ckalloc(sizeof(RenderEvent));
    threadEventPtr->idata = idata;
    threadEventPtr->event.proc = noop_proc;
    Tcl_ThreadQueueEvent(idata->dm_id, (Tcl_Event *) threadEventPtr, TCL_QUEUE_TAIL);
    Tcl_ThreadAlert(idata->dm_id);
    Tcl_MutexUnlock(&threadMutex);

    Tcl_MutexUnlock(&DmMutex);

    // Render complete, we're done with this thread
    Tcl_ExitThread(TCL_OK);
    TCL_THREAD_CREATE_RETURN;
}


static Tcl_ThreadCreateType
Fb_Render(ClientData clientData)
{
    // Unpack the shared data object
    struct img_data *idata = (struct img_data *)clientData;

    // Lock updating of the idata values until we've gotten this run's key
    // information - we don't want this changing mid-render.
    Tcl_MutexLock(&fblock);

    // We're now in process - don't start another frame until this one
    // is complete.
    idata->fb_render_running = 1;

    // Until we're done, make sure nobody thinks we are ready
    Tcl_MutexLock(&threadMutex);
    idata->fb_render_ready = 0;
    Tcl_MutexUnlock(&threadMutex);

    // Lock in this width and height - that's what we've got memory for,
    // so that's what the remainder of this rendering pass will use.
    idata->fb_width = idata->dm_width;
    idata->fb_height = idata->dm_height;

    // If we have insufficient memory, allocate or reallocate a local
    // buffer big enough for the purpose.  We use our own buffer for
    // rendering to allow Tk full control over what it wants to do behind
    // the scenes.  We need this memory to persist, so handle it from the
    // management thread.
    long b_minsize = idata->fb_width * idata->fb_height * 4;
    if (!idata->fbpixel || idata->fb_buff_size < b_minsize) {
	idata->fbpixel = (unsigned char *)realloc(idata->fbpixel, 2*b_minsize*sizeof(char));
	idata->fb_buff_size = b_minsize * 2;
    }

    // Have the key values now, we can unlock and allow interactivity in
    // the parent.  We'll finish this rendering pass before paying any
    // further attention to parent settings, but the parent may now set
    // them for future consideration.
    Tcl_MutexUnlock(&fblock);

    //////////////////////////////////////////////////////////////////////////////
    // Rendering operation - this is where the work of a FB render pass
    // would occur in a real application
    //////////////////////////////////////////////////////////////////////////////

    int r = (*idata->colors)((*idata->gen));
    int g = (*idata->colors)((*idata->gen));
    int b = (*idata->colors)((*idata->gen));

    // Initialize. This alters the actual data, but Tcl/Tk doesn't know about it yet.
    for (int i = 0; i < (idata->fb_width * idata->fb_height * 4); i+=4) {
	// Red
	idata->fbpixel[i] = (r) ? 255 : 0;
	// Green
	idata->fbpixel[i+1] = (g) ? 255 : 0;
	// Blue
	idata->fbpixel[i+2] = (b) ? 255 : 0;
	// Alpha
	idata->fbpixel[i+3] = 100;
    }

    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    Tcl_MutexLock(&fblock);
    idata->fb_render_running = 0;
    Tcl_MutexLock(&threadMutex);
    idata->fb_render_ready = 1;
    Tcl_MutexUnlock(&threadMutex);
    Tcl_MutexUnlock(&fblock);

    std::cout << "FB update: " << r << "," << g << "," << b << "\n";

    // Generate an event for the manager thread to let it know we're done, if the
    // display manager isn't already about to generate such an event
    Tcl_MutexLock(&threadMutex);
    struct RenderEvent *threadEventPtr = (struct RenderEvent *)ckalloc(sizeof(RenderEvent));
    threadEventPtr->idata = idata;
    threadEventPtr->event.proc = noop_proc;
    Tcl_ThreadQueueEvent(idata->fb_id, (Tcl_Event *) threadEventPtr, TCL_QUEUE_TAIL);
    Tcl_ThreadAlert(idata->fb_id);
    Tcl_MutexUnlock(&threadMutex);

    // Render complete, we're done with this thread
    Tcl_ExitThread(TCL_OK);
    TCL_THREAD_CREATE_RETURN;
}


static Tcl_ThreadCreateType
Dm_Update_Manager(ClientData clientData)
{
    // This thread needs to process events - give it its own interp so it can do so.
    Tcl_Interp *interp = Tcl_CreateInterp();
    Tcl_Init(interp);

    // Unpack the shared data object
    struct img_data *idata = (struct img_data *)clientData;

    // Set up our data sources - we'll reuse these for each render, so they are
    // set up in the managing thread
    std::default_random_engine gen;
    std::uniform_int_distribution<int> colors(0,1);
    std::uniform_int_distribution<int> vals(50,255);
    idata->gen = &gen;
    idata->colors = &colors;
    idata->vals = &vals;

    idata->ctx = OSMesaCreateContextExt( OSMESA_RGBA, 16, 0, 0, NULL );
    if (!idata->ctx) {
	printf("OSMesaCreateContext failed!\n");
	exit(1);
    }
    idata->os_b = calloc(idata->screen_width * idata->screen_height, sizeof(GLubyte)*4);
    if (!idata->os_b) {
	printf("buffer allocation failed!\n");
	exit(1);
    }
    if (!OSMesaMakeCurrent(idata->ctx, idata->os_b, GL_UNSIGNED_BYTE, idata->dm_width, idata->dm_height)) {
	printf("OSMesaMakeCurrent failed!\n");
	exit(1);
    }


    // Avoid the need to flip pixels
    OSMesaPixelStore(OSMESA_Y_UP, 0);


    // Have context - set up font info
    idata->f.fs = glfonsCreate(800, 800, FONS_ZERO_TOPLEFT);
    if (idata->f.fs == NULL) {
	printf("Could not create stash.\n");
	exit(1);
    }
    idata->f.fontNormal = fonsAddFont(idata->f.fs, "sans", "../../examples/fontstash/DroidSerif-Regular.ttf");
    if (idata->f.fontNormal == FONS_INVALID) {
	printf("Could not add font normal.\n");
	exit(1);
    }
    idata->f.fontItalic = fonsAddFont(idata->f.fs, "sans-italic", "../../examples/fontstash/DroidSerif-Italic.ttf");
    if (idata->f.fontItalic == FONS_INVALID) {
	printf("Could not add font italic.\n");
	exit(1);
    }
    idata->f.fontBold = fonsAddFont(idata->f.fs, "sans-bold", "../../examples/fontstash/DroidSerif-Bold.ttf");
    if (idata->f.fontBold == FONS_INVALID) {
	printf("Could not add font bold.\n");
	exit(1);
    }
    idata->f.fontJapanese = fonsAddFont(idata->f.fs, "sans-jp", "../../examples/fontstash/DroidSansJapanese.ttf");
    if (idata->f.fontJapanese == FONS_INVALID) {
	printf("Could not add font japanese.\n");
	exit(1);
    }


    idata->x = 0;
    idata->t = 0;

    glViewport( 0, 0, idata->dm_width, idata->dm_height);
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    // Until we're shutting down, check for and process events - this thread will persist
    // for the life of the application.
    while (!idata->shutdown) {

	// Events can come from either the parent (requesting a rendering, announcing a shutdown)
	// or from the rendering thread (announcing completion of a rendering.)
	Tcl_DoOneEvent(0);

	// If anyone flipped the shutdown switch while we were waiting on an
	// event, don't do any more work - there's no point.
	if (idata->shutdown) {
	    continue;
	}

	// If we have a render ready, let the parent know to update the GUI before we
	// go any further.  Even if a completed render is out of data, it's closer to
	// current than what was previously displayed so the application should go ahead
	// and show it.
	if (idata->dm_render_ready) {

	    // Generate an event for the parent thread - its time to update the
	    // Tk_Photo in the GUI that's holding the image
	    Tcl_MutexLock(&threadMutex);
	    struct RenderEvent *threadEventPtr = (struct RenderEvent *)ckalloc(sizeof(RenderEvent));
	    threadEventPtr->idata = idata;
	    threadEventPtr->event.proc = UpdateProc;
	    Tcl_ThreadQueueEvent(idata->parent_id, (Tcl_Event *) threadEventPtr, TCL_QUEUE_TAIL);
	    Tcl_ThreadAlert(idata->parent_id);
	    Tcl_MutexUnlock(&threadMutex);

	    // If we don't have any work pending, go back to waiting.  If we know
	    // we're already out of date, proceed without waiting for another event
	    // from the parent - we've already had one.
	    if (!idata->dm_render_needed) {
		continue;
	    }
	}

	// If we're already rendering and we have another rendering event, it's
	// an update request from the parent - set the flag and continue
	if (idata->dm_render_running) {
	    idata->dm_render_needed = 1;
	    continue;
	}

	// If we need a render and aren't already running, it's time to go to
	// work.  We may have had a resize event, so call make current again to
	// get up to date with the latest dm sizes.
	if (!OSMesaMakeCurrent(idata->ctx, idata->os_b, GL_UNSIGNED_BYTE, idata->dm_width, idata->dm_height)) {
	    printf("OSMesaMakeCurrent failed!\n");
	    exit(1);
	}
	glViewport( 0, 0, idata->dm_width, idata->dm_height);

	// Start a rendering thread.
	Tcl_ThreadId threadID;
	Tcl_MutexLock(&DmMutex);
	if (Tcl_CreateThread(&threadID, Dm_Render, (ClientData)idata, TCL_THREAD_STACK_DEFAULT, TCL_THREAD_NOFLAGS) != TCL_OK) {
	    std::cerr << "can't create dm render thread\n";
	}
    }

    // We're well and truly done - the application is closing down - free the
    // rendering buffer and quit the thread
    if (idata->dmpixel) {
	free(idata->dmpixel);
    }
    Tcl_ExitThread(TCL_OK);
    TCL_THREAD_CREATE_RETURN;
}

static Tcl_ThreadCreateType
Fb_Update_Manager(ClientData clientData)
{
    // This thread needs to process events - give it its own interp so it can do so.
    Tcl_Interp *interp = Tcl_CreateInterp();
    Tcl_Init(interp);

    // Unpack the shared data object
    struct img_data *idata = (struct img_data *)clientData;

    // Until we're shutting down, check for and process events - this thread will persist
    // for the life of the application.
    while (!idata->shutdown) {

	// Events can come from either the parent (requesting a rendering, announcing a shutdown)
	// or from the rendering thread (announcing completion of a rendering.)

	// Eventually we'll want separate events to trigger this, but for now just update it at
	// regular intervals
	if (!idata->fb_render_ready) {
	    Tcl_Sleep(2000);
	}
	//Tcl_DoOneEvent(0);


	// If anyone flipped the shutdown switch while we were waiting, don't
	// do any more work - there's no point.
	if (idata->shutdown) {
	    continue;
	}

	// If we have a render ready, let the parent know to update the GUI.
	if (idata->fb_render_ready) {

	    // Generate an event for the parent thread - its time to update the
	    // Tk_Photo in the GUI that's holding the image
	    Tcl_MutexLock(&threadMutex);
	    struct RenderEvent *threadEventPtr = (struct RenderEvent *)ckalloc(sizeof(RenderEvent));
	    threadEventPtr->idata = idata;
	    threadEventPtr->event.proc = UpdateProc;
	    Tcl_ThreadQueueEvent(idata->parent_id, (Tcl_Event *) threadEventPtr, TCL_QUEUE_TAIL);
	    Tcl_ThreadAlert(idata->parent_id);
	    Tcl_MutexUnlock(&threadMutex);

	    // Go back to waiting.
	    Tcl_MutexLock(&threadMutex);
	    idata->fb_render_ready = 0;
	    Tcl_MutexUnlock(&threadMutex);
	    continue;
	}

	// If we need a render and aren't already running, it's time to go to work.
	// Start a framebuffer thread.
	std::cout << "Framebuffer updating!\n";
	Tcl_ThreadId fbthreadID;
	if (Tcl_CreateThread(&fbthreadID, Fb_Render, (ClientData)idata, TCL_THREAD_STACK_DEFAULT, TCL_THREAD_NOFLAGS) != TCL_OK) {
	    std::cerr << "can't create fb render thread\n";
	}

    }

    // We're well and truly done - the application is closing down - free the
    // rendering buffer and quit the thread
    if (idata->fbpixel) {
	free(idata->fbpixel);
    }
    Tcl_ExitThread(TCL_OK);
    TCL_THREAD_CREATE_RETURN;
}

int
main(int argc, const char *argv[])
{
    std::string bind_cmd;

    // For now, just use a fixed 512x512 image size
    int wsize = 512;

    // Set up random image data generation so we can simulate a raytrace or
    // raster changing the view data.  We need to use these for subsequent
    // image updating, so pack them into a structure we can pass through Tcl's
    // evaluations.
    struct img_data *idata = (struct img_data *)calloc(1, sizeof(struct img_data));
    idata->dm_render_needed = 1;
    idata->dm_render_running = 0;
    idata->dm_render_ready = 0;
    idata->shutdown = 0;
    idata->fb_buff_size = 0;
    idata->fbpixel = NULL;
    idata->parent_id = Tcl_GetCurrentThread();

    // Set up Tcl/Tk
    Tcl_FindExecutable(argv[0]);
    Tcl_Interp *interp = Tcl_CreateInterp();
    Tcl_Init(interp);
    Tk_Init(interp);

    // Save a pointer so we can get at the interp later
    idata->parent_interp = interp;

    // Make a simple toplevel window
    Tk_Window tkwin = Tk_MainWindow(interp);
    Tk_GeometryRequest(tkwin, wsize, wsize);
    Tk_MakeWindowExist(tkwin);
    Tk_MapWindow(tkwin);

    // Store the screen size
    idata->screen_width = WidthOfScreen(Tk_Screen(tkwin));
    idata->screen_height = HeightOfScreen(Tk_Screen(tkwin));

    // Rather than try to resize the memory while multiple threads are trying to draw,
    // make a container big enough to support our screen and be done with it.
    idata->dm_buff_size = idata->screen_width * idata->screen_height * sizeof(GLubyte)*4;
    idata->dmpixel = (unsigned char *)malloc(idata->dm_buff_size*sizeof(char));

    // Create the (initially empty) Tcl/Tk Photo (a.k.a color image) we will
    // use as our rendering canvas for the images.
    //
    // Note: confirmed with Tcl/Tk community that (at least as of Tcl/Tk 8.6)
    // Tcl_Eval is the ONLY way to create an image object.  The C API doesn't
    // expose that ability, although it does support manipulation of the
    // created object.
    std::string img_cmd = std::string("image create photo ") + std::string(DM_PHOTO);
    Tcl_Eval(interp, img_cmd.c_str());
    Tk_PhotoHandle dm_img = Tk_FindPhoto(interp, DM_PHOTO);
    Tk_PhotoBlank(dm_img);
    Tk_PhotoSetSize(interp, dm_img, wsize, wsize);

    // Initialize the PhotoImageBlock information for a color image of size
    // 500x500 pixels.
    Tk_PhotoImageBlock dm_data;
    dm_data.width = wsize;
    dm_data.height = wsize;
    dm_data.pixelSize = 4;
    dm_data.pitch = wsize * 4;
    dm_data.offset[0] = 0;
    dm_data.offset[1] = 1;
    dm_data.offset[2] = 2;
    dm_data.offset[3] = 3;

    // Actually create our memory for the image buffer.  Expects RGBA information
    dm_data.pixelPtr = (unsigned char *)Tcl_AttemptAlloc(dm_data.width * dm_data.height * 4);
    if (!dm_data.pixelPtr) {
	std::cerr << "Tcl/Tk photo memory allocation failed!\n";
	exit(1);
    }

    // Initialize. This alters the actual data, but Tcl/Tk doesn't know about it yet.
    for (int i = 0; i < (dm_data.width * dm_data.height * 4); i+=4) {
	// Red
	dm_data.pixelPtr[i] = 0;
	// Green
	dm_data.pixelPtr[i+1] = 255;
	// Blue
	dm_data.pixelPtr[i+2] = 0;
	// Alpha at 255 - we dont' want transparency for this demo.
	dm_data.pixelPtr[i+3] = 255;
    }

    // Let Tk_Photo know we have data
    Tk_PhotoPutBlock(interp, dm_img, &dm_data, 0, 0, dm_data.width, dm_data.height, TK_PHOTO_COMPOSITE_SET);

    // We now have a window - set the default idata size
    idata->dm_width = dm_data.width;
    idata->dm_height = dm_data.height;

    // Define a canvas widget, pack it into the root window, and associate the image with it
    // TODO - should the canvas be inside a frame?
    std::string canvas_cmd = std::string("canvas ") + std::string(DM_CANVAS) + std::string(" -width ") + std::to_string(wsize) + std::string(" -height ")  + std::to_string(wsize) + std::string(" -borderwidth 0");
    Tcl_Eval(interp, canvas_cmd.c_str());
    std::string pack_cmd = std::string("pack ") + std::string(DM_CANVAS) + std::string(" -fill both -expand 1");
    Tcl_Eval(interp, pack_cmd.c_str());
    std::string canvas_img_cmd = std::string(DM_CANVAS) + std::string(" create image 0 0 -image ") + std::string(DM_PHOTO) + std::string(" -anchor nw");
    Tcl_Eval(interp, canvas_img_cmd.c_str());


    // Register a paint command so we can change the image contents near the cursor position
    (void)Tcl_CreateCommand(interp, "image_paint", (Tcl_CmdProc *)image_paint_xy, (ClientData)idata, (Tcl_CmdDeleteProc* )NULL);
    // Establish the Button-1+Motion combination event as the trigger for drawing on the image
    bind_cmd = std::string("bind . <B1-Motion> {image_paint %x %y}");
    Tcl_Eval(interp, bind_cmd.c_str());


    // Register an update command so we can change the image contents
    (void)Tcl_CreateCommand(interp, "image_update", (Tcl_CmdProc *)image_update_data, (ClientData)idata, (Tcl_CmdDeleteProc* )NULL);
    // Establish the Button-2 and Button-3 event as triggers for updating the image contents
    bind_cmd = std::string("bind . <Button-2> {image_update}");
    Tcl_Eval(interp, bind_cmd.c_str());
    bind_cmd = std::string("bind . <Button-3> {image_update}");
    Tcl_Eval(interp, bind_cmd.c_str());

    // Update the photo if the window changes
    bind_cmd = std::string("bind ") + std::string(DM_CANVAS) + std::string(" <Configure> {image_update [winfo width %W] [winfo height %W]\"}");
    Tcl_Eval(interp, bind_cmd.c_str());

    // Multithreading experiment
    Tcl_ThreadId threadID;
    if (Tcl_CreateThread(&threadID, Dm_Update_Manager, (ClientData)idata, TCL_THREAD_STACK_DEFAULT, TCL_THREAD_JOINABLE) != TCL_OK) {
	std::cerr << "can't create thread\n";
    }
    idata->dm_id = threadID;

    Tcl_ThreadId fbthreadID;
    if (Tcl_CreateThread(&fbthreadID, Fb_Update_Manager, (ClientData)idata, TCL_THREAD_STACK_DEFAULT, TCL_THREAD_JOINABLE) != TCL_OK) {
	std::cerr << "can't create thread\n";
    }
    idata->fb_id = fbthreadID;


    // Enter the main applicatio loop - the initial image will appear, and Button-1 mouse
    // clicks on the window should generate and display new images
    while (1) {
	Tcl_DoOneEvent(0);
	if (!Tk_GetNumMainWindows()) {
	    int tret;

	    // If we've closed the window, we're done - start spreading the word
	    idata->shutdown = 1;


	    // After setting the shutdown flag, send an event to wake up the FB update manager thread.
	    // It will see the change in status and proceed to shut itself down.
	    Tcl_MutexLock(&fblock);
	    struct RenderEvent *threadEventPtr = (struct RenderEvent *)ckalloc(sizeof(RenderEvent));
	    threadEventPtr->idata = idata;
	    threadEventPtr->event.proc = noop_proc;
	    Tcl_ThreadQueueEvent(idata->fb_id, (Tcl_Event *) threadEventPtr, TCL_QUEUE_TAIL);
	    Tcl_ThreadAlert(idata->fb_id);
	    Tcl_MutexUnlock(&fblock);

	    // Wait for the thread cleanup to complete
	    Tcl_JoinThread(idata->fb_id, &tret);
	    if (tret != TCL_OK) {
		std::cerr << "Failed to shut down framebuffer management thread\n";
	    } else {
		std::cout << "Successful framebuffer management thread shutdown\n";
	    }

	    // After setting the shutdown flag, send an event to wake up the update manager thread.
	    // It will see the change in status and proceed to shut itself down.
	    Tcl_MutexLock(&dilock);
	    threadEventPtr = (struct RenderEvent *)ckalloc(sizeof(RenderEvent));
	    threadEventPtr->idata = idata;
	    threadEventPtr->event.proc = noop_proc;
	    Tcl_ThreadQueueEvent(idata->dm_id, (Tcl_Event *) threadEventPtr, TCL_QUEUE_TAIL);
	    Tcl_ThreadAlert(idata->dm_id);
	    Tcl_MutexUnlock(&dilock);

	    // Wait for the thread cleanup to complete
	    Tcl_JoinThread(idata->dm_id, &tret);
	    if (tret != TCL_OK) {
		std::cerr << "Failed to shut down display management thread\n";
	    } else {
		std::cout << "Successful display management thread shutdown\n";
	    }


	    // Clean up memory and exit
	    OSMesaDestroyContext( idata->ctx );
	    free(idata);
	    exit(0);
	}
    }
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
