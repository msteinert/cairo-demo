#include <cairo-xlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

void
draw(cairo_t *cr, int width, int height);

#define NAME "Cairo Demo"

static const char *const events[] = {
	[KeyPress] = "KeyPress",
	[KeyRelease] = "KeyRelease",
	[ButtonPress] = "ButtonPress",
	[ButtonRelease] = "ButtonRelease",
	[MotionNotify] = "MotionNotify",
	[EnterNotify] = "EnterNotify",
	[LeaveNotify] = "LeaveNotify",
	[FocusIn] = "FocusIn",
	[FocusOut] = "FocusOut",
	[KeymapNotify] = "KeymapNotify",
	[Expose] = "Expose",
	[GraphicsExpose] = "GraphicsExpose",
	[NoExpose] = "NoExpose",
	[VisibilityNotify] = "VisibilityNotify",
	[CreateNotify] = "CreateNotify",
	[DestroyNotify] = "DestroyNotify",
	[UnmapNotify] = "UnmapNotify",
	[MapNotify] = "MapNotify",
	[MapRequest] = "MapRequest",
	[ReparentNotify] = "ReparentNotify",
	[ConfigureNotify] = "ConfigureNotify",
	[ConfigureRequest] = "ConfigureRequest",
	[GravityNotify] = "GravityNotify",
	[ResizeRequest] = "ResizeRequest",
	[CirculateNotify] = "CirculateNotify",
	[CirculateRequest] = "CirculateRequest",
	[PropertyNotify] = "PropertyNotify",
	[SelectionClear] = "SelectionClear",
	[SelectionRequest] = "SelectionRequest",
	[SelectionNotify] = "SelectionNotify",
	[ColormapNotify] = "ColormapNotify",
	[ClientMessage] = "ClientMessage",
	[MappingNotify] = "MappingNotify",
	[LASTEvent] = "LASTEvent"
};

int
main(int argc, char **argv)
{
	int status = EXIT_SUCCESS;
	unsigned long key, lower;
	int n, width = 256, height = 256;
	cairo_surface_t *surface = NULL;
	cairo_t *cr = NULL;
	Atom utf8_string, wm_delete_window, wm_protocols;
	XSetWindowAttributes attr;
	Display *display = NULL;
	Window window = 0L;
	XEvent event;
	long mask;
	display = XOpenDisplay(NULL);
	if (!display) {
		fprintf(stderr, "demo: failed to open display\n");
		goto error;
	}
	n = DefaultScreen(display);
	mask = CWEventMask;
	attr.event_mask = ExposureMask | StructureNotifyMask | KeyReleaseMask;
	window = XCreateWindow(display, RootWindow(display, n), 0, 0,
			width, height, 0, DefaultDepth(display, n),
			InputOutput, DefaultVisual(display, n),
			mask, &attr);
	if (!window) {
		fprintf(stderr, "demo: failed to create window\n");
		goto error;
	}
	utf8_string = XInternAtom(display, "UTF8_STRING", False);
	XChangeProperty(display, window,
			XInternAtom(display, "_NET_WM_NAME", False),
			utf8_string, 8, PropModeReplace, NAME, strlen(NAME));
	XChangeProperty(display, window,
			XInternAtom(display, "WM_NAME", False),
			utf8_string, 8, PropModeReplace, NAME, strlen(NAME));
	XChangeProperty(display, window,
			XInternAtom(display, "WM_ICON_NAME", False),
			utf8_string, 8, PropModeReplace, NAME, strlen(NAME));
	wm_protocols = XInternAtom(display, "WM_PROTOCOLS", False);
	wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, window, &wm_delete_window, 1);
	surface = cairo_xlib_surface_create(display, window,
			DefaultVisual(display, n), width, height);
	status = cairo_surface_status(surface);
	if (CAIRO_STATUS_SUCCESS != status) {
		fprintf(stderr, "demo: %s\n", cairo_status_to_string(status));
		goto error;
	}
	cr = cairo_create(surface);
	status = cairo_status(cr);
	if (CAIRO_STATUS_SUCCESS != status) {
		fprintf(stderr, "demo: %s\n", cairo_status_to_string(status));
		goto error;
	}
	XMapWindow(display, window);
	while (true) {
		XNextEvent(display, &event);
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
			cairo_save(cr);
			cairo_rectangle(cr, event.xexpose.x,
					event.xexpose.y,
					event.xexpose.width,
					event.xexpose.height);
			cairo_clip(cr);
			draw(cr, width, height);
			cairo_restore(cr);
			break;
		case ConfigureNotify:
			width = event.xconfigure.width;
			height = event.xconfigure.height;
			cairo_xlib_surface_set_size(surface, width, height);
			break;
		case ClientMessage:
			if (event.xclient.message_type == wm_protocols) {
				if (event.xclient.data.l[0]
						== wm_delete_window) {
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
	if (surface) {
		if (cr) {
			cairo_destroy(cr);
		}
		cairo_surface_destroy(surface);
	}
	if (display) {
		if (window) {
			XDestroyWindow(display, window);
		}
		XCloseDisplay(display);
	}
	exit(status);
error:
	status = EXIT_FAILURE;
	goto exit;
}
