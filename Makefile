# Define program name
PROGRAM = cairo-demo
# Define the program name
NAME = "Cairo Demo"
# Define the program version
VERSION = "0.1"
# Define source files
SOURCES = \
	cairo-demo.c \
	cairo-draw.c \
	cairo-events.c \
	cairo-main.c \
	cairo-operators.c
# Define compiler flags
CFLAGS = -g -O2 -Wall
# Define linker flags
LDFLAGS =
# Define pkg-config dependencies
PKG_CONFIG_DEPS = \
	cairo \
	cairo-xlib \
	pango \
	pangocairo \
	x11
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
	$(V_CC)$(CC) $(CPPFLAGS) -I. -DNAME=\"$(NAME)\" -DPROGRAM=\"$(PROGRAM)\" -DVERSION=\"$(VERSION)\" $(CFLAGS) $(shell pkg-config --cflags $(PKG_CONFIG_DEPS)) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c $< -o $@
	$(V_at)mv $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
# Link rule
$(PROGRAM): $(OBJECTS)
	$(V_LINK)$(CC) -o $@ $(OBJECTS) $(shell pkg-config --libs $(PKG_CONFIG_DEPS))
# Clean build files
clean:
	$(V_at)rm -f $(DEPS) $(OBJECTS) $(PROGRAM)
# Clean everything
distclean: clean
	$(V_at)rm -rf $(DEPDIR)
# Include generated dependencies
-include $(DEPS)
.PHONY: all clean distclean
