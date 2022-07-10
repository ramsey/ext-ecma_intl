#include "src/ecma402/calendar.h"
#include "tests/criterion/test.h"

#define TEST_SUITE ecma402Calendar

#define ADD_CALENDAR_TEST(localeId, day, expected)                             \
  index = addCalendarTest(tests, index, localeId, day, expected)

typedef struct calendarTestParams calendarTestParams;

struct calendarTestParams {
  char *localeId;
  int day;
  int expected;
};

static void freeCalendarTestParams(struct criterion_test_params *crp);
static int addCalendarTest(calendarTestParams *tests, int index,
                           const char *localeId, int day, int expected);

ParameterizedTestParameters(TEST_SUITE, getsExpectedDayOfTheWeekType) {
  calendarTestParams *tests;
  int index = 0;

  tests = cr_malloc(16 * sizeof(calendarTestParams));
  ADD_CALENDAR_TEST("en-US", ECMA402_MONDAY, ECMA402_WEEKDAY);
  ADD_CALENDAR_TEST("en-US", ECMA402_TUESDAY, ECMA402_WEEKDAY);
  ADD_CALENDAR_TEST("en-US", ECMA402_WEDNESDAY, ECMA402_WEEKDAY);
  ADD_CALENDAR_TEST("en-US", ECMA402_THURSDAY, ECMA402_WEEKDAY);
  ADD_CALENDAR_TEST("en-US", ECMA402_FRIDAY, ECMA402_WEEKDAY);
  ADD_CALENDAR_TEST("en-US", ECMA402_SATURDAY, ECMA402_WEEKEND);
  ADD_CALENDAR_TEST("en-US", ECMA402_SUNDAY, ECMA402_WEEKEND);

  ADD_CALENDAR_TEST("ar-OM", ECMA402_MONDAY, ECMA402_WEEKDAY);
  ADD_CALENDAR_TEST("ar-OM", ECMA402_TUESDAY, ECMA402_WEEKDAY);
  ADD_CALENDAR_TEST("ar-OM", ECMA402_WEDNESDAY, ECMA402_WEEKDAY);
  ADD_CALENDAR_TEST("ar-OM", ECMA402_THURSDAY, ECMA402_WEEKDAY);
  ADD_CALENDAR_TEST("ar-OM", ECMA402_FRIDAY, ECMA402_WEEKEND);
  ADD_CALENDAR_TEST("ar-OM", ECMA402_SATURDAY, ECMA402_WEEKEND);
  ADD_CALENDAR_TEST("ar-OM", ECMA402_SUNDAY, ECMA402_WEEKDAY);

  ADD_CALENDAR_TEST("en-US", 8, ECMA_INTL_FAILURE);
  ADD_CALENDAR_TEST("en-US", 0, ECMA_INTL_FAILURE);

  return cr_make_param_array(calendarTestParams, tests, index,
                             freeCalendarTestParams);
  ;
}

ParameterizedTest(calendarTestParams *test, TEST_SUITE,
                  getsExpectedDayOfTheWeekType) {
  int weekdayType = getDayOfWeekType(test->localeId, test->day);

  cr_assert(eq(int, weekdayType, test->expected),
            "Expected %d for day %d in locale \"%s\"; got %d", test->expected,
            test->day, test->localeId, weekdayType);
}

ParameterizedTestParameters(TEST_SUITE, getsExpectedFirstDayOfTheWeek) {
  calendarTestParams *tests;
  int index = 0;

  tests = cr_malloc(3 * sizeof(calendarTestParams));

  // We're setting the day parameter to 0 because it's not used for these tests.
  ADD_CALENDAR_TEST("en-US", 0, ECMA402_SUNDAY);
  ADD_CALENDAR_TEST("en-GB", 0, ECMA402_MONDAY);
  ADD_CALENDAR_TEST("fa-IR", 0, ECMA402_SATURDAY);

  return cr_make_param_array(calendarTestParams, tests, index,
                             freeCalendarTestParams);
}

ParameterizedTest(calendarTestParams *test, TEST_SUITE,
                  getsExpectedFirstDayOfTheWeek) {
  int dayOfWeek = getFirstDayOfWeek(test->localeId);

  cr_assert(eq(int, dayOfWeek, test->expected),
            "Expected %d for locale \"%s\"; got %d", test->expected,
            test->localeId, dayOfWeek);
}

static void freeCalendarTestParams(struct criterion_test_params *crp) {
  calendarTestParams *params = (calendarTestParams *)crp->params;
  for (size_t i = 0; i < crp->length; ++i) {
    if (params[i].localeId) {
      cr_free(params[i].localeId);
    }
  }
  cr_free(params);
}

static int addCalendarTest(calendarTestParams *tests, int index,
                           const char *localeId, int day, int expected) {
  if (localeId == NULL) {
    tests[index].localeId = NULL;
  } else {
    tests[index].localeId = testStrdup(localeId);
  }

  tests[index].day = day;
  tests[index].expected = expected;

  return ++index;
}
