// Copyright (c) 2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "OSMesa/gl.h"
#include "OSMesa/glu.h"
#include "OSMesa/osmesa.h"
#include <SDL/SDL.h>
#define FONTSTASH_IMPLEMENTATION
#include "fontstash/fontstash.h"
#define GLFONTSTASH_IMPLEMENTATION
#include "fontstash/glfontstash.h"

int debug = 0;

void dash(float dx, float dy)
{
    glBegin(GL_LINES);
    glColor4ub(0,0,0,128);
    glVertex2f(dx-5,dy);
    glVertex2f(dx-10,dy);
    glEnd();
}

void line(float sx, float sy, float ex, float ey)
{
    glBegin(GL_LINES);
    glColor4ub(0,0,0,128);
    glVertex2f(sx,sy);
    glVertex2f(ex,ey);
    glEnd();
}

int main(int argc, char **argv)
{
    // initialize SDL video:
    int width = 800;
    int height = 600;
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
    const SDL_VideoInfo* info;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	fprintf(stderr,"ERROR: cannot initialize SDL video.\n");
	return 1;
    }

    info = SDL_GetVideoInfo();

    screen = NULL;
    if ((screen=SDL_SetVideoMode(width, height, info->vfmt->BitsPerPixel, SDL_SWSURFACE)) == 0) {
	fprintf(stderr,"ERROR: Video mode set failed.\n");
	return 1;
    }

    ctx = OSMesaCreateContextExt( OSMESA_RGBA, 16, 0, 0, NULL );
    if (!ctx) {
	printf("OSMesaCreateContext failed!\n");
	exit(1);
    }

    frameBuffer = calloc(width * height, sizeof(GLubyte)*4);
    if (!OSMesaMakeCurrent(ctx, frameBuffer, GL_UNSIGNED_BYTE, width, height)) {
	printf("OSMesaMakeCurrent failed!\n");
	exit(1);
    }

    int fontNormal = FONS_INVALID;
    int fontItalic = FONS_INVALID;
    int fontBold = FONS_INVALID;
    int fontJapanese = FONS_INVALID;
    FONScontext* fs = NULL;
    fs = glfonsCreate(width, height, FONS_ZERO_TOPLEFT);
    if (fs == NULL) {
	printf("Could not create stash.\n");
	return -1;
    }
    fontNormal = fonsAddFont(fs, "sans", "../../../examples/fontstash/DroidSerif-Regular.ttf");
    if (fontNormal == FONS_INVALID) {
	printf("Could not add font normal.\n");
	return -1;
    }
    fontItalic = fonsAddFont(fs, "sans-italic", "../../../examples/fontstash/DroidSerif-Italic.ttf");
    if (fontItalic == FONS_INVALID) {
	printf("Could not add font italic.\n");
	return -1;
    }
    fontBold = fonsAddFont(fs, "sans-bold", "../../../examples/fontstash/DroidSerif-Bold.ttf");
    if (fontBold == FONS_INVALID) {
	printf("Could not add font bold.\n");
	return -1;
    }
    fontJapanese = fonsAddFont(fs, "sans-jp", "../../../examples/fontstash/DroidSansJapanese.ttf");
    if (fontJapanese == FONS_INVALID) {
	printf("Could not add font japanese.\n");
	return -1;
    }

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
	    sprintf(titlestr, "Fontstash Demo (%.1f FPS)", fps);
	    SDL_WM_SetCaption(titlestr,0);
	    t0 = t;
	    frames = 0;
	}
	++frames;

	float sx, sy, dx, dy, lh = 0;
	unsigned int white,black,brown,blue;
	// Update and render
	glViewport(0, 0, width, height);
	glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
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

	dash(dx,dy);

	fonsClearState(fs);

	fonsSetSize(fs, 124.0f);
	fonsSetFont(fs, fontNormal);
	fonsVertMetrics(fs, NULL, NULL, &lh);
	dx = sx;
	dy += lh;
	dash(dx,dy);

	fonsSetSize(fs, 124.0f);
	fonsSetFont(fs, fontNormal);
	fonsSetColor(fs, white);
	dx = fonsDrawText(fs, dx,dy,"The quick ",NULL);

	fonsSetSize(fs, 48.0f);
	fonsSetFont(fs, fontItalic);
	fonsSetColor(fs, brown);
	dx = fonsDrawText(fs, dx,dy,"brown ",NULL);

	fonsSetSize(fs, 24.0f);
	fonsSetFont(fs, fontNormal);
	fonsSetColor(fs, white);
	dx = fonsDrawText(fs, dx,dy,"fox ",NULL);

	fonsVertMetrics(fs, NULL, NULL, &lh);
	dx = sx;
	dy += lh*1.2f;
	dash(dx,dy);
	fonsSetFont(fs, fontItalic);
	dx = fonsDrawText(fs, dx,dy,"jumps over ",NULL);
	fonsSetFont(fs, fontBold);
	dx = fonsDrawText(fs, dx,dy,"the lazy ",NULL);
	fonsSetFont(fs, fontNormal);
	dx = fonsDrawText(fs, dx,dy,"dog.",NULL);

	dx = sx;
	dy += lh*1.2f;
	dash(dx,dy);
	fonsSetSize(fs, 12.0f);
	fonsSetFont(fs, fontNormal);
	fonsSetColor(fs, blue);
	fonsDrawText(fs, dx,dy,"Now is the time for all good men to come to the aid of the party.",NULL);

	fonsVertMetrics(fs, NULL,NULL,&lh);
	dx = sx;
	dy += lh*1.2f*2;
	dash(dx,dy);
	fonsSetSize(fs, 18.0f);
	fonsSetFont(fs, fontItalic);
	fonsSetColor(fs, white);
	fonsDrawText(fs, dx,dy,"Ég get etið gler án þess að meiða mig.",NULL);

	fonsVertMetrics(fs, NULL,NULL,&lh);
	dx = sx;
	dy += lh*1.2f;
	dash(dx,dy);
	fonsSetFont(fs, fontJapanese);
	fonsDrawText(fs, dx,dy,"私はガラスを食べられます。それは私を傷つけません。",NULL);

	// Font alignment
	fonsSetSize(fs, 18.0f);
	fonsSetFont(fs, fontNormal);
	fonsSetColor(fs, white);

	dx = 50; dy = 350;
	line(dx-10,dy,dx+250,dy);
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
	line(dx,dy-30,dx,dy+80.0f);
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
	fonsSetFont(fs, fontItalic);
	fonsSetColor(fs, white);
	fonsSetSpacing(fs, 5.0f);
	fonsSetBlur(fs, 10.0f);
	fonsDrawText(fs, dx,dy,"Blurry...",NULL);

	dy += 50.0f;

	fonsSetSize(fs, 18.0f);
	fonsSetFont(fs, fontBold);
	fonsSetColor(fs, black);
	fonsSetSpacing(fs, 0.0f);
	fonsSetBlur(fs, 3.0f);
	fonsDrawText(fs, dx,dy+2,"DROP THAT SHADOW",NULL);

	fonsSetColor(fs, white);
	fonsSetBlur(fs, 0);
	fonsDrawText(fs, dx,dy,"DROP THAT SHADOW",NULL);

	if (debug)
	    fonsDrawDebug(fs, 800.0, 50.0);


	glEnable(GL_DEPTH_TEST);


	// SDL pixel buffer expects BGRA data, not RGBA data - read accordingly
	glReadPixels(0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, screen->pixels);

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
		memcpy(rgba, screen->pixels + top, sizeof(rgba));
		memcpy(screen->pixels + top, screen->pixels + bottom, sizeof(rgba));
		memcpy(screen->pixels + bottom, rgba, sizeof(rgba));
	    }
	}

	if (SDL_MUSTLOCK(screen)) {
	    SDL_UnlockSurface(screen);
	}
	SDL_Flip(screen);

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
