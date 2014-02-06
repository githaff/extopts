dnl Extopts library: advanced command line arguments parsing

dnl ################################################################
dnl # Initialize autoconf
dnl ################################################################
AC_INIT([Extopts library], [0.1], [haff@midgard.by], [extopts],
        [https://github.com/githaff/extopts/wiki])
AC_PREREQ([2.69])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([libextopts/extopts.c])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])


dnl ################################################################
dnl # Version information
dnl ################################################################
LIBEXTOPTS_MAJOR_VERSION=0
LIBEXTOPTS_MINOR_VERSION=9
LIBEXTOPTS_MICRO_VERSION=5
LIBEXTOPTS_DEVEL_VERSION=0

AC_SUBST(LIBEXTOPTS_MAJOR_VERSION)
AC_SUBST(LIBEXTOPTS_MINOR_VERSION)
AC_SUBST(LIBEXTOPTS_MICRO_VERSION)

LIBEXTOPTS_VERSION=$LIBEXTOPTS_MAJOR_VERSION.$LIBEXTOPTS_MINOR_VERSION.$LIBEXTOPTS_MICRO_VERSION

if test "x$LIBEXTOPTS_DEVEL_VERSION" != "x0"; then
	LIBEXTOPTS_VERSION=$LIBEXTOPTS_VERSION.$LIBEXTOPTS_DEVEL_VERSION
fi

AC_DEFINE_UNQUOTED(LIBEXTOPTS_MAJOR_VERSION, $LIBEXTOPTS_MAJOR_VERSION,
	[libextopts major version.])
AC_DEFINE_UNQUOTED(LIBEXTOPTS_MINOR_VERSION, $LIBEXTOPTS_MINOR_VERSION,
	[libextopts minor version.])
AC_DEFINE_UNQUOTED(LIBEXTOPTS_MICRO_VERSION, $LIBEXTOPTS_MICRO_VERSION,
	[libextopts micro version.])
AC_DEFINE_UNQUOTED(LIBEXTOPTS_VERSION, "$LIBEXTOPTS_VERSION",
	[libextopts version.])

dnl ################################################################
dnl # libtool versioning
dnl ################################################################
dnl #
dnl # +1 :  0 : +1   == new interface that does not break old one.
dnl # +1 :  0 :  0   == removed an interface. Breaks old apps.
dnl #  ? : +1 :  ?   == internal changes that doesn't break anything.
dnl #
dnl # CURRENT : REVISION : AGE
dnl #
LT_CURRENT=1
LT_REVISION=0
LT_AGE=0

LT_RELEASE=$LIBEXTOPTS_VERSION

AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)

dnl ################################################################
dnl # Initialize automake
dnl ################################################################
AM_INIT_AUTOMAKE
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

dnl ################################################################
dnl # Check for some standard stuff.
dnl ################################################################
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_LN_S
AC_PROG_INSTALL

# Initialize libtool
LT_PREREQ([2.4.2])
LT_INIT

AC_SUBST(CFLAGS)


dnl ################################################################
dnl # Output the Makefiles
dnl ################################################################
AC_CONFIG_FILES([
Makefile
libextopts/Makefile
])

AC_OUTPUT

echo "
                    $PACKAGE $VERSION
                    ========================

	prefix:                   ${prefix}
	exec_prefix:              ${exec_prefix}
        bindir:                   ${bindir}
        datadir:                  ${datadir}
	source code location:	  ${srcdir}
	cflags:		          ${CFLAGS}

        Build docs:               ${enable_docbook_docs}

"
