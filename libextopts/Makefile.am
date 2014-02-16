lib_LTLIBRARIES = libextopts.la

libextopts_la_SOURCES = \
	extopts.c \
	extmods.c \
	extopts_usage.c \
	common.h

libextopts_la_LDFLAGS = \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)
libextopts_la_CFLAGS =				\
	-std=c99 -Wpedantic -Wall -Wextra	\
	-I$(top_srcdir)/include
