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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <php.h>
#include <ext/spl/spl_exceptions.h>
#include <unicode/uloc.h>

#include "functions.h"

void toCanonicalBcp47LanguageTag(const char *localeId, char *languageTag)
{
	int32_t languageTagCapacity = ULOC_FULLNAME_CAPACITY;
	UErrorCode status = U_ZERO_ERROR;

	uloc_toLanguageTag(localeId, languageTag, languageTagCapacity, true, &status);

	if (status != U_ZERO_ERROR) {
		zend_throw_error(spl_ce_RangeException,
						 "Invalid language tag: \"%s\"",
						 localeId);
	}
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
		toCanonicalBcp47LanguageTag(Z_STRVAL_P(localeFromArray), languageTag);
		add_next_index_string(return_value, languageTag);
		zval_ptr_dtor(localeFromArray);
	ZEND_HASH_FOREACH_END();

	if (EG(exception)) {
		RETURN_THROWS();
	}
}

PHP_FUNCTION(getSupportedLocales)
{
	int32_t count;

	ZEND_PARSE_PARAMETERS_NONE();

	count = uloc_countAvailable();

	array_init_size(return_value, count);

	for (int i = 0; i < count; i++) {
		const char *locale;
		char languageTag[ULOC_FULLNAME_CAPACITY];
		locale = uloc_getAvailable(i);
		toCanonicalBcp47LanguageTag(locale, languageTag);
		add_next_index_string(return_value, languageTag);
	}
}
