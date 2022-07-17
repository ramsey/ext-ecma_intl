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
    src/ecma402/calendar.c                                                     \
    src/ecma402/category.c                                                     \
    src/ecma402/collation.c                                                    \
    src/ecma402/error.c                                                        \
    src/ecma402/hour_cycle.c                                                   \
    src/ecma402/locale.c                                                       \
    src/ecma402/numbering_system.c                                             \
    src/ecma402/text_direction.c                                               \
    src/ecma402/time_zone.c                                                    \
    src/php/classes/calendar.c                                                 \
    src/php/classes/case_first.c                                               \
    src/php/classes/category.c                                                 \
    src/php/classes/collation.c                                                \
    src/php/classes/exception.c                                                \
    src/php/classes/formatting.c                                               \
    src/php/classes/hour_cycle.c                                               \
    src/php/classes/icu_exception.c                                            \
    src/php/classes/intl.c                                                     \
    src/php/classes/locale.c                                                   \
    src/php/classes/locale/options.c                                           \
    src/php/classes/locale/text_direction.c                                    \
    src/php/classes/locale/text_info.c                                         \
    src/php/classes/locale/week_day.c                                          \
    src/php/classes/locale/week_info.c                                         \
    src/php/classes/locale_matcher.c                                           \
    src/php/classes/numbering_system.c                                         \
    src/php/classes/range_error.c                                              \
    src/php/ecma_intl.c                                                        \
    src/php/support/calendar.c                                                 \
    src/php/support/case_first.c                                               \
    src/php/support/collation.c                                                \
    src/php/support/hour_cycle.c                                               \
    src/php/support/locale/text_direction.c                                    \
    src/php/support/locale/week_day.c                                          \
    src/php/support/numbering_system.c                                         \
    "

  PHP_ECMA_INTL_CXX_SOURCES="                                                  \
    src/ecma402/localeBuilder.cpp                                              \
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
      src/ecma402/calendar.c                                                   \
      src/ecma402/category.c                                                   \
      src/ecma402/collation.c                                                  \
      src/ecma402/error.c                                                      \
      src/ecma402/hour_cycle.c                                                 \
      src/ecma402/locale.c                                                     \
      src/ecma402/localeBuilder.cpp                                            \
      src/ecma402/numbering_system.c                                           \
      src/ecma402/text_direction.c                                             \
      src/ecma402/time_zone.c                                                  \
      src/ecma402/units.cpp                                                    \
      src/php/support/calendar.c                                               \
      src/php/support/case_first.c                                             \
      src/php/support/collation.c                                              \
      src/php/support/hour_cycle.c                                             \
      src/php/support/locale/text_direction.c                                  \
      src/php/support/locale/week_day.c                                        \
      src/php/support/numbering_system.c                                       \
      tests/criterion/ecma402/bcp47_test.c                                     \
      tests/criterion/ecma402/calendar_test.c                                  \
      tests/criterion/ecma402/category_test.c                                  \
      tests/criterion/ecma402/collation_test.c                                 \
      tests/criterion/ecma402/error_test.c                                     \
      tests/criterion/ecma402/hour_cycle_test.c                                \
      tests/criterion/ecma402/localeBuilder_test.c                             \
      tests/criterion/ecma402/locale_test.c                                    \
      tests/criterion/ecma402/numbering_system_test.c                          \
      tests/criterion/ecma402/text_direction_test.c                            \
      tests/criterion/ecma402/time_zone_test.c                                 \
      tests/criterion/ecma402/units_test.c                                     \
      tests/criterion/php/support/calendar_test.c                              \
      tests/criterion/php/support/case_first_test.c                            \
      tests/criterion/php/support/collation_test.c                             \
      tests/criterion/php/support/hour_cycle_test.c                            \
      tests/criterion/php/support/locale/text_direction_test.c                 \
      tests/criterion/php/support/locale/week_day_test.c                       \
      tests/criterion/php/support/numbering_system_test.c                      \
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
