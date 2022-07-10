#include "src/php/support/collation.h"
#include "tests/criterion/test.h"

#define TEST_SUITE phpSupportCollation

ParameterizedTestParameters(TEST_SUITE, getsCollationCaseNameForValue) {
  START_BASIC_TEST_PARAMS(21)

  BASIC_TEST("big5han", "Big5han")
  BASIC_TEST("compat", "Compat")
  BASIC_TEST("dict", "Dict")
  BASIC_TEST("direct", "Direct")
  BASIC_TEST("ducet", "Ducet")
  BASIC_TEST("emoji", "Emoji")
  BASIC_TEST("eor", "Eor")
  BASIC_TEST("gb2312", "Gb2312")
  BASIC_TEST("phonebk", "Phonebk")
  BASIC_TEST("phonetic", "Phonetic")
  BASIC_TEST("pinyin", "Pinyin")
  BASIC_TEST("reformed", "Reformed")
  BASIC_TEST("search", "Search")
  BASIC_TEST("searchjl", "Searchjl")
  BASIC_TEST("standard", "Standard")
  BASIC_TEST("stroke", "Stroke")
  BASIC_TEST("trad", "Trad")
  BASIC_TEST("unihan", "Unihan")
  BASIC_TEST("zhuyin", "Zhuyin")
  BASIC_TEST("foo", NULL)
  BASIC_TEST(NULL, NULL)

  END_BASIC_TEST_PARAMS;
}

BASIC_PARAMETERIZED_TEST(getsCollationCaseNameForValue, getCollationCaseName)
