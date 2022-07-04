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

#include "locale.h"

#include <stdlib.h>
#include <string.h>

ecma402_locale *ecma402_initLocale(const char *localeId) {
  ecma402_locale *locale;

  if (!localeId || strcmp(localeId, "") == 0) {
    return NULL;
  }

  locale = (ecma402_locale *)(malloc(sizeof(*locale)));

  if (!locale) {
    return NULL;
  }

  locale->id = strdup(localeId);
  locale->length = strlen(localeId);

  return locale;
}

void ecma402_freeLocale(ecma402_locale *locale) {
  free(locale->id);
  free(locale);
}
