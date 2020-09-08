# Makefile for GNU make

.PHONY: all texture_array .DEFAULT 

UNAME := $(shell uname)

all: texture_array 

texture_array:
	$(MAKE) -f Makefile.texture_array texture_array

.DEFAULT:
	$(MAKE) -f Makefile.texture_array $@

