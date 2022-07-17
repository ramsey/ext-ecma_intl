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

#include "week_day.h"

#include <stddef.h>

#define CASE_MONDAY "Monday"
#define CASE_TUESDAY "Tuesday"
#define CASE_WEDNESDAY "Wednesday"
#define CASE_THURSDAY "Thursday"
#define CASE_FRIDAY "Friday"
#define CASE_SATURDAY "Saturday"
#define CASE_SUNDAY "Sunday"

char *getWeekDayCaseNameByDayOfWeek(dayOfWeek dayOfWeek) {
  switch (dayOfWeek) {
  case ECMA402_MONDAY:
    return CASE_MONDAY;
  case ECMA402_TUESDAY:
    return CASE_TUESDAY;
  case ECMA402_WEDNESDAY:
    return CASE_WEDNESDAY;
  case ECMA402_THURSDAY:
    return CASE_THURSDAY;
  case ECMA402_FRIDAY:
    return CASE_FRIDAY;
  case ECMA402_SATURDAY:
    return CASE_SATURDAY;
  case ECMA402_SUNDAY:
    return CASE_SUNDAY;
  default:
    return NULL;
  }
}
