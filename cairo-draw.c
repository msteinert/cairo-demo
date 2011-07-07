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
	/* set the drawing scale */
	cairo_scale(cr, width, height);
	/* draw the black 'X' */
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_move_to(cr, 0, 0);
	cairo_line_to(cr, 1, 1);
	cairo_move_to(cr, 1, 0);
	cairo_line_to(cr, 0, 1);
	cairo_set_line_width(cr, 0.2);
	cairo_stroke(cr);
	/* draw the red box */
	cairo_rectangle(cr, 0, 0, 0.5, 0.5);
	cairo_set_source_rgba(cr, 1, 0, 0, 0.80);
	cairo_fill(cr);
	/* draw the green box */
	cairo_rectangle(cr, 0, 0.5, 0.5, 0.5);
	cairo_set_source_rgba(cr, 0, 1, 0, 0.60);
	cairo_fill(cr);
	/* draw the blue box */
	cairo_rectangle(cr, 0.5, 0, 0.5, 0.5);
	cairo_set_source_rgba(cr, 0, 0, 1, 0.40);
	cairo_fill(cr);
}
