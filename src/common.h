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

#ifndef ECMA_INTL_COMMON_H
#define ECMA_INTL_COMMON_H

#define CATEGORY_CALENDAR "calendar"
#define CATEGORY_COLLATION "collation"
#define CATEGORY_CURRENCY "currency"
#define CATEGORY_NUMBERING_SYSTEM "numberingSystem"
#define CATEGORY_TIME_ZONE "timeZone"
#define CATEGORY_UNIT "unit"

#define KEYWORD_ICU_CALENDAR "calendar"
#define KEYWORD_ICU_CASE_FIRST "colcasefirst"
#define KEYWORD_ICU_COLLATION "collation"
#define KEYWORD_ICU_HOUR_CYCLE "hours"
#define KEYWORD_ICU_NUMBERING_SYSTEM "numbers"
#define KEYWORD_ICU_NUMERIC "colnumeric"

typedef enum {
  ECMA_INTL_SUCCESS = 0,
  ECMA_INTL_FAILURE = -1,
} ECMA_INTL_RESULT_CODE;

#endif /* ECMA_INTL_COMMON_H */
