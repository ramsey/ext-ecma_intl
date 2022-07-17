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

#include "week_day.h"

#include "src/php/ecma_intl_arginfo.h"
#include "src/php/support/locale/week_day.h"

zend_class_entry *ecmaIntlLocaleWeekDayEnum = NULL;

void registerEcmaIntlLocaleWeekDayEnum() {
  ecmaIntlLocaleWeekDayEnum = register_class_Ecma_Intl_Locale_WeekDay();
}

zend_object *getWeekDayEnumCaseForDayOfWeek(dayOfWeek dayOfWeek) {
  char *caseName = getWeekDayCaseNameByDayOfWeek(dayOfWeek);

  if (caseName == NULL) {
    return NULL;
  }

  return zend_enum_get_case_cstr(ecmaIntlLocaleWeekDayEnum, caseName);
}
