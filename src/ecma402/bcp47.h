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

#ifndef ECMA_INTL_ECMA402_BCP47_H
#define ECMA_INTL_ECMA402_BCP47_H

#include "src/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Converts an ICU language tag to its BCP 47 equivalent.
 *
 * The icuLanguageTag may be either an ICU language tag or a BCP 47 language
 * tag. In either case, languageTag will receive a well-formed BCP 47 language
 * tag. If we encounter an error, we will raise a PHP exception and return 0.
 *
 * @param icuLanguageTag The language tag to convert to a well-formed BCP 47 tag
 * @param bcp47LanguageTag A buffer in which to store the BCP 47 language tag
 * @return The length of the BCP 47 language tag stored to bcp47LanguageTag
 */
int ecma402_icuToBcp47LanguageTag(const char *icuLanguageTag,
                                  char *bcp47LanguageTag);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ECMA_INTL_ECMA402_BCP47_H */
