/*
   +----------------------------------------------------------------------+
   | Copyright (c) Ben Ramsey <ramsey@php.net>                            |
   +----------------------------------------------------------------------+
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

#include <unicode/uloc.h>
#include <unicode/uversion.h>
#include <php.h>
#include <ext/spl/spl_exceptions.h>
#include <ext/standard/info.h>

#include "php_ecma_intl.h"
#include "ecma_intl_arginfo.h"

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
	HashTable *locales;
	zval *locale;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ARRAY_HT(locales)
	ZEND_PARSE_PARAMETERS_END();

	array_init_size(return_value, zend_hash_num_elements(locales));

	if (zend_hash_num_elements(locales) == 0) {
		return;
	}

	ZEND_HASH_FOREACH_VAL(locales, locale)
		if (Z_TYPE_P(locale) != IS_STRING) {
			zend_throw_error(spl_ce_InvalidArgumentException,
							 "The $locales argument must be an array of type string");
			RETURN_THROWS();
		}
		char languageTag[ULOC_FULLNAME_CAPACITY];
		toCanonicalBcp47LanguageTag(Z_STRVAL_P(locale), languageTag);
		add_next_index_string(return_value, languageTag);
	ZEND_HASH_FOREACH_END();

	if (EG(exception)) {
		RETURN_THROWS();
	}
}

PHP_RINIT_FUNCTION(ecma_intl)
{
#if defined(ZTS) && defined(COMPILE_DL_ECMA_INTL)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}

PHP_MINFO_FUNCTION(ecma_intl)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "ecma_intl support", "enabled");
	php_info_print_table_header(2, "icu version", U_ICU_VERSION);
	php_info_print_table_end();
}

zend_module_entry ecma_intl_module_entry = {
	STANDARD_MODULE_HEADER,
	"ecma_intl",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(ecma_intl),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(ecma_intl),			/* PHP_MINFO - Module info */
	PHP_ECMA_INTL_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ECMA_INTL
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(ecma_intl)
#endif
