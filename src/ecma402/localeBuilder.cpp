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

#include "localeBuilder.h"

#include <cstdlib>
#include <cstring>
#include <unicode/localebuilder.h>

#define SET_OPTIONS_PROPERTY(property)                                         \
  do {                                                                         \
    if (property) {                                                            \
      options->property = strdup(property);                                    \
    } else {                                                                   \
      options->property = nullptr;                                             \
    }                                                                          \
  } while (0)

#define FREE_OPTIONS_PROPERTY(property)                                        \
  do {                                                                         \
    if (options->property) {                                                   \
      free(options->property);                                                 \
    }                                                                          \
  } while (0)

#define SET_BUILDER_PROPERTY(method, value, errorCode)                         \
  do {                                                                         \
    if (value != nullptr) {                                                    \
      TEST_NOT_EMPTY(value, errorCode);                                        \
      icuLocaleBuilder.set##method(value);                                     \
      TEST_BUILDER(errorCode);                                                 \
    }                                                                          \
  } while (0)

#define SET_BUILDER_KEYWORD(keyword, value, errorCode)                         \
  do {                                                                         \
    if (value != nullptr) {                                                    \
      TEST_NOT_EMPTY(value, errorCode);                                        \
      icuLocaleBuilder.setUnicodeLocaleKeyword(keyword, value);                \
      TEST_BUILDER(errorCode);                                                 \
    }                                                                          \
  } while (0)

#define TEST_BUILDER(errorCode)                                                \
  do {                                                                         \
    icuLocaleBuilder.build(status);                                            \
    if (U_FAILURE(status)) {                                                   \
      return localeWithEcmaError(errorCode, __FILE__, __LINE__, nullptr);      \
    }                                                                          \
  } while (0)

#define TEST_NOT_EMPTY(value, errorCode)                                       \
  do {                                                                         \
    if (strcmp(value, "") == 0) {                                              \
      return localeWithEcmaError(errorCode, __FILE__, __LINE__, nullptr);      \
    }                                                                          \
  } while (0)

#ifdef __cplusplus
extern "C" {
#endif

localeBuilderOptions *initLocaleBuilderOptions(
    const char *calendar, const char *caseFirst, const char *collation,
    const char *hourCycle, const char *language, const char *numberingSystem,
    const bool *numeric, const char *region, const char *script) {

  localeBuilderOptions *options;
  options = (localeBuilderOptions *)(malloc(sizeof(*options)));

  if (options == nullptr) {
    return nullptr;
  }

  SET_OPTIONS_PROPERTY(calendar);
  SET_OPTIONS_PROPERTY(caseFirst);
  SET_OPTIONS_PROPERTY(collation);
  SET_OPTIONS_PROPERTY(hourCycle);
  SET_OPTIONS_PROPERTY(language);
  SET_OPTIONS_PROPERTY(numberingSystem);
  SET_OPTIONS_PROPERTY(region);
  SET_OPTIONS_PROPERTY(script);

  if (numeric) {
    options->numeric = (bool *)malloc(sizeof(bool *));
    if (options->numeric != nullptr) {
      *options->numeric = *numeric;
    } else {
      options->numeric = nullptr;
    }
  } else {
    options->numeric = nullptr;
  }

  return options;
}

void freeLocaleBuilderOptions(localeBuilderOptions *options) {
  FREE_OPTIONS_PROPERTY(calendar);
  FREE_OPTIONS_PROPERTY(caseFirst);
  FREE_OPTIONS_PROPERTY(collation);
  FREE_OPTIONS_PROPERTY(hourCycle);
  FREE_OPTIONS_PROPERTY(language);
  FREE_OPTIONS_PROPERTY(numberingSystem);
  FREE_OPTIONS_PROPERTY(numeric);
  FREE_OPTIONS_PROPERTY(region);
  FREE_OPTIONS_PROPERTY(script);

  free(options);
}

locale *buildLocale(const char *localeId, localeBuilderOptions *options) {
  icu::Locale icuLocale;
  icu::LocaleBuilder icuLocaleBuilder;
  UErrorCode status = U_ZERO_ERROR;
  char *numericValue = nullptr;

  icuLocaleBuilder = icu::LocaleBuilder();
  icuLocaleBuilder.setLanguageTag(localeId);
  TEST_BUILDER(INVALID_LOCALE_ID);

  if (options) {
    SET_BUILDER_KEYWORD(BCP47_KEYWORD_CALENDAR, options->calendar,
                        INVALID_CALENDAR);
    SET_BUILDER_KEYWORD(BCP47_KEYWORD_CASE_FIRST, options->caseFirst,
                        INVALID_CASE_FIRST);
    SET_BUILDER_KEYWORD(BCP47_KEYWORD_COLLATION, options->collation,
                        INVALID_COLLATION);
    SET_BUILDER_KEYWORD(BCP47_KEYWORD_HOUR_CYCLE, options->hourCycle,
                        INVALID_HOUR_CYCLE);
    SET_BUILDER_PROPERTY(Language, options->language, INVALID_LANGUAGE);
    SET_BUILDER_KEYWORD(BCP47_KEYWORD_NUMBERING_SYSTEM,
                        options->numberingSystem, INVALID_NUMBERING_SYSTEM);
    SET_BUILDER_PROPERTY(Region, options->region, INVALID_REGION);
    SET_BUILDER_PROPERTY(Script, options->script, INVALID_SCRIPT);

    if (options->numeric != nullptr) {
      numericValue = (char *)malloc(strlen(NUMERIC_FALSE) + 1);
      if (*options->numeric) {
        memcpy(numericValue, NUMERIC_TRUE, strlen(NUMERIC_TRUE) + 1);
      } else {
        memcpy(numericValue, NUMERIC_FALSE, strlen(NUMERIC_FALSE) + 1);
      }
      icuLocaleBuilder.setUnicodeLocaleKeyword(BCP47_KEYWORD_NUMERIC,
                                               numericValue);
    }
  }

  icuLocale = icuLocaleBuilder.build(status);

  if (numericValue) {
    free(numericValue);
  }

  if (U_FAILURE(status)) {
    return localeWithEcmaError(INVALID_LOCALE_ID, __FILE__, __LINE__, nullptr);
  }

  std::string builtLocale = icuLocale.toLanguageTag<std::string>(status);

  return initLocale(builtLocale.c_str());
}

#ifdef __cplusplus
}
#endif
