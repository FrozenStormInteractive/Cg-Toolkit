# Makefile for GNU make

.PHONY: all cginfo cgfxcat .DEFAULT 

UNAME := $(shell uname)

all: cginfo cgfxcat 

cginfo:
	$(MAKE) -C cginfo -f Makefile.cginfo cginfo

cgfxcat:
	$(MAKE) -C cgfxcat -f Makefile.cgfxcat cgfxcat

.DEFAULT:
	$(MAKE) -C cginfo -f Makefile.cginfo $@
	$(MAKE) -C cgfxcat -f Makefile.cgfxcat $@

