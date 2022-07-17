/*
   +----------------------------------------------------------------------+
   | ecma_intl extension for PHP                                          |
   | Internationalization Support, Ecma-style (ECMA-402)                  |
   +----------------------------------------------------------------------+
   | Copyright (c) Ben Ramsey <ben@benramsey.com>                         |
   |                                                                      |
   | Licensed under the MIT License (the "License"); you may not use this |
   | file except in compliance with the License. You may obtain a copy of |
   | the License at                                                       |
   |                                                                      |
   |     https://opensource.org/licenses/MIT                              |
   |                                                                      |
   | Unless required by applicable law or agreed to in writing, software  |
   | distributed under the License IS PROVIDED "AS IS", WITHOUT WARRANTY  |
   | OF ANY KIND, EXPRESS OR IMPLIED. See the License for the specific    |
   | language governing permissions and limitations under the License.    |
   +----------------------------------------------------------------------+
*/

#include "calendar.h"

#include <stdlib.h>
#include <string.h>
#include <unicode/ucal.h>

/**
 * Converts an ECMA-numbered day of the week to an ICU-numbered day of the week.
 */
static UCalendarDaysOfWeek ecmaDayOfWeekToIcuDayOfWeek(dayOfWeek day) {
  switch (day) {
  case ECMA402_MONDAY:
    return UCAL_MONDAY;
  case ECMA402_TUESDAY:
    return UCAL_TUESDAY;
  case ECMA402_WEDNESDAY:
    return UCAL_WEDNESDAY;
  case ECMA402_THURSDAY:
    return UCAL_THURSDAY;
  case ECMA402_FRIDAY:
    return UCAL_FRIDAY;
  case ECMA402_SATURDAY:
    return UCAL_SATURDAY;
  case ECMA402_SUNDAY:
    return UCAL_SUNDAY;
  default:
    return -1;
  }
}

/**
 * Converts an ICU-numbered day of the week to an ECMA-numbered day of the week.
 */
static dayOfWeek icuDayOfWeekToEcmaDayOfWeek(UCalendarDaysOfWeek day) {
  switch (day) {
  case UCAL_MONDAY:
    return ECMA402_MONDAY;
  case UCAL_TUESDAY:
    return ECMA402_TUESDAY;
  case UCAL_WEDNESDAY:
    return ECMA402_WEDNESDAY;
  case UCAL_THURSDAY:
    return ECMA402_THURSDAY;
  case UCAL_FRIDAY:
    return ECMA402_FRIDAY;
  case UCAL_SATURDAY:
    return ECMA402_SATURDAY;
  case UCAL_SUNDAY:
    return ECMA402_SUNDAY;
  default:
    return -1;
  }
}

weekdayType getDayOfWeekType(const char *localeId, dayOfWeek day) {
  UCalendar *calendar;
  UErrorCode icuStatus = U_ZERO_ERROR;
  UCalendarWeekdayType type;
  UCalendarDaysOfWeek dayOfWeek;

  dayOfWeek = ecmaDayOfWeekToIcuDayOfWeek(day);
  if (dayOfWeek == -1) {
    return ECMA402_WEEKDAY;
  }

  calendar = ucal_open(NULL, 0, localeId, UCAL_DEFAULT, &icuStatus);
  if (U_FAILURE(icuStatus)) {
    return ECMA402_WEEKDAY;
  }

  type = ucal_getDayOfWeekType(calendar, dayOfWeek, &icuStatus);
  ucal_close(calendar);

  if (U_FAILURE(icuStatus)) {
    return ECMA402_WEEKDAY;
  }

  switch (type) {
  /* UCAL_WEEKEND_CEASE is a day that starts as the weekend and transitions to a
   * weekday. It means this is a weekend. */
  case UCAL_WEEKEND_CEASE:
  case UCAL_WEEKEND:
    return ECMA402_WEEKEND;

  /* UCAL_WEEKEND_ONSET is a day that starts as a weekday and transitions to the
   * weekend. It means this is a weekday. */
  case UCAL_WEEKEND_ONSET:
  case UCAL_WEEKDAY:
  default:
    return ECMA402_WEEKDAY;
  }
}

dayOfWeek getFirstDayOfWeek(const char *localeId) {
  UCalendar *calendar;
  UErrorCode icuStatus = U_ZERO_ERROR;
  UCalendarDaysOfWeek icuDayOfWeek = UCAL_SUNDAY;
  dayOfWeek ecmaDayOfWeek;

  calendar = ucal_open(NULL, 0, localeId, UCAL_DEFAULT, &icuStatus);

  if (U_SUCCESS(icuStatus)) {
    icuDayOfWeek = ucal_getAttribute(calendar, UCAL_FIRST_DAY_OF_WEEK);
    ucal_close(calendar);
  }

  ecmaDayOfWeek = icuDayOfWeekToEcmaDayOfWeek(icuDayOfWeek);
  if (ecmaDayOfWeek == -1) {
    return ECMA402_SUNDAY;
  }

  return ecmaDayOfWeek;
}

int getSupportedCalendars(const char *localeId, const char **calendars) {
  UEnumeration *supported = NULL;
  UErrorCode icuStatus = U_ZERO_ERROR;
  char *preferred;
  const char *name, *tmpName;
  int preferredLength, count = 0;

  preferred = (char *)malloc(sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  if (!preferred) {
    return 0;
  }

  preferredLength =
      uloc_getKeywordValue(localeId, ICU_KEYWORD_CALENDAR, preferred,
                           ULOC_KEYWORD_AND_VALUES_CAPACITY, &icuStatus);

  if (preferredLength > 0) {
    tmpName = uloc_toUnicodeLocaleType(ICU_KEYWORD_CALENDAR, preferred);
    free(preferred);

    calendars[0] = (const char *)malloc(strlen(tmpName) + 1);
    if (!calendars[0]) {
      return 0;
    }

    memcpy((void *)calendars[0], tmpName, strlen(tmpName) + 1);
    return 1;
  }

  free(preferred);

  supported = ucal_getKeywordValuesForLocale(ICU_KEYWORD_CALENDAR, localeId,
                                             true, &icuStatus);
  if (U_FAILURE(icuStatus)) {
    return 0;
  }

  while ((name = uenum_next(supported, NULL, &icuStatus))) {
    if (U_FAILURE(icuStatus)) {
      break;
    }

    tmpName = uloc_toUnicodeLocaleType(ICU_KEYWORD_CALENDAR, name);
    calendars[count] = (const char *)malloc(strlen(tmpName) + 1);
    if (!calendars[count]) {
      break;
    }

    memcpy((void *)calendars[count], tmpName, strlen(tmpName) + 1);
    count++;
  }

  uenum_close(supported);

  return count;
}

weekInfo *initEmptyWeekInfo(void) {
  weekInfo *info;

  info = (weekInfo *)malloc(sizeof(*info));
  if (!info) {
    return NULL;
  }

  info->weekend = (dayOfWeek *)malloc(sizeof(dayOfWeek) * 4);
  if (!info->weekend) {
    return NULL;
  }

  info->firstDay = 0;
  info->minimalDays = 0;
  info->weekendLength = 0;

  return info;
}

weekInfo *getWeekInfo(const char *localeId) {
  UCalendar *calendar;
  UErrorCode icuStatus = U_ZERO_ERROR;
  weekInfo *info;
  int weekendDayCount = 0;

  info = initEmptyWeekInfo();
  if (!info) {
    return NULL;
  }

  info->firstDay = getFirstDayOfWeek(localeId);

  for (int day = ECMA402_MONDAY; day <= ECMA402_SUNDAY; day++) {
    switch (getDayOfWeekType(localeId, day)) {
    case ECMA402_WEEKEND:
      info->weekend[weekendDayCount++] = day;
      break;
    case ECMA402_WEEKDAY:
    default:
      break;
    }
  }

  info->weekendLength = weekendDayCount;

  calendar = ucal_open(NULL, 0, localeId, UCAL_DEFAULT, &icuStatus);
  if (U_SUCCESS(icuStatus)) {
    info->minimalDays =
        ucal_getAttribute(calendar, UCAL_MINIMAL_DAYS_IN_FIRST_WEEK);
    ucal_close(calendar);
  } else {
    info->minimalDays = 1;
  }

  return info;
}

void freeWeekInfo(weekInfo *info) {
  if (info->weekend) {
    free(info->weekend);
  }
  free(info);
}
