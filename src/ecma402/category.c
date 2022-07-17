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

#include "category.h"

#include "src/common.h"
#include "units.h"

#include <stdlib.h>
#include <string.h>
#include <unicode/ucal.h>
#include <unicode/ucol.h>
#include <unicode/ucurr.h>
#include <unicode/uenum.h>
#include <unicode/unumsys.h>

static void sort(const char *array[], int length);
static int compareStrings(const void *left, const void *right);

int getSupportedValuesForCategory(const char *category, const char **values) {
  UEnumeration *enumeration = NULL;
  UErrorCode status = U_ZERO_ERROR;
  const char *identifier, **units = NULL;
  int identifierLength, unitsCount, valuesCount = 0;

  if (strcmp(CATEGORY_CALENDAR, category) == 0) {
    enumeration = ucal_getKeywordValuesForLocale("calendar", NULL, 0, &status);
  } else if (strcmp(CATEGORY_COLLATION, category) == 0) {
    enumeration = ucol_getKeywordValues("collation", &status);
  } else if (strcmp(CATEGORY_CURRENCY, category) == 0) {
    enumeration = ucurr_openISOCurrencies(UCURR_ALL, &status);
  } else if (strcmp(CATEGORY_NUMBERING_SYSTEM, category) == 0) {
    enumeration = unumsys_openAvailableNames(&status);
  } else if (strcmp(CATEGORY_TIME_ZONE, category) == 0) {
    enumeration = ucal_openTimeZones(&status);
  } else if (strcmp(CATEGORY_UNIT, category) == 0) {
    units = (const char **)malloc(sizeof(const char *) * UNITS_CAPACITY);
    unitsCount = getAllMeasurementUnits(units);
    enumeration = uenum_openCharStringsEnumeration(units, unitsCount, &status);
  } else {
    return 0;
  }

  if (U_FAILURE(status)) {
    return 0;
  }

  while ((identifier = uenum_next(enumeration, &identifierLength, &status))) {
    if (strcmp("", identifier) == 0) {
      continue;
    }

    const char *tmpIdentifier = NULL;
    if (strcmp(CATEGORY_CALENDAR, category) == 0) {
      tmpIdentifier =
          uloc_toUnicodeLocaleType(ICU_KEYWORD_CALENDAR, identifier);
    } else if (strcasecmp(CATEGORY_COLLATION, category) == 0) {
      tmpIdentifier =
          uloc_toUnicodeLocaleType(ICU_KEYWORD_COLLATION, identifier);
    } else if (strcasecmp(CATEGORY_NUMBERING_SYSTEM, category) == 0) {
      tmpIdentifier =
          uloc_toUnicodeLocaleType(ICU_KEYWORD_NUMBERING_SYSTEM, identifier);
    } else {
      tmpIdentifier = identifier;
    }

    values[valuesCount] = (const char *)malloc(strlen(tmpIdentifier) + 1);
    memcpy((void *)values[valuesCount], tmpIdentifier,
           strlen(tmpIdentifier) + 1);

    valuesCount++;
  }

  uenum_close(enumeration);

  if (units) {
    for (int i = 0; i < unitsCount; i++) {
      free((void *)units[i]);
    }
    free(units);
  }

  sort(values, valuesCount);

  return valuesCount;
}

int getCapacityForCategory(const char *category) {
  if (strcmp(CATEGORY_CALENDAR, category) == 0) {
    return CATEGORY_CALENDAR_CAPACITY;
  } else if (strcmp(CATEGORY_COLLATION, category) == 0) {
    return CATEGORY_COLLATION_CAPACITY;
  } else if (strcmp(CATEGORY_CURRENCY, category) == 0) {
    return CATEGORY_CURRENCY_CAPACITY;
  } else if (strcmp(CATEGORY_NUMBERING_SYSTEM, category) == 0) {
    return CATEGORY_NUMBERING_SYSTEM_CAPACITY;
  } else if (strcmp(CATEGORY_TIME_ZONE, category) == 0) {
    return CATEGORY_TIME_ZONE_CAPACITY;
  } else if (strcmp(CATEGORY_UNIT, category) == 0) {
    return CATEGORY_UNIT_CAPACITY;
  }

  return 0;
}

static void sort(const char *array[], int length) {
  qsort(array, length, sizeof(const char *), compareStrings);
}

static int compareStrings(const void *left, const void *right) {
  return strcmp(*(const char **)left, *(const char **)right);
}
