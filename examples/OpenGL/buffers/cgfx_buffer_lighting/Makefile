# Makefile for GNU make

.PHONY: all cgfx_buffer_lighting .DEFAULT 

UNAME := $(shell uname)

all: cgfx_buffer_lighting 

cgfx_buffer_lighting:
	$(MAKE) -f Makefile.cgfx_buffer_lighting cgfx_buffer_lighting

.DEFAULT:
	$(MAKE) -f Makefile.cgfx_buffer_lighting $@

