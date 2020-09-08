# Makefile for GNU make

.PHONY: all buffer_lighting ubo_lighting cgfx_buffer_lighting .DEFAULT 

UNAME := $(shell uname)

all: buffer_lighting ubo_lighting cgfx_buffer_lighting 

buffer_lighting:
	$(MAKE) -C buffer_lighting -f Makefile.buffer_lighting buffer_lighting

ubo_lighting:
	$(MAKE) -C ubo_lighting -f Makefile.ubo_lighting ubo_lighting

cgfx_buffer_lighting:
	$(MAKE) -C cgfx_buffer_lighting -f Makefile.cgfx_buffer_lighting cgfx_buffer_lighting

.DEFAULT:
	$(MAKE) -C buffer_lighting -f Makefile.buffer_lighting $@
	$(MAKE) -C ubo_lighting -f Makefile.ubo_lighting $@
	$(MAKE) -C cgfx_buffer_lighting -f Makefile.cgfx_buffer_lighting $@

