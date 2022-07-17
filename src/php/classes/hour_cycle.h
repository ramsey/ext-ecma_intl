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

#ifndef ECMA_INTL_PHP_CLASSES_HOUR_CYCLE_H
#define ECMA_INTL_PHP_CLASSES_HOUR_CYCLE_H

#include "src/php/php_common.h"
#include <unicode/udat.h>

extern zend_class_entry *ecmaIntlHourCycleEnum;

void registerEcmaIntlHourCycleEnum(void);

/**
 * Returns an HourCycle enum case for the given value.
 *
 * @param value The value of the enum case to retrieve.
 *
 * @return A zend_object representing the enum case or NULL if a case does not
 * exist for the value.
 */
zend_object *getHourCycleEnumCaseByValue(const char *value);

/**
 * Returns an HourCycle enum case for the given UDateFormatHourCycle.
 *
 * @param value The value of the enum case to retrieve.
 *
 * @return A zend_object representing the enum case or NULL if a case does not
 * exist for the UDateFormatHourCycle.
 */
zend_object *getHourCycleEnumCaseByHourCycle(UDateFormatHourCycle hourCycle);

#endif /* ECMA_INTL_PHP_CLASSES_HOUR_CYCLE_H */
