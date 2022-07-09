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

#include "units.h"

#include <cstring>
#include <unicode/measunit.h>
#include <unicode/putil.h>
#include <unicode/strenum.h>

#define UNITS_TYPE_CAPACITY 40

int getAllMeasurementUnits(const char **units) {
  icu::StringEnumeration *availableTypes;
  icu::MeasureUnit measureUnits[UNITS_TYPE_CAPACITY];
  UErrorCode status = U_ZERO_ERROR;
  int typesCount, numUnitsInType, unitsCount = 0;
  const char *type;

  availableTypes = icu::MeasureUnit::getAvailableTypes(status);
  typesCount = availableTypes->count(status);
  availableTypes->reset(status);

  for (int i = 0; i < typesCount; i++) {
    type = availableTypes->next(nullptr, status);

    /* Skip currency; we do not want to return currency identifiers as
     * measurement units. */
    if (strcmp("currency", type) == 0) {
      continue;
    }

    numUnitsInType = icu::MeasureUnit::getAvailable(
        type, measureUnits, UNITS_TYPE_CAPACITY, status);

    for (int j = 0; j < numUnitsInType; j++) {
      units[unitsCount++] = measureUnits[j].getIdentifier();
    }
  }

  delete availableTypes;

  return unitsCount;
}
