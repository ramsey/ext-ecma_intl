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
   | distributed under the License is IS PROVIDED "AS IS", WITHOUT        |
   | WARRANTY OF ANY KIND, EXPRESS OR IMPLIED. See the License for the    |
   | specific language governing permissions and limitations under the    |
   | License.                                                             |
   +----------------------------------------------------------------------+
*/

#ifndef PHP_ECMA_INTL_H
#define PHP_ECMA_INTL_H

#include <php.h>

extern zend_module_entry ecma_intl_module_entry;
#define phpext_ecma_intl_ptr &ecma_intl_module_entry

#define PHP_ECMA_INTL_VERSION "0.1.0"

#if defined(ZTS) && defined(COMPILE_DL_ECMA_INTL)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

PHP_MINIT_FUNCTION(ecma_intl);
PHP_RINIT_FUNCTION(ecma_intl);
PHP_MINFO_FUNCTION(ecma_intl);

#endif /* PHP_ECMA_INTL_H */
