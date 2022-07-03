#include "src/common.h"
#include "src/ecma402/bcp47.h"

#include <criterion/parameterized.h>

#include <criterion/new/assert.h>
#include <string.h>
#include <unicode/uloc.h>

typedef struct tagParam {
  char *input;
  char *expected;
} tagParam;

void cr_freeStrings(struct criterion_test_params *crp) {
  char **strings = (char **)crp->params;
  for (size_t i = 0; i < crp->length; ++i) {
    cr_free(strings[i]);
  }
  cr_free(strings);
}

void cr_freeTagParams(struct criterion_test_params *crp) {
  struct tagParam **params = (struct tagParam **)crp->params;
  for (size_t i = 0; i < crp->length; ++i) {
    cr_free(params[i]->expected);
    cr_free(params[i]->input);
  }
  cr_free(params);
}

char *cr_strdup(const char *str) {
  char *ptr = cr_malloc(strlen(str) + 1);
  if (ptr) {
    strcpy(ptr, str);
  }
  return ptr;
}

int addTest(struct tagParam *tests, int index, const char *input,
            const char *expected) {
  tests[index].input = cr_strdup(input);
  tests[index].expected = cr_strdup(expected);

  return ++index;
}

ParameterizedTestParameters(ecma402Bcp47, successfulLanguageTagConversion) {
  struct tagParam *tests;
  int index = 0;

  tests = malloc(100 * sizeof(tagParam));
  index = addTest(tests, index, "en-US", "en-US");
  index = addTest(tests, index, "en_US", "en-US");
  index = addTest(tests, index, "de-DE", "de-DE");
  index = addTest(tests, index, "de_DE", "de-DE");
  index = addTest(tests, index, "es-MX", "es-MX");
  index = addTest(tests, index, "es_MX", "es-MX");
  index = addTest(tests, index, "fr-FR", "fr-FR");
  index = addTest(tests, index, "fr_FR", "fr-FR");
  index = addTest(tests, index, "_US", "und-US");
  index = addTest(tests, index, "und-US", "und-US");
  index = addTest(tests, index, "_Latn", "und-Latn");
  index = addTest(tests, index, "und-latn", "und-Latn");
  index = addTest(tests, index, "zh-hakka", "hak");
  index = addTest(tests, index, "zh-cmn-CH-u-co-pinyin", "cmn-CH-u-co-pinyin");
  index = addTest(tests, index, "en-latn-us", "en-Latn-US");
  index = addTest(tests, index, "en-blah-foo-x-baz", "en-Blah");

  index = addTest(tests, index,
                  "zh-cmn-Hans-CN-boont-u-kf-lower-co-trad-kn-false-ca-"
                  "buddhist-nu-latn-hc-h24",
                  "cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-"
                  "false-nu-latn");

  index = addTest(tests, index,
                  "cmn_Hans_CN_BOONT@calendar=buddhist;colcasefirst=lower;"
                  "collation=traditional;colnumeric=no;hours=h24;numbers=latn",
                  "cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-"
                  "false-nu-latn");

  return cr_make_param_array(struct tagParam, tests, index, cr_freeTagParams);
}

ParameterizedTestParameters(ecma402Bcp47, failedLanguageTagConversion) {
  char **tests = cr_malloc(sizeof(*tests) * 3);
  tests[0] = cr_strdup("");
  tests[1] = cr_strdup("1234");
  tests[2] = cr_strdup("en-latn-us-co-foo");

  return cr_make_param_array(const char *, tests, 3, cr_freeStrings);
}

ParameterizedTest(struct tagParam *test, ecma402Bcp47,
                  successfulLanguageTagConversion) {
  char *bcp47LanguageTag = NULL;
  int bcp47LanguageTagLen;

  bcp47LanguageTag = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  bcp47LanguageTagLen = icuToBcp47LanguageTag(test->input, bcp47LanguageTag);

  cr_assert(eq(str, bcp47LanguageTag, test->expected));
  cr_assert(eq(int, bcp47LanguageTagLen, strlen(test->expected)));

  free(bcp47LanguageTag);
}

ParameterizedTest(char **input, ecma402Bcp47, failedLanguageTagConversion) {
  char *bcp47LanguageTag = NULL;
  int bcp47LanguageTagLen;

  bcp47LanguageTag = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  bcp47LanguageTagLen = icuToBcp47LanguageTag(*input, bcp47LanguageTag);

  cr_assert(eq(int, bcp47LanguageTagLen, ECMA_INTL_FAILURE));

  free(bcp47LanguageTag);
}
