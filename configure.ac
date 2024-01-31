# Process this file with autoconf to produce a configure script.

AC_INIT([blame], [1.3.1], [dickey@invisible-island.net])
AC_CONFIG_SRCDIR([src/blame.c])
AC_CONFIG_HEADER([config.h])
AC_SUBST(RELEASE, 1)

AC_DEFINE_UNQUOTED(PACKAGE_STRING,"$PACKAGE_STRING")
AC_DEFINE_UNQUOTED(PACKAGE_BUGREPORT,"$PACKAGE_BUGREPORT")

AC_AIX
AC_MINIX
gl_USE_SYSTEM_EXTENSIONS

dnl AC_CONFIG_MACRO_DIR(m4)
dnl AC_CONFIG_LIBOBJ_DIR(lib)
dnl AC_CONFIG_TESTDIR(tests, tests:src)

dnl AC_GNU_SOURCE

CF_CYGPATH_W

# Checks for programs.
AC_PROG_CC
dnl FIXME: gl_EARLY
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_RANLIB
AC_PROG_INSTALL
AC_PROG_MAKE_SET

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([libintl.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_C_PROTOTYPES
gl_INLINE
AC_C_STRINGIZE
AC_C_VOLATILE
AC_TYPE_SIZE_T
AC_TYPE_OFF_T
AC_FUNC_MKTIME

dnl FIXME: gl_INIT
gl_FUNC_ALLOCA
gl_GETOPT
gl_ARGP
gl_TIME_R
gl_TM_GMTOFF
gl_SYSEXITS

gt_TYPE_WCHAR_T
gl_AC_TYPE_LONG_LONG
gt_TYPE_LONGDOUBLE

# canonicalize gnulib module needs this

AH_BOTTOM([
#ifndef PARAMS
# if PROTOTYPES
#  define PARAMS(protos) protos
# else /* ! PROTOTYPES */
#  define PARAMS(protos) ()
# endif /* ! PROTOTYPES */
#endif
])

AH_BOTTOM([
/* Avoid memory leak in argp */
#define GNULIB_ARGP_DISABLE_DIRNAME 1
])

# Checks for library functions.
mac_HAVE_NL_LANGINFO

AC_FUNC_MMAP
AC_SYS_LONG_FILE_NAMES

dnl This relies on certain dos.m4 behaviour...
AC_SUBST(FILE_SYSTEM_BACKSLASH_IS_FILE_NAME_SEPARATOR,
	[$ac_fs_backslash_is_file_name_separator])

AH_BOTTOM([
#if FILE_SYSTEM_BACKSLASH_IS_FILE_NAME_SEPARATOR
# define SUFFIXES "\\,v"
# define DIRECTORY_SEPARATOR '\\'
# define SSLASH "\\"
#else /* ! FILE_SYSTEM_BACKSLASH_IS_FILE_NAME_SEPARATOR */
# define SUFFIXES ",v/"
# define DIRECTORY_SEPARATOR '/'
# define SSLASH "/"
#endif /* ! FILE_SYSTEM_BACKSLASH_IS_FILE_NAME_SEPARATOR */
])

AC_ARG_ENABLE(debug,
	AC_HELP_STRING(--enable-debug, [include debug code (e.g. assertions)]))
case "$enable_debug" in
no|"")
	AC_DEFINE(NDEBUG, 1, [Define to 1 to disable assertions])
	;;
*)
	;;
esac

AC_ARG_ENABLE(debug,
	AC_HELP_STRING(--enable-profile, [enable profiling]))
case "$enable_profile" in
no|"")
	;;
*)
	if test "$GCC" != "yes"; then
		AC_MSG_ERROR([I can only use profiling on GCC])
	fi
	CFLAGS=`echo $CFLAGS -pg -fprofile-arcs -ftest-coverage | sed -e s,-O2,-O0,`
	LDFLAGS="$LDFLAGS -pg -fprofile-arcs -ftest-coverage"
	;;
esac

AC_ARG_ENABLE(fastexit,
	AC_HELP_STRING(--disable-fastexit, [free all memory when exiting]))
case "$enable_fastexit" in
yes|"")
	AC_DEFINE(FASTEXIT, 1, [Define to 1 to exit quickly without freeing all memory])
	FASTEXIT=1
	;;
*)
	FASTEXIT=0
	;;
esac
AC_SUBST([FASTEXIT])

CFLAGS=`echo $CFLAGS | sed -e s,-O2,-O3,`

NEWS=NEWS
AC_SUBST_FILE(NEWS)

AC_CONFIG_FILES([
	Makefile
	doc/Makefile
	lib/Makefile
	src/Makefile
	tests/Makefile
	tests/atlocal
	blame.spec
])

echo "creating tests/atconfig"
cat >tests/atconfig <<ATEOF
#!/bin/sh
at_testdir='tests'
abs_builddir='`pwd`'
at_srcdir='$srcdir'
abs_srcdir='`cd $srcdir && pwd`'
at_top_srcdir='$srcdir'
abs_top_srcdir='`cd $srcdir && pwd`'
at_top_builddir='.'
abs_top_builddir='`pwd`'

AUTOTEST_PATH='tests:src'

SHELL=\${CONFIG_SHELL-'$SHELL'}
ATEOF
chmod +x tests/atconfig

AC_OUTPUT
