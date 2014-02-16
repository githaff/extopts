## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

SUBDIRS = libextopts example include

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libextopts.pc

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

example:
	$(MAKE) -C example example

.PHONY: example
