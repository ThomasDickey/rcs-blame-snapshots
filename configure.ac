# Process this file with autoconf to produce a configure script.
# $Id: configure.ac,v 1.28 2024/02/05 09:21:33 tom Exp $

AC_INIT([blame], [1.4], [dickey@invisible-island.net])
AC_CONFIG_SRCDIR([src/blame.c])
AC_CONFIG_HEADER([config.h])

CHECK_VERSION=`sed -e 's/[[ 	]].*//' $srcdir/VERSION`
test "[$]CHECK_VERSION" = "[$]PACKAGE_VERSION" || AC_MSG_ERROR(inconsistent VERSION)

PACKAGE_DATE=`sed -e 's/^[[^ 	]]*[[ 	]]*//' $srcdir/VERSION`

AC_SUBST(PACKAGE_DATE)
AC_SUBST(PACKAGE_STRING)
AC_SUBST(PACKAGE_BUGREPORT)

echo "configuring $PACKAGE_NAME ($PACKAGE_VERSION $PACKAGE_DATE)"

AC_AIX
AC_MINIX

CF_WITHOUT_X

# Checks for programs.
CF_PROG_CC
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_RANLIB
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_AWK
CF_AR_FLAGS
CF_CYGPATH_W

# Checks for libraries.

# Checks for header files.
gl_USE_SYSTEM_EXTENSIONS
CF_XOPEN_SOURCE
AC_HEADER_STDC
AC_CHECK_HEADERS([libintl.h])

AC_HEADER_STDBOOL
# Define two additional variables used in the Makefile substitution.
if test "$ac_cv_header_stdbool_h" = yes; then
  STDBOOL_H=''
else
  STDBOOL_H='stdbool.h'
fi
if test "$ac_cv_type__Bool" = yes; then
  HAVE__BOOL=1
else
  HAVE__BOOL=0
fi
AC_SUBST(STDBOOL_H)
AC_SUBST(HAVE__BOOL)

CF_DISABLE_ECHO
CF_ENABLE_WARNINGS(Wno-undef)

# Checks for typedefs, structures, and compiler characteristics.
dnl CF_LARGEFILE
CF_SIZEOF_TIME_T
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
gl_CHECK_TYPE_STRUCT_DIRENT_D_INO
gl_TIME_R
gl_TM_GMTOFF
gl_SYSEXITS

gt_TYPE_WCHAR_T
gl_AC_TYPE_LONG_LONG
gt_TYPE_LONGDOUBLE

gl_CYCLE_CHECK
gl_FUNC_GETDELIM
gl_FUNC_GETLINE
gl_FILE_NAME_CONCAT
gl_FUNC_STRCHRNUL
gl_FUNC_MEMPCPY
gl_FUNC_STRNLEN
gl_XALLOC
gl_XGETCWD
gl_XREADLINK
AC_FUNC_CANONICALIZE_FILE_NAME

AC_MSG_CHECKING(for error module)
AC_TRY_LINK([
$ac_includes_default
#include <error.h>],[
error (0, 1, "testing: %d", 2);],
	cf_have_func_error=yes,
	cf_have_func_error=no)
AC_MSG_RESULT($cf_have_func_error)
if test "$cf_have_func_error" = no; then
	AC_LIBOBJ(error)
fi

AC_MSG_CHECKING(for obstack module)
AC_TRY_LINK([
$ac_includes_default
#include <obstack.h>],[
struct obstack *data = 0;
__obstack_free(data, 0);
(void) data;],
	cf_have_func_obstack=yes,
	cf_have_func_obstack=no)
AC_MSG_RESULT($cf_have_func_obstack)
if test "$cf_have_func_obstack" = no; then
	AC_LIBOBJ(obstack)
fi

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
