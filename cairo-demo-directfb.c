#include "cairo-demo.h"
#include "cairo-draw.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _cairo_demo_t {
	cairo_surface_t *surface;
	cairo_t *cr;
	int width, height;
	cairo_demo_draw_function_t draw;
	char *png;
};

cairo_demo_t *
cairo_demo_new(__attribute__ ((unused)) const char *name, int width, int height)
{
	cairo_demo_t *self = calloc(1, sizeof(*self));
	if (!self) {
		return NULL;
	}
	self->width = width;
	self->height = height;
#if 0
	self->surface = cairo_directfb_surface_create(self->dfb, self->surface);
	status = cairo_surface_status(self->surface);
	if (CAIRO_STATUS_SUCCESS != status) {
		fprintf(stderr, "demo: %s\n", cairo_status_to_string(status));
		goto error;
	}
	self->cr = cairo_create(self->surface);
	status = cairo_status(self->cr);
	if (CAIRO_STATUS_SUCCESS != status) {
		fprintf(stderr, "demo: %s\n", cairo_status_to_string(status));
		goto error;
	}
#endif
	self->draw = cairo_draw;
	return self;
#if 0
error:
	cairo_demo_destroy(self);
	return NULL;
#endif
}

void
cairo_demo_destroy(cairo_demo_t *self)
{
	if (self) {
		if (self->surface) {
			if (self->cr) {
				cairo_destroy(self->cr);
			}
			cairo_surface_destroy(self->surface);
		}
		if (self->png) {
			free(self->png);
		}
		free(self);
	}
}

void
cairo_demo_set_draw_function(cairo_demo_t *self,
		cairo_demo_draw_function_t draw)
{
	self->draw = draw;
}

void
cairo_demo_set_png(cairo_demo_t *self, const char *png)
{
	self->png = strdup(png);
}

int
cairo_demo_run(cairo_demo_t *self)
{
	int status = EXIT_SUCCESS;
	while (true) {
	}
#if 0
exit:
#endif
	if (self->png) {
		cairo_surface_write_to_png(self->surface, self->png);
	}
	cairo_demo_destroy(self);
	return status;
}
