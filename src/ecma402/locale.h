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

#ifndef ECMA_INTL_ECMA402_ECMA_LOCALE_H
#define ECMA_INTL_ECMA402_ECMA_LOCALE_H

#include "src/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Represents a locale identifier, e.g. "en-US."
 */
typedef struct ecma402_locale {
  /**
   * Locale identifier, e.g., "en-US."
   */
  char *id;

  /**
   * Length of the locale identifier.
   */
  unsigned long length;

} ecma402_locale;

/**
 * Initializes a locale struct with the given locale identifier. This also
 * allocates the struct on the stack; free it using ecma402_freeLocale().
 *
 * @param localeId The locale identifier, e.g., "en-US."
 *
 * @return A locale.
 */
ecma402_locale *ecma402_initLocale(const char *localeId);

/**
 * Frees a locale initialized with ecma402_initLocale().
 *
 * @param locale The locale to free.
 */
void ecma402_freeLocale(ecma402_locale *locale);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_ECMA402_ECMA_LOCALE_H */
