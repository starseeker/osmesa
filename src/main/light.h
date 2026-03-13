/**
 * \file light.h
 * Lighting.
 */

/*
 * Mesa 3-D graphics library
 * Version:  3.5
 *
 * Copyright (C) 1999-2001  Brian Paul   All Rights Reserved.
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
 */


#ifndef LIGHT_H
#define LIGHT_H


#include "mtypes.h"

extern void GLAPIENTRY
_mesa_ShadeModel(ctx, GLcontext *ctx, GLenum mode);

#if _HAVE_FULL_GL
extern void GLAPIENTRY
_mesa_ColorMaterial(ctx, GLcontext *ctx, GLenum face, GLenum mode);

extern void GLAPIENTRY
_mesa_Lightf(GLenum light, GLenum pname, GLfloat param);

extern void GLAPIENTRY
_mesa_Lightfv(ctx, GLcontext *ctx, GLenum light, GLenum pname, const GLfloat *params);

extern void GLAPIENTRY
_mesa_Lightiv(GLenum light, GLenum pname, const GLint *params);

extern void GLAPIENTRY
_mesa_Lighti(GLenum light, GLenum pname, GLint param);

extern void GLAPIENTRY
_mesa_LightModelf(GLenum pname, GLfloat param);

extern void GLAPIENTRY
_mesa_LightModelfv(ctx, GLcontext *ctx, GLenum pname, const GLfloat *params);

extern void GLAPIENTRY
_mesa_LightModeli(GLenum pname, GLint param);

extern void GLAPIENTRY
_mesa_LightModeliv(GLenum pname, const GLint *params);

extern void GLAPIENTRY
_mesa_GetLightfv(ctx, GLcontext *ctx, GLenum light, GLenum pname, GLfloat *params);

extern void GLAPIENTRY
_mesa_GetLightiv(ctx, GLcontext *ctx, GLenum light, GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetMaterialfv(ctx, GLcontext *ctx, GLenum face, GLenum pname, GLfloat *params);

extern void GLAPIENTRY
_mesa_GetMaterialiv(ctx, GLcontext *ctx, GLenum face, GLenum pname, GLint *params);


extern void
_mesa_light(ctx, GLcontext *ctx, GLuint lnum, GLenum pname, const GLfloat *params);


/* Lerp between adjacent values in the f(x) lookup table, giving a
 * continuous function, with adequeate overall accuracy.  (Though
 * still pretty good compared to a straight lookup).
 * Result should be a GLfloat.
 */
#define GET_SHINE_TAB_ENTRY( table, dp, result )			\
do {									\
   struct gl_shine_tab *_tab = table;					\
   float f = (dp * (SHINE_TABLE_SIZE-1));				\
   int k = (int) f;							\
   if (k < 0 /* gcc may cast an overflow float value to negative int value*/ \
	|| k > SHINE_TABLE_SIZE-2)					\
      result = (GLfloat) pow( dp, _tab->shininess );		\
   else									\
      result = _tab->tab[k] + (f-k)*(_tab->tab[k+1]-_tab->tab[k]);	\
} while (0)


extern GLuint _mesa_material_bitmask(ctx, GLcontext *ctx,
				     GLenum face, GLenum pname,
				     GLuint legal,
				     const char *);

extern void _mesa_invalidate_spot_exp_table(struct gl_light *l);

extern void _mesa_invalidate_shine_table(ctx, GLcontext *ctx, GLuint i);

extern void _mesa_validate_all_lighting_tables(ctx, GLcontext *ctx);

extern void _mesa_update_lighting(ctx, GLcontext *ctx);

extern void _mesa_update_tnl_spaces(ctx, GLcontext *ctx, GLuint new_state);

extern void _mesa_update_material(ctx, GLcontext *ctx,
				  GLuint bitmask);

extern void _mesa_copy_materials(struct gl_material *dst,
				 const struct gl_material *src,
				 GLuint bitmask);

extern void _mesa_update_color_material(ctx, GLcontext *ctx,
					const GLfloat rgba[4]);

extern void _mesa_init_lighting(ctx, GLcontext *ctx);

extern void _mesa_free_lighting_data(ctx, GLcontext *ctx);

extern void _mesa_allow_light_in_model(ctx, GLcontext *ctx, GLboolean flag);

#else
#define _mesa_update_color_material(ctx, c, r) ((void)0)
#define _mesa_validate_all_lighting_tables(ctx, c) ((void)0)
#define _mesa_invalidate_spot_exp_table( l ) ((void)0)
#define _mesa_material_bitmask(ctx, c, f, p, l, s) 0
#define _mesa_init_lighting(ctx, c) ((void)0)
#define _mesa_free_lighting_data(ctx, c) ((void)0)
#define _mesa_update_lighting(ctx, c) ((void)0)
#define _mesa_update_tnl_spaces(ctx, c, n) ((void)0)
#define GET_SHINE_TAB_ENTRY( table, dp, result )  ((result)=0)
#endif

#endif

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
