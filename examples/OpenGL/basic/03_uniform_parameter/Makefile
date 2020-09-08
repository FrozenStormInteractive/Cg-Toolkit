# Makefile for GNU make

.PHONY: all 03_uniform_parameter .DEFAULT 

UNAME := $(shell uname)

all: 03_uniform_parameter 

03_uniform_parameter:
	$(MAKE) -f Makefile.03_uniform_parameter 03_uniform_parameter

.DEFAULT:
	$(MAKE) -f Makefile.03_uniform_parameter $@

