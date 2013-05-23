#include "cairo-demo.h"
#include "cairo-draw.h"
#include <cairo-directfb.h>
#include <directfb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct _cairo_demo_t {
	IDirectFB *dfb;
	IDirectFBDisplayLayer *layer;
	IDirectFBWindow *window;
	IDirectFBEventBuffer *buffer;
	IDirectFBSurface *surface;
	int width, height;
	cairo_demo_draw_function_t draw;
	char *image;
	char *png;
};

#define directfb_error_message(err) \
	fprintf(stderr, "%s:%d - %s\n", __FILE__, __LINE__, \
		DirectFBErrorString(err));

#define cairo_error_message(err) \
	fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, \
		cairo_status_to_string(err));

cairo_demo_t *
cairo_demo_new(int argc, char **argv,
	       __attribute__ ((unused)) const char *name,
	       int width, int height)
{
	DFBResult err;
	cairo_demo_t *self = calloc(1, sizeof(*self));
	if (!self) {
		return NULL;
	}
	self->width = width;
	self->height = height;
	err = DirectFBInit(&argc, &argv);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	err = DirectFBCreate(&self->dfb);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	err = self->dfb->CreateInputEventBuffer(self->dfb,
			DICAPS_ALL, DFB_TRUE, &self->buffer);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	err = self->dfb->GetDisplayLayer(self->dfb, DLID_PRIMARY, &self->layer);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	err = self->layer->SetCooperativeLevel(self->layer,
			DLSCL_ADMINISTRATIVE);
	if (DFB_OK != err) {
		directfb_error_message(err);
	}
	err = self->layer->EnableCursor(self->layer, 1);
	if (DFB_OK != err) {
		directfb_error_message(err);
	}
	DFBWindowDescription win_dsc = {
		.flags = DWDESC_POSX | DWDESC_POSY
			| DWDESC_WIDTH | DWDESC_HEIGHT
			| DWDESC_CAPS | DWDESC_SURFACE_CAPS
			| DWDESC_STACKING,
		.posx = 600,
		.posy = 300,
		.width = width,
		.height = height,
		.caps = DWCAPS_ALPHACHANNEL,
		.surface_caps = DSCAPS_PREMULTIPLIED,
		.stacking = DWSC_UPPER,
	};
	err = self->layer->CreateWindow(self->layer, &win_dsc, &self->window);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	(void)self->window->SetOpacity(self->window, 0xff);
	err = self->window->GetSurface(self->window, &self->surface);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	self->draw = cairo_draw;
	return self;
error:
	cairo_demo_destroy(self);
	return NULL;
}

void
cairo_demo_destroy(cairo_demo_t *self)
{
	if (self) {
		if (self->surface) {
			self->surface->Release(self->surface);
		}
		if (self->buffer) {
			self->buffer->Release(self->buffer);
		}
		if (self->window) {
			self->window->Release(self->window);
		}
		if (self->layer) {
			self->layer->Release(self->layer);
		}
		if (self->dfb) {
			self->dfb->Release(self->dfb);
		}
		free(self->image);
		free(self->png);
		free(self);
	}
}

void
cairo_demo_set_draw_function(cairo_demo_t *self,
		cairo_demo_draw_function_t draw)
{
	self->draw = draw;
}

cairo_surface_t *
cairo_demo_get_image(cairo_demo_t *self)
{
	return cairo_image_surface_create_from_png(self->image);
}

void
cairo_demo_set_image(cairo_demo_t *self, const char *image)
{
	self->image = strdup(image);
}

void
cairo_demo_set_png(cairo_demo_t *self, const char *png)
{
	self->png = strdup(png);
}

int
cairo_demo_run(cairo_demo_t *self)
{
	cairo_t *cr = NULL;
	DFBInputEvent event;
	int status = EXIT_SUCCESS;
	cairo_surface_t *surface = NULL;
	surface = cairo_directfb_surface_create(self->dfb, self->surface);
	if (CAIRO_STATUS_SUCCESS != cairo_surface_status(surface)) {
		cairo_error_message(cairo_surface_status(surface));
		status = EXIT_FAILURE;
		goto exit;
	}
	cr = cairo_create(surface);
	self->draw(self, cr, self->width, self->height);
	self->surface->Flip(self->surface, NULL, DSFLIP_WAITFORSYNC);
	cairo_destroy(cr);
	while (true) {
		(void)self->buffer->WaitForEvent(self->buffer);
		while (DFB_OK == self->buffer->GetEvent(self->buffer,
					DFB_EVENT(&event))) {
			switch (event.type) {
			case DIET_KEYPRESS:
				switch (event.key_id) {
				case DIKI_RIGHT:
					self->window->Move(self->window,
							10, 0);
					break;
				case DIKI_LEFT:
					self->window->Move(self->window,
							-10, 0);
					break;
				case DIKI_UP:
					self->window->Move(self->window,
							0, -10);
					break;
				case DIKI_DOWN:
					self->window->Move(self->window,
							0, 10);
					break;
				case DIKI_Q:
					goto exit;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		cr = cairo_create(surface);
		self->draw(self, cr, self->width, self->height);
		self->surface->Flip(self->surface, NULL, DSFLIP_WAITFORSYNC);
		cairo_destroy(cr);
	}
exit:
	if (self->png) {
		cairo_surface_write_to_png(surface, self->png);
	}
	cairo_surface_destroy(surface);
	cairo_demo_destroy(self);
	return status;
}

cairo_surface_t *
cairo_demo_create_surface(cairo_demo_t *self, int width, int height)
{
	cairo_surface_t *surface;
	IDirectFBSurface *dfb_surface = NULL;
	DFBSurfaceDescription dsc = {
		.flags = DSDESC_WIDTH | DSDESC_HEIGHT |
			DSDESC_CAPS | DSDESC_PIXELFORMAT,
		.width = width,
		.height = height,
		.caps = DSCAPS_PREMULTIPLIED,
		.pixelformat = DSPF_ARGB
	};
	(void)self->dfb->CreateSurface(self->dfb, &dsc, &dfb_surface);
	surface = cairo_directfb_surface_create(self->dfb, dfb_surface);
	if (dfb_surface) {
		(void)dfb_surface->Release(dfb_surface);
	}
	return surface;
}
