#ifndef CAIRO_DEMO_H
#define CAIRO_DEMO_H

#include <cairo.h>

typedef struct _cairo_demo_t cairo_demo_t;

typedef void (*cairo_demo_draw_function_t)(cairo_t *cr, int width, int height);

cairo_demo_t *
cairo_demo_new(const char *name, int width, int height);

void
cairo_demo_destroy(cairo_demo_t *self);

void
cairo_demo_set_draw_function(cairo_demo_t *self,
		cairo_demo_draw_function_t draw);

int
cairo_demo_run(cairo_demo_t *self);

#endif /* CAIRO_DEMO_H */
