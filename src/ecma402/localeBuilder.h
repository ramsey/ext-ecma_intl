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

#ifndef ECMA_INTL_ECMA402_LOCALE_BUILDER_H
#define ECMA_INTL_ECMA402_LOCALE_BUILDER_H

#include "locale.h"
#include "src/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Options that may be used to dynamically build a locale.
 */
typedef struct ecma402_localeBuilderOptions {
  /**
   * The calendar type to use with the locale, e.g., "buddhist," "hebrew,"
   * "gregory," etc.
   */
  char *calendar;

  /**
   * Whether to sort by uppercase or lowercase first. Acceptable values are
   * "upper," "lower," and the string "false."
   */
  char *caseFirst;

  /**
   * The collation type to use with the locale, e.g. "big5han," "eor,"
   * "phonebk," etc.
   */
  char *collation;

  /**
   * The time cycle to use with the locale. Acceptable values are "h12," "h23,"
   * "h11," and "h24."
   */
  char *hourCycle;

  /**
   * The locale's language, e.g. "en."
   */
  char *language;

  /**
   * The numbering system to use with the locale, e.g., "latn," "arab," "jpan,"
   * etc.
   */
  char *numberingSystem;

  /**
   * Whether the locale has special collation handling for numeric characters.
   */
  bool *numeric;

  /**
   * The locale's region, e.g. "US."
   */
  char *region;

  /**
   * The locale's script, e.g. "Latn," "Cyrl," etc.
   */
  char *script;

} ecma402_localeBuilderOptions;

/**
 * Initializes a locale options struct that may be used to dynamically build a
 * locale. This also allocates the struct on the stack; free it using
 * ecma402_freeLocaleBuilderOptions().
 *
 * @param calendar The calendar type to use with the locale.
 * @param caseFirst Whether to sort by uppercase or lowercase first.
 * @param collation The collation type to use with the locale.
 * @param hourCycle The time cycle to use with the locale.
 * @param language The locale's language.
 * @param numberingSystem The numbering system to use with the locale.
 * @param numeric Whether the locale has special collation handling for numeric
 *     characters.
 * @param region The locale's region.
 * @param script The locale's script.
 *
 * @return An ecma402_localeBuilderOptions struct.
 */
ecma402_localeBuilderOptions *ecma402_initLocaleBuilderOptions(
    char *calendar, char *caseFirst, char *collation, char *hourCycle,
    char *language, char *numberingSystem, const bool *numeric, char *region,
    char *script);

/**
 * Frees locale builder options initialized with
 * ecma402_initLocaleBuilderOptions().
 *
 * @param options The locale builder options to free.
 */
void ecma402_freeLocaleBuilderOptions(ecma402_localeBuilderOptions *options);

/**
 * Uses localeId as a starting point for dynamically building a locale by adding
 * the options provided to the locale.
 *
 * @param localeId The locale identifier, e.g., "en-US."
 * @param options The options to apply to build a new locale.
 *
 * @return The new locale.
 */
ecma402_locale *ecma402_buildLocale(const char *localeId,
                                    ecma402_localeBuilderOptions *options);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_ECMA402_LOCALE_BUILDER_H */
