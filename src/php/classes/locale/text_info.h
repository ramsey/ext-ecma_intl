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

#ifndef ECMA_INTL_CLASSES_PHP_LOCALE_TEXT_INFO_H
#define ECMA_INTL_CLASSES_PHP_LOCALE_TEXT_INFO_H

#include "src/php/php_common.h"

#define TEXT_INFO_DIRECTION "direction"

typedef struct textInfoObj textInfoObj;

struct textInfoObj {
  zend_object std;
};

static inline textInfoObj *textInfoObjFromObj(zend_object *obj) {
  return (textInfoObj *)((char *)(obj)-XtOffsetOf(textInfoObj, std));
}

#define Z_TEXT_INFO_P(zv) textInfoObjFromObj(Z_OBJ_P(zv))

extern zend_class_entry *ecmaIntlLocaleTextInfoClass;
extern zend_object_handlers ecmaIntlLocaleTextInfoHandlers;

void registerEcmaIntlLocaleTextInfoClass(void);
zend_object *createTextInfoObj(zend_class_entry *classEntry);

#endif /* ECMA_INTL_CLASSES_PHP_LOCALE_TEXT_INFO_H */
