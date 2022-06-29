#include "CppUTest/TestHarness.h"
#include "src/ecma402/bcp47.h"

TEST_GROUP(UnicodeBcp47) {
};

TEST(UnicodeBcp47, FirstTest) {
  const char *icuLanguageTag = "en_US";
  char *bcp47LanguageTag = NULL;
  int bcp47LanguageTagLen = 0;

  bcp47LanguageTag = (char *)malloc(sizeof(char *) * 157);
  bcp47LanguageTagLen = icuToBcp47LanguageTag(icuLanguageTag, bcp47LanguageTag);

  STRCMP_EQUAL("en-US", bcp47LanguageTag);
  LONGS_EQUAL(5, bcp47LanguageTagLen);

  free(bcp47LanguageTag);
};
