m4_include([m4/tests.m4])

PHP_ARG_ENABLE(
  [ecma_intl],
  [for i18n support, Ecma-style (ECMA-402)],
  [AS_HELP_STRING(
    [--enable-ecma_intl],
    [Enable i18n support, Ecma-style (ECMA-402)])
  ],
  [yes]
)

PHP_ARG_ENABLE(
  [criterion],
  [whether to enable support for Criterion tests],
  [AS_HELP_STRING(
    [--enable-criterion],
    [Enable support for running Criterion tests (development only)])
  ],
  [no],
  [no]
)

if test "$PHP_ECMA_INTL" != "no"; then
  PKG_CHECK_MODULES([ICU], [icu-uc >= 67.1 icu-i18n icu-io])

  PHP_EVAL_INCLINE($ICU_CFLAGS)
  PHP_EVAL_LIBLINE($ICU_LIBS, ECMA_INTL_SHARED_LIBADD)

  PHP_SUBST(ECMA_INTL_SHARED_LIBADD)
  AC_DEFINE(HAVE_ECMA_INTL, 1, [ Have ecma_intl support ])

  ECMA_INTL_COMMON_FLAGS="$ICU_CFLAGS"

  PHP_ECMA_INTL_C_SOURCES="                                                    \
    src/ecma402/bcp47.c                                                        \
    src/php/classes/php_enums_ce.c                                             \
    src/php/classes/php_exceptions_ce.c                                        \
    src/php/classes/php_intl_ce.c                                              \
    src/php/ecma_intl.c                                                        \
    "

  PHP_ECMA_INTL_CXX_SOURCES="                                                  \
    src/ecma402/units.cpp                                                      \
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

  EXTRA_CXXFLAGS="$PHP_ECMA_INTL_STDCXX $ICU_CXXFLAGS"
  PHP_SUBST(EXTRA_CXXFLAGS)

  if test "$ext_shared" = "no"; then
    PHP_ADD_SOURCES(
      PHP_EXT_DIR(ecma_intl),
      $PHP_ECMA_INTL_CXX_SOURCES,
      $ECMA_INTL_COMMON_FLAGS
    )
  else
    PHP_ADD_SOURCES_X(
      PHP_EXT_DIR(ecma_intl),
      $PHP_ECMA_INTL_CXX_SOURCES,
      $ECMA_INTL_COMMON_FLAGS,
      shared_objects_ecma_intl,
      yes
    )
  fi

  PHP_ADD_EXTENSION_DEP(ecma_intl, spl)

  PHP_ADD_MAKEFILE_FRAGMENT

  if test "$PHP_CRITERION" != "no"; then
    PKG_CHECK_MODULES([CRITERION], [criterion])

    PHP_EVAL_INCLINE($CRITERION_CFLAGS)
    PHP_EVAL_LIBLINE($CRITERION_LIBS, CRITERION_LIBS)

    PHP_SUBST(CRITERION_LIBS)
    AC_DEFINE(HAVE_CRITERION, 1, [ Have Criterion support ])

    TEST_SOURCES="                                                             \
      src/ecma402/bcp47.c                                                      \
      src/ecma402/units.cpp                                                    \
      tests/criterion/ecma402/bcp47_test.c                                     \
      tests/criterion/ecma402/units_test.c                                     \
      tests/criterion/test.c                                                   \
      "

    TEST_ADD_SOURCES(
      PHP_EXT_DIR(ecma_intl),
      $TEST_SOURCES,
      $ICU_CFLAGS,
      criterion_objects,
    )

    PHP_SUBST(criterion_objects)
  fi
fi
