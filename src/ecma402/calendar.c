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
    return ECMA_INTL_FAILURE;
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
    return ECMA_INTL_FAILURE;
  }
}

weekdayType getDayOfWeekType(char *localeId, dayOfWeek day) {
  UCalendar *calendar;
  UErrorCode status = U_ZERO_ERROR;
  UCalendarWeekdayType type;
  UCalendarDaysOfWeek dayOfWeek;

  dayOfWeek = ecmaDayOfWeekToIcuDayOfWeek(day);
  if (dayOfWeek == ECMA_INTL_FAILURE) {
    return ECMA_INTL_FAILURE;
  }

  calendar = ucal_open(NULL, 0, localeId, UCAL_DEFAULT, &status);

  if (calendar) {
    type = ucal_getDayOfWeekType(calendar, dayOfWeek, &status);
    ucal_close(calendar);
  }

  if (U_FAILURE(status)) {
    return ECMA_INTL_FAILURE;
  }

  switch (type) {
  /* UCAL_WEEKEND_ONSET is a day that starts as a weekday and transitions to the
   * weekend. It means this is a weekday. */
  case UCAL_WEEKEND_ONSET:
  case UCAL_WEEKDAY:
    return ECMA402_WEEKDAY;

  /* UCAL_WEEKEND_CEASE is a day that starts as the weekend and transitions to a
   * weekday. It means this is a weekend. */
  case UCAL_WEEKEND_CEASE:
  case UCAL_WEEKEND:
    return ECMA402_WEEKEND;

  default:
    return ECMA_INTL_FAILURE;
  }
}

dayOfWeek getFirstDayOfWeek(char *localeId) {
  UCalendar *calendar;
  UErrorCode status = U_ZERO_ERROR;
  UCalendarDaysOfWeek dayOfWeek = 0;

  calendar = ucal_open(NULL, 0, localeId, UCAL_DEFAULT, &status);

  if (calendar) {
    dayOfWeek = ucal_getAttribute(calendar, UCAL_FIRST_DAY_OF_WEEK);
    ucal_close(calendar);
  }

  return icuDayOfWeekToEcmaDayOfWeek(dayOfWeek);
}
