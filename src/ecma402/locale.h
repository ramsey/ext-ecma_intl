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

#ifndef ECMA_INTL_ECMA402_LOCALE_H
#define ECMA_INTL_ECMA402_LOCALE_H

#include "src/common.h"

#include "error.h"

#include <stdbool.h>
#include <unicode/utypes.h>

#define NUMERIC_TRUE "true"
#define NUMERIC_FALSE "false"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Represents a locale identifier, e.g. "en-US."
 */
typedef struct locale {
  /**
   * The base name of this locale without extensions.
   */
  char *baseName;

  /**
   * The calendar type of this locale.
   */
  char *calendar;

  /**
   * The ICU canonical version of the locale identifier.
   */
  char *canonicalId;

  /**
   * Whether to sort strings in this locale by uppercase or lowercase first.
   */
  char *caseFirst;

  /**
   * The collation type of this locale.
   */
  char *collation;

  /**
   * The hour cycle for this locale.
   */
  char *hourCycle;

  /**
   * The full locale identifier.
   */
  char *id;

  /**
   * The language of this locale.
   */
  char *language;

  /**
   * The numbering system for this locale.
   */
  char *numberingSystem;

  /**
   * Whether this locale has special collation handling for numeric characters.
   */
  bool numeric;

  /**
   * The original full locale identifier, before processing.
   */
  char *originalId;

  /**
   * The region of this locale.
   */
  char *region;

  /**
   * This script of this locale.
   */
  char *script;

  /**
   * Indicates whether there is an error with this locale. This property allows
   * us to pass the error(s) back up for proper PHP exception throwing, etc.
   */
  errorStatus *status;

} locale;

/**
 * Initializes an empty locale struct. This also allocates the struct on the
 * stack; free it using freeLocale().
 *
 * @return A locale.
 */
locale *initEmptyLocale(void);

/**
 * Initializes a locale struct with the given locale identifier. This
 * also allocates the struct and its properties on the stack; free it using
 * freeLocale().
 *
 * @param localeId The locale identifier, e.g., "en-US."
 *
 * @return A locale.
 */
locale *initLocale(const char *localeId);

/**
 * Frees a locale initialized with initLocale().
 *
 * @param locale The locale to free.
 */
void freeLocale(locale *locale);

/**
 * Returns a new empty locale with the errorStatus field populated with an
 * ecmaErrorCode as the error.
 */
locale *localeWithEcmaError(ecmaErrorCode errorCode, const char *fileName,
                            int lineNumber, const char *errorMessage);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_ECMA402_LOCALE_H */
