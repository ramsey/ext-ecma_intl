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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <unicode/ucal.h>
#include <unicode/uchar.h>
#include <unicode/uversion.h>

#include "ecma_intl.h"

#include "src/ecma_intl_arginfo.h"
#include "src/php/classes/php_calendar_ce.h"
#include "src/php/classes/php_category_ce.h"
#include "src/php/classes/php_case_first_ce.h"
#include "src/php/classes/php_collation_ce.h"
#include "src/php/classes/php_exceptions_ce.h"
#include "src/php/classes/php_formatting_ce.h"
#include "src/php/classes/php_hour_cycle_ce.h"
#include "src/php/classes/php_intl_ce.h"
#include "src/php/classes/php_numbering_system_ce.h"

#include <ext/standard/info.h>

zend_module_entry ecma_intl_module_entry = {STANDARD_MODULE_HEADER,
                                            "ecma_intl",
                                            NULL,
                                            PHP_MINIT(ecma_intl),
                                            NULL,
                                            PHP_RINIT(ecma_intl),
                                            NULL,
                                            PHP_MINFO(ecma_intl),
                                            PHP_ECMA_INTL_VERSION,
                                            STANDARD_MODULE_PROPERTIES};

#ifdef COMPILE_DL_ECMA_INTL
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(ecma_intl)
#endif

PHP_MINIT_FUNCTION(ecma_intl) {
  ecmaIntlCalendarRegisterEnum();
  ecmaIntlCaseFirstRegisterEnum();
  ecmaIntlCategoryRegisterEnum();
  ecmaIntlCollationRegisterEnum();
  ecmaIntlFormattingRegisterEnum();
  ecmaIntlHourCycleRegisterEnum();
  ecmaIntlNumberingSystemRegisterEnum();
  ecmaIntlRegisterExceptionClasses();
  ecmaIntlRegisterClass();

  return SUCCESS;
}

PHP_RINIT_FUNCTION(ecma_intl) {
#if defined(ZTS) && defined(COMPILE_DL_ECMA_INTL)
  ZEND_TSRMLS_CACHE_UPDATE();
#endif

  return SUCCESS;
}

PHP_MINFO_FUNCTION(ecma_intl) {
  UErrorCode status = U_ZERO_ERROR;
  const char *timeZoneDataVersion;

  timeZoneDataVersion = ucal_getTZDataVersion(&status);
  if (U_FAILURE(status)) {
    timeZoneDataVersion = "n/a";
  }

  php_info_print_table_start();
  php_info_print_table_header(
      2, "Internationalization Support, Ecma-style (ECMA-402)", "enabled");
  php_info_print_table_row(2, "ecma_intl version", PHP_ECMA_INTL_VERSION);
  php_info_print_table_row(2, "ICU version", U_ICU_VERSION);
  php_info_print_table_row(2, "ICU Data version", U_ICU_DATA_VERSION);
  php_info_print_table_row(2, "ICU TZData version", timeZoneDataVersion);
  php_info_print_table_row(2, "ICU Unicode version", U_UNICODE_VERSION);
  php_info_print_table_end();
}
