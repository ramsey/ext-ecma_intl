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

#ifndef ECMA_INTL_PHP_INTL_H
#define ECMA_INTL_PHP_INTL_H

#include "src/common.h"

typedef struct ecmaIntlObj ecmaIntlObj;

struct ecmaIntlObj {
  zend_object std;
};

static inline ecmaIntlObj *ecmaIntlObjFromObj(zend_object *obj) {
  return (ecmaIntlObj *)((char *)(obj)-XtOffsetOf(ecmaIntlObj, std));
}

#define Z_ECMA_INTL_P(zv) ecmaIntlObjFromObj(Z_OBJ_P(zv))

zend_object *ecmaIntlObjCreate(zend_class_entry *classType);

#endif /* ECMA_INTL_PHP_INTL_H */
