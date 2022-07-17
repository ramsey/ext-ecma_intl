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

#ifndef ECMA_INTL_PHP_SUPPORT_NUMBERING_SYSTEM_H
#define ECMA_INTL_PHP_SUPPORT_NUMBERING_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the PHP numbering system enum case name for the given value.
 *
 * @param value The numbering system value.
 *
 * @return A case name for the PHP numbering system enum.
 */
const char *getNumberingSystemCaseName(const char *value);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_PHP_SUPPORT_NUMBERING_SYSTEM_H */
