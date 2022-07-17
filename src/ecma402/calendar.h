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

#include "locale.h"

#define CALENDAR_BUDDHIST "buddhist"
#define CALENDAR_CHINESE "chinese"
#define CALENDAR_COPTIC "coptic"
#define CALENDAR_DANGI "dangi"
#define CALENDAR_ETHIOAA "ethioaa"
#define CALENDAR_ETHIOPIC "ethiopic"
#define CALENDAR_GREGORY "gregory"
#define CALENDAR_HEBREW "hebrew"
#define CALENDAR_INDIAN "indian"
#define CALENDAR_ISLAMIC "islamic"
#define CALENDAR_ISLAMIC_CIVIL "islamic-civil"
#define CALENDAR_ISLAMIC_RGSA "islamic-rgsa"
#define CALENDAR_ISLAMIC_TBLA "islamic-tbla"
#define CALENDAR_ISLAMIC_UMALQURA "islamic-umalqura"
#define CALENDAR_ISO8601 "iso8601"
#define CALENDAR_JAPANESE "japanese"
#define CALENDAR_PERSIAN "persian"
#define CALENDAR_ROC "roc"

#define CALENDARS_CAPACITY 10

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Type of the day of the week, i.e., weekday or weekend.
 */
typedef enum weekdayType {
  /**
   * The day of the week is considered a weekday.
   */
  ECMA402_WEEKDAY = 10,

  /**
   * The day of the week is considered a weekend.
   */
  ECMA402_WEEKEND

} weekdayType;

/**
 * The day of the week. The days of the week in this enum are ordered and
 * numbered according to the definition for WeekInfoOfLocale in the TC39 Intl
 * Locale Info Proposal, Stage 3 Draft.
 *
 * @link https://tc39.es/proposal-intl-locale-info/#sec-week-info-of-locale
 */
typedef enum dayOfWeek {
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

} dayOfWeek;

/**
 * Information about the structure of a week for a given locale.
 */
typedef struct weekInfo {
  /**
   * The first day of the week in the locale.
   */
  dayOfWeek firstDay;

  /**
   * The minimal amount of days that must be in the first week of a month/year
   * in the locale.
   */
  int minimalDays;

  /**
   * An array of the days that are considered "weekend" days in the locale.
   */
  dayOfWeek *weekend;

  /**
   * The number of values in the weekend array.
   */
  int weekendLength;

} weekInfo;

/**
 * Returns the weekday type (i.e., weekday or weekend) for the given day of the
 * week in the given locale.
 *
 * @param localeId The locale to check.
 * @param day The day of the week ot check.
 *
 * @return The weekday type for the day (i.e., weekday or weekend).
 */
weekdayType getDayOfWeekType(const char *localeId, dayOfWeek day);

/**
 * Returns the day of the week that is considered the first day of the week for
 * the given locale.
 *
 * @param localeId The locale to check.
 *
 * @return The day of the week considered the first day.
 */
dayOfWeek getFirstDayOfWeek(const char *localeId);

/**
 * Returns an array of calendars supported for the given locale. If the locale
 * defines a calendar using a keyword, the resulting array will have only that
 * calendar as the locale's preferred supported calendar.
 *
 * The calendars parameter should already be allocated on the stack with enough
 * memory to store all the calendars. Typically, this should use
 * CALENDARS_CAPACITY. For example:
 *
 *     (const char **)malloc(sizeof(const char *) * CALENDARS_CAPACITY)
 *
 * @param localeId The locale to check.
 * @param calendars A pointer in which to store the resulting char array of
 * calendars.
 *
 * @return The total count of the number of calendars stored to the calendars
 * array.
 */
int getSupportedCalendars(const char *localeId, const char **calendars);

/**
 * Initializes an empty weekInfo struct.
 *
 * This allocates the struct on the stack, so you must free the object with
 * freeWeekInfo().
 */
weekInfo *initEmptyWeekInfo(void);

/**
 * Returns week information for the given locale.
 *
 * This allocates the struct on the stack, so you must free the object with
 * freeWeekInfo().
 *
 * @param localeId The locale to check.
 *
 * @return A weekInfo struct with locale-specific information about days of the
 * week.
 */
weekInfo *getWeekInfo(const char *localeId);

/**
 * Frees the weekInfo struct.
 */
void freeWeekInfo(weekInfo *info);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_ECMA402_CALENDAR_H */
