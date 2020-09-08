# Makefile for GNU make

.PHONY: all ubo_lighting .DEFAULT 

UNAME := $(shell uname)

all: ubo_lighting 

ubo_lighting:
	$(MAKE) -f Makefile.ubo_lighting ubo_lighting

.DEFAULT:
	$(MAKE) -f Makefile.ubo_lighting $@

