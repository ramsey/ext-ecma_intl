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

#ifndef ECMA_INTL_PHP_COMMON_H
#define ECMA_INTL_PHP_COMMON_H

#include <php.h>
#include <zend_enum.h>

#include "src/common.h"

#define RETURN_ENUM_CASE(enumClassEntry, enumCaseName, enumValue)              \
  do {                                                                         \
    if (enumCaseName == NULL) {                                                \
      zend_value_error("\"%s\" is not a valid backing value for enum \"%s\"",  \
                       enumValue, ZSTR_VAL(enumClassEntry->name));             \
      return NULL;                                                             \
    }                                                                          \
    zend_string *enumCaseStr =                                                 \
        zend_string_init(enumCaseName, strlen(enumCaseName), 0);               \
    zend_object *enumCase = zend_enum_get_case(enumClassEntry, enumCaseStr);   \
    zend_string_release(enumCaseStr);                                          \
    return enumCase;                                                           \
  } while (0)

#endif /* ECMA_INTL_PHP_COMMON_H */
