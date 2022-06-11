dnl config.m4 for extension ecma_intl

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([ecma_intl],
dnl   [for ecma_intl support],
dnl   [AS_HELP_STRING([--with-ecma_intl],
dnl     [Include ecma_intl support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([ecma_intl],
  [whether to enable ecma_intl support],
  [AS_HELP_STRING([--enable-ecma_intl],
    [Enable ecma_intl support])],
  [no])

if test "$PHP_ECMA_INTL" != "no"; then
  dnl Write more examples of tests here...

  dnl Remove this code block if the library does not support pkg-config.
  dnl PKG_CHECK_MODULES([LIBFOO], [foo])
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBS, ECMA_INTL_SHARED_LIBADD)

  dnl If you need to check for a particular library version using PKG_CHECK_MODULES,
  dnl you can use comparison operators. For example:
  dnl PKG_CHECK_MODULES([LIBFOO], [foo >= 1.2.3])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo < 3.4])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo = 1.2.3])

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-ecma_intl -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/ecma_intl.h"  # you most likely want to change this
  dnl if test -r $PHP_ECMA_INTL/$SEARCH_FOR; then # path given as parameter
  dnl   ECMA_INTL_DIR=$PHP_ECMA_INTL
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for ecma_intl files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ECMA_INTL_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ECMA_INTL_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the ecma_intl distribution])
  dnl fi

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-ecma_intl -> add include path
  dnl PHP_ADD_INCLUDE($ECMA_INTL_DIR/include)

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-ecma_intl -> check for lib and symbol presence
  dnl LIBNAME=ECMA_INTL # you may want to change this
  dnl LIBSYMBOL=ECMA_INTL # you most likely want to change this

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   AC_DEFINE(HAVE_ECMA_INTL_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your ecma_intl library.])
  dnl ], [
  dnl   $LIBFOO_LIBS
  dnl ])

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are not using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ECMA_INTL_DIR/$PHP_LIBDIR, ECMA_INTL_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ECMA_INTL_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your ecma_intl library.])
  dnl ],[
  dnl   -L$ECMA_INTL_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ECMA_INTL_SHARED_LIBADD)

  dnl In case of no dependencies
  AC_DEFINE(HAVE_ECMA_INTL, 1, [ Have ecma_intl support ])

  PHP_NEW_EXTENSION(ecma_intl, ecma_intl.c, $ext_shared)
fi
