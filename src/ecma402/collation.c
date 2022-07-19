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

#include "collation.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unicode/ucol.h>

int getSupportedCollations(const char *localeId, const char **collations) {
  UEnumeration *supported = NULL;
  UErrorCode status = U_ZERO_ERROR;
  char *preferred;
  const char *name, *tmpName;
  int preferredLength, count = 0;

  preferred = (char *)malloc(sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  if (!preferred) {
    return 0;
  }

  preferredLength =
      uloc_getKeywordValue(localeId, ICU_KEYWORD_COLLATION, preferred,
                           ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

  if (preferredLength > 0) {
    tmpName = uloc_toUnicodeLocaleType(ICU_KEYWORD_COLLATION, preferred);
    collations[0] = (const char *)malloc(strlen(tmpName) + 1);
    memcpy((void *)collations[0], tmpName, strlen(tmpName) + 1);
    free(preferred);

    return 1;
  }

  free(preferred);

  supported = ucol_getKeywordValuesForLocale(ICU_KEYWORD_COLLATION, localeId,
                                             true, &status);
  if (U_FAILURE(status)) {
    return 0;
  }

  while ((name = uenum_next(supported, NULL, &status))) {
    if (U_FAILURE(status)) {
      continue;
    }

    /* Intl Locale Info Proposal, section 1.1.3, step 4, requires the values
     * "standard" and "search" must be excluded from this list.
     * See: https://tc39.es/proposal-intl-locale-info/#sec-collations-of-locale
     */
    if (strcmp(name, "standard") == 0 || strcmp(name, "search") == 0) {
      continue;
    }

    tmpName = uloc_toUnicodeLocaleType(ICU_KEYWORD_COLLATION, name);
    collations[count] = (const char *)malloc(strlen(tmpName) + 1);
    if (!collations[count]) {
      continue;
    }
    memcpy((void *)collations[count], tmpName, strlen(tmpName) + 1);

    count++;
  }

  uenum_close(supported);

  return count;
}
