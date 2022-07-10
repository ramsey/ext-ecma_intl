#include "src/php/support/case_first.h"
#include "tests/criterion/test.h"

#define TEST_SUITE phpSupportCaseFirst

ParameterizedTestParameters(TEST_SUITE, getsCaseFirstCaseNameForValue) {
  START_BASIC_TEST_PARAMS(7)

  BASIC_TEST("false", "False")
  BASIC_TEST("no", "False")
  BASIC_TEST("lower", "Lower")
  BASIC_TEST("upper", "Upper")
  BASIC_TEST("yes", "Upper")
  BASIC_TEST("foo", NULL)
  BASIC_TEST(NULL, NULL)

  END_BASIC_TEST_PARAMS;
}

BASIC_PARAMETERIZED_TEST(getsCaseFirstCaseNameForValue, getCaseFirstCaseName)
