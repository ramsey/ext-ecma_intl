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

#ifndef ECMA_INTL_PHP_SUPPORT_CALENDAR_H
#define ECMA_INTL_PHP_SUPPORT_CALENDAR_H

#define CALENDAR_BUDDHIST "buddhist"
#define CALENDAR_CHINESE "chinese"
#define CALENDAR_COPTIC "coptic"
#define CALENDAR_DANGI "dangi"
#define CALENDAR_ETHIOAA "ethioaa"
#define CALENDAR_ETHIOPIC "ethiopic"
#define CALENDAR_GREGORY "gregory"
#define CALENDAR_HEBREW "hebrew"
#define CALENDAR_INDIAN "indian"
#define CALENDAR_ISLAMIC "islamic"
#define CALENDAR_ISLAMIC_CIVIL "islamic-civil"
#define CALENDAR_ISLAMIC_RGSA "islamic-rgsa"
#define CALENDAR_ISLAMIC_TBLA "islamic-tbla"
#define CALENDAR_ISLAMIC_UMALQURA "islamic-umalqura"
#define CALENDAR_ISO8601 "iso8601"
#define CALENDAR_JAPANESE "japanese"
#define CALENDAR_PERSIAN "persian"
#define CALENDAR_ROC "roc"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the PHP calendar enum case name for the given value.
 *
 * @param value The calendar value.
 *
 * @return A case name for the PHP calendar enum.
 */
const char *getCalendarCaseName(const char *value);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_PHP_SUPPORT_CALENDAR_H */
