#include "cairo-operators.h"
#include <stdlib.h>
#include <string.h>

static void
setup(cairo_t *cr, int width, int height)
{
	cairo_scale(cr, width, height);
	cairo_rectangle(cr, 0., 0., 1., 1.);
	cairo_clip(cr);
	cairo_save(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
	cairo_paint(cr);
	cairo_restore(cr);
}

static void
red(cairo_t *cr)
{
	cairo_rectangle(cr, 0., 0., .75, .75);
	cairo_set_source_rgba(cr, .7, 0., 0., .8);
	cairo_fill(cr);
}

static void
blue(cairo_t *cr)
{
	cairo_rectangle(cr, .25, .25, .75, .75);
	cairo_set_source_rgba(cr, 0., 0., .9, .4);
	cairo_fill(cr);
}

static void
draw_clear(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	   int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
	blue(cr);
}

static void
draw_source(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	    int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	blue(cr);
}

static void
draw_over(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	  int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
	blue(cr);
}

static void
draw_in(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_IN);
	blue(cr);
}

static void
draw_out(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	 int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_OUT);
	blue(cr);
}

static void
draw_atop(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	  int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_ATOP);
	blue(cr);
}

static void
draw_dest(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	  int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DEST);
	blue(cr);
}

static void
draw_dest_over(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	       int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DEST_OVER);
	blue(cr);
}

static void
draw_dest_in(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	     int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DEST_IN);
	blue(cr);
}

static void
draw_dest_out(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	      int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DEST_OUT);
	blue(cr);
}

static void
draw_dest_atop(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	       int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DEST_ATOP);
	blue(cr);
}

static void
draw_xor(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	 int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_XOR);
	blue(cr);
}

static void
draw_add(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	 int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_ADD);
	blue(cr);
}

static void
draw_saturate(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	      int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_SATURATE);
	blue(cr);
}

static void
draw_multiply(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	      int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_MULTIPLY);
	blue(cr);
}

static void
draw_screen(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	    int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_SCREEN);
	blue(cr);
}

static void
draw_overlay(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	     int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_OVERLAY);
	blue(cr);
}

static void
draw_darken(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	    int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DARKEN);
	blue(cr);
}

static void
draw_lighten(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	     int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_LIGHTEN);
	blue(cr);
}

static void
draw_color_dodge(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
		 int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_COLOR_DODGE);
	blue(cr);
}

static void
draw_color_burn(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
		int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_COLOR_BURN);
	blue(cr);
}

static void
draw_hard_light(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
		int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_HARD_LIGHT);
	blue(cr);
}

static void
draw_soft_light(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
		int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_SOFT_LIGHT);
	blue(cr);
}

static void
draw_difference(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
		int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DIFFERENCE);
	blue(cr);
}

static void
draw_exclusion(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	       int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_EXCLUSION);
	blue(cr);
}

static void
draw_hsl_hue(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	     int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_HSL_HUE);
	blue(cr);
}

static void
draw_hsl_saturation(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
		    int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_HSL_SATURATION);
	blue(cr);
}

static void
draw_hsl_color(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
	       int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_HSL_COLOR);
	blue(cr);
}

static void
draw_hsl_luminosity(__attribute__((unused)) cairo_demo_t *self, cairo_t *cr,
		    int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_HSL_LUMINOSITY);
	blue(cr);
}

cairo_demo_draw_function_t
cairo_operators_get_function(const char *op)
{
	if (0 == strcmp(op, "clear")) {
		return draw_clear;
	} else if (0 == strcmp(op, "source")) {
		return draw_source;
	} else if (0 == strcmp(op, "over")) {
		return draw_over;
	} else if (0 == strcmp(op, "in")) {
		return draw_in;
	} else if (0 == strcmp(op, "out")) {
		return draw_out;
	} else if (0 == strcmp(op, "atop")) {
		return draw_atop;
	} else if (0 == strcmp(op, "dest")) {
		return draw_dest;
	} else if (0 == strcmp(op, "dest_over")) {
		return draw_dest_over;
	} else if (0 == strcmp(op, "dest_in")) {
		return draw_dest_in;
	} else if (0 == strcmp(op, "dest_out")) {
		return draw_dest_out;
	} else if (0 == strcmp(op, "dest_atop")) {
		return draw_dest_atop;
	} else if (0 == strcmp(op, "xor")) {
		return draw_xor;
	} else if (0 == strcmp(op, "add")) {
		return draw_add;
	} else if (0 == strcmp(op, "saturate")) {
		return draw_saturate;
	} else if (0 == strcmp(op, "multiply")) {
		return draw_multiply;
	} else if (0 == strcmp(op, "screen")) {
		return draw_screen;
	} else if (0 == strcmp(op, "overlay")) {
		return draw_overlay;
	} else if (0 == strcmp(op, "darken")) {
		return draw_darken;
	} else if (0 == strcmp(op, "lighten")) {
		return draw_lighten;
	} else if (0 == strcmp(op, "color_dodge")) {
		return draw_color_dodge;
	} else if (0 == strcmp(op, "color_burn")) {
		return draw_color_burn;
	} else if (0 == strcmp(op, "hard_light")) {
		return draw_hard_light;
	} else if (0 == strcmp(op, "soft_light")) {
		return draw_soft_light;
	} else if (0 == strcmp(op, "difference")) {
		return draw_difference;
	} else if (0 == strcmp(op, "exclusion")) {
		return draw_exclusion;
	} else if (0 == strcmp(op, "hsl_hue")) {
		return draw_hsl_hue;
	} else if (0 == strcmp(op, "hsl_saturation")) {
		return draw_hsl_saturation;
	} else if (0 == strcmp(op, "hsl_color")) {
		return draw_hsl_color;
	} else if (0 == strcmp(op, "hsl_luminosity")) {
		return draw_hsl_luminosity;
	}
	return NULL;
}
