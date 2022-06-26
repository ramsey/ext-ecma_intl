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

UEnumeration *icuGetMeasurementUnits(const char **units,
                                     const UErrorCode *errorCode) {
  static constexpr int unitsCapacity = 40;

  icu::StringEnumeration *availableTypes;
  icu::MeasureUnit measureUnits[unitsCapacity];

  UEnumeration *enumeratedUnits = nullptr;
  UErrorCode localStatus = U_ZERO_ERROR;

  int typesCount, numUnits, unitsCount = 0, resultLength = 40;
  const char *type, *identifier;

  availableTypes = icu::MeasureUnit::getAvailableTypes(localStatus);
  typesCount = availableTypes->count(localStatus);
  availableTypes->reset(localStatus);

  for (int i = 0; i < typesCount; i++) {
    type = availableTypes->next(&resultLength, localStatus);

    /* Skip currency; we do not want to return currency identifiers as
     * measurement units. */
    if (strcmp("currency", type) == 0) {
      continue;
    }

    numUnits = icu::MeasureUnit::getAvailable(type, measureUnits, unitsCapacity,
                                              localStatus);

    if (numUnits == 0) {
      continue;
    }

    for (int j = 0; j < numUnits; j++) {
      identifier = measureUnits[j].getIdentifier();

      if (strcmp(identifier, "") == 0) {
        continue;
      }

      units[unitsCount++] = identifier;
    }
  }

  delete availableTypes;
  enumeratedUnits =
      uenum_openCharStringsEnumeration(units, unitsCount, &localStatus);

  if (U_FAILURE(localStatus)) {
    errorCode = &localStatus;
  }

  return enumeratedUnits;
}
