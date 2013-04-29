# Define program name
PROGRAM = cairo-demo
# Define the program name
NAME = "Cairo Demo"
# Define the program version
VERSION = "0.1"
# Select the graphics backend
backend ?= x11
# Set the install prefix
prefix ?= /usr/local
# Define source files
SOURCES += cairo-demo-$(backend).c
SOURCES += cairo-draw.c
SOURCES += cairo-main.c
SOURCES += cairo-operators.c
# Define compiler flags
CFLAGS = -g -O2 -Wall -Wextra -D_GNU_SOURCE
# Define linker flags
LDFLAGS =
# Define pkg-config dependencies
PKG_CONFIG = pkg-config
ifeq ($(CAIRO_CFLAGS),)
CAIRO_CFLAGS = $(shell $(PKG_CONFIG) --cflags cairo)
endif
CPPFLAGS += $(CAIRO_CFLAGS)
ifeq ($(CAIRO_LIBS),)
CAIRO_LIBS = $(shell $(PKG_CONFIG) --libs cairo)
endif
LDFLAGS += $(CAIRO_LIBS)
ifeq ($(backend),x11)
ifeq ($(X11_CFLAGS),)
X11_CFLAGS = $($(PKG_CONFIG) --cflags x11)
endif
CPPFLAGS += $(X11_CFLAGS)
ifeq ($(X11_LIBS),)
X11_LIBS = $(shell $(PKG_CONFIG) --libs x11)
endif
LDFLAGS += $(X11_LIBS)
ifeq ($(CAIRO_XLIB_CFLAGS),)
CAIRO_XLIB_CFLAGS = $($(PKG_CONFIG) --cflags cairo-xlib)
endif
CPPFLAGS += $(CAIRO_XLIB_CFLAGS)
ifeq ($(CAIRO_XLIB_LIBS),)
CAIRO_XLIB_LIBS = $($(PKG_CONFIG) --libs cairo-xlib)
endif
LDFLAGS += $(CAIRO_XLIB_LIBS)
endif
ifeq ($(backend),directfb)
ifeq ($(directfb_CFLAGS),)
directfb_CFLAGS = $(shell $(PKG_CONFIG) --cflags directfb)
endif
CPPFLAGS += $(directfb_CFLAGS)
ifeq ($(directfb_LIBS),)
directfb_LIBS = $(shell $(PKG_CONFIG) --libs directfb)
endif
LDFLAGS += $(directfb_LIBS)
endif
# Define object files
OBJECTS = $(SOURCES:%.c=%.o)
# Define dependencies
DEPS = $(SOURCES:%.c=$(DEPDIR)/%.Po)
DEPDIR = .deps
# Quiet by default
VERBOSE ?= 0
# Define CC verbose macro
V_CC = $(v_CC_$(V))
v_CC_ = $(v_CC_$(VERBOSE))
v_CC_0 = @echo "  CC    " $(@F);
# Define LINK verbose macro
V_LINK = $(v_LINK_$(V))
v_LINK_ = $(v_LINK_$(VERBOSE))
v_LINK_0 = @echo "  LINK  " $(@F);
# Define INSTALL verbose macro
V_INSTALL = $(v_INSTALL_$(V))
v_INSTALL_ = $(v_INSTALL_$(VERBOSE))
v_INSTALL_0 = @echo "  INSTALL  " $?;
# Define "at" verbose macro
V_at = $(v_at_$(V))
v_at_ = $(v_at_$(VERBOSE))
v_at_0 = @
# Default rule
all: $(PROGRAM)
.DEFAULT: all
# Directory creation rule
$(DEPDIR):
	$(V_at)mkdir -p $@
# Implicit compilation rule
%.o: %.c | $(DEPDIR)
	$(V_CC)$(CC) -std=c99 $(CPPFLAGS) -I. -DNAME=\"$(NAME)\" \
		-DPROGRAM=\"$(PROGRAM)\" -DVERSION=\"$(VERSION)\" \
		$(CFLAGS) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c $< -o $@
	$(V_at)mv $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
# Link rule
$(PROGRAM): $(OBJECTS)
	$(V_LINK)$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LDFLAGS)
# Clean build files
clean:
	$(V_at)rm -f $(DEPS) $(OBJECTS) $(PROGRAM)
# Clean everything
distclean: clean
	$(V_at)rm -rf $(DEPDIR)
install: $(PROGRAM)
	$(V_at)install -d $(DESTDIR)$(prefix)/bin
	$(V_INSTALL)install $(PROGRAM) $(DESTDIR)$(prefix)/bin
# Include generated dependencies
-include $(DEPS)
.PHONY: all clean distclean install
