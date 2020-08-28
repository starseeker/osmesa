/*

 * Z buffer: 16 bits Z / 16 bits color
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "zbuffer.h"

ZBuffer *ZB_open(int xsize, int ysize, int mode,
		 int nb_colors,
		 unsigned char *color_indexes,
		 int *color_table,
		 void *frame_buffer)
{
    ZBuffer *zb;
    int size;

    zb = gl_malloc(sizeof(ZBuffer));
    if (zb == NULL)
	return NULL;

    zb->xsize = xsize;
    zb->ysize = ysize;
    zb->mode = mode;
    zb->linesize = (xsize * PSZB + 3) & ~3;

    switch (mode) {
#ifdef TGL_FEATURE_32_BITS
    case ZB_MODE_RGBA:
#endif
    case ZB_MODE_5R6G5B:
	zb->nb_colors = 0;
	break;
    default:
	goto error;
    }

    size = zb->xsize * zb->ysize * sizeof(unsigned short);

    zb->zbuf = gl_malloc(size);
    if (zb->zbuf == NULL)
	goto error;

    if (frame_buffer == NULL) {
	zb->pbuf = gl_malloc(zb->ysize * zb->linesize);
	if (zb->pbuf == NULL) {
	    gl_free(zb->zbuf);
	    goto error;
	}
	zb->frame_buffer_allocated = 1;
    } else {
	zb->frame_buffer_allocated = 0;
	zb->pbuf = frame_buffer;
    }

    zb->current_texture = NULL;

    return zb;
  error:
    gl_free(zb);
    return NULL;
}

void ZB_close(ZBuffer * zb)
{

    if (zb->frame_buffer_allocated)
	gl_free(zb->pbuf);

    gl_free(zb->zbuf);
    gl_free(zb);
}

void ZB_resize(ZBuffer * zb, void *frame_buffer, int xsize, int ysize)
{
    int size;

    /* xsize must be a multiple of 4 */
    xsize = xsize & ~3;

    zb->xsize = xsize;
    zb->ysize = ysize;
    zb->linesize = (xsize * PSZB + 3) & ~3;

    size = zb->xsize * zb->ysize * sizeof(unsigned short);

    gl_free(zb->zbuf);
    zb->zbuf = gl_malloc(size);

    if (zb->frame_buffer_allocated)
	gl_free(zb->pbuf);

    if (frame_buffer == NULL) {
	zb->pbuf = gl_malloc(zb->ysize * zb->linesize);
	zb->frame_buffer_allocated = 1;
    } else {
	zb->pbuf = frame_buffer;
	zb->frame_buffer_allocated = 0;
    }
}

static void ZB_copyBuffer(ZBuffer * zb,
                          void *buf,
                          int linesize)
{
    unsigned char *p1;
    PIXEL *q;
    int y, n;

    q = zb->pbuf;
    p1 = buf;
    n = zb->xsize * PSZB;
    for (y = 0; y < zb->ysize; y++) {
	memcpy(p1, q, n);
	p1 += linesize;
	q = (PIXEL *) ((char *) q + zb->linesize);
    }
}

void ZB_copyFrameBuffer(ZBuffer * zb, void *buf,
			int linesize)
{
    switch (zb->mode) {
#ifdef TGL_FEATURE_32_BITS
    case ZB_MODE_RGBA:
	ZB_copyBuffer(zb, buf, linesize);
	break;
#endif
    default:
	assert(0);
    }
}

/*
 * adr must be aligned on an 'int'
 */
void memset_s(void *adr, int val, int count)
{
    int i, n, v;
    unsigned int *p;
    unsigned short *q;

    p = adr;
    v = val | (val << 16);

    n = count >> 3;
    for (i = 0; i < n; i++) {
	p[0] = v;
	p[1] = v;
	p[2] = v;
	p[3] = v;
	p += 4;
    }

    q = (unsigned short *) p;
    n = count & 7;
    for (i = 0; i < n; i++)
	*q++ = val;
}

void memset_l(void *adr, int val, int count)
{
    int i, n, v;
    unsigned int *p;

    p = adr;
    v = val;
    n = count >> 2;
    for (i = 0; i < n; i++) {
	p[0] = v;
	p[1] = v;
	p[2] = v;
	p[3] = v;
	p += 4;
    }

    n = count & 3;
    for (i = 0; i < n; i++)
	*p++ = val;
}

/* count must be a multiple of 4 and >= 4 */
void memset_RGB24(void *adr,int r, int v, int b,long count)
{
    long i, n;
    register long v1,v2,v3,*pt=(long *)(adr);
    unsigned char *p,R=(unsigned char)r,V=(unsigned char)v,B=(unsigned char)b;

    p=(unsigned char *)adr;
    *p++=R;
    *p++=V;
    *p++=B;
    *p++=R;
    *p++=V;
    *p++=B;
    *p++=R;
    *p++=V;
    *p++=B;
    *p++=R;
    *p++=V;
    *p++=B;
    v1=*pt++;
    v2=*pt++;
    v3=*pt++;
    n = count >> 2;
    for(i=1;i<n;i++) {
        *pt++=v1;
        *pt++=v2;
        *pt++=v3;
    }
}

void ZB_clear(ZBuffer * zb, int clear_z, int z,
	      int clear_color, int r, int g, int b)
{
    int color;
    int y;
    PIXEL *pp;

    if (clear_z) {
	memset_s(zb->zbuf, z, zb->xsize * zb->ysize);
    }
    if (clear_color) {
	pp = zb->pbuf;
	for (y = 0; y < zb->ysize; y++) {
            color = RGB_TO_PIXEL(r, g, b);
	    memset_l(pp, color, zb->xsize);
	    pp = (PIXEL *) ((char *) pp + zb->linesize);
	}
    }
}
