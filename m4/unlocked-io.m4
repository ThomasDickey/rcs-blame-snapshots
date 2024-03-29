# unlocked-io.m4 serial 14

# Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006
# Free Software Foundation, Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

dnl From Jim Meyering.
dnl
dnl See if the glibc *_unlocked I/O macros or functions are available.
dnl Use only those *_unlocked macros or functions that are declared
dnl (because some of them were declared in Solaris 2.5.1 but were removed
dnl in Solaris 2.6, whereas we want binaries built on Solaris 2.5.1 to run
dnl on Solaris 2.6).

AC_DEFUN([gl_FUNC_GLIBC_UNLOCKED_IO],
[
  AC_DEFINE([USE_UNLOCKED_IO], 1,
    [Define to 1 if you want getc etc. to use unlocked I/O if available.
     Unlocked I/O can improve performance in unithreaded apps,
     but it is not safe for multithreaded apps.])

  dnl Persuade glibc and Solaris <stdio.h> to declare
  dnl fgets_unlocked(), fputs_unlocked() etc.
  AC_REQUIRE([gl_USE_SYSTEM_EXTENSIONS])

  AC_CHECK_DECLS([clearerr_unlocked])
  AC_CHECK_DECLS([feof_unlocked])
  AC_CHECK_DECLS([ferror_unlocked])
  AC_CHECK_DECLS([fflush_unlocked])
  AC_CHECK_DECLS([fgets_unlocked])
  AC_CHECK_DECLS([fputc_unlocked])
  AC_CHECK_DECLS([fputs_unlocked])
  AC_CHECK_DECLS([fread_unlocked])
  AC_CHECK_DECLS([fwrite_unlocked])
  AC_CHECK_DECLS([getc_unlocked])
  AC_CHECK_DECLS([getchar_unlocked])
  AC_CHECK_DECLS([putc_unlocked])
  AC_CHECK_DECLS([putchar_unlocked])
])
