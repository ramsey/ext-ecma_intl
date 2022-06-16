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

#include "php_intl_ce.h"

#include "src/ecma_intl_arginfo.h"
#include "src/php/handlers/php_intl_handlers.h"
#include "src/php/objects/php_intl.h"
#include "src/unicode/bcp47.h"

#include <unicode/uloc.h>
#include <zend_exceptions.h>

zend_class_entry *ecmaIntlClass = NULL;

PHP_METHOD(Ecma_Intl, __construct) { ZEND_PARSE_PARAMETERS_NONE(); }

PHP_METHOD(Ecma_Intl, getCanonicalLocales) {
  HashTable *localeArray;
  zval *localeFromArray, localeFromString;
  zend_string *localeString;

  ZEND_PARSE_PARAMETERS_START(1, 1)
  Z_PARAM_ARRAY_HT_OR_STR(localeArray, localeString)
  ZEND_PARSE_PARAMETERS_END();

  if (localeArray == NULL) {
    ALLOC_HASHTABLE(localeArray);
    zend_hash_init(localeArray, 1, NULL, ZVAL_PTR_DTOR, 0);
    ZVAL_STR_COPY(&localeFromString, localeString);
    zend_hash_index_update(localeArray, 0, &localeFromString);
  }

  array_init_size(return_value, zend_hash_num_elements(localeArray));

  if (zend_hash_num_elements(localeArray) == 0) {
    if (localeString) {
      zend_hash_destroy(localeArray);
      FREE_HASHTABLE(localeArray);
    }
    return;
  }

  ZEND_HASH_FOREACH_VAL(localeArray, localeFromArray)
  if (Z_TYPE_P(localeFromArray) != IS_STRING) {
    zend_value_error("The $locales argument must be type string or an array of type string");
    RETURN_THROWS();
  }
  char bcp47LanguageTag[ULOC_FULLNAME_CAPACITY];
  if (icuToBcp47LanguageTag(Z_STRVAL_P(localeFromArray), bcp47LanguageTag)) {
    add_next_index_string(return_value, bcp47LanguageTag);
  }
  ZEND_HASH_FOREACH_END();

  if (localeString) {
    zend_hash_destroy(localeArray);
    FREE_HASHTABLE(localeArray);
  }

  if (EG(exception)) {
    RETURN_THROWS();
  }
}

void ecmaIntlRegisterClass() {
  ecmaIntlClass = register_class_Ecma_Intl();
  ecmaIntlClass->create_object = ecmaIntlObjCreate;

  ecmaIntlRegisterHandlers();
}
