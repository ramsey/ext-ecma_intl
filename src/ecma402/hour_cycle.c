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

#include "hour_cycle.h"

#include <stdlib.h>
#include <string.h>
#include <unicode/udatpg.h>

#define HOUR_CYCLE_LENGTH 4

int getSupportedHourCycles(const char *localeId, const char **hourCycles) {
  UDateTimePatternGenerator *patternGenerator;
  UDateFormatHourCycle hourCycle;
  UErrorCode status = U_ZERO_ERROR;
  char *preferred;
  int preferredLength;

  preferred = (char *)malloc(sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  if (!preferred) {
    return 0;
  }

  preferredLength =
      uloc_getKeywordValue(localeId, ICU_KEYWORD_HOUR_CYCLE, preferred,
                           ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

  if (preferredLength > 0) {
    hourCycles[0] = (const char *)malloc(HOUR_CYCLE_LENGTH);

    if (!hourCycles[0]) {
      free(preferred);
      return 0;
    }

    memcpy((void *)hourCycles[0], preferred, HOUR_CYCLE_LENGTH);
    free(preferred);

    return 1;
  }

  free(preferred);

  patternGenerator = udatpg_open(localeId, &status);
  if (U_FAILURE(status)) {
    return 0;
  }

  hourCycle = udatpg_getDefaultHourCycle(patternGenerator, &status);
  udatpg_close(patternGenerator);

  if (U_FAILURE(status)) {
    return 0;
  }

  hourCycles[0] = (const char *)malloc(HOUR_CYCLE_LENGTH);
  if (!hourCycles[0]) {
    return 0;
  }

  switch (hourCycle) {
  case UDAT_HOUR_CYCLE_11:
    hourCycles[0] = strdup(HOUR_CYCLE_H11);
    break;
  case UDAT_HOUR_CYCLE_23:
    hourCycles[0] = strdup(HOUR_CYCLE_H23);
    break;
  case UDAT_HOUR_CYCLE_24:
    hourCycles[0] = strdup(HOUR_CYCLE_H24);
    break;
  case UDAT_HOUR_CYCLE_12:
    hourCycles[0] = strdup(HOUR_CYCLE_H12);
  default:
    break;
  }

  return 1;
}
