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

#ifndef ECMA_INTL_ECMA402_HOUR_CYCLE_H
#define ECMA_INTL_ECMA402_HOUR_CYCLE_H

#include "src/common.h"

#define HOUR_CYCLE_H11 "h11"
#define HOUR_CYCLE_H12 "h12"
#define HOUR_CYCLE_H23 "h23"
#define HOUR_CYCLE_H24 "h24"

#define HOUR_CYCLES_CAPACITY 4

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns an array of hour cycles supported for the given locale. If the locale
 * defines an hour cycle using a keyword, the resulting array will have only
 * that hour cycle as the locale's preferred supported hour cycle.
 *
 * The hour cycle parameter should already be allocated on the stack with enough
 * memory to store all the hour cycles. Typically, this should use
 * HOUR_CYCLES_CAPACITY. For example:
 *
 *     (const char **)malloc(sizeof(const char *) * HOUR_CYCLES_CAPACITY)
 *
 * @param localeId The locale to check.
 * @param hourCycles A pointer in which to store the resulting char array of
 * hour cycles.
 *
 * @return The total count of the number of hour cycles stored to the hour
 * cycles array.
 */
int getSupportedHourCycles(const char *localeId, const char **hourCycles);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_ECMA402_HOUR_CYCLE_H */
