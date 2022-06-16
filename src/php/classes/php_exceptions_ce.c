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

#include "php_exceptions_ce.h"

#include <Zend/zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>

#include "src/ecma_intl_arginfo.h"

zend_class_entry *ecmaIntlIcuExceptionClass = NULL;
zend_class_entry *ecmaIntlRangeErrorClass = NULL;
zend_class_entry *ecmaIntlExceptionInterface = NULL;

void ecmaIntlRegisterExceptionClasses() {
  ecmaIntlExceptionInterface = register_class_Ecma_Intl_Exception();

  ecmaIntlIcuExceptionClass = register_class_Ecma_Intl_IcuException(
      spl_ce_RuntimeException, ecmaIntlExceptionInterface);

  ecmaIntlRangeErrorClass = register_class_Ecma_Intl_RangeError(
      zend_ce_value_error, ecmaIntlExceptionInterface);
}
