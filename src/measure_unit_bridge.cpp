/*
   +----------------------------------------------------------------------+
   | ecma_intl extension for PHP                                          |
   | Internationalization Support, Ecma-style (ECMA-402)                  |
   +----------------------------------------------------------------------+
   | Copyright (c) Ben Ramsey <ben@benramsey.com>                         |
   |                                                                      |
   | Licensed under the Apache License, Version 2.0 (the "License");      |
   | you may not use this file except in compliance with the License.     |
   | You may obtain a copy of the License at                              |
   |                                                                      |
   |     http://www.apache.org/licenses/LICENSE-2.0                       |
   |                                                                      |
   | Unless required by applicable law or agreed to in writing, software  |
   | distributed under the License is distributed on an "AS IS" BASIS,    |
   | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
   | implied. See the License for the specific language governing         |
   | permissions and limitations under the License.                       |
   +----------------------------------------------------------------------+
*/

#include <cstring>
#include <unicode/measunit.h>
#include <unicode/putil.h>
#include <unicode/strenum.h>
#include <unicode/uenum.h>
#include <vector>

#include "measure_unit_bridge.h"

#ifdef __cplusplus
extern "C" {
#endif

UEnumeration *ecma_intl_getMeasurementUnits(const UErrorCode *errorCode)
{
	static constexpr int TOTAL_CAPACITY = 200;
	static constexpr int UNITS_CAPACITY = 40;

	icu::StringEnumeration *availableTypes;
	icu::MeasureUnit measureUnits[UNITS_CAPACITY];

	UEnumeration *enumeratedUnits = nullptr;
	UErrorCode localStatus = U_ZERO_ERROR;

	int typesCount, numUnits, unitsCount = 0, resultLength = 40;
	const char *type, *identifier, *units[TOTAL_CAPACITY];

	availableTypes = icu::MeasureUnit::getAvailableTypes(localStatus);

	typesCount = availableTypes->count(localStatus);
	availableTypes->reset(localStatus);

	for (int i = 0; i < typesCount; i++) {
		type = availableTypes->next(&resultLength, localStatus);

		/* Skip currency; we do not want to return currency identifiers as measurement units. */
		if (strcmp("currency", type) == 0) {
			continue;
		}

		numUnits = icu::MeasureUnit::getAvailable(type, measureUnits, UNITS_CAPACITY, localStatus);

		if (numUnits == 0) {
			continue;
		}

		for (int j = 0; j < numUnits; j++) {
			identifier = measureUnits[j].getIdentifier();

			if (strcmp(identifier, "") == 0) {
				continue;
			}

			units[unitsCount++] = type;
		}
	}

	enumeratedUnits = uenum_openCharStringsEnumeration(units, unitsCount, &localStatus);

	if (U_FAILURE(localStatus)) {
		errorCode = &localStatus;
	}

	return enumeratedUnits;
}

#ifdef __cplusplus
}
#endif
