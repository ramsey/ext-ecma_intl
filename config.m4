PHP_ARG_ENABLE([ecma_intl],
  [whether to enable ecma_intl support],
  [AS_HELP_STRING([--enable-ecma_intl],
    [Enable ecma_intl support])],
  [no])

PHP_ARG_WITH([icu],
  [for icu support],
  [AS_HELP_STRING([--with-icu],
    [Include icu support])])

if test "$PHP_ECMA_INTL" != "no"; then
  PKG_CHECK_MODULES([ICU], [icu-uc >= 71.1 icu-i18n icu-io])

  PHP_EVAL_INCLINE($ICU_CFLAGS)
  PHP_EVAL_LIBLINE($ICU_LIBS, ICU_SHARED_LIBADD)

  PHP_SUBST(INTL_SHARED_LIBADD)

  AC_DEFINE(HAVE_ICU, 1, [ Have icu support ])
  AC_DEFINE(HAVE_ECMA_INTL, 1, [ Have ecma_intl support ])

  PHP_NEW_EXTENSION(ecma_intl, ecma_intl.c, $ext_shared)
fi
