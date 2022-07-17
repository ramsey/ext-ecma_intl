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

#ifndef ECMA_INTL_CLASSES_PHP_LOCALE_OPTIONS_H
#define ECMA_INTL_CLASSES_PHP_LOCALE_OPTIONS_H

#include "src/php/php_common.h"

#define OPTION_CALENDAR "calendar"
#define OPTION_CASE_FIRST "caseFirst"
#define OPTION_COLLATION "collation"
#define OPTION_HOUR_CYCLE "hourCycle"
#define OPTION_LANGUAGE "language"
#define OPTION_NUMBERING_SYSTEM "numberingSystem"
#define OPTION_NUMERIC "numeric"
#define OPTION_REGION "region"
#define OPTION_SCRIPT "script"

typedef struct localeOptionsObj localeOptionsObj;

struct localeOptionsObj {
  zend_object std;
};

static inline localeOptionsObj *localeOptionsObjFromObj(zend_object *obj) {
  return (localeOptionsObj *)((char *)(obj)-XtOffsetOf(localeOptionsObj, std));
}

#define Z_LOCALE_OPTIONS_P(zv) localeOptionsObjFromObj(Z_OBJ_P(zv))

extern zend_class_entry *ecmaIntlLocaleOptionsClass;
extern zend_object_handlers ecmaIntlLocaleOptionsHandlers;

void registerEcmaIntlLocaleOptionsClass(void);
zend_object *createLocaleOptionsObj(zend_class_entry *classType);

#endif /* ECMA_INTL_CLASSES_PHP_LOCALE_OPTIONS_H */
