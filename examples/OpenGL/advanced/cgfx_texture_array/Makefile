# Makefile for GNU make

.PHONY: all cgfx_texture_array .DEFAULT 

UNAME := $(shell uname)

all: cgfx_texture_array 

cgfx_texture_array:
	$(MAKE) -f Makefile.cgfx_texture_array cgfx_texture_array

.DEFAULT:
	$(MAKE) -f Makefile.cgfx_texture_array $@

