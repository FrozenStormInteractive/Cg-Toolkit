# Makefile for GNU make

.PHONY: all 02_vertex_and_fragment_program .DEFAULT 

UNAME := $(shell uname)

all: 02_vertex_and_fragment_program 

02_vertex_and_fragment_program:
	$(MAKE) -f Makefile.02_vertex_and_fragment_program 02_vertex_and_fragment_program

.DEFAULT:
	$(MAKE) -f Makefile.02_vertex_and_fragment_program $@

