#include "cairo-demo.h"
#include "cairo-draw.h"
#include "cairo-events.h"
#include <cairo-xlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

struct _cairo_demo_t {
	Display *display;
	Window window;
	cairo_surface_t *surface;
	cairo_t *cr;
	Atom wm_delete_window;
	int width, height;
	cairo_demo_draw_function_t draw;
	char *png;
};

cairo_demo_t *
cairo_demo_new(const char *name, int width, int height)
{
	int n;
	long mask;
	Atom utf8_string;
	cairo_status_t status;
	XSetWindowAttributes attr;
	cairo_demo_t *self = calloc(1, sizeof(*self));
	if (!self) {
		return NULL;
	}
	self->width = width;
	self->height = height;
	self->display = XOpenDisplay(NULL);
	if (!self->display) {
		fprintf(stderr, "demo: failed to open display\n");
		goto error;
	}
	n = DefaultScreen(self->display);
	mask = CWBackPixel | CWBorderPixel | CWEventMask;
	attr.background_pixel = BlackPixel(self->display, n);
	attr.border_pixel = BlackPixel(self->display, n);
	attr.event_mask = ExposureMask | StructureNotifyMask | KeyReleaseMask;
	self->window = XCreateWindow(self->display,
			RootWindow(self->display, n), 0, 0,
			self->width, self->height, 0,
			DefaultDepth(self->display, n), InputOutput,
			DefaultVisual(self->display, n), mask, &attr);
	if (!self->window) {
		fprintf(stderr, "demo: failed to create window\n");
		goto error;
	}
	utf8_string = XInternAtom(self->display, "UTF8_STRING", False);
	XChangeProperty(self->display, self->window,
			XInternAtom(self->display, "_NET_WM_NAME", False),
			utf8_string, 8, PropModeReplace,
			(const unsigned char *)name, strlen(name));
	XChangeProperty(self->display, self->window,
			XInternAtom(self->display, "WM_NAME", False),
			utf8_string, 8, PropModeReplace,
			(const unsigned char *)name, strlen(name));
	XChangeProperty(self->display, self->window,
			XInternAtom(self->display, "WM_ICON_NAME", False),
			utf8_string, 8, PropModeReplace,
			(const unsigned char *)name, strlen(name));
	self->wm_delete_window =
		XInternAtom(self->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(self->display, self->window,
			&self->wm_delete_window, 1);
	self->surface = cairo_xlib_surface_create(self->display, self->window,
			DefaultVisual(self->display, n),
			self->width, self->height);
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
			if (self->cr) {
				cairo_destroy(self->cr);
			}
			cairo_surface_destroy(self->surface);
		}
		if (self->display) {
			if (self->window) {
				XDestroyWindow(self->display, self->window);
			}
			XCloseDisplay(self->display);
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
	unsigned long key, lower;
	XEvent event;
	Atom wm_protocols = XInternAtom(self->display, "WM_PROTOCOLS", False);
	XMapWindow(self->display, self->window);
	while (true) {
		XNextEvent(self->display, &event);
		switch (event.type) {
		case KeyRelease:
			key = XLookupKeysym(&event.xkey, 0);
			if (ShiftMask & event.xkey.state) {
				XConvertCase(key, &lower, &key);
			}
			switch (key) {
			case XK_q:
				goto exit;
			default:
				break;
			}
			break;
		case Expose:
			if (!self->draw) {
				break;
			}
			cairo_save(self->cr);
			cairo_rectangle(self->cr,
					event.xexpose.x, event.xexpose.y,
					event.xexpose.width,
					event.xexpose.height);
			cairo_clip(self->cr);
			self->draw(self->cr, self->width, self->height);
			cairo_restore(self->cr);
			break;
		case ConfigureNotify:
			self->width = event.xconfigure.width;
			self->height = event.xconfigure.height;
			cairo_xlib_surface_set_size(self->surface,
					self->width, self->height);
			break;
		case ClientMessage:
			if (event.xclient.message_type == wm_protocols) {
				if (event.xclient.data.l[0]
						== self->wm_delete_window) {
					goto exit;
				}
			}
			break;
		case MapNotify:
		case ReparentNotify:
			break;
		default:
			fprintf(stderr, "demo: unhandled event %s [%d]\n",
					events[event.type], event.type);
			break;
		}
	}
exit:
	if (self->png) {
		cairo_surface_write_to_png(self->surface, self->png);
	}
	cairo_demo_destroy(self);
	return status;
}
