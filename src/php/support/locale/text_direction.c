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

#include "src/ecma402/text_direction.h"

#include <string.h>

#define CASE_BTT "BottomToTop"
#define CASE_LTR "LeftToRight"
#define CASE_RTL "RightToLeft"
#define CASE_TTB "TopToBottom"

const char *getTextDirectionCaseName(const char *value) {
  if (value == NULL || strcmp(value, TEXT_DIRECTION_LTR) == 0) {
    return CASE_LTR;
  } else if (strcmp(value, TEXT_DIRECTION_BTT) == 0) {
    return CASE_BTT;
  } else if (strcmp(value, TEXT_DIRECTION_RTL) == 0) {
    return CASE_RTL;
  } else if (strcmp(value, TEXT_DIRECTION_TTB) == 0) {
    return CASE_TTB;
  }

  return CASE_LTR;
}

const char *getTextDirectionCaseNameByTextDirection(textDirection direction) {
  switch (direction) {
  case BOTTOM_TO_TOP:
    return CASE_BTT;
  case RIGHT_TO_LEFT:
    return CASE_RTL;
  case TOP_TO_BOTTOM:
    return CASE_TTB;
  case LEFT_TO_RIGHT:
  default:
    return CASE_LTR;
  }
}

const char *getTextDirectionCaseNameByLayoutType(ULayoutType layoutType) {
  switch (layoutType) {
  case ULOC_LAYOUT_BTT:
    return CASE_BTT;
  case ULOC_LAYOUT_RTL:
    return CASE_RTL;
  case ULOC_LAYOUT_TTB:
    return CASE_TTB;
  case ULOC_LAYOUT_LTR:
  case ULOC_LAYOUT_UNKNOWN:
  default:
    return CASE_LTR;
  }
}
