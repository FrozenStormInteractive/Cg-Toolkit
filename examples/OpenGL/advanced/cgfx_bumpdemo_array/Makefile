# Makefile for GNU make

.PHONY: all cgfx_bumpdemo_array .DEFAULT 

UNAME := $(shell uname)

all: cgfx_bumpdemo_array 

cgfx_bumpdemo_array:
	$(MAKE) -f Makefile.cgfx_bumpdemo_array cgfx_bumpdemo_array

.DEFAULT:
	$(MAKE) -f Makefile.cgfx_bumpdemo_array $@

