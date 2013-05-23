#include "cairo-demo.h"
#include <cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

__attribute__((unused))
static void
draw_1(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
       int width, int height)
{
	/* set the drawing scale */
	cairo_scale(cr, width, height);
	cairo_rectangle(cr, 0., 0., 1., 1.);
	cairo_clip(cr);
	/* draw the black 'X' */
	cairo_set_source_rgb(cr, 0., 0., 0.);
	cairo_move_to(cr, 0., 0.);
	cairo_line_to(cr, 1., 1.);
	cairo_move_to(cr, 1., 0.);
	cairo_line_to(cr, 0., 1.);
	cairo_set_line_width(cr, .2);
	cairo_stroke(cr);
	/* draw the red box */
	cairo_rectangle(cr, 0., 0., .5, .5);
	cairo_set_source_rgba(cr, 1., 0., 0., .8);
	cairo_fill(cr);
	/* draw the green box */
	cairo_rectangle(cr, 0., .5, .5, .5);
	cairo_set_source_rgba(cr, 0., 1., 0., .6);
	cairo_fill(cr);
	/* draw the blue box */
	cairo_rectangle(cr, .5, 0., .5, .5);
	cairo_set_source_rgba(cr, 0., 0., 1., .4);
	cairo_fill(cr);
}

__attribute__((unused))
static void
draw_2(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
       int width, int height)
{
	cairo_pattern_t *radial, *linear;
	int i, j;
	/* set the drawing scale */
	cairo_scale(cr, width, height);
	cairo_rectangle(cr, 0., 0., 1., 1.);
	cairo_clip(cr);
	/* draw the radial pattern */
	radial = cairo_pattern_create_radial(.25, .25, .1, .5, .5, .5);
	cairo_pattern_add_color_stop_rgb(radial, 0., 1., .8, .8);
	cairo_pattern_add_color_stop_rgb(radial, 1., .9, 0., 0.);
	for (i = 1; i < 10; ++i) {
		for (j = 1; j < 10; ++j) {
			cairo_rectangle(cr, i / 10. - .04, j / 10. - .04,
					.08, .08);
		}
	}
	cairo_set_source(cr, radial);
	cairo_fill(cr);
	/* draw the linear pattern */
	linear = cairo_pattern_create_linear(.25, .35, .75, .65);
	cairo_pattern_add_color_stop_rgba(linear, 0., 1., 1., 1., 0.);
	cairo_pattern_add_color_stop_rgba(linear, .25, 0., 1., 0., .5);
	cairo_pattern_add_color_stop_rgba(linear, .5, 1., 1., 1., 0.);
	cairo_pattern_add_color_stop_rgba(linear, .75, 0., 0., 1., .5);
	cairo_pattern_add_color_stop_rgba(linear, 1., 1., 1., 1., 0.);
	cairo_rectangle(cr, 0., 0., 1., 1.);
	cairo_set_source(cr, linear);
	cairo_fill(cr);
}

__attribute__((unused))
static void
draw_3(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
       int width, int height)
{
	double x, y, px, ux = 1., uy = 1., dashlength;
	cairo_font_extents_t fe;
	cairo_text_extents_t te;
	char text[] = "joy";
	/* set the drawing scale */
	cairo_scale(cr, width, height);
	cairo_rectangle(cr, 0., 0., 1., 1.);
	cairo_clip(cr);
	cairo_set_font_size(cr, .5);
	cairo_set_source_rgb(cr, 0., 0., 0.);
	cairo_select_font_face(cr, "DejaVu Sans", CAIRO_FONT_SLANT_NORMAL,
			CAIRO_FONT_WEIGHT_NORMAL);
	cairo_font_extents(cr, &fe);
	cairo_device_to_user_distance(cr, &ux, &uy);
	if (ux > uy) {
		px = ux;
	} else {
		px = uy;
	}
	cairo_font_extents(cr, &fe);
	cairo_text_extents(cr, text, &te);
	x = .5 - te.x_bearing - te.width / 2.;
	y = .5 - fe.descent + fe.height / 2.;
	/* baseline, descent, ascent, height */
	cairo_set_line_width(cr, 4 * px);
	dashlength = 9 * px;
	cairo_set_dash(cr, &dashlength, 1, 0.);
	cairo_set_source_rgba(cr, 0., 0.6, 0., .5);
	cairo_move_to(cr, x + te.x_bearing, y);
	cairo_rel_line_to(cr, te.width, 0.);
	cairo_move_to(cr, x + te.x_bearing, y + fe.descent);
	cairo_rel_line_to(cr, te.width, 0.);
	cairo_move_to(cr, x + te.x_bearing, y - fe.ascent);
	cairo_rel_line_to(cr, te.width, 0.);
	cairo_move_to(cr, x + te.x_bearing, y - fe.height);
	cairo_rel_line_to(cr, te.width, 0.);
	cairo_stroke(cr);
	/* extents: width & height */
	cairo_set_source_rgba(cr, 0., 0., .75, .5);
	cairo_set_line_width(cr, px);
	dashlength = 3 * px;
	cairo_set_dash(cr, &dashlength, 1, 0.);
	cairo_rectangle(cr, x + te.x_bearing, y + te.y_bearing, te.width,
			te.height);
	cairo_stroke(cr);
	/* text */
	cairo_move_to(cr, x, y);
	cairo_set_source_rgb(cr, 0., 0., 0.);
	cairo_show_text(cr, text);
	/* bearing */
	cairo_set_dash(cr, NULL, 0, 0.);
	cairo_set_line_width(cr, 2. * px);
	cairo_set_source_rgba(cr, 0., 0., .75, .5);
	cairo_move_to(cr, x, y);
	cairo_rel_line_to(cr, te.x_bearing, te.y_bearing);
	cairo_stroke(cr);
	/* text's advance */
	cairo_set_source_rgba(cr, 0., 0., .75, .5);
	cairo_arc(cr, x + te.x_advance, y + te.y_advance, 5. * px, 0.,
			2. * M_PI);
	cairo_fill(cr);
	/* reference point */
	cairo_arc(cr, x, y, 5. * px, 0., 2. * M_PI);
	cairo_set_source_rgba(cr, .75, 0., 0., .5);
	cairo_fill(cr);
}

__attribute__((unused))
static void
draw_4(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
       int width, int height)
{
	cairo_pattern_t *linpat, *radpat;
	/* set the drawing scale */
	cairo_scale(cr, width, height);
	cairo_rectangle(cr, 0., 0., 1., 1.);
	cairo_clip(cr);
	linpat = cairo_pattern_create_linear(0, 0, 1, 1);
	cairo_pattern_add_color_stop_rgb(linpat, 0, 0, 0.3, 0.8);
	cairo_pattern_add_color_stop_rgb(linpat, 1, 0, 0.8, 0.3);
	radpat = cairo_pattern_create_radial(0.5, 0.5, 0.25, 0.5, 0.5, 0.75);
	cairo_pattern_add_color_stop_rgba(radpat, 0, 0, 0, 0, 1);
	cairo_pattern_add_color_stop_rgba(radpat, 0.5, 0, 0, 0, 0);
	cairo_set_source(cr, linpat);
	cairo_mask(cr, radpat);
	cairo_pattern_destroy(linpat);
	cairo_pattern_destroy(radpat);
}

__attribute__((unused))
static void
draw_5(cairo_demo_t *self, cairo_t *cr,
       int width, int height)
{
	cairo_t *native_cr = NULL;
	cairo_pattern_t *pattern = NULL;
	int image_width, image_height;
	/* load a background image */
	cairo_surface_t *image, *native, *mask;
	/* create a native mask surface */
	image = cairo_image_surface_create_from_png("mask.png");
	mask = cairo_demo_create_surface(self, width, height);
	native_cr = cairo_create(mask);
	cairo_set_source_surface(native_cr, image, 0, 0);
	cairo_paint(native_cr);
	cairo_destroy(native_cr);
	cairo_surface_destroy(image);
	/* create a native image surface */
	image = cairo_demo_get_image(self);
	image_width = cairo_image_surface_get_width(image);
	image_height = cairo_image_surface_get_height(image);
	native = cairo_demo_create_surface(self, image_width, image_height);
	native_cr = cairo_create(native);
	cairo_set_source_surface(native_cr, image, 0, 0);
	cairo_paint(native_cr);
	cairo_destroy(native_cr);
	cairo_surface_destroy(image);
	/* copy/scale the native image surface */
	cairo_scale(cr,
		    (double)width / image_width,
		    (double)height / image_height);
	/* src:surface mask:solid */
	/*
	pattern = cairo_pattern_create_rgba(0.0, 0.0, 0.0, 0.5);
	cairo_set_source_surface(cr, native, 0, 0);
	cairo_mask(cr, pattern);
	*/
	/* src:solid mask:surface */
	/*
	cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 0.5);
	cairo_mask_surface(cr, native, 0, 0);
	*/
	/* src:surface mask:surface */
	cairo_set_source_surface(cr, native, 0, 0);
	cairo_mask_surface(cr, mask, 0, 0);
	/* clean up */
	cairo_pattern_destroy(pattern);
	cairo_surface_destroy(native);
	cairo_surface_destroy(mask);
}

void
cairo_draw(cairo_demo_t *self, cairo_t *cr, int width, int height)
{
	cairo_set_source_rgb(cr, 1., 1., 1.);
	cairo_paint(cr);
	//draw_1(self, cr, width, height);
	//draw_2(self, cr, width, height);
	draw_3(self, cr, width, height);
	//draw_4(self, cr, width, height);
	//draw_5(self, cr, width, height);
}
