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

#include "calendar.h"

#include "src/php/ecma_intl_arginfo.h"
#include "src/php/support/calendar.h"
#include <unicode/uloc.h>

zend_class_entry *ecmaIntlCalendarEnum = NULL;

void registerEcmaIntlCalendarEnum() {
  ecmaIntlCalendarEnum = register_class_Ecma_Intl_Calendar();
}

zend_object *getCalendarEnumCaseByValue(const char *value) {
  if (value == NULL) {
    return NULL;
  }

  RETURN_ENUM_CASE(ecmaIntlCalendarEnum, getCalendarCaseName(value), value);
}
