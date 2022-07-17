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

#include "numbering_system.h"

#include "src/ecma402/numbering_system.h"

#include <string.h>

#define CASE_ADLM "Adlm"
#define CASE_AHOM "Ahom"
#define CASE_ARAB "Arab"
#define CASE_ARABEXT "Arabext"
#define CASE_ARMN "Armn"
#define CASE_ARMNLOW "Armnlow"
#define CASE_BALI "Bali"
#define CASE_BENG "Beng"
#define CASE_BHKS "Bhks"
#define CASE_BRAH "Brah"
#define CASE_CAKM "Cakm"
#define CASE_CHAM "Cham"
#define CASE_CYRL "Cyrl"
#define CASE_DEVA "Deva"
#define CASE_DIAK "Diak"
#define CASE_ETHI "Ethi"
#define CASE_FINANCE "Finance"
#define CASE_FULLWIDE "Fullwide"
#define CASE_GEOR "Geor"
#define CASE_GONG "Gong"
#define CASE_GONM "Gonm"
#define CASE_GREK "Grek"
#define CASE_GREKLOW "Greklow"
#define CASE_GUJR "Gujr"
#define CASE_GURU "Guru"
#define CASE_HANIDAYS "Hanidays"
#define CASE_HANIDEC "Hanidec"
#define CASE_HANS "Hans"
#define CASE_HANSFIN "Hansfin"
#define CASE_HANT "Hant"
#define CASE_HANTFIN "Hantfin"
#define CASE_HEBR "Hebr"
#define CASE_HMNG "Hmng"
#define CASE_HMNP "Hmnp"
#define CASE_JAVA "Java"
#define CASE_JPAN "Jpan"
#define CASE_JPANFIN "Jpanfin"
#define CASE_JPANYEAR "Jpanyear"
#define CASE_KALI "Kali"
#define CASE_KAWI "Kawi"
#define CASE_KHMR "Khmr"
#define CASE_KNDA "Knda"
#define CASE_LANA "Lana"
#define CASE_LANATHAM "Lanatham"
#define CASE_LAOO "Laoo"
#define CASE_LATN "Latn"
#define CASE_LEPC "Lepc"
#define CASE_LIMB "Limb"
#define CASE_MATHBOLD "Mathbold"
#define CASE_MATHDBL "Mathdbl"
#define CASE_MATHMONO "Mathmono"
#define CASE_MATHSANB "Mathsanb"
#define CASE_MATHSANS "Mathsans"
#define CASE_MLYM "Mlym"
#define CASE_MODI "Modi"
#define CASE_MONG "Mong"
#define CASE_MROO "Mroo"
#define CASE_MTEI "Mtei"
#define CASE_MYMR "Mymr"
#define CASE_MYMRSHAN "Mymrshan"
#define CASE_MYMRTLNG "Mymrtlng"
#define CASE_NAGM "Nagm"
#define CASE_NATIVE "Native"
#define CASE_NEWA "Newa"
#define CASE_NKOO "Nkoo"
#define CASE_OLCK "Olck"
#define CASE_ORYA "Orya"
#define CASE_OSMA "Osma"
#define CASE_ROHG "Rohg"
#define CASE_ROMAN "Roman"
#define CASE_ROMANLOW "Romanlow"
#define CASE_SAUR "Saur"
#define CASE_SEGMENT "Segment"
#define CASE_SHRD "Shrd"
#define CASE_SIND "Sind"
#define CASE_SINH "Sinh"
#define CASE_SORA "Sora"
#define CASE_SUND "Sund"
#define CASE_TAKR "Takr"
#define CASE_TALU "Talu"
#define CASE_TAML "Taml"
#define CASE_TAMLDEC "Tamldec"
#define CASE_TELU "Telu"
#define CASE_THAI "Thai"
#define CASE_TIBT "Tibt"
#define CASE_TIRH "Tirh"
#define CASE_TNSA "Tnsa"
#define CASE_TRADITIO "Traditio"
#define CASE_VAII "Vaii"
#define CASE_WARA "Wara"
#define CASE_WCHO "Wcho"

const char *getNumberingSystemCaseName(const char *value) {
  if (value == NULL) {
    return NULL;
  } else if (strcmp(value, NUMBERING_SYSTEM_ADLM) == 0) {
    return CASE_ADLM;
  } else if (strcmp(value, NUMBERING_SYSTEM_AHOM) == 0) {
    return CASE_AHOM;
  } else if (strcmp(value, NUMBERING_SYSTEM_ARAB) == 0) {
    return CASE_ARAB;
  } else if (strcmp(value, NUMBERING_SYSTEM_ARABEXT) == 0) {
    return CASE_ARABEXT;
  } else if (strcmp(value, NUMBERING_SYSTEM_ARMN) == 0) {
    return CASE_ARMN;
  } else if (strcmp(value, NUMBERING_SYSTEM_ARMNLOW) == 0) {
    return CASE_ARMNLOW;
  } else if (strcmp(value, NUMBERING_SYSTEM_BALI) == 0) {
    return CASE_BALI;
  } else if (strcmp(value, NUMBERING_SYSTEM_BENG) == 0) {
    return CASE_BENG;
  } else if (strcmp(value, NUMBERING_SYSTEM_BHKS) == 0) {
    return CASE_BHKS;
  } else if (strcmp(value, NUMBERING_SYSTEM_BRAH) == 0) {
    return CASE_BRAH;
  } else if (strcmp(value, NUMBERING_SYSTEM_CAKM) == 0) {
    return CASE_CAKM;
  } else if (strcmp(value, NUMBERING_SYSTEM_CHAM) == 0) {
    return CASE_CHAM;
  } else if (strcmp(value, NUMBERING_SYSTEM_CYRL) == 0) {
    return CASE_CYRL;
  } else if (strcmp(value, NUMBERING_SYSTEM_DEVA) == 0) {
    return CASE_DEVA;
  } else if (strcmp(value, NUMBERING_SYSTEM_DIAK) == 0) {
    return CASE_DIAK;
  } else if (strcmp(value, NUMBERING_SYSTEM_ETHI) == 0) {
    return CASE_ETHI;
  } else if (strcmp(value, NUMBERING_SYSTEM_FINANCE) == 0) {
    return CASE_FINANCE;
  } else if (strcmp(value, NUMBERING_SYSTEM_FULLWIDE) == 0) {
    return CASE_FULLWIDE;
  } else if (strcmp(value, NUMBERING_SYSTEM_GEOR) == 0) {
    return CASE_GEOR;
  } else if (strcmp(value, NUMBERING_SYSTEM_GONG) == 0) {
    return CASE_GONG;
  } else if (strcmp(value, NUMBERING_SYSTEM_GONM) == 0) {
    return CASE_GONM;
  } else if (strcmp(value, NUMBERING_SYSTEM_GREK) == 0) {
    return CASE_GREK;
  } else if (strcmp(value, NUMBERING_SYSTEM_GREKLOW) == 0) {
    return CASE_GREKLOW;
  } else if (strcmp(value, NUMBERING_SYSTEM_GUJR) == 0) {
    return CASE_GUJR;
  } else if (strcmp(value, NUMBERING_SYSTEM_GURU) == 0) {
    return CASE_GURU;
  } else if (strcmp(value, NUMBERING_SYSTEM_HANIDAYS) == 0) {
    return CASE_HANIDAYS;
  } else if (strcmp(value, NUMBERING_SYSTEM_HANIDEC) == 0) {
    return CASE_HANIDEC;
  } else if (strcmp(value, NUMBERING_SYSTEM_HANS) == 0) {
    return CASE_HANS;
  } else if (strcmp(value, NUMBERING_SYSTEM_HANSFIN) == 0) {
    return CASE_HANSFIN;
  } else if (strcmp(value, NUMBERING_SYSTEM_HANT) == 0) {
    return CASE_HANT;
  } else if (strcmp(value, NUMBERING_SYSTEM_HANTFIN) == 0) {
    return CASE_HANTFIN;
  } else if (strcmp(value, NUMBERING_SYSTEM_HEBR) == 0) {
    return CASE_HEBR;
  } else if (strcmp(value, NUMBERING_SYSTEM_HMNG) == 0) {
    return CASE_HMNG;
  } else if (strcmp(value, NUMBERING_SYSTEM_HMNP) == 0) {
    return CASE_HMNP;
  } else if (strcmp(value, NUMBERING_SYSTEM_JAVA) == 0) {
    return CASE_JAVA;
  } else if (strcmp(value, NUMBERING_SYSTEM_JPAN) == 0) {
    return CASE_JPAN;
  } else if (strcmp(value, NUMBERING_SYSTEM_JPANFIN) == 0) {
    return CASE_JPANFIN;
  } else if (strcmp(value, NUMBERING_SYSTEM_JPANYEAR) == 0) {
    return CASE_JPANYEAR;
  } else if (strcmp(value, NUMBERING_SYSTEM_KALI) == 0) {
    return CASE_KALI;
  } else if (strcmp(value, NUMBERING_SYSTEM_KAWI) == 0) {
    return CASE_KAWI;
  } else if (strcmp(value, NUMBERING_SYSTEM_KHMR) == 0) {
    return CASE_KHMR;
  } else if (strcmp(value, NUMBERING_SYSTEM_KNDA) == 0) {
    return CASE_KNDA;
  } else if (strcmp(value, NUMBERING_SYSTEM_LANA) == 0) {
    return CASE_LANA;
  } else if (strcmp(value, NUMBERING_SYSTEM_LANATHAM) == 0) {
    return CASE_LANATHAM;
  } else if (strcmp(value, NUMBERING_SYSTEM_LAOO) == 0) {
    return CASE_LAOO;
  } else if (strcmp(value, NUMBERING_SYSTEM_LATN) == 0) {
    return CASE_LATN;
  } else if (strcmp(value, NUMBERING_SYSTEM_LEPC) == 0) {
    return CASE_LEPC;
  } else if (strcmp(value, NUMBERING_SYSTEM_LIMB) == 0) {
    return CASE_LIMB;
  } else if (strcmp(value, NUMBERING_SYSTEM_MATHBOLD) == 0) {
    return CASE_MATHBOLD;
  } else if (strcmp(value, NUMBERING_SYSTEM_MATHDBL) == 0) {
    return CASE_MATHDBL;
  } else if (strcmp(value, NUMBERING_SYSTEM_MATHMONO) == 0) {
    return CASE_MATHMONO;
  } else if (strcmp(value, NUMBERING_SYSTEM_MATHSANB) == 0) {
    return CASE_MATHSANB;
  } else if (strcmp(value, NUMBERING_SYSTEM_MATHSANS) == 0) {
    return CASE_MATHSANS;
  } else if (strcmp(value, NUMBERING_SYSTEM_MLYM) == 0) {
    return CASE_MLYM;
  } else if (strcmp(value, NUMBERING_SYSTEM_MODI) == 0) {
    return CASE_MODI;
  } else if (strcmp(value, NUMBERING_SYSTEM_MONG) == 0) {
    return CASE_MONG;
  } else if (strcmp(value, NUMBERING_SYSTEM_MROO) == 0) {
    return CASE_MROO;
  } else if (strcmp(value, NUMBERING_SYSTEM_MTEI) == 0) {
    return CASE_MTEI;
  } else if (strcmp(value, NUMBERING_SYSTEM_MYMR) == 0) {
    return CASE_MYMR;
  } else if (strcmp(value, NUMBERING_SYSTEM_MYMRSHAN) == 0) {
    return CASE_MYMRSHAN;
  } else if (strcmp(value, NUMBERING_SYSTEM_MYMRTLNG) == 0) {
    return CASE_MYMRTLNG;
  } else if (strcmp(value, NUMBERING_SYSTEM_NAGM) == 0) {
    return CASE_NAGM;
  } else if (strcmp(value, NUMBERING_SYSTEM_NATIVE) == 0) {
    return CASE_NATIVE;
  } else if (strcmp(value, NUMBERING_SYSTEM_NEWA) == 0) {
    return CASE_NEWA;
  } else if (strcmp(value, NUMBERING_SYSTEM_NKOO) == 0) {
    return CASE_NKOO;
  } else if (strcmp(value, NUMBERING_SYSTEM_OLCK) == 0) {
    return CASE_OLCK;
  } else if (strcmp(value, NUMBERING_SYSTEM_ORYA) == 0) {
    return CASE_ORYA;
  } else if (strcmp(value, NUMBERING_SYSTEM_OSMA) == 0) {
    return CASE_OSMA;
  } else if (strcmp(value, NUMBERING_SYSTEM_ROHG) == 0) {
    return CASE_ROHG;
  } else if (strcmp(value, NUMBERING_SYSTEM_ROMAN) == 0) {
    return CASE_ROMAN;
  } else if (strcmp(value, NUMBERING_SYSTEM_ROMANLOW) == 0) {
    return CASE_ROMANLOW;
  } else if (strcmp(value, NUMBERING_SYSTEM_SAUR) == 0) {
    return CASE_SAUR;
  } else if (strcmp(value, NUMBERING_SYSTEM_SEGMENT) == 0) {
    return CASE_SEGMENT;
  } else if (strcmp(value, NUMBERING_SYSTEM_SHRD) == 0) {
    return CASE_SHRD;
  } else if (strcmp(value, NUMBERING_SYSTEM_SIND) == 0) {
    return CASE_SIND;
  } else if (strcmp(value, NUMBERING_SYSTEM_SINH) == 0) {
    return CASE_SINH;
  } else if (strcmp(value, NUMBERING_SYSTEM_SORA) == 0) {
    return CASE_SORA;
  } else if (strcmp(value, NUMBERING_SYSTEM_SUND) == 0) {
    return CASE_SUND;
  } else if (strcmp(value, NUMBERING_SYSTEM_TAKR) == 0) {
    return CASE_TAKR;
  } else if (strcmp(value, NUMBERING_SYSTEM_TALU) == 0) {
    return CASE_TALU;
  } else if (strcmp(value, NUMBERING_SYSTEM_TAML) == 0) {
    return CASE_TAML;
  } else if (strcmp(value, NUMBERING_SYSTEM_TAMLDEC) == 0) {
    return CASE_TAMLDEC;
  } else if (strcmp(value, NUMBERING_SYSTEM_TELU) == 0) {
    return CASE_TELU;
  } else if (strcmp(value, NUMBERING_SYSTEM_THAI) == 0) {
    return CASE_THAI;
  } else if (strcmp(value, NUMBERING_SYSTEM_TIBT) == 0) {
    return CASE_TIBT;
  } else if (strcmp(value, NUMBERING_SYSTEM_TIRH) == 0) {
    return CASE_TIRH;
  } else if (strcmp(value, NUMBERING_SYSTEM_TNSA) == 0) {
    return CASE_TNSA;
  } else if (strcmp(value, NUMBERING_SYSTEM_TRADITIO) == 0) {
    return CASE_TRADITIO;
  } else if (strcmp(value, NUMBERING_SYSTEM_VAII) == 0) {
    return CASE_VAII;
  } else if (strcmp(value, NUMBERING_SYSTEM_WARA) == 0) {
    return CASE_WARA;
  } else if (strcmp(value, NUMBERING_SYSTEM_WCHO) == 0) {
    return CASE_WCHO;
  }

  return NULL;
}
