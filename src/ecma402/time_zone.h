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

#ifndef ECMA_INTL_ECMA402_TIME_ZONE_H
#define ECMA_INTL_ECMA402_TIME_ZONE_H

#include "src/common.h"

#define TIME_ZONES_CAPACITY 50

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns an array of time zones supported for the given locale.
 *
 * The time zones parameter should already be allocated on the stack with enough
 * memory to store all the time zones. Typically, this should use
 * TIME_ZONES_CAPACITY. For example:
 *
 *     (const char **)malloc(sizeof(const char *) * TIME_ZONES_CAPACITY)
 *
 * @param localeId The locale to check.
 * @param timeZones A pointer in which to store the resulting char array of
 * time zones.
 *
 * @return The total count of the number of time zones stored to the time zones
 * array.
 */
int getSupportedTimeZones(const char *localeId, const char **timeZones);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_ECMA402_TIME_ZONE_H */
