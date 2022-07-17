#include "src/ecma402/time_zone.h"
#include "tests/criterion/test.h"

#define TEST_SUITE ecma402TimeZone

Test(TEST_SUITE, getsSupportedTimeZonesIsEmptyWhenThereIsNoRegion) {
  const char **timeZones;
  int timeZoneCount;

  timeZones = (const char **)malloc(sizeof(const char *) * TIME_ZONES_CAPACITY);
  timeZoneCount = getSupportedTimeZones("en", timeZones);

  cr_assert(eq(int, timeZoneCount, 0));

  for (int i = 0; i < timeZoneCount; i++) {
    free((void *)timeZones[i]);
  }
  free(timeZones);
}

Test(TEST_SUITE, getsSupportedTimeZonesForLocale) {
  const char **timeZones;
  int timeZoneCount;
  bool foundAmericaNewYork = false, foundAmericaChicago = false,
       foundAmericaDenver = false, foundAmericaLosAngeles = false;

  timeZones = (const char **)malloc(sizeof(const char *) * TIME_ZONES_CAPACITY);
  timeZoneCount = getSupportedTimeZones("en-US", timeZones);

  cr_assert(gt(int, timeZoneCount, 1));

  for (int i = 0; i < timeZoneCount; i++) {
    if (strcmp(timeZones[i], "America/New_York") == 0) {
      foundAmericaNewYork = true;
    } else if (strcmp(timeZones[i], "America/Chicago") == 0) {
      foundAmericaChicago = true;
    } else if (strcmp(timeZones[i], "America/Denver") == 0) {
      foundAmericaDenver = true;
    } else if (strcmp(timeZones[i], "America/Los_Angeles") == 0) {
      foundAmericaLosAngeles = true;
    }
    free((void *)timeZones[i]);
  }
  free(timeZones);

  cr_assert(eq(int, foundAmericaNewYork, true));
  cr_assert(eq(int, foundAmericaChicago, true));
  cr_assert(eq(int, foundAmericaDenver, true));
  cr_assert(eq(int, foundAmericaLosAngeles, true));
}
