# Makefile for GNU make

.PHONY: all cgfx_procfx .DEFAULT 

UNAME := $(shell uname)

all: cgfx_procfx 

cgfx_procfx:
	$(MAKE) -f Makefile.cgfx_procfx cgfx_procfx

.DEFAULT:
	$(MAKE) -f Makefile.cgfx_procfx $@

