# Makefile for GNU make

.PHONY: all 06_vertex_twisting .DEFAULT 

UNAME := $(shell uname)

all: 06_vertex_twisting 

06_vertex_twisting:
	$(MAKE) -f Makefile.06_vertex_twisting 06_vertex_twisting

.DEFAULT:
	$(MAKE) -f Makefile.06_vertex_twisting $@

