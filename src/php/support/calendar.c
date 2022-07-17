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

#include "calendar.h"

#include "src/ecma402/calendar.h"

#include <string.h>

#define CASE_BUDDHIST "Buddhist"
#define CASE_CHINESE "Chinese"
#define CASE_COPTIC "Coptic"
#define CASE_DANGI "Dangi"
#define CASE_ETHIOAA "Ethioaa"
#define CASE_ETHIOPIC "Ethiopic"
#define CASE_GREGORY "Gregory"
#define CASE_HEBREW "Hebrew"
#define CASE_INDIAN "Indian"
#define CASE_ISLAMIC "Islamic"
#define CASE_ISLAMIC_CIVIL "IslamicCivil"
#define CASE_ISLAMIC_RGSA "IslamicRgsa"
#define CASE_ISLAMIC_TBLA "IslamicTbla"
#define CASE_ISLAMIC_UMALQURA "IslamicUmalqura"
#define CASE_ISO8601 "Iso8601"
#define CASE_JAPANESE "Japanese"
#define CASE_PERSIAN "Persian"
#define CASE_ROC "Roc"

const char *getCalendarCaseName(const char *value) {
  if (value == NULL) {
    return NULL;
  } else if (strcmp(value, CALENDAR_BUDDHIST) == 0) {
    return CASE_BUDDHIST;
  } else if (strcmp(value, CALENDAR_CHINESE) == 0) {
    return CASE_CHINESE;
  } else if (strcmp(value, CALENDAR_COPTIC) == 0) {
    return CASE_COPTIC;
  } else if (strcmp(value, CALENDAR_DANGI) == 0) {
    return CASE_DANGI;
  } else if (strcmp(value, CALENDAR_ETHIOAA) == 0) {
    return CASE_ETHIOAA;
  } else if (strcmp(value, CALENDAR_ETHIOPIC) == 0) {
    return CASE_ETHIOPIC;
  } else if (strcmp(value, CALENDAR_GREGORY) == 0) {
    return CASE_GREGORY;
  } else if (strcmp(value, CALENDAR_HEBREW) == 0) {
    return CASE_HEBREW;
  } else if (strcmp(value, CALENDAR_INDIAN) == 0) {
    return CASE_INDIAN;
  } else if (strcmp(value, CALENDAR_ISLAMIC) == 0) {
    return CASE_ISLAMIC;
  } else if (strcmp(value, CALENDAR_ISLAMIC_CIVIL) == 0) {
    return CASE_ISLAMIC_CIVIL;
  } else if (strcmp(value, CALENDAR_ISLAMIC_RGSA) == 0) {
    return CASE_ISLAMIC_RGSA;
  } else if (strcmp(value, CALENDAR_ISLAMIC_TBLA) == 0) {
    return CASE_ISLAMIC_TBLA;
  } else if (strcmp(value, CALENDAR_ISLAMIC_UMALQURA) == 0) {
    return CASE_ISLAMIC_UMALQURA;
  } else if (strcmp(value, CALENDAR_ISO8601) == 0) {
    return CASE_ISO8601;
  } else if (strcmp(value, CALENDAR_JAPANESE) == 0) {
    return CASE_JAPANESE;
  } else if (strcmp(value, CALENDAR_PERSIAN) == 0) {
    return CASE_PERSIAN;
  } else if (strcmp(value, CALENDAR_ROC) == 0) {
    return CASE_ROC;
  }

  return NULL;
}
