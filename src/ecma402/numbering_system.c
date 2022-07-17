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

#include "numbering_system.h"

#include <stdlib.h>
#include <string.h>
#include <unicode/uloc.h>
#include <unicode/unumsys.h>

int getSupportedNumberingSystems(const char *localeId,
                                 const char **numberingSystems) {
  UNumberingSystem *numberingSystem;
  UErrorCode status = U_ZERO_ERROR;
  char *preferred;
  const char *name, *tmpName;
  int preferredLength;

  preferred = (char *)malloc(sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  if (!preferred) {
    return 0;
  }

  preferredLength =
      uloc_getKeywordValue(localeId, ICU_KEYWORD_NUMBERING_SYSTEM, preferred,
                           ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

  if (preferredLength > 0) {
    tmpName = uloc_toUnicodeLocaleType(ICU_KEYWORD_NUMBERING_SYSTEM, preferred);
    free(preferred);

    numberingSystems[0] = (const char *)malloc(strlen(tmpName) + 1);
    if (!numberingSystems[0]) {
      return 0;
    }
    memcpy((void *)numberingSystems[0], tmpName, strlen(tmpName) + 1);

    return 1;
  }

  free(preferred);

  numberingSystem = unumsys_open(localeId, &status);
  if (U_FAILURE(status)) {
    return 0;
  }

  name = unumsys_getName(numberingSystem);

  tmpName = uloc_toUnicodeLocaleType(ICU_KEYWORD_NUMBERING_SYSTEM, name);
  unumsys_close(numberingSystem);

  numberingSystems[0] = (const char *)malloc(strlen(tmpName) + 1);
  if (!numberingSystems[0]) {
    return 0;
  }
  memcpy((void *)numberingSystems[0], tmpName, strlen(tmpName) + 1);

  return 1;
}
