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

#ifndef ECMA_INTL_ECMA402_TEXT_DIRECTION_H
#define ECMA_INTL_ECMA402_TEXT_DIRECTION_H

#include "src/common.h"

#define TEXT_DIRECTION_BTT "btt"
#define TEXT_DIRECTION_LTR "ltr"
#define TEXT_DIRECTION_RTL "rtl"
#define TEXT_DIRECTION_TTB "ttb"

/**
 * Direction of text as it is written in a locale.
 */
typedef enum textDirection {
  /**
   * Bottom-to-top text direction.
   */
  BOTTOM_TO_TOP,

  /**
   * Left-to-right text direction.
   */
  LEFT_TO_RIGHT,

  /**
   * Right-to-left text direction.
   */
  RIGHT_TO_LEFT,

  /**
   * Top-to-bottom text direction.
   */
  TOP_TO_BOTTOM

} textDirection;

/**
 * Returns the text direction for the given locale.
 */
textDirection getTextDirection(const char *localeId);

#endif /* ECMA_INTL_ECMA402_TEXT_DIRECTION_H */
