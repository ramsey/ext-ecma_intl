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

#include "time_zone.h"

#include <stdlib.h>
#include <string.h>
#include <unicode/ucal.h>
#include <unicode/uloc.h>

int getSupportedTimeZones(const char *localeId, const char **timeZones) {
  UEnumeration *supported = NULL;
  UErrorCode status = U_ZERO_ERROR;
  char *region = NULL;
  const char *timeZone;
  int regionLen, timeZoneLen, count = 0;

  region = (char *)malloc(sizeof(char *) * ULOC_COUNTRY_CAPACITY);
  if (!region) {
    return 0;
  }

  regionLen = uloc_getCountry(localeId, region, ULOC_COUNTRY_CAPACITY, &status);
  if (U_FAILURE(status) || regionLen == 0) {
    free(region);
    return 0;
  }

  supported = ucal_openTimeZoneIDEnumeration(UCAL_ZONE_TYPE_CANONICAL, region,
                                             NULL, &status);
  if (U_FAILURE(status)) {
    free(region);
    return 0;
  }

  while ((timeZone = uenum_next(supported, &timeZoneLen, &status))) {
    if (U_FAILURE(status)) {
      continue;
    }

    timeZones[count] = (const char *)malloc(strlen(timeZone) + 1);
    if (!timeZones[count]) {
      continue;
    }
    memcpy((void *)timeZones[count], timeZone, strlen(timeZone) + 1);

    count++;
  }

  uenum_close(supported);
  free(region);

  return count;
}
