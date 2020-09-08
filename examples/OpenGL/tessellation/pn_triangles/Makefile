# Makefile for GNU make

.PHONY: all pn_triangles .DEFAULT 

UNAME := $(shell uname)

all: pn_triangles 

pn_triangles:
	$(MAKE) -f Makefile.pn_triangles pn_triangles

.DEFAULT:
	$(MAKE) -f Makefile.pn_triangles $@

