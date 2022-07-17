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

#ifndef ECMA_INTL_PHP_CLASSES_LOCALE_TEXT_DIRECTION_H
#define ECMA_INTL_PHP_CLASSES_LOCALE_TEXT_DIRECTION_H

#include "src/php/php_common.h"

#include "src/ecma402/text_direction.h"

#include <unicode/uloc.h>

extern zend_class_entry *ecmaIntlLocaleTextDirectionEnum;

void registerEcmaIntlLocaleTextDirectionEnum(void);

/**
 * Returns a TextDirection enum case for the given textDirection enum value.
 *
 * @param direction The textDirection enum value for which to get an enum case.
 *
 * @return A zend_object representing the enum case.
 */
zend_object *getTextDirectionEnumCaseForTextDirection(textDirection direction);

#endif /* ECMA_INTL_PHP_CLASSES_LOCALE_TEXT_DIRECTION_H */
