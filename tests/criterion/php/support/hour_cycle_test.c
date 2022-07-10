#include "src/php/support/hour_cycle.h"
#include "tests/criterion/test.h"

#include <unicode/udat.h>

#define TEST_SUITE phpSupportHourCycle

typedef struct hourCycleTestParams hourCycleTestParams;

struct hourCycleTestParams {
  int input;
  char *expected;
};

static void freeHourCycleTestParams(struct criterion_test_params *crp);
static int addHourCycleTest(struct hourCycleTestParams *tests, int index,
                            int input, const char *expected);

ParameterizedTestParameters(TEST_SUITE, getsHourCycleCaseNameForValue) {
  START_BASIC_TEST_PARAMS(6)

  BASIC_TEST("h11", "H11")
  BASIC_TEST("h12", "H12")
  BASIC_TEST("h23", "H23")
  BASIC_TEST("h24", "H24")
  BASIC_TEST("foo", NULL)
  BASIC_TEST(NULL, NULL)

  END_BASIC_TEST_PARAMS;
}

ParameterizedTestParameters(TEST_SUITE,
                            getsHourCycleCaseNameForUDateFormatHourCycle) {
  struct hourCycleTestParams *tests;
  int index = 0;

  tests = cr_malloc(5 * sizeof(hourCycleTestParams));
  index = addHourCycleTest(tests, index, UDAT_HOUR_CYCLE_11, "H11");
  index = addHourCycleTest(tests, index, UDAT_HOUR_CYCLE_12, "H12");
  index = addHourCycleTest(tests, index, UDAT_HOUR_CYCLE_23, "H23");
  index = addHourCycleTest(tests, index, UDAT_HOUR_CYCLE_24, "H24");
  index = addHourCycleTest(tests, index, 24, NULL);

  return cr_make_param_array(struct hourCycleTestParams, tests, index,
                             freeHourCycleTestParams);
}

BASIC_PARAMETERIZED_TEST(getsHourCycleCaseNameForValue, getHourCycleCaseName)

ParameterizedTest(struct hourCycleTestParams *test, TEST_SUITE,
                  getsHourCycleCaseNameForUDateFormatHourCycle) {
  const char *caseName = getHourCycleCaseNameByHourCycle(test->input);

  if (test->expected == NULL) {
    cr_assert_null(caseName);
  } else {
    cr_assert(eq(str, (char *)caseName, test->expected),
              "Expected case \"%s\" for value \"%d\"; got \"%s\"",
              test->expected, test->input, caseName);
  }
}

static void freeHourCycleTestParams(struct criterion_test_params *crp) {
  struct hourCycleTestParams *params =
      (struct hourCycleTestParams *)crp->params;

  for (size_t i = 0; i < crp->length; ++i) {
    if (params[i].expected != NULL) {
      cr_free(params[i].expected);
    }
  }

  cr_free(params);
}

static int addHourCycleTest(struct hourCycleTestParams *tests, int index,
                            int input, const char *expected) {
  tests[index].input = input;

  if (expected != NULL) {
    tests[index].expected = testStrdup(expected);
  } else {
    tests[index].expected = NULL;
  }

  return ++index;
}
