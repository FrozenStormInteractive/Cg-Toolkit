# Makefile for GNU make

.PHONY: all phong_tess .DEFAULT 

UNAME := $(shell uname)

all: phong_tess 

phong_tess:
	$(MAKE) -f Makefile.phong_tess phong_tess

.DEFAULT:
	$(MAKE) -f Makefile.phong_tess $@

