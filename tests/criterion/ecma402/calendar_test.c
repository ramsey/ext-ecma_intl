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

  ADD_CALENDAR_TEST("en-US", 8, ECMA402_WEEKDAY);
  ADD_CALENDAR_TEST("en-US", 0, ECMA402_WEEKDAY);

  return cr_make_param_array(calendarTestParams, tests, index,
                             freeCalendarTestParams);
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

Test(TEST_SUITE, getsSupportedCalendarsFromCalendarKeyword) {
  const char **calendars;
  int calendarCount;

  calendars = (const char **)malloc(sizeof(const char *) * CALENDARS_CAPACITY);
  calendarCount = getSupportedCalendars("fa-IR-u-ca-gregory", calendars);

  cr_assert(eq(int, calendarCount, 1));
  cr_assert(eq(str, (char *)calendars[0], "gregory"));

  for (int i = 0; i < calendarCount; i++) {
    free((void *)calendars[i]);
  }
  free(calendars);
}

Test(TEST_SUITE, getsDefaultSupportedCalendarsForLocale) {
  const char **calendars;
  int calendarCount;

  calendars = (const char **)malloc(sizeof(const char *) * CALENDARS_CAPACITY);
  calendarCount = getSupportedCalendars("fa-IR", calendars);

  cr_assert(eq(int, calendarCount, 5));
  cr_assert(eq(str, (char *)calendars[0], "persian"));
  cr_assert(eq(str, (char *)calendars[1], "gregory"));
  cr_assert(eq(str, (char *)calendars[2], "islamic"));
  cr_assert(eq(str, (char *)calendars[3], "islamic-civil"));
  cr_assert(eq(str, (char *)calendars[4], "islamic-tbla"));

  for (int i = 0; i < calendarCount; i++) {
    free((void *)calendars[i]);
  }
  free(calendars);
}

Test(TEST_SUITE, getsWeekInfoForEnUs) {
  weekInfo *info = getWeekInfo("en-US");

  cr_assert(eq(int, info->firstDay, ECMA402_SUNDAY));
  cr_assert(eq(int, info->minimalDays, 1));
  cr_assert(eq(int, info->weekendLength, 2));
  cr_assert(eq(int, info->weekend[0], ECMA402_SATURDAY));
  cr_assert(eq(int, info->weekend[1], ECMA402_SUNDAY));

  freeWeekInfo(info);
}

Test(TEST_SUITE, getsWeekInfoForEnGb) {
  weekInfo *info = getWeekInfo("en-GB");

  cr_assert(eq(int, info->firstDay, ECMA402_MONDAY));
  cr_assert(eq(int, info->minimalDays, 4));
  cr_assert(eq(int, info->weekendLength, 2));
  cr_assert(eq(int, info->weekend[0], ECMA402_SATURDAY));
  cr_assert(eq(int, info->weekend[1], ECMA402_SUNDAY));

  freeWeekInfo(info);
}

Test(TEST_SUITE, getsWeekInfoForFaIr) {
  weekInfo *info = getWeekInfo("fa-IR");

  cr_assert(eq(int, info->firstDay, ECMA402_SATURDAY));
  cr_assert(eq(int, info->minimalDays, 1));
  cr_assert(eq(int, info->weekendLength, 1));
  cr_assert(eq(int, info->weekend[0], ECMA402_FRIDAY));

  freeWeekInfo(info);
}

Test(TEST_SUITE, getsWeekInfoForUnknownLocale) {
  weekInfo *info = getWeekInfo("");

  cr_assert(eq(int, info->firstDay, ECMA402_SUNDAY));
  cr_assert(eq(int, info->minimalDays, 1));
  cr_assert(eq(int, info->weekendLength, 2));
  cr_assert(eq(int, info->weekend[0], ECMA402_SATURDAY));
  cr_assert(eq(int, info->weekend[1], ECMA402_SUNDAY));

  freeWeekInfo(info);
}

Test(TEST_SUITE, initializesEmptyWeekInfo) {
  weekInfo *info = initEmptyWeekInfo();

  cr_assert(eq(int, info->firstDay, 0));
  cr_assert(eq(int, info->minimalDays, 0));
  cr_assert(eq(int, info->weekendLength, 0));
  cr_assert_not_null(info->weekend);

  freeWeekInfo(info);
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
