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

#include "hour_cycle.h"

#include <string.h>

#define CASE_H11 "H11"
#define CASE_H12 "H12"
#define CASE_H23 "H23"
#define CASE_H24 "H24"

const char *getHourCycleCaseName(const char *value) {
  if (value == NULL) {
    return NULL;
  } else if (strcmp(value, HOUR_CYCLE_H11) == 0) {
    return CASE_H11;
  } else if (strcmp(value, HOUR_CYCLE_H12) == 0) {
    return CASE_H12;
  } else if (strcmp(value, HOUR_CYCLE_H23) == 0) {
    return CASE_H23;
  } else if (strcmp(value, HOUR_CYCLE_H24) == 0) {
    return CASE_H24;
  }

  return NULL;
}

const char *getHourCycleCaseNameByHourCycle(UDateFormatHourCycle hourCycle) {
  if (hourCycle == UDAT_HOUR_CYCLE_11) {
    return CASE_H11;
  } else if (hourCycle == UDAT_HOUR_CYCLE_12) {
    return CASE_H12;
  } else if (hourCycle == UDAT_HOUR_CYCLE_23) {
    return CASE_H23;
  } else if (hourCycle == UDAT_HOUR_CYCLE_24) {
    return CASE_H24;
  }

  return NULL;
}
