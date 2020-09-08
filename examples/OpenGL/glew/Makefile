# Makefile for GNU make

.PHONY: all glew glewlib visualinfo glewinfo .DEFAULT 

UNAME := $(shell uname)

all: glew glewlib visualinfo glewinfo 

glew:
	$(MAKE) -f Makefile.glew glew

glewlib:
	$(MAKE) -f Makefile.glewlib glewlib

visualinfo:
	$(MAKE) -f Makefile.visualinfo visualinfo

glewinfo:
	$(MAKE) -f Makefile.glewinfo glewinfo

.DEFAULT:
	$(MAKE) -f Makefile.glew $@
	$(MAKE) -f Makefile.glewlib $@
	$(MAKE) -f Makefile.visualinfo $@
	$(MAKE) -f Makefile.glewinfo $@

