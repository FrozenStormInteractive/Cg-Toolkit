# Makefile for GNU make

.PHONY: all cgfx_bumpdemo cgfx_bumpdemo_array cgfx_bumpdemo2 cgfx_interfaces cgfx_latest cgfx_boxfilter cgfx_procfx cgfx_texture_array combine_program combine_info custom_state_assignments generic_attribs gs_md2bump gs_md2shadowvol gs_md2shadow gs_shrinky gs_simple gs_quadnormal gs_interp_quad include_string interpolation_modifier texture_array vertex_texture .DEFAULT 

UNAME := $(shell uname)

all: cgfx_bumpdemo cgfx_bumpdemo_array cgfx_bumpdemo2 cgfx_interfaces cgfx_latest cgfx_boxfilter cgfx_procfx cgfx_texture_array combine_program combine_info custom_state_assignments generic_attribs gs_md2bump gs_md2shadowvol gs_md2shadow gs_shrinky gs_simple gs_quadnormal gs_interp_quad include_string interpolation_modifier texture_array vertex_texture 

cgfx_bumpdemo:
	$(MAKE) -C cgfx_bumpdemo -f Makefile.cgfx_bumpdemo cgfx_bumpdemo

cgfx_bumpdemo_array:
	$(MAKE) -C cgfx_bumpdemo_array -f Makefile.cgfx_bumpdemo_array cgfx_bumpdemo_array

cgfx_bumpdemo2:
	$(MAKE) -C cgfx_bumpdemo -f Makefile.cgfx_bumpdemo2 cgfx_bumpdemo2

cgfx_interfaces:
	$(MAKE) -C cgfx_interfaces -f Makefile.cgfx_interfaces cgfx_interfaces

cgfx_latest:
	$(MAKE) -C cgfx_latest -f Makefile.cgfx_latest cgfx_latest

cgfx_boxfilter:
	$(MAKE) -C cgfx_boxfilter -f Makefile.cgfx_boxfilter cgfx_boxfilter

cgfx_procfx:
	$(MAKE) -C cgfx_procfx -f Makefile.cgfx_procfx cgfx_procfx

cgfx_texture_array:
	$(MAKE) -C cgfx_texture_array -f Makefile.cgfx_texture_array cgfx_texture_array

combine_program:
	$(MAKE) -C combine_program -f Makefile.combine_program combine_program

combine_info:
	$(MAKE) -C combine_program -f Makefile.combine_info combine_info

custom_state_assignments:
	$(MAKE) -C custom_state_assignments -f Makefile.custom_state_assignments custom_state_assignments

generic_attribs:
	$(MAKE) -C generic_attribs -f Makefile.generic_attribs generic_attribs

gs_md2bump:
	$(MAKE) -C gs_md2render -f Makefile.gs_md2bump gs_md2bump

gs_md2shadowvol:
	$(MAKE) -C gs_md2render -f Makefile.gs_md2shadowvol gs_md2shadowvol

gs_md2shadow:
	$(MAKE) -C gs_md2render -f Makefile.gs_md2shadow gs_md2shadow

gs_shrinky:
	$(MAKE) -C gs_shrinky -f Makefile.gs_shrinky gs_shrinky

gs_simple:
	$(MAKE) -C gs_simple -f Makefile.gs_simple gs_simple

gs_quadnormal:
	$(MAKE) -C gs_quadnormal -f Makefile.gs_quadnormal gs_quadnormal

gs_interp_quad:
	$(MAKE) -C gs_interp_quad -f Makefile.gs_interp_quad gs_interp_quad

include_string:
	$(MAKE) -C include_string -f Makefile.include_string include_string

interpolation_modifier:
	$(MAKE) -C interpolation_modifier -f Makefile.interpolation_modifier interpolation_modifier

texture_array:
	$(MAKE) -C texture_array -f Makefile.texture_array texture_array

vertex_texture:
	$(MAKE) -C vertex_texture -f Makefile.vertex_texture vertex_texture

.DEFAULT:
	$(MAKE) -C cgfx_bumpdemo -f Makefile.cgfx_bumpdemo $@
	$(MAKE) -C cgfx_bumpdemo_array -f Makefile.cgfx_bumpdemo_array $@
	$(MAKE) -C cgfx_bumpdemo -f Makefile.cgfx_bumpdemo2 $@
	$(MAKE) -C cgfx_interfaces -f Makefile.cgfx_interfaces $@
	$(MAKE) -C cgfx_latest -f Makefile.cgfx_latest $@
	$(MAKE) -C cgfx_boxfilter -f Makefile.cgfx_boxfilter $@
	$(MAKE) -C cgfx_procfx -f Makefile.cgfx_procfx $@
	$(MAKE) -C cgfx_texture_array -f Makefile.cgfx_texture_array $@
	$(MAKE) -C combine_program -f Makefile.combine_program $@
	$(MAKE) -C combine_program -f Makefile.combine_info $@
	$(MAKE) -C custom_state_assignments -f Makefile.custom_state_assignments $@
	$(MAKE) -C generic_attribs -f Makefile.generic_attribs $@
	$(MAKE) -C gs_md2render -f Makefile.gs_md2bump $@
	$(MAKE) -C gs_md2render -f Makefile.gs_md2shadowvol $@
	$(MAKE) -C gs_md2render -f Makefile.gs_md2shadow $@
	$(MAKE) -C gs_shrinky -f Makefile.gs_shrinky $@
	$(MAKE) -C gs_simple -f Makefile.gs_simple $@
	$(MAKE) -C gs_quadnormal -f Makefile.gs_quadnormal $@
	$(MAKE) -C gs_interp_quad -f Makefile.gs_interp_quad $@
	$(MAKE) -C include_string -f Makefile.include_string $@
	$(MAKE) -C interpolation_modifier -f Makefile.interpolation_modifier $@
	$(MAKE) -C texture_array -f Makefile.texture_array $@
	$(MAKE) -C vertex_texture -f Makefile.vertex_texture $@

