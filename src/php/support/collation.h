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

#ifndef ECMA_INTL_PHP_SUPPORT_COLLATION_H
#define ECMA_INTL_PHP_SUPPORT_COLLATION_H

#define COLLATION_BIG5HAN "big5han"
#define COLLATION_COMPAT "compat"
#define COLLATION_DICT "dict"
#define COLLATION_DIRECT "direct"
#define COLLATION_DUCET "ducet"
#define COLLATION_EMOJI "emoji"
#define COLLATION_EOR "eor"
#define COLLATION_GB2312 "gb2312"
#define COLLATION_PHONEBK "phonebk"
#define COLLATION_PHONETIC "phonetic"
#define COLLATION_PINYIN "pinyin"
#define COLLATION_REFORMED "reformed"
#define COLLATION_SEARCH "search"
#define COLLATION_SEARCHJL "searchjl"
#define COLLATION_STANDARD "standard"
#define COLLATION_STROKE "stroke"
#define COLLATION_TRAD "trad"
#define COLLATION_UNIHAN "unihan"
#define COLLATION_ZHUYIN "zhuyin"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the PHP collation enum case name for the given value.
 *
 * @param value The collation value.
 *
 * @return A case name for the PHP collation enum.
 */
const char *getCollationCaseName(const char *value);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_PHP_SUPPORT_COLLATION_H */
