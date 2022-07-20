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

#include "icu_exception.h"
#include "src/ecma402/calendar.h"
#include "src/ecma402/collation.h"
#include "src/ecma402/hour_cycle.h"
#include "src/ecma402/localeBuilder.h"
#include "src/ecma402/numbering_system.h"
#include "src/ecma402/text_direction.h"
#include "src/ecma402/time_zone.h"
#include "src/php/classes/calendar.h"
#include "src/php/classes/case_first.h"
#include "src/php/classes/collation.h"
#include "src/php/classes/hour_cycle.h"
#include "src/php/classes/locale/options.h"
#include "src/php/classes/locale/text_direction.h"
#include "src/php/classes/locale/text_info.h"
#include "src/php/classes/locale/week_day.h"
#include "src/php/classes/locale/week_info.h"
#include "src/php/classes/numbering_system.h"
#include "src/php/classes/range_error.h"
#include "src/php/ecma_intl_arginfo.h"

#include <unicode/uloc.h>
#include <zend_interfaces.h>

#define GET_OPTION_ENUM_VALUE(var, obj, option, enumClassEntry)                \
  do {                                                                         \
    zval *zv = zend_read_property(ecmaIntlLocaleOptionsClass, &(obj)->std,     \
                                  option, strlen(option), false, NULL);        \
    if (Z_TYPE_P(zv) == IS_OBJECT) {                                           \
      zend_object *enumCase = Z_OBJ_P(zv);                                     \
      zval *enumValue = zend_enum_fetch_case_value(enumCase);                  \
      (var) = Z_STRVAL_P(enumValue);                                           \
    } else {                                                                   \
      (var) = NULL;                                                            \
    }                                                                          \
  } while (0)

#define GET_OPTION_STRING(var, obj, option)                                    \
  do {                                                                         \
    zval *zv = zend_read_property(ecmaIntlLocaleOptionsClass, &(obj)->std,     \
                                  option, strlen(option), false, NULL);        \
    if (Z_TYPE_P(zv) == IS_STRING) {                                           \
      (var) = Z_STRVAL_P(zv);                                                  \
    } else {                                                                   \
      (var) = NULL;                                                            \
    }                                                                          \
  } while (0)

#define GET_OPTION_BOOL(var, obj, option)                                      \
  do {                                                                         \
    zval *zv = zend_read_property(ecmaIntlLocaleOptionsClass, &(obj)->std,     \
                                  option, strlen(option), false, NULL);        \
    if (Z_TYPE_P(zv) == IS_TRUE || Z_TYPE_P(zv) == IS_FALSE) {                 \
      (var) = Z_TYPE_P(zv) == IS_TRUE ? NUMERIC_TRUE : NUMERIC_FALSE;          \
    } else {                                                                   \
      (var) = NUMERIC_NULL;                                                    \
    }                                                                          \
  } while (0)

#define SET_PROP_ZVAL(property, value)                                         \
  do {                                                                         \
    zend_update_property(ecmaIntlLocaleClass, object, property,                \
                         sizeof(property) - 1, value);                         \
  } while (0)

#define SET_PROP_ZOBJ_OR_NULL(property, value)                                 \
  do {                                                                         \
    if ((value) == NULL) {                                                     \
      SET_PROP_NULL(property);                                                 \
    } else {                                                                   \
      zval zv;                                                                 \
      ZVAL_OBJ_COPY(&zv, value);                                               \
      SET_PROP_ZVAL(property, &zv);                                            \
    }                                                                          \
  } while (0)

#define SET_PROP_STRING_OR_NULL(property, value)                               \
  do {                                                                         \
    if ((value) == NULL) {                                                     \
      SET_PROP_NULL(property);                                                 \
    } else {                                                                   \
      zend_update_property_string(ecmaIntlLocaleClass, object, property,       \
                                  sizeof(property) - 1, value);                \
    }                                                                          \
  } while (0)

#define SET_PROP_BOOL(property, value)                                         \
  do {                                                                         \
    zend_update_property_bool(ecmaIntlLocaleClass, object, property,           \
                              sizeof(property) - 1, value);                    \
  } while (0)

#define SET_PROP_NULL(property)                                                \
  do {                                                                         \
    zend_update_property_null(ecmaIntlLocaleClass, object, property,           \
                              sizeof(property) - 1);                           \
  } while (0)

#define ADD_NEXT_ZOBJ(array, value)                                            \
  do {                                                                         \
    if (value) {                                                               \
      zval zv;                                                                 \
      ZVAL_OBJ_COPY(&zv, value);                                               \
      add_next_index_zval(array, &zv);                                         \
    }                                                                          \
  } while (0)

zend_class_entry *ecmaIntlLocaleClass = NULL;
zend_object_handlers ecmaIntlLocaleHandlers;

static void freeLocaleObj(zend_object *object);
static localeBuilderOptions *convertToBuilderOptions(zval *options);
static void initLocaleObj(localeObj *localeObj, locale *locale);
static void setSupportedCalendars(zend_object *object, locale *locale);
static void setSupportedCollations(zend_object *object, locale *locale);
static void setSupportedHourCycles(zend_object *object, locale *locale);
static void setSupportedNumberingSystems(zend_object *object, locale *locale);
static void setSupportedTimeZones(zend_object *object, locale *locale);
static void setTextInfo(zend_object *object, locale *locale);
static void setWeekInfo(zend_object *object, locale *locale);
static void handleError(errorStatus *status, const char *localeId);

void registerEcmaIntlLocaleClass() {
  ecmaIntlLocaleClass = register_class_Ecma_Intl_Locale(zend_ce_stringable);
  ecmaIntlLocaleClass->create_object = createLocaleObj;

  memcpy(&ecmaIntlLocaleHandlers, zend_get_std_object_handlers(),
         sizeof(zend_object_handlers));

  ecmaIntlLocaleHandlers.offset = XtOffsetOf(localeObj, std);
  ecmaIntlLocaleHandlers.free_obj = freeLocaleObj;
}

zend_object *createLocaleObj(zend_class_entry *classEntry) {
  localeObj *localeObj;

  localeObj = zend_object_alloc(sizeof(struct localeObj), classEntry);

  zend_object_std_init(&localeObj->std, classEntry);
  object_properties_init(&localeObj->std, classEntry);

  localeObj->std.handlers = &ecmaIntlLocaleHandlers;
  localeObj->locale = NULL;

  return &localeObj->std;
}

PHP_METHOD(Ecma_Intl_Locale, __construct) {
  char *localeId = NULL;
  size_t localeIdLength = 0;
  zval *options = NULL;
  localeObj *localeObj;
  locale *locale;

  ZEND_PARSE_PARAMETERS_START(1, 2)
  Z_PARAM_STRING(localeId, localeIdLength)
  Z_PARAM_OPTIONAL
  Z_PARAM_OBJECT_OF_CLASS_OR_NULL(options, ecmaIntlLocaleOptionsClass)
  ZEND_PARSE_PARAMETERS_END();

  if (localeIdLength == 0) {
    zend_throw_error(ecmaIntlRangeErrorClass, "invalid language tag: %s",
                     localeId);
  }

  localeObj = Z_LOCALE_P(getThis());

  if (options) {
    localeBuilderOptions *builderOptions;

    builderOptions = convertToBuilderOptions(options);
    locale = buildLocale(localeId, builderOptions);

    if (builderOptions) {
      freeLocaleBuilderOptions(builderOptions);
    }
  } else {
    locale = initLocale(localeId);
  }

  if (hasError(locale->status)) {
    handleError(locale->status, localeId);
  } else {
    initLocaleObj(localeObj, locale);
  }
}

PHP_METHOD(Ecma_Intl_Locale, maximize) {
  char *maxLocaleId;
  localeObj *localeObj, *newLocaleObj;
  zend_object *newObject;
  locale *maxLocale;

  ZEND_PARSE_PARAMETERS_NONE();

  localeObj = Z_LOCALE_P(getThis());
  maxLocale = maximizeLocale(localeObj->locale);

  if (hasError(maxLocale->status)) {
    handleError(maxLocale->status, maxLocaleId);
  }

  newObject = createLocaleObj(ecmaIntlLocaleClass);
  newLocaleObj = localeObjFromObj(newObject);
  initLocaleObj(newLocaleObj, maxLocale);

  RETURN_OBJ(&newLocaleObj->std);
}

PHP_METHOD(Ecma_Intl_Locale, minimize) {
  char *minLocaleId;
  localeObj *localeObj, *newLocaleObj;
  zend_object *newObject;
  locale *minLocale;

  ZEND_PARSE_PARAMETERS_NONE();

  localeObj = Z_LOCALE_P(getThis());
  minLocale = minimizeLocale(localeObj->locale);

  if (hasError(minLocale->status)) {
    handleError(minLocale->status, minLocaleId);
  }

  newObject = createLocaleObj(ecmaIntlLocaleClass);
  newLocaleObj = localeObjFromObj(newObject);
  initLocaleObj(newLocaleObj, minLocale);

  RETURN_OBJ(&newLocaleObj->std);
}

PHP_METHOD(Ecma_Intl_Locale, __toString) {
  ZEND_PARSE_PARAMETERS_NONE();

  localeObj *localeObj = Z_LOCALE_P(getThis());

  RETURN_STRING(localeObj->locale->id);
}

static void initLocaleObj(localeObj *localeObj, locale *locale) {
  zend_object *object = &localeObj->std;
  localeObj->locale = locale;

  SET_PROP_STRING_OR_NULL(LOCALE_BASE_NAME, locale->baseName);
  SET_PROP_ZOBJ_OR_NULL(LOCALE_CALENDAR,
                        getCalendarEnumCaseByValue(locale->calendar));
  SET_PROP_ZOBJ_OR_NULL(LOCALE_CASE_FIRST,
                        getCaseFirstEnumCaseByValue(locale->caseFirst));
  SET_PROP_ZOBJ_OR_NULL(LOCALE_COLLATION,
                        getCollationEnumCaseByValue(locale->collation));
  SET_PROP_ZOBJ_OR_NULL(LOCALE_HOUR_CYCLE,
                        getHourCycleEnumCaseByValue(locale->hourCycle));
  SET_PROP_STRING_OR_NULL(LOCALE_LANGUAGE, locale->language);
  SET_PROP_ZOBJ_OR_NULL(
      LOCALE_NUMBERING_SYSTEM,
      getNumberingSystemEnumCaseByValue(locale->numberingSystem));
  SET_PROP_BOOL(LOCALE_NUMERIC, locale->numeric);
  SET_PROP_STRING_OR_NULL(LOCALE_REGION, locale->region);
  SET_PROP_STRING_OR_NULL(LOCALE_SCRIPT, locale->script);

  setSupportedCalendars(object, locale);
  setSupportedCollations(object, locale);
  setSupportedHourCycles(object, locale);
  setSupportedNumberingSystems(object, locale);
  setSupportedTimeZones(object, locale);

  setTextInfo(object, locale);
  setWeekInfo(object, locale);
}

static void setSupportedCalendars(zend_object *object, locale *locale) {
  const char **supported;
  int count, capacity = CALENDARS_CAPACITY;
  zval values;

  supported = (const char **)emalloc(sizeof(const char *) * capacity);
  count = getSupportedCalendars(locale->canonicalId, supported);

  array_init(&values);

  for (int i = 0; i < count; i++) {
    ADD_NEXT_ZOBJ(&values, getCalendarEnumCaseByValue(supported[i]));
    free((void *)supported[i]);
  }

  SET_PROP_ZVAL(LOCALE_CALENDARS, &values);

  efree(supported);
  zend_array_release(Z_ARRVAL(values));
}

static void setSupportedCollations(zend_object *object, locale *locale) {
  const char **supported;
  int count, capacity = COLLATIONS_CAPACITY;
  zval values;

  supported = (const char **)emalloc(sizeof(const char *) * capacity);
  count = getSupportedCollations(locale->canonicalId, supported);

  array_init(&values);

  for (int i = 0; i < count; i++) {
    ADD_NEXT_ZOBJ(&values, getCollationEnumCaseByValue(supported[i]));
    free((void *)supported[i]);
  }

  SET_PROP_ZVAL(LOCALE_COLLATIONS, &values);

  efree(supported);
  zend_array_release(Z_ARRVAL(values));
}

static void setSupportedHourCycles(zend_object *object, locale *locale) {
  const char **supported;
  int count, capacity = HOUR_CYCLES_CAPACITY;
  zval values;

  supported = (const char **)emalloc(sizeof(const char *) * capacity);
  count = getSupportedHourCycles(locale->canonicalId, supported);

  array_init(&values);

  for (int i = 0; i < count; i++) {
    ADD_NEXT_ZOBJ(&values, getHourCycleEnumCaseByValue(supported[i]));
    free((void *)supported[i]);
  }

  SET_PROP_ZVAL(LOCALE_HOUR_CYCLES, &values);

  efree(supported);
  zend_array_release(Z_ARRVAL(values));
}

static void setSupportedNumberingSystems(zend_object *object, locale *locale) {
  const char **supported;
  int count, capacity = NUMBERING_SYSTEMS_CAPACITY;
  zval values;

  supported = (const char **)emalloc(sizeof(const char *) * capacity);
  count = getSupportedNumberingSystems(locale->canonicalId, supported);

  array_init(&values);

  for (int i = 0; i < count; i++) {
    ADD_NEXT_ZOBJ(&values, getNumberingSystemEnumCaseByValue(supported[i]));
    free((void *)supported[i]);
  }

  SET_PROP_ZVAL(LOCALE_NUMBERING_SYSTEMS, &values);

  efree(supported);
  zend_array_release(Z_ARRVAL(values));
}

static void setTextInfo(zend_object *object, locale *locale) {
  zend_object *textInfoObj, *textDirectionCase;
  zval textInfo, textDirection;

  textDirectionCase = getTextDirectionEnumCaseForTextDirection(
      getTextDirection(locale->canonicalId));
  ZVAL_OBJ(&textDirection, textDirectionCase);

  textInfoObj = createTextInfoObj(ecmaIntlLocaleTextInfoClass);

  zend_update_property(ecmaIntlLocaleTextInfoClass, textInfoObj,
                       TEXT_INFO_DIRECTION, sizeof(TEXT_INFO_DIRECTION) - 1,
                       &textDirection);

  ZVAL_OBJ(&textInfo, textInfoObj);
  SET_PROP_ZVAL(LOCALE_TEXT_INFO, &textInfo);
  zend_object_release(textInfoObj);
}

static void setSupportedTimeZones(zend_object *object, locale *locale) {
  const char **supported;
  int count, capacity = TIME_ZONES_CAPACITY;
  zval values;

  supported = (const char **)emalloc(sizeof(const char *) * capacity);
  count = getSupportedTimeZones(locale->canonicalId, supported);

  if (count == 0) {
    SET_PROP_NULL(LOCALE_TIME_ZONES);
    efree(supported);
    return;
  }

  array_init(&values);

  for (int i = 0; i < count; i++) {
    add_next_index_string(&values, supported[i]);
    free((void *)supported[i]);
  }

  SET_PROP_ZVAL(LOCALE_TIME_ZONES, &values);

  efree(supported);
  zend_array_release(Z_ARRVAL(values));
}

static void setWeekInfo(zend_object *object, locale *locale) {
  zend_object *weekInfoObj, *firstDayOfWeekCase;
  zval weekInfo, firstDayOfWeek, weekend;
  struct weekInfo *info;

  info = getWeekInfo(locale->canonicalId);

  weekInfoObj = createWeekInfoObj(ecmaIntlLocaleWeekInfoClass);
  ZVAL_OBJ(&weekInfo, weekInfoObj);

  firstDayOfWeekCase = getWeekDayEnumCaseForDayOfWeek(info->firstDay);
  ZVAL_OBJ(&firstDayOfWeek, firstDayOfWeekCase);
  zend_update_property(ecmaIntlLocaleWeekInfoClass, weekInfoObj,
                       WEEK_INFO_FIRST_DAY, sizeof(WEEK_INFO_FIRST_DAY) - 1,
                       &firstDayOfWeek);

  zend_update_property_long(
      ecmaIntlLocaleWeekInfoClass, weekInfoObj, WEEK_INFO_MINIMAL_DAYS,
      sizeof(WEEK_INFO_MINIMAL_DAYS) - 1, info->minimalDays);

  array_init(&weekend);
  for (int i = 0; i < info->weekendLength; i++) {
    ADD_NEXT_ZOBJ(&weekend, getWeekDayEnumCaseForDayOfWeek(info->weekend[i]));
  }
  zend_update_property(ecmaIntlLocaleWeekInfoClass, weekInfoObj,
                       WEEK_INFO_WEEKEND, sizeof(WEEK_INFO_WEEKEND) - 1,
                       &weekend);

  SET_PROP_ZVAL(LOCALE_WEEK_INFO, &weekInfo);

  zend_array_release(Z_ARRVAL(weekend));
  zend_object_release(weekInfoObj);
  freeWeekInfo(info);
}

static void freeLocaleObj(zend_object *object) {
  localeObj *localeObj = localeObjFromObj(object);

  zend_object_std_dtor(&localeObj->std);

  if (localeObj->locale) {
    freeLocale(localeObj->locale);
    localeObj->locale = NULL;
  }
}

static localeBuilderOptions *convertToBuilderOptions(zval *options) {
  localeOptionsObj *optionsObj;
  char *calendar, *caseFirst, *collation, *hourCycle, *language,
      *numberingSystem, *region, *script;
  numericValue numeric;

  optionsObj = Z_LOCALE_OPTIONS_P(options);

  GET_OPTION_ENUM_VALUE(calendar, optionsObj, OPTION_CALENDAR,
                        ecmaIntlCalendarEnum);
  GET_OPTION_ENUM_VALUE(caseFirst, optionsObj, OPTION_CASE_FIRST,
                        ecmaIntlCaseFirstEnum);
  GET_OPTION_ENUM_VALUE(collation, optionsObj, OPTION_COLLATION,
                        ecmaIntlCollationEnum);
  GET_OPTION_ENUM_VALUE(hourCycle, optionsObj, OPTION_HOUR_CYCLE,
                        ecmaIntlHourCycleEnum);
  GET_OPTION_STRING(language, optionsObj, OPTION_LANGUAGE);
  GET_OPTION_ENUM_VALUE(numberingSystem, optionsObj, OPTION_NUMBERING_SYSTEM,
                        ecmaIntlNumberingSystemEnum);
  GET_OPTION_BOOL(numeric, optionsObj, OPTION_NUMERIC);
  GET_OPTION_STRING(region, optionsObj, OPTION_REGION);
  GET_OPTION_STRING(script, optionsObj, OPTION_SCRIPT);

  return initLocaleBuilderOptions(calendar, caseFirst, collation, hourCycle,
                                  language, numberingSystem, numeric, region,
                                  script);
}

static void handleError(errorStatus *status, const char *localeId) {
  if (!hasError(status)) {
    return;
  }

  switch (status->ecma) {
  case INVALID_LANGUAGE:
    zend_throw_error(ecmaIntlRangeErrorClass,
                     "language is not a well-formed language value");
    return;
  case INVALID_REGION:
    zend_throw_error(ecmaIntlRangeErrorClass,
                     "region is not a well-formed region value");
    return;
  case INVALID_SCRIPT:
    zend_throw_error(ecmaIntlRangeErrorClass,
                     "script is not a well-formed script value");
    return;
  case UNABLE_TO_MAXIMIZE_LOCALE:
    zend_throw_error(ecmaIntlIcuExceptionClass, "unable to maximize locale: %s",
                     localeId);
    return;
  case UNABLE_TO_MINIMIZE_LOCALE:
    zend_throw_error(ecmaIntlIcuExceptionClass, "unable to minimize locale: %s",
                     localeId);
    return;
  }

  zend_throw_error(ecmaIntlRangeErrorClass, "invalid language tag: %s",
                   localeId);
}
