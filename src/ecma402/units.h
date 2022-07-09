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

#ifndef ECMA_INTL_ECMA402_UNITS_H
#define ECMA_INTL_ECMA402_UNITS_H

#include "src/common.h"

#include <unicode/errorcode.h>
#include <unicode/uenum.h>

#define UNITS_CAPACITY 200

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Points the provided units char pointer to an array of all measurement units
 * and returns the total number of measurement units stored in that array.
 *
 * The units parameter should already be allocated on the stack with enough
 * memory to store all the units. Typically, this should use UNITS_CAPACITY.
 * For example:
 *
 *     (const char **)malloc(sizeof(const char *) * UNITS_CAPACITY)
 *
 * @param units A pointer in which to store the resulting char array of units.
 *
 * @return The total count of the number of units returned.
 */
int getAllMeasurementUnits(const char **units);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_ECMA402_UNITS_H */
