# Makefile for GNU make

.PHONY: all vertex_texture .DEFAULT 

UNAME := $(shell uname)

all: vertex_texture 

vertex_texture:
	$(MAKE) -f Makefile.vertex_texture vertex_texture

.DEFAULT:
	$(MAKE) -f Makefile.vertex_texture $@

