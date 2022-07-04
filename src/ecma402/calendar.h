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

#ifndef ECMA_INTL_ECMA402_CALENDAR_H
#define ECMA_INTL_ECMA402_CALENDAR_H

#include "src/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Type of the day of the week, i.e., weekday or weekend.
 */
typedef enum ecma402_weekdayType {
  /**
   * The day of the week is considered a weekday.
   */
  ECMA402_WEEKDAY,

  /**
   * The day of the week is considered a weekend.
   */
  ECMA402_WEEKEND

} ecma402_weekdayType;

/**
 * The day of the week. The days of the week in this enum are ordered and
 * numbered according to the definition for WeekInfoOfLocale in the TC39 Intl
 * Locale Info Proposal, Stage 3 Draft.
 *
 * @link https://tc39.es/proposal-intl-locale-info/#sec-week-info-of-locale
 */
typedef enum ecma402_dayOfWeek {
  /**
   * Monday
   */
  ECMA402_MONDAY = 1,

  /**
   * Tuesday
   */
  ECMA402_TUESDAY,

  /**
   * Wednesday
   */
  ECMA402_WEDNESDAY,

  /**
   * Thursday
   */
  ECMA402_THURSDAY,

  /**
   * Friday
   */
  ECMA402_FRIDAY,

  /**
   * Saturday
   */
  ECMA402_SATURDAY,

  /**
   * Sunday
   */
  ECMA402_SUNDAY,

} ecma402_dayOfWeek;

/**
 * Returns the weekday type (i.e., weekday or weekend) for the given day of the
 * week in the given locale.
 *
 * @param localeId The locale to check.
 * @param day The day of the week ot check.
 * @return The weekday type for the day (i.e., weekday or weekend).
 */
ecma402_weekdayType ecma402_getDayOfWeekType(char *localeId,
                                             enum ecma402_dayOfWeek day);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_ECMA402_CALENDAR_H */
