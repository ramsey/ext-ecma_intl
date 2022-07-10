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

#ifndef ECMA_INTL_PHP_SUPPORT_HOUR_CYCLE_H
#define ECMA_INTL_PHP_SUPPORT_HOUR_CYCLE_H

#include <unicode/udat.h>

#define HOUR_CYCLE_H11 "h11"
#define HOUR_CYCLE_H12 "h12"
#define HOUR_CYCLE_H23 "h23"
#define HOUR_CYCLE_H24 "h24"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the PHP hour cycle enum case name for the given value.
 *
 * @param value The hour cycle value.
 *
 * @return A case name for the PHP hour cycle enum.
 */
const char *getHourCycleCaseName(const char *value);

/**
 * Returns the PHP hour cycle enum case name for the given UDateFormatHourCycle.
 *
 * @param value The hour cycle value.
 *
 * @return A case name for the PHP hour cycle enum.
 */
const char *getHourCycleCaseNameByHourCycle(UDateFormatHourCycle hourCycle);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_PHP_SUPPORT_HOUR_CYCLE_H */
