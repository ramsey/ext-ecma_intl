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

#include "bcp47.h"

#include <string.h>
#include <unicode/uloc.h>

int icuToBcp47LanguageTag(const char *icuLanguageTag, char *bcp47LanguageTag,
                          errorStatus *status) {
  int languageTagLen;
  UErrorCode icuStatus = U_ZERO_ERROR;

  languageTagLen = uloc_toLanguageTag(icuLanguageTag, bcp47LanguageTag,
                                      ULOC_FULLNAME_CAPACITY, 1, &icuStatus);

  if (U_FAILURE(icuStatus)) {
    icuError(status, icuStatus, __FILE__, __LINE__, NULL);
    return 0;
  }

  return languageTagLen;
}
