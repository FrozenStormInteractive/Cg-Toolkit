# Makefile for GNU make

.PHONY: all 09_vertex_lighting .DEFAULT 

UNAME := $(shell uname)

all: 09_vertex_lighting 

09_vertex_lighting:
	$(MAKE) -f Makefile.09_vertex_lighting 09_vertex_lighting

.DEFAULT:
	$(MAKE) -f Makefile.09_vertex_lighting $@

