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

#include "text_direction.h"

#include <unicode/uloc.h>

textDirection getTextDirection(const char *localeId) {
  ULayoutType layout;
  UErrorCode status = U_ZERO_ERROR;

  layout = uloc_getCharacterOrientation(localeId, &status);

  if (U_FAILURE(status)) {
    return LEFT_TO_RIGHT;
  }

  switch (layout) {
  case ULOC_LAYOUT_RTL:
    return RIGHT_TO_LEFT;
  case ULOC_LAYOUT_TTB:
    return TOP_TO_BOTTOM;
  case ULOC_LAYOUT_BTT:
    return BOTTOM_TO_TOP;
  case ULOC_LAYOUT_LTR:
  case ULOC_LAYOUT_UNKNOWN:
  default:
    return LEFT_TO_RIGHT;
  }
}
