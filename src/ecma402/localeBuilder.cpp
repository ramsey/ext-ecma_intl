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

#define NUMERIC_TRUE "true"
#define NUMERIC_FALSE "false"

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

#define SET_BUILDER_PROPERTY(method, value)                                    \
  do {                                                                         \
    if (value) {                                                               \
      icuLocaleBuilder.set##method(value);                                     \
    }                                                                          \
  } while (0)

#define SET_BUILDER_KEYWORD(keyword, value)                                    \
  do {                                                                         \
    if (value) {                                                               \
      icuLocaleBuilder.setUnicodeLocaleKeyword(keyword, value);                \
    }                                                                          \
  } while (0)

#ifdef __cplusplus
extern "C" {
#endif

ecma402_localeBuilderOptions *ecma402_initLocaleBuilderOptions(
    char *calendar, char *caseFirst, char *collation, char *hourCycle,
    char *language, char *numberingSystem, const bool *numeric, char *region,
    char *script) {

  ecma402_localeBuilderOptions *options;
  options = (ecma402_localeBuilderOptions *)(malloc(sizeof(*options)));

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
    *options->numeric = *numeric;
  } else {
    options->numeric = nullptr;
  }

  return options;
}

void ecma402_freeLocaleBuilderOptions(ecma402_localeBuilderOptions *options) {
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

ecma402_locale *ecma402_buildLocale(const char *localeId,
                                    ecma402_localeBuilderOptions *options) {
  icu::Locale icuLocale;
  icu::LocaleBuilder icuLocaleBuilder;
  UErrorCode status = U_ZERO_ERROR;

  icuLocaleBuilder = icu::LocaleBuilder();
  icuLocaleBuilder.setLanguageTag(localeId);

  if (options) {
    SET_BUILDER_PROPERTY(Language, options->language);
    SET_BUILDER_PROPERTY(Region, options->region);
    SET_BUILDER_PROPERTY(Script, options->script);

    SET_BUILDER_KEYWORD(BCP47_KEYWORD_CALENDAR, options->calendar);
    SET_BUILDER_KEYWORD(BCP47_KEYWORD_CASE_FIRST, options->caseFirst);
    SET_BUILDER_KEYWORD(BCP47_KEYWORD_COLLATION, options->collation);
    SET_BUILDER_KEYWORD(BCP47_KEYWORD_HOUR_CYCLE, options->hourCycle);
    SET_BUILDER_KEYWORD(BCP47_KEYWORD_NUMBERING_SYSTEM,
                        options->numberingSystem);

    if (options->numeric != nullptr) {
      icuLocaleBuilder.setUnicodeLocaleKeyword(
          BCP47_KEYWORD_NUMERIC,
          *options->numeric ? NUMERIC_TRUE : NUMERIC_FALSE);
    }
  }

  icuLocale = icuLocaleBuilder.build(status);

  if (U_FAILURE(status)) {
    return nullptr;
  }

  std::string builtLocale = icuLocale.toLanguageTag<std::string>(status);

  return ecma402_initLocale(builtLocale.c_str());
}

#ifdef __cplusplus
}
#endif
