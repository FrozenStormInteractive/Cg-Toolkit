# Makefile for GNU make

.PHONY: all combine_program combine_info .DEFAULT 

UNAME := $(shell uname)

all: combine_program combine_info 

combine_program:
	$(MAKE) -f Makefile.combine_program combine_program

combine_info:
	$(MAKE) -f Makefile.combine_info combine_info

.DEFAULT:
	$(MAKE) -f Makefile.combine_program $@
	$(MAKE) -f Makefile.combine_info $@

