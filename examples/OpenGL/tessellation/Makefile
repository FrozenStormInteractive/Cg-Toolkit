# Makefile for GNU make

.PHONY: all cgfx_tessellation tess_simple tess_bezier pn_triangles quad_tri_bezier phong_tess terrain_tess .DEFAULT 

UNAME := $(shell uname)

all: cgfx_tessellation tess_simple tess_bezier pn_triangles quad_tri_bezier phong_tess terrain_tess 

cgfx_tessellation:
	$(MAKE) -C cgfx_tessellation -f Makefile.cgfx_tessellation cgfx_tessellation

tess_simple:
	$(MAKE) -C tess_simple -f Makefile.tess_simple tess_simple

tess_bezier:
	$(MAKE) -C tess_bezier -f Makefile.tess_bezier tess_bezier

pn_triangles:
	$(MAKE) -C pn_triangles -f Makefile.pn_triangles pn_triangles

quad_tri_bezier:
	$(MAKE) -C quad_tri_bezier -f Makefile.quad_tri_bezier quad_tri_bezier

phong_tess:
	$(MAKE) -C phong_tess -f Makefile.phong_tess phong_tess

terrain_tess:
	$(MAKE) -C terrain_tess -f Makefile.terrain_tess terrain_tess

.DEFAULT:
	$(MAKE) -C cgfx_tessellation -f Makefile.cgfx_tessellation $@
	$(MAKE) -C tess_simple -f Makefile.tess_simple $@
	$(MAKE) -C tess_bezier -f Makefile.tess_bezier $@
	$(MAKE) -C pn_triangles -f Makefile.pn_triangles $@
	$(MAKE) -C quad_tri_bezier -f Makefile.quad_tri_bezier $@
	$(MAKE) -C phong_tess -f Makefile.phong_tess $@
	$(MAKE) -C terrain_tess -f Makefile.terrain_tess $@

