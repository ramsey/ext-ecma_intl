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

#include "range_error.h"

#include "exception.h"
#include <Zend/zend_exceptions.h>

#include "src/php/ecma_intl_arginfo.h"

zend_class_entry *ecmaIntlRangeErrorClass = NULL;

void registerEcmaIntlRangeErrorClass() {
  ecmaIntlRangeErrorClass = register_class_Ecma_Intl_RangeError(
      zend_ce_value_error, ecmaIntlExceptionInterface);
}
