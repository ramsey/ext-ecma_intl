#include "src/ecma402/category.h"
#include "tests/criterion/test.h"

#define TEST_SUITE ecma402Category

#define CATEGORY_VALUES_TEST(name, category)                                   \
  Test(TEST_SUITE, getsSupportedValuesFor##name##Category) {                   \
    const char **values = NULL;                                                \
    int count;                                                                 \
    values =                                                                   \
        (const char **)malloc(sizeof(const char *) * category##_CAPACITY);     \
    count = getSupportedValuesForCategory(category, values);                   \
    cr_assert_not_null(values);                                                \
    cr_assert_gt(count, 1);                                                    \
    if (values) {                                                              \
      for (int i = 0; i < count; i++) {                                        \
        free((void *)values[i]);                                               \
      }                                                                        \
      free(values);                                                            \
    }                                                                          \
  }

#define CATEGORY_CAPACITY_TEST(name, category, expectedCapacity)               \
  Test(TEST_SUITE, getsCapacityFor##name##Category) {                          \
    int actualCapacity = getCapacityForCategory(category);                     \
    cr_assert(eq(int, actualCapacity, expectedCapacity));                      \
  }

CATEGORY_VALUES_TEST(Calendar, CATEGORY_CALENDAR)
CATEGORY_VALUES_TEST(Collation, CATEGORY_COLLATION)
CATEGORY_VALUES_TEST(Currency, CATEGORY_CURRENCY)
CATEGORY_VALUES_TEST(NumberingSystem, CATEGORY_NUMBERING_SYSTEM)
CATEGORY_VALUES_TEST(TimeZone, CATEGORY_TIME_ZONE)
CATEGORY_VALUES_TEST(Unit, CATEGORY_UNIT)

CATEGORY_CAPACITY_TEST(Calendar, CATEGORY_CALENDAR, CATEGORY_CALENDAR_CAPACITY)
CATEGORY_CAPACITY_TEST(Collation, CATEGORY_COLLATION,
                       CATEGORY_COLLATION_CAPACITY)
CATEGORY_CAPACITY_TEST(Currency, CATEGORY_CURRENCY, CATEGORY_CURRENCY_CAPACITY)
CATEGORY_CAPACITY_TEST(NumberingSystem, CATEGORY_NUMBERING_SYSTEM,
                       CATEGORY_NUMBERING_SYSTEM_CAPACITY)
CATEGORY_CAPACITY_TEST(TimeZone, CATEGORY_TIME_ZONE,
                       CATEGORY_TIME_ZONE_CAPACITY)
CATEGORY_CAPACITY_TEST(Unit, CATEGORY_UNIT, CATEGORY_UNIT_CAPACITY)

Test(TEST_SUITE, getsSupportedValuesForInvalidCategory) {
  const char **values;
  int count;

  values = (const char **)malloc(sizeof(const char *) * 1);
  count = getSupportedValuesForCategory("foo", values);

  cr_assert(eq(int, count, 0));

  free(values);
}

Test(TEST_SUITE, calendarValuesAreBcp47Values) {
  const char **values = NULL;
  int count;

  values =
      (const char **)malloc(sizeof(const char *) * CATEGORY_CALENDAR_CAPACITY);
  count = getSupportedValuesForCategory(CATEGORY_CALENDAR, values);

  for (int i = 0; i < count; i++) {
    if (strcmp(values[i], "gregorian") == 0) {
      cr_fail(
          "Expected \"gregory\" but found \"gregorian\" in calendar values");
    }

    if (strcmp(values[i], "ethiopic-amete-alem") == 0) {
      cr_fail("Expected \"ethioaa\" but found \"ethiopic-amete-alem\" in "
              "calendar values");
    }
  }

  if (values) {
    for (int i = 0; i < count; i++) {
      free((void *)values[i]);
    }
    free(values);
  }
}

Test(TEST_SUITE, collationValuesAreBcp47Values) {
  const char **values = NULL;
  int count;

  values =
      (const char **)malloc(sizeof(const char *) * CATEGORY_COLLATION_CAPACITY);
  count = getSupportedValuesForCategory(CATEGORY_COLLATION, values);

  for (int i = 0; i < count; i++) {
    if (strcmp(values[i], "dictionary") == 0) {
      cr_fail("Expected \"dict\" but found \"dictionary\" in collation values");
    }

    if (strcmp(values[i], "gb2312han") == 0) {
      cr_fail(
          "Expected \"gb2312\" but found \"gb2312han\" in collation values");
    }

    if (strcmp(values[i], "phonebook") == 0) {
      cr_fail(
          "Expected \"phonebk\" but found \"phonebook\" in collation values");
    }

    if (strcmp(values[i], "traditional") == 0) {
      cr_fail(
          "Expected \"trad\" but found \"traditional\" in collation values");
    }
  }

  if (values) {
    for (int i = 0; i < count; i++) {
      free((void *)values[i]);
    }
    free(values);
  }
}

Test(TEST_SUITE, unitValuesDoNotHaveAnyEmptyStrings) {
  const char **values = NULL;
  int count;

  values = (const char **)malloc(sizeof(const char *) * CATEGORY_UNIT_CAPACITY);
  count = getSupportedValuesForCategory(CATEGORY_UNIT, values);

  for (int i = 0; i < count; i++) {
    if (strcmp(values[i], "") == 0) {
      cr_fail("Found an unexpected empty string value");
    }
  }

  if (values) {
    for (int i = 0; i < count; i++) {
      free((void *)values[i]);
    }
    free(values);
  }
}
