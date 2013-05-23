#ifndef CAIRO_DRAW_H
#define CAIRO_DRAW_H

#include <cairo.h>
#include "cairo-demo.h"

/**
 * \brief Draw on a window.
 *
 * \param self A cairo-demo object
 * \param cr A cairo context to draw with
 * \param width The width of the window
 * \param height The height of the window
 */
void
cairo_draw(cairo_demo_t *self, cairo_t *cr, int width, int height);

#endif /* CAIRO_DRAW_H */
