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

#include "intl.h"

#include "category.h"
#include "range_error.h"
#include "src/ecma402/bcp47.h"
#include "src/ecma402/category.h"
#include "src/php/ecma_intl_arginfo.h"

#include <unicode/uloc.h>
#include <zend_exceptions.h>

zend_class_entry *ecmaIntlClass = NULL;

void registerEcmaIntlClass() { ecmaIntlClass = register_class_Ecma_Intl(); }

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
    zend_value_error(
        "The $locales argument must be type string or an array of type string");
    RETURN_THROWS();
  }
  char bcp47LanguageTag[ULOC_FULLNAME_CAPACITY];
  if (icuToBcp47LanguageTag(Z_STRVAL_P(localeFromArray), bcp47LanguageTag) ==
      ECMA_INTL_FAILURE) {
    zend_throw_error(ecmaIntlRangeErrorClass, "invalid language tag: %s",
                     Z_STRVAL_P(localeFromArray));
  } else {
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

PHP_METHOD(Ecma_Intl, supportedValuesOf) {
  zend_object *categoryEnum;
  zval *category;
  const char **values = NULL;
  char *categoryValue;
  int valuesCount;

  ZEND_PARSE_PARAMETERS_START(1, 1)
  Z_PARAM_OBJ_OF_CLASS(categoryEnum, ecmaIntlCategoryEnum)
  ZEND_PARSE_PARAMETERS_END();

  category = zend_enum_fetch_case_value(categoryEnum);
  categoryValue = ZSTR_VAL(Z_STR_P(category));

  values = (const char **)emalloc(sizeof(const char *) *
                                  getCapacityForCategory(categoryValue));
  valuesCount = getSupportedValuesForCategory(categoryValue, values);

  array_init_size(return_value, valuesCount);

  for (int i = 0; i < valuesCount; i++) {
    add_next_index_string(return_value, values[i]);
  }

  if (values) {
    for (int i = 0; i < valuesCount; i++) {
      free((void *)values[i]);
    }
    efree(values);
  }
}
