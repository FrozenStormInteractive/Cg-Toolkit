# Makefile for GNU make

.PHONY: all gs_interp_quad .DEFAULT 

UNAME := $(shell uname)

all: gs_interp_quad 

gs_interp_quad:
	$(MAKE) -f Makefile.gs_interp_quad gs_interp_quad

.DEFAULT:
	$(MAKE) -f Makefile.gs_interp_quad $@

