#include <stdio.h>
#include <TGL/gl.h>
//#include <tgl.h>
#include "svpng.h"

#define RGB_TO_PIXEL(r,g,b) ( (((r) << 8) & 0xff0000) | ((g) & 0xff00) | ((b) >> 8) )

int main(int argc, char **argv)
{

    unsigned long p;
    unsigned int r = 255;
    unsigned int g = 0;
    unsigned int b = 0;
    unsigned int a = 255;
    p = (r << 24) | (g << 16) | (b << 8) | 255;
    r = p >> 24 & 0xFF;
    g = p >> 16 & 0xFF;
    b = p >> 8 & 0xFF;
    a = p & 0xFF;

    printf("%ld: %d, %d, %d, %d\n", p, r, g, b, a);
#if 0
	// Doesn't work just feeding in screen->pixels... generates invalid pngs
	char fname[20000];
	sprintf(fname, "frame%.5d.png", frames);
	FILE *fp = fopen(fname, "wb");
	svpng(fp, winSizeX, winSizeY, screen->pixels, 1);
#endif
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
