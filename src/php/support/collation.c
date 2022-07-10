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

#include "collation.h"

#include <string.h>

#define CASE_BIG5HAN "Big5han"
#define CASE_COMPAT "Compat"
#define CASE_DICT "Dict"
#define CASE_DIRECT "Direct"
#define CASE_DUCET "Ducet"
#define CASE_EMOJI "Emoji"
#define CASE_EOR "Eor"
#define CASE_GB2312 "Gb2312"
#define CASE_PHONEBK "Phonebk"
#define CASE_PHONETIC "Phonetic"
#define CASE_PINYIN "Pinyin"
#define CASE_REFORMED "Reformed"
#define CASE_SEARCH "Search"
#define CASE_SEARCHJL "Searchjl"
#define CASE_STANDARD "Standard"
#define CASE_STROKE "Stroke"
#define CASE_TRAD "Trad"
#define CASE_UNIHAN "Unihan"
#define CASE_ZHUYIN "Zhuyin"

const char *getCollationCaseName(const char *value) {
  if (value == NULL) {
    return NULL;
  } else if (strcmp(value, COLLATION_BIG5HAN) == 0) {
    return CASE_BIG5HAN;
  } else if (strcmp(value, COLLATION_COMPAT) == 0) {
    return CASE_COMPAT;
  } else if (strcmp(value, COLLATION_DICT) == 0) {
    return CASE_DICT;
  } else if (strcmp(value, COLLATION_DIRECT) == 0) {
    return CASE_DIRECT;
  } else if (strcmp(value, COLLATION_DUCET) == 0) {
    return CASE_DUCET;
  } else if (strcmp(value, COLLATION_EMOJI) == 0) {
    return CASE_EMOJI;
  } else if (strcmp(value, COLLATION_EOR) == 0) {
    return CASE_EOR;
  } else if (strcmp(value, COLLATION_GB2312) == 0) {
    return CASE_GB2312;
  } else if (strcmp(value, COLLATION_PHONEBK) == 0) {
    return CASE_PHONEBK;
  } else if (strcmp(value, COLLATION_PHONETIC) == 0) {
    return CASE_PHONETIC;
  } else if (strcmp(value, COLLATION_PINYIN) == 0) {
    return CASE_PINYIN;
  } else if (strcmp(value, COLLATION_REFORMED) == 0) {
    return CASE_REFORMED;
  } else if (strcmp(value, COLLATION_SEARCH) == 0) {
    return CASE_SEARCH;
  } else if (strcmp(value, COLLATION_SEARCHJL) == 0) {
    return CASE_SEARCHJL;
  } else if (strcmp(value, COLLATION_STANDARD) == 0) {
    return CASE_STANDARD;
  } else if (strcmp(value, COLLATION_STROKE) == 0) {
    return CASE_STROKE;
  } else if (strcmp(value, COLLATION_TRAD) == 0) {
    return CASE_TRAD;
  } else if (strcmp(value, COLLATION_UNIHAN) == 0) {
    return CASE_UNIHAN;
  } else if (strcmp(value, COLLATION_ZHUYIN) == 0) {
    return CASE_ZHUYIN;
  }

  return NULL;
}
