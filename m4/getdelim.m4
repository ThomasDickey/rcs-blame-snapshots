AC_DEFUN([gl_FUNC_GETDELIM],
[
  AC_REPLACE_FUNCS(getdelim)
  AC_CHECK_DECLS(getdelim)

  if test $ac_cv_func_getdelim = no; then
    AC_CHECK_FUNCS([flockfile funlockfile])
  fi
])
