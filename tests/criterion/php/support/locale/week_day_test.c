#include "src/ecma402/calendar.h"
#include "src/php/support/locale/week_day.h"
#include "tests/criterion/test.h"

#define TEST_SUITE phpSupportLocaleWeekDay

typedef struct weekDayTestParams weekDayTestParams;

struct weekDayTestParams {
  int input;
  char *expected;
};

static void freeWeekDayTestParams(struct criterion_test_params *crp);
static int addWeekDayTest(struct weekDayTestParams *tests, int index, int input,
                          const char *expected);

ParameterizedTestParameters(TEST_SUITE, getsWeekDayCaseNameForDayOfWeek) {
  struct weekDayTestParams *tests;
  int index = 0;

  tests = cr_malloc(9 * sizeof(weekDayTestParams));
  index = addWeekDayTest(tests, index, ECMA402_MONDAY, "Monday");
  index = addWeekDayTest(tests, index, ECMA402_TUESDAY, "Tuesday");
  index = addWeekDayTest(tests, index, ECMA402_WEDNESDAY, "Wednesday");
  index = addWeekDayTest(tests, index, ECMA402_THURSDAY, "Thursday");
  index = addWeekDayTest(tests, index, ECMA402_FRIDAY, "Friday");
  index = addWeekDayTest(tests, index, ECMA402_SATURDAY, "Saturday");
  index = addWeekDayTest(tests, index, ECMA402_SUNDAY, "Sunday");
  index = addWeekDayTest(tests, index, 0, NULL);
  index = addWeekDayTest(tests, index, 8, NULL);

  return cr_make_param_array(struct weekDayTestParams, tests, index,
                             freeWeekDayTestParams);
}

ParameterizedTest(struct weekDayTestParams *test, TEST_SUITE,
                  getsWeekDayCaseNameForDayOfWeek) {
  const char *caseName = getWeekDayCaseNameByDayOfWeek(test->input);

  if (test->expected == NULL) {
    cr_assert_null(caseName);
  } else {
    cr_assert(eq(str, (char *)caseName, test->expected),
              "Expected case \"%s\" for value \"%d\"; got \"%s\"",
              test->expected, test->input, caseName);
  }
}

static void freeWeekDayTestParams(struct criterion_test_params *crp) {
  struct weekDayTestParams *params = (struct weekDayTestParams *)crp->params;

  for (size_t i = 0; i < crp->length; ++i) {
    if (params[i].expected != NULL) {
      cr_free(params[i].expected);
    }
  }

  cr_free(params);
}

static int addWeekDayTest(struct weekDayTestParams *tests, int index, int input,
                          const char *expected) {
  tests[index].input = input;

  if (expected != NULL) {
    tests[index].expected = testStrdup(expected);
  } else {
    tests[index].expected = NULL;
  }

  return ++index;
}
