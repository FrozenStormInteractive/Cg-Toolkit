# Makefile for GNU make

.PHONY: all cgfx_latest .DEFAULT 

UNAME := $(shell uname)

all: cgfx_latest 

cgfx_latest:
	$(MAKE) -f Makefile.cgfx_latest cgfx_latest

.DEFAULT:
	$(MAKE) -f Makefile.cgfx_latest $@

