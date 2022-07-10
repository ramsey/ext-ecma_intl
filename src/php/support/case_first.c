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

#include "case_first.h"

#include <string.h>

#define YES "yes"
#define NO "no"

#define CASE_FALSE "False"
#define CASE_LOWER "Lower"
#define CASE_UPPER "Upper"

const char *getCaseFirstCaseName(const char *value) {
  if (value == NULL) {
    return NULL;
  } else if (strcmp(value, CASE_FIRST_FALSE) == 0) {
    return CASE_FALSE;
  } else if (strcmp(value, CASE_FIRST_LOWER) == 0) {
    return CASE_LOWER;
  } else if (strcmp(value, CASE_FIRST_UPPER) == 0) {
    return CASE_UPPER;
  }

  /* Special cases */
  if (strcmp(value, NO) == 0) {
    return CASE_FALSE;
  } else if (strcmp(value, YES) == 0) {
    return CASE_UPPER;
  }

  return NULL;
}
