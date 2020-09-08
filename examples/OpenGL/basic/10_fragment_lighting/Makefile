# Makefile for GNU make

.PHONY: all 10_fragment_lighting .DEFAULT 

UNAME := $(shell uname)

all: 10_fragment_lighting 

10_fragment_lighting:
	$(MAKE) -f Makefile.10_fragment_lighting 10_fragment_lighting

.DEFAULT:
	$(MAKE) -f Makefile.10_fragment_lighting $@

