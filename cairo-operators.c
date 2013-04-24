#include "cairo-operators.h"
#include <stdlib.h>
#include <string.h>

void
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

void
red(cairo_t *cr)
{
	cairo_rectangle(cr, 0., 0., .75, .75);
	cairo_set_source_rgba(cr, .7, 0., 0., .8);
	cairo_fill(cr);
}

void
blue(cairo_t *cr)
{
	cairo_rectangle(cr, .25, .25, .75, .75);
	cairo_set_source_rgba(cr, 0., 0., .9, .4);
	cairo_fill(cr);
}

void
draw_clear(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
	blue(cr);
}

void
draw_source(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	blue(cr);
}

void
draw_over(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
	blue(cr);
}

void
draw_in(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_IN);
	blue(cr);
}

void
draw_out(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_OUT);
	blue(cr);
}

void
draw_atop(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_ATOP);
	blue(cr);
}

void
draw_dest(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DEST);
	blue(cr);
}

void
draw_dest_over(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DEST_OVER);
	blue(cr);
}

void
draw_dest_in(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DEST_IN);
	blue(cr);
}

void
draw_dest_out(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DEST_OUT);
	blue(cr);
}

void
draw_dest_atop(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DEST_ATOP);
	blue(cr);
}

void
draw_xor(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_XOR);
	blue(cr);
}

void
draw_add(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_ADD);
	blue(cr);
}

void
draw_saturate(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_SATURATE);
	blue(cr);
}

void
draw_multiply(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_MULTIPLY);
	blue(cr);
}

void
draw_screen(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_SCREEN);
	blue(cr);
}

void
draw_overlay(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_OVERLAY);
	blue(cr);
}

void
draw_darken(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DARKEN);
	blue(cr);
}

void
draw_lighten(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_LIGHTEN);
	blue(cr);
}

void
draw_color_dodge(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_COLOR_DODGE);
	blue(cr);
}

void
draw_color_burn(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_COLOR_BURN);
	blue(cr);
}

void
draw_hard_light(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_HARD_LIGHT);
	blue(cr);
}

void
draw_soft_light(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_SOFT_LIGHT);
	blue(cr);
}

void
draw_difference(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_DIFFERENCE);
	blue(cr);
}

void
draw_exclusion(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_EXCLUSION);
	blue(cr);
}

void
draw_hsl_hue(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_HSL_HUE);
	blue(cr);
}

void
draw_hsl_saturation(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_HSL_SATURATION);
	blue(cr);
}

void
draw_hsl_color(cairo_t *cr, int width, int height)
{
	setup(cr, width, height);
	red(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_HSL_COLOR);
	blue(cr);
}

void
draw_hsl_luminosity(cairo_t *cr, int width, int height)
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
