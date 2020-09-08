# Makefile for GNU make

.PHONY: all 24_bump_map_torus .DEFAULT 

UNAME := $(shell uname)

all: 24_bump_map_torus 

24_bump_map_torus:
	$(MAKE) -f Makefile.24_bump_map_torus 24_bump_map_torus

.DEFAULT:
	$(MAKE) -f Makefile.24_bump_map_torus $@

