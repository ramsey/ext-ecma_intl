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

#include "php_intl_handlers.h"
#include "src/php/objects/php_intl.h"

zend_object_handlers ecmaIntlObjHandlers;

static void ecmaIntlObjFree(zend_object *object) {
  ecmaIntlObj *intlObj = ecmaIntlObjFromObj(object);

  zend_object_std_dtor(&intlObj->std);
}

void ecmaIntlRegisterHandlers() {
  memcpy(&ecmaIntlObjHandlers, zend_get_std_object_handlers(),
         sizeof(zend_object_handlers));

  ecmaIntlObjHandlers.offset = XtOffsetOf(ecmaIntlObj, std);
  ecmaIntlObjHandlers.free_obj = ecmaIntlObjFree;
}
