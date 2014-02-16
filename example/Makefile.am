noinst_PROGRAMS = example

example_SOURCES = main.c modules.c
example_CFLAGS =				\
	-std=c99 -Wpedantic -Wall -Wextra	\
	-I$(top_srcdir)/include
example_LDADD = ../libextopts/libextopts.la
