#include "src/ecma402/calendar.h"
#include "tests/criterion/test.h"

typedef struct testParams {
  char *localeId;
  int day;
  int expected;
} testParams;

static void freeTestParams(struct criterion_test_params *crp) {
  struct testParams *params = (struct testParams *)crp->params;
  for (size_t i = 0; i < crp->length; ++i) {
    if (params[i].localeId) {
      cr_free(params[i].localeId);
    }
  }
  cr_free(params);
}

static int addTest(struct testParams *tests, int index, const char *localeId,
                   int day, int expected) {
  if (localeId == NULL) {
    tests[index].localeId = NULL;
  } else {
    tests[index].localeId = test_strdup(localeId);
  }

  tests[index].day = day;
  tests[index].expected = expected;

  return ++index;
}

ParameterizedTestParameters(ecma402Calendar, foo) {
  struct testParams *tests;
  int index = 0;

  tests = cr_malloc(2 * sizeof(testParams));
  index = addTest(tests, index, "en-US", ECMA402_MONDAY, ECMA402_WEEKDAY);
  index = addTest(tests, index, "en-US", ECMA402_TUESDAY, ECMA402_WEEKDAY);
  index = addTest(tests, index, "en-US", ECMA402_WEDNESDAY, ECMA402_WEEKDAY);
  index = addTest(tests, index, "en-US", ECMA402_THURSDAY, ECMA402_WEEKDAY);
  index = addTest(tests, index, "en-US", ECMA402_FRIDAY, ECMA402_WEEKDAY);
  index = addTest(tests, index, "en-US", ECMA402_SATURDAY, ECMA402_WEEKEND);
  index = addTest(tests, index, "en-US", ECMA402_SUNDAY, ECMA402_WEEKEND);

  index = addTest(tests, index, "ar-OM", ECMA402_MONDAY, ECMA402_WEEKDAY);
  index = addTest(tests, index, "ar-OM", ECMA402_TUESDAY, ECMA402_WEEKDAY);
  index = addTest(tests, index, "ar-OM", ECMA402_WEDNESDAY, ECMA402_WEEKDAY);
  index = addTest(tests, index, "ar-OM", ECMA402_THURSDAY, ECMA402_WEEKDAY);
  index = addTest(tests, index, "ar-OM", ECMA402_FRIDAY, ECMA402_WEEKEND);
  index = addTest(tests, index, "ar-OM", ECMA402_SATURDAY, ECMA402_WEEKEND);
  index = addTest(tests, index, "ar-OM", ECMA402_SUNDAY, ECMA402_WEEKDAY);

  index = addTest(tests, index, "en-US", 8, ECMA_INTL_FAILURE);
  index = addTest(tests, index, "en-US", 0, ECMA_INTL_FAILURE);

  return cr_make_param_array(struct testParams, tests, index, freeTestParams);
}

ParameterizedTest(struct testParams *test, ecma402Calendar, foo) {
  int weekdayType = ecma402_getDayOfWeekType(test->localeId, test->day);

  cr_assert(eq(int, weekdayType, test->expected),
            "Expected %d for day %d in locale \"%s\"; got %d", test->expected,
            test->day, test->localeId, weekdayType);
}
