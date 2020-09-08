# Makefile for GNU make

.PHONY: all quad_tri_bezier .DEFAULT 

UNAME := $(shell uname)

all: quad_tri_bezier 

quad_tri_bezier:
	$(MAKE) -f Makefile.quad_tri_bezier quad_tri_bezier

.DEFAULT:
	$(MAKE) -f Makefile.quad_tri_bezier $@

