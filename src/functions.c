/*
   +----------------------------------------------------------------------+
   | ecma_intl extension for PHP                                          |
   | Internationalization Support, Ecma-style (ECMA-402)                  |
   +----------------------------------------------------------------------+
   | Copyright (c) Ben Ramsey <ben@benramsey.com>                         |
   |                                                                      |
   | Licensed under the Apache License, Version 2.0 (the "License");      |
   | you may not use this file except in compliance with the License.     |
   | You may obtain a copy of the License at                              |
   |                                                                      |
   |     http://www.apache.org/licenses/LICENSE-2.0                       |
   |                                                                      |
   | Unless required by applicable law or agreed to in writing, software  |
   | distributed under the License is distributed on an "AS IS" BASIS,    |
   | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
   | implied. See the License for the specific language governing         |
   | permissions and limitations under the License.                       |
   +----------------------------------------------------------------------+
*/

#include <php.h>
#include <ext/spl/spl_exceptions.h>
#include <unicode/ucal.h>
#include <unicode/ucol.h>
#include <unicode/ucurr.h>
#include <unicode/uloc.h>
#include <unicode/unumsys.h>
#include <unicode/utypes.h>

#include "exceptions.h"
#include "functions.h"
#include "measure_unit_bridge.h"

#define CATEGORY_CALENDAR "calendar"
#define CATEGORY_COLLATION "collation"
#define CATEGORY_CURRENCY "currency"
#define CATEGORY_NUMBERING_SYSTEM "numberingSystem"
#define CATEGORY_TIME_ZONE "timeZone"
#define CATEGORY_UNIT "unit"

void ecma_intl_toCanonicalBcp47LanguageTag(const char *localeId, char *languageTag)
{
	int32_t languageTagCapacity = ULOC_FULLNAME_CAPACITY;
	UErrorCode status = U_ZERO_ERROR;

	uloc_toLanguageTag(localeId, languageTag, languageTagCapacity, true, &status);

	if (U_FAILURE(status)) {
		zend_throw_error(spl_ce_RangeException,
						 "Invalid language tag: \"%s\"",
						 localeId);
	}
}

static zend_always_inline int php_array_string_case_compare(Bucket *f, Bucket *s)
{
	return string_case_compare_function(&f->val, &s->val);
}

PHP_FUNCTION(getCanonicalLocales)
{
	HashTable *localeArray;
	zval *localeFromArray, localeFromString;
	zend_string *localeString;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ARRAY_HT_OR_STR(localeArray, localeString)
	ZEND_PARSE_PARAMETERS_END();

	if (localeArray == NULL) {
		localeArray = (HashTable *) malloc(sizeof(HashTable));
		zend_hash_init(localeArray, 1, NULL, ZVAL_PTR_DTOR, 0);
		ZVAL_STR(&localeFromString, localeString);
		zend_hash_index_update(localeArray, 0, &localeFromString);
		zend_string_release(localeString);
		zval_ptr_dtor(&localeFromString);
	}

	array_init_size(return_value, zend_hash_num_elements(localeArray));

	if (zend_hash_num_elements(localeArray) == 0) {
		return;
	}

	ZEND_HASH_FOREACH_VAL(localeArray, localeFromArray)
		if (Z_TYPE_P(localeFromArray) != IS_STRING) {
			zend_throw_error(spl_ce_InvalidArgumentException,
							 "The $locales argument must be an array of type string");
			RETURN_THROWS();
		}
		char languageTag[ULOC_FULLNAME_CAPACITY];
		ecma_intl_toCanonicalBcp47LanguageTag(Z_STRVAL_P(localeFromArray), languageTag);
		add_next_index_string(return_value, languageTag);
		zval_ptr_dtor(localeFromArray);
	ZEND_HASH_FOREACH_END();

	if (EG(exception)) {
		RETURN_THROWS();
	}
}

PHP_FUNCTION(getSupportedLocales)
{
	ZEND_PARSE_PARAMETERS_NONE();

	int count = uloc_countAvailable();

	array_init_size(return_value, count);

	for (int i = 0; i < count; i++) {
		const char *locale;
		char languageTag[ULOC_FULLNAME_CAPACITY];
		locale = uloc_getAvailable(i);
		ecma_intl_toCanonicalBcp47LanguageTag(locale, languageTag);
		add_next_index_string(return_value, languageTag);
	}
}

PHP_FUNCTION(supportedValuesOf)
{
	zend_string *key;
	UEnumeration *values = NULL;
	UErrorCode status = U_ZERO_ERROR;

	int count, length, i;
	const char* identifier;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		 Z_PARAM_STR(key)
	ZEND_PARSE_PARAMETERS_END();

	if (strcasecmp(CATEGORY_CALENDAR, ZSTR_VAL(key)) == 0) {
		values = ucal_getKeywordValuesForLocale("calendar", NULL, 0, &status);
	} else if (strcasecmp(CATEGORY_COLLATION, ZSTR_VAL(key)) == 0) {
		values = ucol_getKeywordValues("collation", &status);
	} else if (strcasecmp(CATEGORY_CURRENCY, ZSTR_VAL(key)) == 0) {
		values = ucurr_openISOCurrencies(UCURR_ALL, &status);
	} else if (strcasecmp(CATEGORY_NUMBERING_SYSTEM, ZSTR_VAL(key)) == 0) {
		values = unumsys_openAvailableNames(&status);
	} else if (strcasecmp(CATEGORY_TIME_ZONE, ZSTR_VAL(key)) == 0) {
		values = ucal_openTimeZones(&status);
	} else if (strcasecmp(CATEGORY_UNIT, ZSTR_VAL(key)) == 0) {
		values = ecma_intl_getMeasurementUnits(&status);
	} else {
		zend_throw_error(spl_ce_RangeException,
						 "Unknown key for Ecma\\Intl\\supportedValuesOf()");
		RETURN_THROWS();
	}

	if (U_FAILURE(status)) {
		zend_throw_error(ecma_intl_ce_Exception,"%s", u_errorName(status));
		RETURN_THROWS();
	}

	count = uenum_count(values, &status);
	uenum_reset(values, &status);

	array_init_size(return_value, count);

	for (i = 0; i < count; i++) {
		identifier = uenum_next(values, &length, &status);
		add_next_index_string(return_value, identifier);
	}

	uenum_close(values);

	zend_hash_sort(Z_ARRVAL_P(return_value), php_array_string_case_compare, 1);
}
