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

#include "options.h"
#include "src/php/classes/calendar.h"
#include "src/php/classes/case_first.h"
#include "src/php/classes/collation.h"
#include "src/php/classes/hour_cycle.h"
#include "src/php/classes/numbering_system.h"
#include "src/php/ecma_intl_arginfo.h"

#define SET_PROP_ZVAL(property, value)                                         \
  zend_update_property(ecmaIntlLocaleOptionsClass, this, property,             \
                       sizeof(property) - 1, value)

#define SET_PROP_STRINGL(property, value, valueLength)                         \
  zend_update_property_stringl(ecmaIntlLocaleOptionsClass, this, property,     \
                               sizeof(property) - 1, value, valueLength)

#define SET_PROP_BOOL(property, value)                                         \
  zend_update_property_bool(ecmaIntlLocaleOptionsClass, this, property,        \
                            sizeof(property) - 1, value)

zend_class_entry *ecmaIntlLocaleOptionsClass = NULL;
zend_object_handlers ecmaIntlLocaleOptionsHandlers;

static void localeOptionsObjFree(zend_object *object);

PHP_METHOD(Ecma_Intl_Locale_Options, __construct) {
  zend_object *this;
  zval *calendar = NULL, *caseFirst = NULL, *collation = NULL,
       *hourCycle = NULL, *numberingSystem = NULL;
  char *language = NULL, *region = NULL, *script = NULL;
  size_t languageLength, regionLength, scriptLength;
  bool numeric = false, numericNull = true;

  ZEND_PARSE_PARAMETERS_START(0, 9)
  Z_PARAM_OPTIONAL
  Z_PARAM_OBJECT_OF_CLASS_OR_NULL(calendar, ecmaIntlCalendarEnum)
  Z_PARAM_OBJECT_OF_CLASS_OR_NULL(caseFirst, ecmaIntlCaseFirstEnum)
  Z_PARAM_OBJECT_OF_CLASS_OR_NULL(collation, ecmaIntlCollationEnum)
  Z_PARAM_OBJECT_OF_CLASS_OR_NULL(hourCycle, ecmaIntlHourCycleEnum)
  Z_PARAM_STRING_OR_NULL(language, languageLength)
  Z_PARAM_OBJECT_OF_CLASS_OR_NULL(numberingSystem, ecmaIntlNumberingSystemEnum)
  Z_PARAM_BOOL_OR_NULL(numeric, numericNull)
  Z_PARAM_STRING_OR_NULL(region, regionLength)
  Z_PARAM_STRING_OR_NULL(script, scriptLength)
  ZEND_PARSE_PARAMETERS_END();

  this = Z_OBJ_P(getThis());

  if (calendar) {
    SET_PROP_ZVAL(OPTION_CALENDAR, calendar);
  }

  if (caseFirst) {
    SET_PROP_ZVAL(OPTION_CASE_FIRST, caseFirst);
  }

  if (collation) {
    SET_PROP_ZVAL(OPTION_COLLATION, collation);
  }

  if (hourCycle) {
    SET_PROP_ZVAL(OPTION_HOUR_CYCLE, hourCycle);
  }

  if (language) {
    SET_PROP_STRINGL(OPTION_LANGUAGE, language, languageLength);
  }

  if (numberingSystem) {
    SET_PROP_ZVAL(OPTION_NUMBERING_SYSTEM, numberingSystem);
  }

  if (numericNull == false) {
    SET_PROP_BOOL(OPTION_NUMERIC, numeric);
  }

  if (region) {
    SET_PROP_STRINGL(OPTION_REGION, region, regionLength);
  }

  if (script) {
    SET_PROP_STRINGL(OPTION_SCRIPT, script, scriptLength);
  }
}

void registerEcmaIntlLocaleOptionsClass() {
  ecmaIntlLocaleOptionsClass = register_class_Ecma_Intl_Locale_Options();
  ecmaIntlLocaleOptionsClass->create_object = createLocaleOptionsObj;

  memcpy(&ecmaIntlLocaleOptionsHandlers, zend_get_std_object_handlers(),
         sizeof(zend_object_handlers));

  ecmaIntlLocaleOptionsHandlers.offset = XtOffsetOf(localeOptionsObj, std);
  ecmaIntlLocaleOptionsHandlers.free_obj = localeOptionsObjFree;
}

zend_object *createLocaleOptionsObj(zend_class_entry *classType) {
  localeOptionsObj *localeOptionsObj =
      zend_object_alloc(sizeof(struct localeOptionsObj), classType);
  zend_object_std_init(&localeOptionsObj->std, classType);
  object_properties_init(&localeOptionsObj->std, classType);
  localeOptionsObj->std.handlers = &ecmaIntlLocaleOptionsHandlers;

  return &localeOptionsObj->std;
}

static void localeOptionsObjFree(zend_object *object) {
  localeOptionsObj *localeOptionsObj = localeOptionsObjFromObj(object);

  zend_object_std_dtor(&localeOptionsObj->std);
}
