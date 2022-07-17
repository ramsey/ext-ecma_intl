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

#ifndef ECMA_INTL_ECMA402_CATEGORY_H
#define ECMA_INTL_ECMA402_CATEGORY_H

#define CATEGORY_CALENDAR "calendar"
#define CATEGORY_COLLATION "collation"
#define CATEGORY_CURRENCY "currency"
#define CATEGORY_NUMBERING_SYSTEM "numberingSystem"
#define CATEGORY_TIME_ZONE "timeZone"
#define CATEGORY_UNIT "unit"

#define CATEGORY_CALENDAR_CAPACITY 25
#define CATEGORY_COLLATION_CAPACITY 25
#define CATEGORY_CURRENCY_CAPACITY 325
#define CATEGORY_NUMBERING_SYSTEM_CAPACITY 100
#define CATEGORY_TIME_ZONE_CAPACITY 650
#define CATEGORY_UNIT_CAPACITY 200

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Points the provided values char pointer to an array of all supported values
 * for the given category, and returns the total number of supported values
 * for the category.
 *
 * The values parameter should already be allocated on the stack with enough
 * memory to store all the units. Typically, this should use
 * getCapacityForCategory(category). For example:
 *
 *     (const char **)malloc(sizeof(const char *)
 *         * getCapacityForCategory(category))
 *
 * @param category The category keyword to get supported values for.
 * @param values A pointer in which to store the resulting char array of values.
 *
 * @return The total count of the supported values returned for the category.
 */
int getSupportedValuesForCategory(const char *category, const char **values);

/**
 * Returns the recommended const char ** capacity for the given category.
 */
int getCapacityForCategory(const char *category);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_ECMA402_CATEGORY_H */
