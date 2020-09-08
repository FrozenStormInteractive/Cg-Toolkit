# Makefile for GNU make

.PHONY: all terrain_tess .DEFAULT 

UNAME := $(shell uname)

all: terrain_tess 

terrain_tess:
	$(MAKE) -f Makefile.terrain_tess terrain_tess

.DEFAULT:
	$(MAKE) -f Makefile.terrain_tess $@

