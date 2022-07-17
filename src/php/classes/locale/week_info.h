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

#ifndef ECMA_INTL_PHP_CLASSES_LOCALE_WEEK_INFO_H
#define ECMA_INTL_PHP_CLASSES_LOCALE_WEEK_INFO_H

#include "src/php/php_common.h"

#define WEEK_INFO_FIRST_DAY "firstDay"
#define WEEK_INFO_MINIMAL_DAYS "minimalDays"
#define WEEK_INFO_WEEKEND "weekend"

typedef struct weekInfoObj weekInfoObj;

struct weekInfoObj {
  zend_object std;
};

static inline weekInfoObj *weekInfoObjFromObj(zend_object *obj) {
  return (weekInfoObj *)((char *)(obj)-XtOffsetOf(weekInfoObj, std));
}

#define Z_WEEK_INFO_P(zv) weekInfoObjFromObj(Z_OBJ_P(zv))

extern zend_class_entry *ecmaIntlLocaleWeekInfoClass;
extern zend_object_handlers ecmaIntlLocaleWeekInfoHandlers;

void registerEcmaIntlLocaleWeekInfoClass(void);
zend_object *createWeekInfoObj(zend_class_entry *classType);

#endif /* ECMA_INTL_PHP_CLASSES_LOCALE_WEEK_INFO_H */
