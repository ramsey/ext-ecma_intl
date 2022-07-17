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

#include "text_info.h"

#include "src/php/ecma_intl_arginfo.h"
#include "text_direction.h"

zend_class_entry *ecmaIntlLocaleTextInfoClass = NULL;
zend_object_handlers ecmaIntlLocaleTextInfoHandlers;

static void textInfoObjFree(zend_object *object);

PHP_METHOD(Ecma_Intl_Locale_TextInfo, __construct) {
  zval *textDirection, *object;

  ZEND_PARSE_PARAMETERS_START(1, 1)
  Z_PARAM_OBJECT_OF_CLASS(textDirection, ecmaIntlLocaleTextDirectionEnum)
  ZEND_PARSE_PARAMETERS_END();

  object = getThis();

  zend_update_property(ecmaIntlLocaleTextInfoClass, Z_OBJ_P(object),
                       TEXT_INFO_DIRECTION, sizeof(TEXT_INFO_DIRECTION) - 1,
                       textDirection);
}

void registerEcmaIntlLocaleTextInfoClass() {
  ecmaIntlLocaleTextInfoClass = register_class_Ecma_Intl_Locale_TextInfo();
  ecmaIntlLocaleTextInfoClass->create_object = createTextInfoObj;

  memcpy(&ecmaIntlLocaleTextInfoHandlers, zend_get_std_object_handlers(),
         sizeof(zend_object_handlers));

  ecmaIntlLocaleTextInfoHandlers.offset = XtOffsetOf(textInfoObj, std);
  ecmaIntlLocaleTextInfoHandlers.free_obj = textInfoObjFree;
}

zend_object *createTextInfoObj(zend_class_entry *classEntry) {
  textInfoObj *textInfoObj = zend_object_alloc(sizeof(struct textInfoObj), classEntry);
  zend_object_std_init(&textInfoObj->std, classEntry);
  object_properties_init(&textInfoObj->std, classEntry);
  textInfoObj->std.handlers = &ecmaIntlLocaleTextInfoHandlers;

  return &textInfoObj->std;
}

static void textInfoObjFree(zend_object *object) {
  textInfoObj *textInfoObj = textInfoObjFromObj(object);

  zend_object_std_dtor(&textInfoObj->std);
}
