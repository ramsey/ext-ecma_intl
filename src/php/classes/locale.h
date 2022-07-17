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

#ifndef ECMA_INTL_PHP_CLASSES_LOCALE_H
#define ECMA_INTL_PHP_CLASSES_LOCALE_H

#include "src/php/php_common.h"

#include "src/ecma402/locale.h"

#define LOCALE_BASE_NAME "baseName"
#define LOCALE_CALENDAR "calendar"
#define LOCALE_CALENDARS "calendars"
#define LOCALE_CASE_FIRST "caseFirst"
#define LOCALE_COLLATION "collation"
#define LOCALE_COLLATIONS "collations"
#define LOCALE_HOUR_CYCLE "hourCycle"
#define LOCALE_HOUR_CYCLES "hourCycles"
#define LOCALE_LANGUAGE "language"
#define LOCALE_NUMBERING_SYSTEM "numberingSystem"
#define LOCALE_NUMBERING_SYSTEMS "numberingSystems"
#define LOCALE_NUMERIC "numeric"
#define LOCALE_REGION "region"
#define LOCALE_SCRIPT "script"
#define LOCALE_TEXT_INFO "textInfo"
#define LOCALE_TIME_ZONES "timeZones"
#define LOCALE_WEEK_INFO "weekInfo"

typedef struct localeObj localeObj;

struct localeObj {
  locale *locale;
  zend_object std;
};

static inline localeObj *localeObjFromObj(zend_object *obj) {
  return (localeObj *)((char *)(obj)-XtOffsetOf(localeObj, std));
}

#define Z_LOCALE_P(zv) localeObjFromObj(Z_OBJ_P(zv))

extern zend_class_entry *ecmaIntlLocaleClass;
extern zend_object_handlers ecmaIntlLocaleHandlers;

void registerEcmaIntlLocaleClass(void);
zend_object *createLocaleObj(zend_class_entry *classEntry);

#endif /* ECMA_INTL_PHP_CLASSES_LOCALE_H */
