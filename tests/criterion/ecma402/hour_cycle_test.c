#include "src/ecma402/hour_cycle.h"
#include "tests/criterion/test.h"

#define TEST_SUITE ecma402HourCycle

Test(TEST_SUITE, getsSupportedHourCyclesFromHourCycleKeyword) {
  const char **hourCycles;
  int hourCycleCount;

  hourCycles =
      (const char **)malloc(sizeof(const char *) * HOUR_CYCLES_CAPACITY);
  hourCycleCount = getSupportedHourCycles("de-DE-u-hc-h11", hourCycles);

  cr_assert(eq(int, hourCycleCount, 1));
  cr_assert(eq(str, (char *)hourCycles[0], "h11"));

  for (int i = 0; i < hourCycleCount; i++) {
    free((void *)hourCycles[i]);
  }
  free(hourCycles);
}

Test(TEST_SUITE, getsDefaultSupportedHourCyclesForLocale) {
  const char **hourCycles;
  int hourCycleCount;

  hourCycles =
      (const char **)malloc(sizeof(const char *) * HOUR_CYCLES_CAPACITY);
  hourCycleCount = getSupportedHourCycles("de-DE", hourCycles);

  cr_assert(eq(int, hourCycleCount, 1));
  cr_assert(eq(str, (char *)hourCycles[0], "h23"));

  for (int i = 0; i < hourCycleCount; i++) {
    free((void *)hourCycles[i]);
  }
  free(hourCycles);
}
