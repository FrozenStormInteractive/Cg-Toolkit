# Makefile for GNU make

.PHONY: all 04_varying_parameter .DEFAULT 

UNAME := $(shell uname)

all: 04_varying_parameter 

04_varying_parameter:
	$(MAKE) -f Makefile.04_varying_parameter 04_varying_parameter

.DEFAULT:
	$(MAKE) -f Makefile.04_varying_parameter $@

