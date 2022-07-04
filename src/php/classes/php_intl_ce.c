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

#include "php_enums_ce.h"
#include "php_exceptions_ce.h"
#include "src/ecma402/bcp47.h"
#include "src/ecma402/units.h"
#include "src/php/ecma_intl_arginfo.h"

#include <unicode/ucal.h>
#include <unicode/ucol.h>
#include <unicode/ucurr.h>
#include <unicode/uloc.h>
#include <unicode/unumsys.h>
#include <zend_exceptions.h>

zend_class_entry *ecmaIntlClass = NULL;

static zend_always_inline int phpArrayStringCaseCompare(Bucket *f, Bucket *s) {
  return string_case_compare_function(&f->val, &s->val);
}

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
  if (ecma402_icuToBcp47LanguageTag(Z_STRVAL_P(localeFromArray),
                                    bcp47LanguageTag) == ECMA_INTL_FAILURE) {
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
  zend_string *categoryValue;
  UEnumeration *values = NULL;
  UErrorCode status = U_ZERO_ERROR;
  const char *identifier, **units = NULL;
  int identifierLen;

  ZEND_PARSE_PARAMETERS_START(1, 1)
  Z_PARAM_OBJ_OF_CLASS(categoryEnum, ecmaIntlCategoryEnum)
  ZEND_PARSE_PARAMETERS_END();

  category = zend_enum_fetch_case_value(categoryEnum);
  categoryValue = Z_STR_P(category);

  if (strcasecmp(CATEGORY_CALENDAR, ZSTR_VAL(categoryValue)) == 0) {
    values = ucal_getKeywordValuesForLocale("calendar", NULL, 0, &status);
  } else if (strcasecmp(CATEGORY_COLLATION, ZSTR_VAL(categoryValue)) == 0) {
    values = ucol_getKeywordValues("collation", &status);
  } else if (strcasecmp(CATEGORY_CURRENCY, ZSTR_VAL(categoryValue)) == 0) {
    values = ucurr_openISOCurrencies(UCURR_ALL, &status);
  } else if (strcasecmp(CATEGORY_NUMBERING_SYSTEM, ZSTR_VAL(categoryValue)) ==
             0) {
    values = unumsys_openAvailableNames(&status);
  } else if (strcasecmp(CATEGORY_TIME_ZONE, ZSTR_VAL(categoryValue)) == 0) {
    values = ucal_openTimeZones(&status);
  } else if (strcasecmp(CATEGORY_UNIT, ZSTR_VAL(categoryValue)) == 0) {
    int unitsCount;
    units = ecma402_getAllMeasurementUnits(&unitsCount);
    values = uenum_openCharStringsEnumeration(units, unitsCount, &status);
  }

  if (U_FAILURE(status)) {
    zend_throw_error(ecmaIntlIcuExceptionClass, "%s", u_errorName(status));
    RETURN_THROWS();
  }

  int count = uenum_count(values, &status);
  uenum_reset(values, &status);

  array_init_size(return_value, count);

  for (int i = 0; i < count; i++) {
    identifier = uenum_next(values, &identifierLen, &status);

    if (strcasecmp(CATEGORY_CALENDAR, ZSTR_VAL(categoryValue)) == 0) {
      add_next_index_string(
          return_value,
          uloc_toUnicodeLocaleType(ICU_KEYWORD_CALENDAR, identifier));
    } else if (strcasecmp(CATEGORY_COLLATION, ZSTR_VAL(categoryValue)) == 0) {
      add_next_index_string(
          return_value,
          uloc_toUnicodeLocaleType(ICU_KEYWORD_COLLATION, identifier));
    } else if (strcasecmp(CATEGORY_NUMBERING_SYSTEM, ZSTR_VAL(categoryValue)) ==
               0) {
      add_next_index_string(
          return_value,
          uloc_toUnicodeLocaleType(ICU_KEYWORD_NUMBERING_SYSTEM, identifier));
    } else {
      add_next_index_stringl(return_value, identifier, identifierLen);
    }
  }

  uenum_close(values);

  if (units) {
    free(units);
  }

  zend_hash_sort(Z_ARRVAL_P(return_value), phpArrayStringCaseCompare, 1);
}

void ecmaIntlRegisterClass() { ecmaIntlClass = register_class_Ecma_Intl(); }
