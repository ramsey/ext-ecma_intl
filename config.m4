PHP_ARG_ENABLE(
  [ecma_intl],
  [for ECMA-402 Intl support with ICU],
  [AS_HELP_STRING([--enable-ecma_intl], [Enable ECMA-402 Intl support with ICU])],
  [yes]
)

if test "$PHP_ECMA_INTL" != "no"; then
  PKG_CHECK_MODULES([ICU], [icu-uc >= 71.1 icu-i18n icu-io])

  PHP_EVAL_INCLINE($ICU_CFLAGS)
  PHP_EVAL_LIBLINE($ICU_LIBS, ECMA_INTL_SHARED_LIBADD)

  AC_DEFINE(HAVE_ECMA_INTL, 1, [ Have ecma_intl support ])

  PHP_NEW_EXTENSION(ecma_intl, ecma_intl.c, $ext_shared)
  PHP_SUBST(ECMA_INTL_SHARED_LIBADD)
fi
