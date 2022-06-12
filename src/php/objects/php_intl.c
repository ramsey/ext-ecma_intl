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

#include "php_intl.h"
#include "src/php/handlers/php_intl_handlers.h"

zend_object *ecmaIntlObjCreate(zend_class_entry *classType) {
  ecmaIntlObj *intlObj = zend_object_alloc(sizeof(ecmaIntlObj), classType);
  zend_object_std_init(&intlObj->std, classType);
  object_properties_init(&intlObj->std, classType);
  intlObj->std.handlers = &ecmaIntlObjHandlers;

  return &intlObj->std;
}
