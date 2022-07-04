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

enum ecma402_weekdayType { ECMA402_WEEKDAY, ECMA402_WEEKEND };
typedef enum ecma402_weekdayType ecma402_weekdayType;

enum ecma402_dayOfWeek {
  ECMA402_MONDAY = 1,
  ECMA402_TUESDAY,
  ECMA402_WEDNESDAY,
  ECMA402_THURSDAY,
  ECMA402_FRIDAY,
  ECMA402_SATURDAY,
  ECMA402_SUNDAY,
};
typedef enum ecma402_dayOfWeek ecma402_dayOfWeek;

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
