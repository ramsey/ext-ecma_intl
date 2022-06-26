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

#ifndef ECMA_INTL_PHP_ENUMS_CE_H
#define ECMA_INTL_PHP_ENUMS_CE_H

#include "src/php/php_common.h"

extern zend_class_entry *ecmaIntlCalendarEnum;
extern zend_class_entry *ecmaIntlCaseFirstEnum;
extern zend_class_entry *ecmaIntlCategoryEnum;
extern zend_class_entry *ecmaIntlCollationEnum;
extern zend_class_entry *ecmaIntlFormattingEnum;
extern zend_class_entry *ecmaIntlHourCycleEnum;
extern zend_class_entry *ecmaIntlLocaleMatcherEnum;
extern zend_class_entry *ecmaIntlNumberingSystemEnum;

void ecmaIntlRegisterEnums(void);

#endif /* ECMA_INTL_PHP_ENUMS_CE_H */
