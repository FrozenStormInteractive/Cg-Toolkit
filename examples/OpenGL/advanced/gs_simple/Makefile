# Makefile for GNU make

.PHONY: all gs_simple .DEFAULT 

UNAME := $(shell uname)

all: gs_simple 

gs_simple:
	$(MAKE) -f Makefile.gs_simple gs_simple

.DEFAULT:
	$(MAKE) -f Makefile.gs_simple $@

