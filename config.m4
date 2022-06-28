PHP_ARG_ENABLE(
  [ecma_intl],
  [for i18n support, Ecma-style (ECMA-402)],
  [AS_HELP_STRING(
    [--enable-ecma_intl],
    [Enable i18n support, Ecma-style (ECMA-402)])
  ],
  [yes]
)

if test "$PHP_ECMA_INTL" != "no"; then
  PKG_CHECK_MODULES([ICU], [icu-uc >= 67.1 icu-i18n icu-io])

  PHP_EVAL_INCLINE($ICU_CFLAGS)
  PHP_EVAL_LIBLINE($ICU_LIBS, ECMA_INTL_SHARED_LIBADD)

  PHP_SUBST(ECMA_INTL_SHARED_LIBADD)
  AC_DEFINE(HAVE_ECMA_INTL, 1, [ Have ecma_intl support ])

  ECMA_INTL_COMMON_FLAGS="$ICU_CFLAGS"

  PHP_ECMA_INTL_C_SOURCES="                                                    \
    src/ecma_intl.c                                                            \
    src/php/classes/php_calendar_ce.c                                          \
    src/php/classes/php_case_first_ce.c                                        \
    src/php/classes/php_category_ce.c                                          \
    src/php/classes/php_collation_ce.c                                         \
    src/php/classes/php_exceptions_ce.c                                        \
    src/php/classes/php_formatting_ce.c                                        \
    src/php/classes/php_hour_cycle_ce.c                                        \
    src/php/classes/php_intl_ce.c                                              \
    src/php/classes/php_locale_matcher_ce.c                                    \
    src/php/classes/php_numbering_system_ce.c                                  \
    src/unicode/bcp47.c                                                        \
    "

  PHP_ECMA_INTL_CXX_SOURCES="                                                  \
    src/unicode/units.cpp                                                      \
    "

  PHP_NEW_EXTENSION(
    ecma_intl,
    $PHP_ECMA_INTL_C_SOURCES,
    $ext_shared,
    ,
    $ECMA_INTL_COMMON_FLAGS,
    cxx
  )

  PHP_REQUIRE_CXX()
  PHP_CXX_COMPILE_STDCXX(11, mandatory, PHP_ECMA_INTL_STDCXX)
  PHP_ECMA_INTL_CXX_FLAGS="                                                    \
    $ECMA_INTL_COMMON_FLAGS                                                    \
    $PHP_ECMA_INTL_STDCXX                                                      \
    $ICU_CXXFLAGS                                                              \
    "

  if test "$ext_shared" = "no"; then
    PHP_ADD_SOURCES(
      PHP_EXT_DIR(ecma_intl),
      $PHP_ECMA_INTL_CXX_SOURCES,
      $PHP_ECMA_INTL_CXX_FLAGS
    )
  else
    PHP_ADD_SOURCES_X(
      PHP_EXT_DIR(ecma_intl),
      $PHP_ECMA_INTL_CXX_SOURCES,
      $PHP_ECMA_INTL_CXX_FLAGS,
      shared_objects_ecma_intl,
      yes
    )
  fi

  PHP_ADD_BUILD_DIR([$ext_srcdir])
  PHP_ADD_BUILD_DIR([$ext_srcdir/src])
  PHP_ADD_BUILD_DIR([$ext_srcdir/src/php])
  PHP_ADD_BUILD_DIR([$ext_srcdir/src/php/classes])
  PHP_ADD_BUILD_DIR([$ext_srcdir/src/unicode])

  PHP_ADD_EXTENSION_DEP(ecma_intl, spl)

  PHP_ADD_MAKEFILE_FRAGMENT
fi
