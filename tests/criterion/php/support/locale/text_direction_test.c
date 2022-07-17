#include "src/php/support/locale/text_direction.h"
#include "tests/criterion/test.h"

#define TEST_SUITE phpSupportLocaleTextDirection

typedef struct textDirectionTestParams textDirectionTestParams;

struct textDirectionTestParams {
  int input;
  char *expected;
};

static void freeTextDirectionTestParams(struct criterion_test_params *crp);
static int addTextDirectionTest(struct textDirectionTestParams *tests,
                                int index, int input, const char *expected);

ParameterizedTestParameters(TEST_SUITE, getsTextDirectionCaseNameForValue) {
  START_BASIC_TEST_PARAMS(6)

  BASIC_TEST("btt", "BottomToTop")
  BASIC_TEST("ltr", "LeftToRight")
  BASIC_TEST("rtl", "RightToLeft")
  BASIC_TEST("ttb", "TopToBottom")
  BASIC_TEST("foo", "LeftToRight")
  BASIC_TEST(NULL, "LeftToRight")

  END_BASIC_TEST_PARAMS;
}

ParameterizedTestParameters(TEST_SUITE,
                            getsTextDirectionCaseNameForULayoutType) {
  struct textDirectionTestParams *tests;
  int index = 0;

  tests = cr_malloc(5 * sizeof(textDirectionTestParams));
  index = addTextDirectionTest(tests, index, ULOC_LAYOUT_BTT, "BottomToTop");
  index = addTextDirectionTest(tests, index, ULOC_LAYOUT_LTR, "LeftToRight");
  index = addTextDirectionTest(tests, index, ULOC_LAYOUT_RTL, "RightToLeft");
  index = addTextDirectionTest(tests, index, ULOC_LAYOUT_TTB, "TopToBottom");
  index = addTextDirectionTest(tests, index, 18, "LeftToRight");

  return cr_make_param_array(struct textDirectionTestParams, tests, index,
                             freeTextDirectionTestParams);
}

ParameterizedTestParameters(TEST_SUITE,
                            getsTextDirectionCaseNameForTextDirection) {
  struct textDirectionTestParams *tests;
  int index = 0;

  tests = cr_malloc(5 * sizeof(textDirectionTestParams));
  index = addTextDirectionTest(tests, index, BOTTOM_TO_TOP, "BottomToTop");
  index = addTextDirectionTest(tests, index, LEFT_TO_RIGHT, "LeftToRight");
  index = addTextDirectionTest(tests, index, RIGHT_TO_LEFT, "RightToLeft");
  index = addTextDirectionTest(tests, index, TOP_TO_BOTTOM, "TopToBottom");
  index = addTextDirectionTest(tests, index, 14, "LeftToRight");

  return cr_make_param_array(struct textDirectionTestParams, tests, index,
                             freeTextDirectionTestParams);
}

BASIC_PARAMETERIZED_TEST(getsTextDirectionCaseNameForValue,
                         getTextDirectionCaseName)

ParameterizedTest(struct textDirectionTestParams *test, TEST_SUITE,
                  getsTextDirectionCaseNameForULayoutType) {
  const char *caseName = getTextDirectionCaseNameByLayoutType(test->input);

  cr_assert(eq(str, (char *)caseName, test->expected),
            "Expected case \"%s\" for value \"%d\"; got \"%s\"", test->expected,
            test->input, caseName);
}

ParameterizedTest(struct textDirectionTestParams *test, TEST_SUITE,
                  getsTextDirectionCaseNameForTextDirection) {
  const char *caseName = getTextDirectionCaseNameByTextDirection(test->input);

  cr_assert(eq(str, (char *)caseName, test->expected),
            "Expected case \"%s\" for value \"%d\"; got \"%s\"", test->expected,
            test->input, caseName);
}

static void freeTextDirectionTestParams(struct criterion_test_params *crp) {
  struct textDirectionTestParams *params =
      (struct textDirectionTestParams *)crp->params;

  for (size_t i = 0; i < crp->length; ++i) {
    cr_free(params[i].expected);
  }

  cr_free(params);
}

static int addTextDirectionTest(struct textDirectionTestParams *tests,
                                int index, int input, const char *expected) {
  tests[index].input = input;
  tests[index].expected = testStrdup(expected);

  return ++index;
}
