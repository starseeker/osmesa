// TinyGL triangle example
//
// adapted from GLFW, glfw.sf.net
// updated by Norbert Kett (anchor@rocketmail.com)
//
// Assuming this version derives from GLFW's version of the triangle demo
// (there are a lot of variations), GLFW uses the zlib license:
//
// Copyright (c) 2002-2006 Marcus Geelnard
// Copyright (c) 2006-2010 Camilla Berglund <elmindreda@elmindreda.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//
//
// Routines from GLU's libutil/project.c included
// to make this stand-alone:
//
// SGI FREE SOFTWARE LICENSE B (Version 2.0, Sept. 18, 2008)
// Copyright (C) 1991-2000 Silicon Graphics, Inc. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice including the dates of first publication and
// either this permission notice or a reference to
// http://oss.sgi.com/projects/FreeB/
// shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// SILICON GRAPHICS, INC. BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
// OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// Except as contained in this notice, the name of Silicon Graphics, Inc.
// shall not be used in advertising or otherwise to promote the sale, use or
// other dealings in this Software without prior written authorization from
// Silicon Graphics, Inc.


#define _USE_MATH_DEFINES /* for M_PI */
#include <math.h>
#include <stdio.h>
#include "OSMesa/gl.h"
#include "OSMesa/osmesa.h"
#include <SDL2/SDL.h>
#include "svpng.h"

static
void gluMakeIdentityd(GLdouble *m)
{
    m[0+4*0] = 1; m[0+4*1] = 0; m[0+4*2] = 0; m[0+4*3] = 0;
    m[1+4*0] = 0; m[1+4*1] = 1; m[1+4*2] = 0; m[1+4*3] = 0;
    m[2+4*0] = 0; m[2+4*1] = 0; m[2+4*2] = 1; m[2+4*3] = 0;
    m[3+4*0] = 0; m[3+4*1] = 0; m[3+4*2] = 0; m[3+4*3] = 1;
}

void
gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble m[4][4];
    double sine, cotangent, deltaZ;
    double radians = fovy / 2 * M_PI / 180;

    deltaZ = zFar - zNear;
    sine = sin(radians);
    if ((deltaZ == 0) || (sine == 0) || (aspect == 0)) {
        return;
    }
    cotangent = cos(radians) / sine;

    gluMakeIdentityd((GLdouble *)&m[0][0]);
    m[0][0] = cotangent / aspect;
    m[1][1] = cotangent;
    m[2][2] = -(zFar + zNear) / deltaZ;
    m[2][3] = -1;
    m[3][2] = -2 * zNear * zFar / deltaZ;
    m[3][3] = 0;
    glMultMatrixd(&m[0][0]);
}

int main(int argc, char **argv)
{
    // initialize SDL video:
    int winSizeX = 640;
    int winSizeY = 480;
    SDL_Window* window;
    SDL_Surface* screen;
    unsigned int pitch;
    int	mode;
    int frames;
    int x;
    double t, t0, fps;
    char titlestr[ 200 ];
    int running;
    OSMesaContext ctx;
    void *frameBuffer;
    SDL_Event evt;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	fprintf(stderr,"ERROR: cannot initialize SDL video.\n");
	return 1;
    }

    window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			      winSizeX, winSizeY, SDL_WINDOW_SHOWN);
    if (!window) {
	fprintf(stderr, "ERROR: Window creation failed. SDL_Error: %s\n",
		SDL_GetError());
	exit(1);
    }

    screen = SDL_GetWindowSurface(window);
    if (!screen) {
	fprintf(stderr, "ERROR: Getting window surface failed. SDL_Error: %s\n",
		SDL_GetError());
	exit(1);
    }

    ctx = OSMesaCreateContextExt( OSMESA_RGBA, 16, 0, 0, NULL );
    if (!ctx) {
	printf("OSMesaCreateContext failed!\n");
	exit(1);
    }

    frameBuffer = calloc(winSizeX * winSizeY, sizeof(GLubyte)*4);
    if (!OSMesaMakeCurrent(ctx, frameBuffer, GL_UNSIGNED_BYTE, winSizeX, winSizeY)) {
	printf("OSMesaMakeCurrent failed!\n");
	exit(1);
    }

    // set viewport
    glViewport(0, 0, winSizeX, winSizeY);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // main loop:
    frames = 0;
    x = 0;
    running = GL_TRUE;
    t0 = (double)SDL_GetTicks()/1000.0;
    while (running) {
	// calculate and display FPS (frames per second):
	t = (double)SDL_GetTicks()/1000.0;
	if ((t-t0) > 1.0 || frames == 0) {
	    fps = (double)frames / (t-t0);
	    sprintf(titlestr, "Spinning Triangle (%.1f FPS)", fps);
	    SDL_SetWindowTitle(window, titlestr);
	    t0 = t;
	    frames = 0;
	}
	++frames;

	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Select and setup the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0f, (GLfloat)winSizeX/(GLfloat)winSizeY, 1.0f, 100.0f);

	// Select and setup the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-90, 1,0,0);
	glTranslatef(0,0,-1.0f);

	// Draw a rotating colorful triangle
	glTranslatef(0.0f, 14.0f, 0.0f);
	glRotatef(0.3*(GLfloat)x + (GLfloat)t*100.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-5.0f, 0.0f, -4.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, -4.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 6.0f);
	glEnd();

	// swap buffers:
	if (SDL_MUSTLOCK(screen) && (SDL_LockSurface(screen)<0)) {
	    fprintf(stderr, "SDL ERROR: Can't lock screen: %s\n", SDL_GetError());
	    return 1;
	}

	// SDL pixel buffer expects BGRA data, not RGBA data - read accordingly
	glReadPixels(0, 0, winSizeX, winSizeY, GL_BGRA, GL_UNSIGNED_BYTE, screen->pixels);

	// Image will be upside-down from SDL's perspective, flip manually using an RGBA
	// variation of the math from:
	// https://github.com/vallentin/GLCollection/blob/master/screenshot.cpp
	//
	// Apparently this is necessary, since OpenGL doesn't provide a built-in way
	// to handle this:
	// https://www.opengl.org/archives/resources/features/KilgardTechniques/oglpitfall/
	for (int y = 0; y < winSizeY / 2; ++y) {
	    for (int x = 0; x < winSizeX; ++x) {
		int top = (x + y * winSizeX) * 4;
		int bottom = (x + (winSizeY - y - 1) * winSizeX) * 4;
		char rgba[4];
		memcpy(rgba, screen->pixels + top, sizeof(rgba));
		memcpy(screen->pixels + top, screen->pixels + bottom, sizeof(rgba));
		memcpy(screen->pixels + bottom, rgba, sizeof(rgba));
	    }
	}

	if (SDL_MUSTLOCK(screen)) {
	    SDL_UnlockSurface(screen);
	}
	SDL_UpdateWindowSurface(window);

	// check if the ESC key was pressed or the window was closed:

	while (SDL_PollEvent(&evt)) {
	    switch (evt.type) {
		case SDL_KEYDOWN:
		    if (evt.key.keysym.sym == SDLK_ESCAPE) {
			running = 0;
		    }
		    break;
		case SDL_QUIT:
		    running = 0;
		    break;
	    }
	}
    }

    // cleanup:
    OSMesaDestroyContext( ctx );
    free(frameBuffer);
    if (SDL_WasInit(SDL_INIT_VIDEO)) {
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
    SDL_Quit();
    return 0;
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
