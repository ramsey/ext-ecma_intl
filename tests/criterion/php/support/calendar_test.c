#include "src/php/support/calendar.h"
#include "tests/criterion/test.h"

#define TEST_SUITE phpSupportCalendar

ParameterizedTestParameters(TEST_SUITE, getsCalendarCaseNameForValue) {
  START_BASIC_TEST_PARAMS(19)

  BASIC_TEST("buddhist", "Buddhist")
  BASIC_TEST("chinese", "Chinese")
  BASIC_TEST("coptic", "Coptic")
  BASIC_TEST("dangi", "Dangi")
  BASIC_TEST("ethioaa", "Ethioaa")
  BASIC_TEST("ethiopic", "Ethiopic")
  BASIC_TEST("gregory", "Gregory")
  BASIC_TEST("hebrew", "Hebrew")
  BASIC_TEST("indian", "Indian")
  BASIC_TEST("islamic", "Islamic")
  BASIC_TEST("islamic-civil", "IslamicCivil")
  BASIC_TEST("islamic-rgsa", "IslamicRgsa")
  BASIC_TEST("islamic-tbla", "IslamicTbla")
  BASIC_TEST("islamic-umalqura", "IslamicUmalqura")
  BASIC_TEST("iso8601", "Iso8601")
  BASIC_TEST("japanese", "Japanese")
  BASIC_TEST("persian", "Persian")
  BASIC_TEST("roc", "Roc")
  BASIC_TEST("foo", NULL)
  BASIC_TEST(NULL, NULL)

  END_BASIC_TEST_PARAMS;
}

BASIC_PARAMETERIZED_TEST(getsCalendarCaseNameForValue, getCalendarCaseName)
