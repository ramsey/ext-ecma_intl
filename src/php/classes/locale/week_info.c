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

#include "week_info.h"

#include "src/php/ecma_intl_arginfo.h"
#include "week_day.h"

zend_class_entry *ecmaIntlLocaleWeekInfoClass = NULL;
zend_object_handlers ecmaIntlLocaleWeekInfoHandlers;

static void freeWeekInfoObj(zend_object *object);

void registerEcmaIntlLocaleWeekInfoClass() {
  ecmaIntlLocaleWeekInfoClass = register_class_Ecma_Intl_Locale_WeekInfo();
  ecmaIntlLocaleWeekInfoClass->create_object = createWeekInfoObj;

  memcpy(&ecmaIntlLocaleWeekInfoHandlers, zend_get_std_object_handlers(),
         sizeof(zend_object_handlers));

  ecmaIntlLocaleWeekInfoHandlers.offset = XtOffsetOf(weekInfoObj, std);
  ecmaIntlLocaleWeekInfoHandlers.free_obj = freeWeekInfoObj;
}

zend_object *createWeekInfoObj(zend_class_entry *classType) {
  weekInfoObj *weekInfoObj =
      zend_object_alloc(sizeof(struct weekInfoObj), classType);
  zend_object_std_init(&weekInfoObj->std, classType);
  object_properties_init(&weekInfoObj->std, classType);
  weekInfoObj->std.handlers = &ecmaIntlLocaleWeekInfoHandlers;

  return &weekInfoObj->std;
}

PHP_METHOD(Ecma_Intl_Locale_WeekInfo, __construct) {
  zval *firstDay, *day, weekend;
  zend_long minimalDays;
  zend_object *this;
  HashTable *weekendArray;

  ZEND_PARSE_PARAMETERS_START(3, 3)
  Z_PARAM_OBJECT_OF_CLASS(firstDay, ecmaIntlLocaleWeekDayEnum)
  Z_PARAM_LONG(minimalDays)
  Z_PARAM_ARRAY_HT(weekendArray)
  ZEND_PARSE_PARAMETERS_END();

  ZEND_HASH_FOREACH_VAL(weekendArray, day)
  if (Z_TYPE_P(day) != IS_OBJECT ||
      !instanceof_function(Z_OBJCE_P(day), ecmaIntlLocaleWeekDayEnum)) {
    zend_value_error("Argument $weekend must be an array of values of type "
                     "Ecma\\Intl\\Locale\\WeekDay");
  }
  ZEND_HASH_FOREACH_END();

  if (zend_hash_num_elements(weekendArray) > 0) {
    ZVAL_ARR(&weekend, weekendArray);
  } else {
    ZVAL_EMPTY_ARRAY(&weekend);
  }

  this = Z_OBJ_P(getThis());

  zend_update_property(ecmaIntlLocaleWeekInfoClass, this, WEEK_INFO_FIRST_DAY,
                       sizeof(WEEK_INFO_FIRST_DAY) - 1, firstDay);
  zend_update_property_long(ecmaIntlLocaleWeekInfoClass, this,
                            WEEK_INFO_MINIMAL_DAYS,
                            sizeof(WEEK_INFO_MINIMAL_DAYS) - 1, minimalDays);
  zend_update_property(ecmaIntlLocaleWeekInfoClass, this, WEEK_INFO_WEEKEND,
                       sizeof(WEEK_INFO_WEEKEND) - 1, &weekend);
}

static void freeWeekInfoObj(zend_object *object) {
  weekInfoObj *weekInfoObj = weekInfoObjFromObj(object);

  zend_object_std_dtor(&weekInfoObj->std);
}
