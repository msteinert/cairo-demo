#include <cairo.h>

/**
 * \brief Draw on a window.
 *
 * \param cr A cairo context to draw with.
 * \param width The width of the window.
 * \param height The height of the window.
 */
void
draw(cairo_t *cr, int width, int height)
{
	cairo_set_source_rgb(cr, 0., 0., 1.);
	cairo_paint(cr);
}
