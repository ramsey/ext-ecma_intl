PHP_ARG_ENABLE(
  [ecma_intl],
  [for internationalization support, Ecma-style (ECMA-402)],
  [AS_HELP_STRING([--enable-ecma_intl], [Enable internationalization support, Ecma-style (ECMA-402)])],
  [yes]
)

if test "$PHP_ECMA_INTL" != "no"; then
  PKG_CHECK_MODULES([ICU], [icu-uc >= 71.1 icu-i18n icu-io])

  PHP_EVAL_INCLINE($ICU_CFLAGS)
  PHP_EVAL_LIBLINE($ICU_LIBS, ECMA_INTL_SHARED_LIBADD)

  AC_DEFINE(HAVE_ECMA_INTL, 1, [ Have ecma_intl support ])

  PHP_NEW_EXTENSION(ecma_intl, php_ecma_intl.c \
    src/exceptions.c \
    src/functions.c \
    , $ext_shared)

  PHP_SUBST(ECMA_INTL_SHARED_LIBADD)
fi
