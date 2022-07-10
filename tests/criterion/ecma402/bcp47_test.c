#include "src/ecma402/bcp47.h"
#include "tests/criterion/test.h"

#include <unicode/uloc.h>

#define TEST_SUITE ecma402Bcp47

ParameterizedTestParameters(TEST_SUITE, successfulLanguageTagConversion) {
  START_BASIC_TEST_PARAMS(18)

  BASIC_TEST("en-US", "en-US")
  BASIC_TEST("en_US", "en-US")
  BASIC_TEST("de-DE", "de-DE")
  BASIC_TEST("de_DE", "de-DE")
  BASIC_TEST("es-MX", "es-MX")
  BASIC_TEST("es_MX", "es-MX")
  BASIC_TEST("fr-FR", "fr-FR")
  BASIC_TEST("fr_FR", "fr-FR")
  BASIC_TEST("_US", "und-US")
  BASIC_TEST("und-US", "und-US")
  BASIC_TEST("_Latn", "und-Latn")
  BASIC_TEST("und-latn", "und-Latn")
  BASIC_TEST("zh-hakka", "hak")
  BASIC_TEST("zh-cmn-CH-u-co-pinyin", "cmn-CH-u-co-pinyin")
  BASIC_TEST("en-latn-us", "en-Latn-US")
  BASIC_TEST("en-blah-foo-x-baz", "en-Blah")

  BASIC_TEST("zh-cmn-Hans-CN-boont-u-kf-lower-co-trad-kn-false-ca-"
             "buddhist-nu-latn-hc-h24",
             "cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-"
             "false-nu-latn")

  BASIC_TEST("cmn_Hans_CN_BOONT@calendar=buddhist;colcasefirst=lower;"
             "collation=traditional;colnumeric=no;hours=h24;numbers=latn",
             "cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-"
             "false-nu-latn")

  END_BASIC_TEST_PARAMS;
}

ParameterizedTestParameters(TEST_SUITE, failedLanguageTagConversion) {
  char **tests = cr_malloc(sizeof(*tests) * 3);
  tests[0] = testStrdup("");
  tests[1] = testStrdup("1234");
  tests[2] = testStrdup("en-latn-us-co-foo");

  return cr_make_param_array(const char *, tests, 3, testFreeStrings);
}

ParameterizedTest(basicTestParams *test, ecma402Bcp47,
                  successfulLanguageTagConversion) {
  char *bcp47LanguageTag = NULL;

  bcp47LanguageTag = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  icuToBcp47LanguageTag(test->input, bcp47LanguageTag);

  cr_assert(
      eq(str, bcp47LanguageTag, test->expected),
      "Expected language tag \"%s\" to convert to \"%s\"; got \"%s\" instead",
      test->input, test->expected, bcp47LanguageTag);

  free(bcp47LanguageTag);
}

ParameterizedTest(char **input, TEST_SUITE, failedLanguageTagConversion) {
  char *bcp47LanguageTag = NULL;
  int bcp47LanguageTagLen;

  bcp47LanguageTag = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  bcp47LanguageTagLen = icuToBcp47LanguageTag(*input, bcp47LanguageTag);

  cr_assert(eq(int, bcp47LanguageTagLen, ECMA_INTL_FAILURE),
            "Expected language tag \"%s\" to fail", *input);

  free(bcp47LanguageTag);
}
