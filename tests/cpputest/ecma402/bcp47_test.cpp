#include "CppUTest/TestHarness.h"
#include "src/ecma402/bcp47.h"
#include "src/common.h"
#include <cstring>

#define TAG_TEST(group, name, input, expected)                                 \
  TEST(group, name) {                                                          \
    const char *icuLanguageTag = input;                                        \
    char *bcp47LanguageTag = NULL;                                             \
    int bcp47LanguageTagLen = 0;                                               \
    bcp47LanguageTag = (char *)malloc(sizeof(char *) * 157);                   \
    bcp47LanguageTagLen = icuToBcp47LanguageTag(icuLanguageTag,                \
                                                bcp47LanguageTag);             \
    STRCMP_EQUAL(expected, bcp47LanguageTag);                                  \
    LONGS_EQUAL(strlen(expected), bcp47LanguageTagLen);                        \
    free(bcp47LanguageTag);                                                    \
  };

#define TAG_TEST_FAILURE(group, name, input)                                   \
  TEST(group, name) {                                                          \
    const char *icuLanguageTag = input;                                        \
    char *bcp47LanguageTag = NULL;                                             \
    int bcp47LanguageTagLen = 0;                                               \
    bcp47LanguageTag = (char *)malloc(sizeof(char *) * 157);                   \
    bcp47LanguageTagLen = icuToBcp47LanguageTag(icuLanguageTag,                \
                                                bcp47LanguageTag);             \
    LONGS_EQUAL(ECMA_INTL_FAILURE, bcp47LanguageTagLen);                       \
    free(bcp47LanguageTag);                                                    \
  };

TEST_GROUP(ecma402Bcp47) {
};

TAG_TEST(ecma402Bcp47, expectedSuccess1, "en-US", "en-US")
TAG_TEST(ecma402Bcp47, expectedSuccess2, "en_US", "en-US")
TAG_TEST(ecma402Bcp47, expectedSuccess3, "de-DE", "de-DE")
TAG_TEST(ecma402Bcp47, expectedSuccess4, "de_DE", "de-DE")
TAG_TEST(ecma402Bcp47, expectedSuccess5, "es-MX", "es-MX")
TAG_TEST(ecma402Bcp47, expectedSuccess6, "es_MX", "es-MX")
TAG_TEST(ecma402Bcp47, expectedSuccess7, "fr-FR", "fr-FR")
TAG_TEST(ecma402Bcp47, expectedSuccess8, "fr_FR", "fr-FR")
TAG_TEST(ecma402Bcp47, expectedSuccess9, "_US", "und-US")
TAG_TEST(ecma402Bcp47, expectedSuccess10, "und-US", "und-US")
TAG_TEST(ecma402Bcp47, expectedSuccess11, "_Latn", "und-Latn")
TAG_TEST(ecma402Bcp47, expectedSuccess12, "und-latn", "und-Latn")
TAG_TEST(ecma402Bcp47, expectedSuccess13, "zh-hakka", "hak")
TAG_TEST(ecma402Bcp47, expectedSuccess14, "zh-cmn-CH-u-co-pinyin", "cmn-CH-u-co-pinyin")
TAG_TEST(ecma402Bcp47, expectedSuccess15, "en-latn-us", "en-Latn-US")
TAG_TEST(ecma402Bcp47, expectedSuccess16, "en-blah-foo-x-baz", "en-Blah")
TAG_TEST(
  ecma402Bcp47,
  expectectedSuccess17,
  "zh-cmn-Hans-CN-boont-u-kf-lower-co-trad-kn-false-ca-buddhist-nu-latn-hc-h24",
  "cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-false-nu-latn"
)
TAG_TEST(
    ecma402Bcp47,
    expectectedSuccess18,
    "cmn_Hans_CN_BOONT@calendar=buddhist;colcasefirst=lower;collation=traditional;colnumeric=no;hours=h24;numbers=latn",
    "cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-false-nu-latn"
)

TAG_TEST_FAILURE(ecma402Bcp47, expectedFailure1, "")
TAG_TEST_FAILURE(ecma402Bcp47, expectedFailure2, "1234")
TAG_TEST_FAILURE(ecma402Bcp47, expectedFailure3, "en-latn-us-co-foo")
