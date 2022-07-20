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

#include "bcp47.h"

#include <stdlib.h>
#include <string.h>
#include <unicode/errorcode.h>
#include <unicode/uloc.h>

#define FREE_PROPERTY(property)                                                \
  do {                                                                         \
    if (locale->property != NULL) {                                            \
      free(locale->property);                                                  \
    }                                                                          \
  } while (0)

static char *copyOriginalId(const char *localeId, errorStatus *status);
static char *getBaseName(const char *localeId, errorStatus *status);
static char *getBcp47Identifier(const char *localeId, errorStatus *status);
static char *getKeyword(const char *keyword, const char *localeId,
                        errorStatus *status);
static char *getLanguage(const char *localeId, errorStatus *status);
static bool getNumeric(const char *localeId, errorStatus *status);
static char *getRegion(const char *localeId, errorStatus *status);
static char *getScript(const char *localeId, errorStatus *status);
static const char *normalizeLocaleId(const char *localeId);

locale *initEmptyLocale() {
  locale *locale;

  locale = (struct locale *)malloc(sizeof(*locale));
  if (!locale) {
    return NULL;
  }

  locale->baseName = NULL;
  locale->calendar = NULL;
  locale->canonicalId = NULL;
  locale->caseFirst = NULL;
  locale->collation = NULL;
  locale->hourCycle = NULL;
  locale->id = NULL;
  locale->language = NULL;
  locale->numberingSystem = NULL;
  locale->numeric = false;
  locale->originalId = NULL;
  locale->region = NULL;
  locale->script = NULL;
  locale->status = initErrorStatus();

  return locale;
}

locale *initLocale(const char *localeId) {
  locale *locale;
  char *canonicalId;
  UErrorCode icuStatus = U_ZERO_ERROR;

  localeId = normalizeLocaleId(localeId);
  if (localeId == NULL) {
    return NULL;
  }

  locale = initEmptyLocale();
  if (!locale) {
    return NULL;
  }

  locale->originalId = copyOriginalId(localeId, locale->status);

  canonicalId = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  if (!canonicalId) {
    memoryError(locale->status, __FILE__, __LINE__);
    return locale;
  }

  uloc_canonicalize(locale->originalId, canonicalId, ULOC_FULLNAME_CAPACITY,
                    &icuStatus);
  if (U_FAILURE(icuStatus)) {
    free(canonicalId);
    icuError(locale->status, icuStatus, __FILE__, __LINE__, NULL);
    return locale;
  }

  locale->canonicalId = canonicalId;

  locale->baseName = getBaseName(canonicalId, locale->status);
  locale->calendar =
      getKeyword(ICU_KEYWORD_CALENDAR, canonicalId, locale->status);
  locale->caseFirst =
      getKeyword(ICU_KEYWORD_CASE_FIRST, canonicalId, locale->status);
  locale->collation =
      getKeyword(ICU_KEYWORD_COLLATION, canonicalId, locale->status);
  locale->hourCycle =
      getKeyword(ICU_KEYWORD_HOUR_CYCLE, canonicalId, locale->status);
  locale->id = getBcp47Identifier(canonicalId, locale->status);
  locale->language = getLanguage(canonicalId, locale->status);
  locale->numberingSystem =
      getKeyword(ICU_KEYWORD_NUMBERING_SYSTEM, canonicalId, locale->status);
  locale->numeric = getNumeric(canonicalId, locale->status);
  locale->region = getRegion(canonicalId, locale->status);
  locale->script = getScript(canonicalId, locale->status);

  return locale;
}

void freeLocale(locale *locale) {
  FREE_PROPERTY(baseName);
  FREE_PROPERTY(calendar);
  FREE_PROPERTY(canonicalId);
  FREE_PROPERTY(caseFirst);
  FREE_PROPERTY(collation);
  FREE_PROPERTY(hourCycle);
  FREE_PROPERTY(id);
  FREE_PROPERTY(language);
  FREE_PROPERTY(numberingSystem);
  FREE_PROPERTY(originalId);
  FREE_PROPERTY(region);
  FREE_PROPERTY(script);
  freeErrorStatus(locale->status);
  free(locale);
}

locale *localeWithEcmaError(ecmaErrorCode errorCode, const char *fileName,
                            int lineNumber, const char *errorMessage) {
  locale *locale = initEmptyLocale();
  ecmaError(locale->status, errorCode, fileName, lineNumber, errorMessage);

  return locale;
}

locale *maximizeLocale(locale *locale) {
  char *maxLocaleId;
  struct locale *maxLocale;
  UErrorCode icuStatus = U_ZERO_ERROR;

  maxLocaleId = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  uloc_addLikelySubtags(locale->canonicalId, maxLocaleId,
                        ULOC_FULLNAME_CAPACITY, &icuStatus);

  if (U_FAILURE(icuStatus)) {
    free(maxLocaleId);
    return localeWithEcmaError(UNABLE_TO_MAXIMIZE_LOCALE, __FILE__, __LINE__,
                               NULL);
  }

  maxLocale = initLocale(getBcp47Identifier(maxLocaleId, NULL));
  free(maxLocaleId);

  return maxLocale;
}

locale *minimizeLocale(locale *locale) {
  char *minLocaleId;
  UErrorCode icuStatus = U_ZERO_ERROR;
  struct locale *maxLocale;
  struct locale *minLocale;

  /* We get the max locale first and then minimize it. */
  maxLocale = maximizeLocale(locale);
  if (hasError(maxLocale->status)) {
    free(maxLocale);
    return localeWithEcmaError(UNABLE_TO_MINIMIZE_LOCALE, __FILE__, __LINE__,
                               NULL);
  }

  minLocaleId = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  uloc_minimizeSubtags(maxLocale->canonicalId, minLocaleId,
                       ULOC_FULLNAME_CAPACITY, &icuStatus);

  minLocale = initLocale(getBcp47Identifier(minLocaleId, NULL));

  free(minLocaleId);
  free(maxLocale);

  return minLocale;
}

static char *copyOriginalId(const char *localeId, errorStatus *status) {
  char *originalId;

  originalId = (char *)malloc(strlen(localeId) + 1);
  if (!originalId) {
    memoryError(status, __FILE__, __LINE__);
    return NULL;
  }

  originalId = strdup(localeId);

  return originalId;
}

static char *getBaseName(const char *localeId, errorStatus *status) {
  char *icuBaseName, *bcp47BaseName;
  UErrorCode icuStatus = U_ZERO_ERROR;

  icuBaseName = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  if (!icuBaseName) {
    memoryError(status, __FILE__, __LINE__);
    return NULL;
  }

  uloc_getBaseName(localeId, icuBaseName, ULOC_FULLNAME_CAPACITY, &icuStatus);
  if (U_FAILURE(icuStatus)) {
    free(icuBaseName);
    icuError(status, icuStatus, __FILE__, __LINE__, NULL);
    return NULL;
  }

  bcp47BaseName = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  if (!bcp47BaseName) {
    free(icuBaseName);
    memoryError(status, __FILE__, __LINE__);
    return NULL;
  }

  icuToBcp47LanguageTag(icuBaseName, bcp47BaseName, status);

  free(icuBaseName);

  return bcp47BaseName;
}

static char *getBcp47Identifier(const char *localeId, errorStatus *status) {
  char *bcp47LocaleId;
  int bcp47LocaleLength;

  bcp47LocaleId = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  if (!bcp47LocaleId) {
    memoryError(status, __FILE__, __LINE__);
    return NULL;
  }

  bcp47LocaleLength = icuToBcp47LanguageTag(localeId, bcp47LocaleId, status);
  if (bcp47LocaleLength == 0) {
    free(bcp47LocaleId);
    return NULL;
  }

  return bcp47LocaleId;
}

static char *getKeyword(const char *keyword, const char *localeId,
                        errorStatus *status) {
  char *icu, *bcp47;
  const char *bcpValue;
  UErrorCode icuStatus = U_ZERO_ERROR;

  icu = (char *)malloc(sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  if (!icu) {
    memoryError(status, __FILE__, __LINE__);
    return NULL;
  }

  uloc_getKeywordValue(localeId, keyword, icu, ULOC_KEYWORD_AND_VALUES_CAPACITY,
                       &icuStatus);
  if (U_FAILURE(icuStatus)) {
    free(icu);
    icuError(status, icuStatus, __FILE__, __LINE__, NULL);
    return NULL;
  }

  if (strcmp(icu, "") == 0) {
    free(icu);
    return NULL;
  }

  bcp47 = (char *)malloc(sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  if (!bcp47) {
    free(icu);
    memoryError(status, __FILE__, __LINE__);
    return NULL;
  }

  bcpValue = uloc_toUnicodeLocaleType(keyword, icu);

  if (!bcpValue) {
    free(icu);
    free(bcp47);
    return NULL;
  }

  bcp47 = strdup(bcpValue);
  free(icu);

  return bcp47;
}

static char *getLanguage(const char *localeId, errorStatus *status) {
  char *language;
  UErrorCode icuStatus = U_ZERO_ERROR;

  language = (char *)malloc(sizeof(char *) * ULOC_LANG_CAPACITY);
  if (!language) {
    memoryError(status, __FILE__, __LINE__);
    return NULL;
  }

  uloc_getLanguage(localeId, language, ULOC_LANG_CAPACITY, &icuStatus);
  if (U_FAILURE(icuStatus)) {
    free(language);
    icuError(status, icuStatus, __FILE__, __LINE__, NULL);
    return NULL;
  }

  if (strcmp(language, "") == 0 ||
      strcmp(language, UNDETERMINED_LANGUAGE) == 0) {
    free(language);
    return NULL;
  }

  return language;
}

static bool getNumeric(const char *localeId, errorStatus *status) {
  char *numeric;
  bool numericValue = false;

  numeric = getKeyword(ICU_KEYWORD_NUMERIC, localeId, status);
  if (numeric == NULL) {
    return numericValue;
  }

  if (strcmp(numeric, BCP47_NUMERIC_TRUE) == 0) {
    numericValue = true;
  }

  free(numeric);

  return numericValue;
}

static char *getRegion(const char *localeId, errorStatus *status) {
  char *region;
  UErrorCode icuStatus = U_ZERO_ERROR;

  region = (char *)malloc(sizeof(char *) * ULOC_COUNTRY_CAPACITY);
  if (!region) {
    memoryError(status, __FILE__, __LINE__);
    return NULL;
  }

  uloc_getCountry(localeId, region, ULOC_COUNTRY_CAPACITY, &icuStatus);
  if (U_FAILURE(icuStatus)) {
    free(region);
    icuError(status, icuStatus, __FILE__, __LINE__, NULL);
    return NULL;
  }

  if (strcmp(region, "") == 0) {
    free(region);
    return NULL;
  }

  return region;
}

static char *getScript(const char *localeId, errorStatus *status) {
  char *script;
  UErrorCode icuStatus = U_ZERO_ERROR;

  script = (char *)malloc(sizeof(char *) * ULOC_SCRIPT_CAPACITY);
  if (!script) {
    memoryError(status, __FILE__, __LINE__);
    return NULL;
  }

  uloc_getScript(localeId, script, ULOC_SCRIPT_CAPACITY, &icuStatus);
  if (U_FAILURE(icuStatus)) {
    free(script);
    icuError(status, icuStatus, __FILE__, __LINE__, NULL);
    return NULL;
  }

  if (strcmp(script, "") == 0) {
    free(script);
    return NULL;
  }

  return script;
}

static const char *normalizeLocaleId(const char *localeId) {
  char *defaultName;
  int defaultNameLength = 0;

  if (localeId == NULL) {
    return NULL;
  }

  if (strcmp(localeId, "") == 0 ||
      strcmp(localeId, UNDETERMINED_LANGUAGE) == 0) {

    defaultName = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
    if (defaultName) {
      defaultNameLength =
          icuToBcp47LanguageTag(uloc_getDefault(), defaultName, NULL);
    }

    if (defaultNameLength > 0) {
      localeId = defaultName;
    } else {
      localeId = UNDETERMINED_LANGUAGE;
    }
  }

  return localeId;
}
