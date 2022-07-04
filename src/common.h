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

#define BCP47_KEYWORD_CALENDAR "ca"
#define BCP47_KEYWORD_CASE_FIRST "kf"
#define BCP47_KEYWORD_COLLATION "co"
#define BCP47_KEYWORD_HOUR_CYCLE "hc"
#define BCP47_KEYWORD_NUMBERING_SYSTEM "nu"
#define BCP47_KEYWORD_NUMERIC "kn"

#define CATEGORY_CALENDAR "calendar"
#define CATEGORY_COLLATION "collation"
#define CATEGORY_CURRENCY "currency"
#define CATEGORY_NUMBERING_SYSTEM "numberingSystem"
#define CATEGORY_TIME_ZONE "timeZone"
#define CATEGORY_UNIT "unit"

#define ICU_KEYWORD_CALENDAR "calendar"
#define ICU_KEYWORD_CASE_FIRST "colcasefirst"
#define ICU_KEYWORD_COLLATION "collation"
#define ICU_KEYWORD_HOUR_CYCLE "hours"
#define ICU_KEYWORD_NUMBERING_SYSTEM "numbers"
#define ICU_KEYWORD_NUMERIC "colnumeric"

#define UNDETERMINED_LANGUAGE "und"

enum ecmaIntlResultCode {
  ECMA_INTL_FAILURE = -1,
  ECMA_INTL_NOOP = 0,
  ECMA_INTL_SUCCESS = 1,
};
typedef enum ecmaIntlResultCode ecmaIntlResultCode;

#endif /* ECMA_INTL_COMMON_H */
