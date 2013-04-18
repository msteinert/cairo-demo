#include "cairo-demo.h"
#include "cairo-draw.h"
#include <cairo-directfb.h>
#include <directfb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _cairo_demo_t {
	IDirectFB *dfb;
	IDirectFBEventBuffer *buffer;
	IDirectFBDisplayLayer *layer;
	IDirectFBWindow *window;
	IDirectFBSurface *window_surface;
	cairo_surface_t *surface;
	cairo_t *cr;
	int width, height;
	cairo_demo_draw_function_t draw;
	char *png;
};

#define directfb_error_message(err) \
	fprintf(stderr, "%s:%d - %s\n", __FILE__, __LINE__, \
		DirectFBErrorString(err));

#define cairo_error_message(err) \
	fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, \
		cairo_status_to_string(status));

cairo_demo_t *
cairo_demo_new(int argc, char **argv,
	       __attribute__ ((unused)) const char *name,
	       int width, int height)
{
	DFBResult err;
	cairo_status_t status;
	cairo_demo_t *self = calloc(1, sizeof(*self));
	if (!self) {
		return NULL;
	}
	self->width = width;
	self->height = height;
	// Initialize DirectFB
	err = DirectFBInit(&argc, &argv);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	// Get the DirectFB handle
	err = DirectFBCreate(&self->dfb);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	// Get an input buffer
	err = self->dfb->CreateInputEventBuffer(self->dfb, DICAPS_KEYS,
			DFB_FALSE, &self->buffer);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	// Get the primary layer
	err = self->dfb->GetDisplayLayer(self->dfb, DLID_PRIMARY, &self->layer);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	err = self->layer->SetCooperativeLevel(self->layer,
			DLSCL_ADMINISTRATIVE);
	if (DFB_OK == err) {
		self->layer->SetBackgroundMode(self->layer, DLBM_COLOR);
	}
	err = self->layer->EnableCursor(self->layer, DFB_FALSE);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	err = self->layer->SetCursorOpacity(self->layer, 0);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	err = self->layer->SetBackgroundColor(self->layer, 0, 0, 0, 0);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	// Create a window
	DFBWindowDescription dsc;
	dsc.flags = DWDESC_POSX | DWDESC_POSY
		| DWDESC_WIDTH | DWDESC_HEIGHT
		| DWDESC_CAPS;
        dsc.posx = 0;
        dsc.posy = 0;
        dsc.width = self->width;
        dsc.height = self->height;
        dsc.caps = DWCAPS_ALPHACHANNEL;
	err = self->layer->CreateWindow(self->layer, &dsc, &self->window);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	err = self->window->SetOpacity(self->window, 0xff);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	// Get the window surface
	err = self->window->GetSurface(self->window, &self->window_surface);
	if (DFB_OK != err) {
		directfb_error_message(err);
		goto error;
	}
	self->surface = cairo_directfb_surface_create(self->dfb,
			self->window_surface);
	status = cairo_surface_status(self->surface);
	if (CAIRO_STATUS_SUCCESS != status) {
		cairo_error_message(status);
		goto error;
	}
	self->cr = cairo_create(self->surface);
	status = cairo_status(self->cr);
	if (CAIRO_STATUS_SUCCESS != status) {
		cairo_error_message(status);
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
		if (self->cr) {
			cairo_destroy(self->cr);
		}
		if (self->surface) {
			cairo_surface_destroy(self->surface);
		}
		if (self->window_surface) {
			self->window_surface->Release(self->window_surface);
		}
		if (self->window) {
			self->window->Release(self->window);
		}
		if (self->layer) {
			self->layer->Release(self->layer);
		}
		if (self->buffer) {
			self->buffer->Release(self->buffer);
		}
		if (self->dfb) {
			self->dfb->Release(self->dfb);
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
	self->draw(self->cr, self->width, self->height);
	self->window_surface->Flip(self->window_surface, NULL, 0);
	while (self->buffer->WaitForEvent(self->buffer) == DFB_OK) {
		DFBEvent event;
		while (self->buffer->GetEvent(self->buffer, &event) == DFB_OK) {
			switch (event.clazz) {
			case DFEC_INPUT:
			      break;
			default:
			      break;
			}
		}
	}
	if (self->png) {
		cairo_surface_write_to_png(self->surface, self->png);
	}
	cairo_demo_destroy(self);
	return status;
}
