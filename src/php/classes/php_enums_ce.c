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

#include "php_enums_ce.h"
#include "src/php/ecma_intl_arginfo.h"

zend_class_entry *ecmaIntlCalendarEnum = NULL;
zend_class_entry *ecmaIntlCaseFirstEnum = NULL;
zend_class_entry *ecmaIntlCategoryEnum = NULL;
zend_class_entry *ecmaIntlCollationEnum = NULL;
zend_class_entry *ecmaIntlFormattingEnum = NULL;
zend_class_entry *ecmaIntlHourCycleEnum = NULL;
zend_class_entry *ecmaIntlLocaleMatcherEnum = NULL;
zend_class_entry *ecmaIntlNumberingSystemEnum = NULL;

void ecmaIntlRegisterEnums() {
  ecmaIntlCalendarEnum = register_class_Ecma_Intl_Calendar();
  ecmaIntlCaseFirstEnum = register_class_Ecma_Intl_CaseFirst();
  ecmaIntlCategoryEnum = register_class_Ecma_Intl_Category();
  ecmaIntlCollationEnum = register_class_Ecma_Intl_Collation();
  ecmaIntlFormattingEnum = register_class_Ecma_Intl_Formatting();
  ecmaIntlHourCycleEnum = register_class_Ecma_Intl_HourCycle();
  ecmaIntlLocaleMatcherEnum = register_class_Ecma_Intl_LocaleMatcher();
  ecmaIntlNumberingSystemEnum = register_class_Ecma_Intl_NumberingSystem();
}
