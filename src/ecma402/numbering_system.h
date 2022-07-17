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

#ifndef ECMA_INTL_ECMA402_NUMBERING_SYSTEM_H
#define ECMA_INTL_ECMA402_NUMBERING_SYSTEM_H

#include "src/common.h"

#define NUMBERING_SYSTEM_ADLM "adlm"
#define NUMBERING_SYSTEM_AHOM "ahom"
#define NUMBERING_SYSTEM_ARAB "arab"
#define NUMBERING_SYSTEM_ARABEXT "arabext"
#define NUMBERING_SYSTEM_ARMN "armn"
#define NUMBERING_SYSTEM_ARMNLOW "armnlow"
#define NUMBERING_SYSTEM_BALI "bali"
#define NUMBERING_SYSTEM_BENG "beng"
#define NUMBERING_SYSTEM_BHKS "bhks"
#define NUMBERING_SYSTEM_BRAH "brah"
#define NUMBERING_SYSTEM_CAKM "cakm"
#define NUMBERING_SYSTEM_CHAM "cham"
#define NUMBERING_SYSTEM_CYRL "cyrl"
#define NUMBERING_SYSTEM_DEVA "deva"
#define NUMBERING_SYSTEM_DIAK "diak"
#define NUMBERING_SYSTEM_ETHI "ethi"
#define NUMBERING_SYSTEM_FINANCE "finance"
#define NUMBERING_SYSTEM_FULLWIDE "fullwide"
#define NUMBERING_SYSTEM_GEOR "geor"
#define NUMBERING_SYSTEM_GONG "gong"
#define NUMBERING_SYSTEM_GONM "gonm"
#define NUMBERING_SYSTEM_GREK "grek"
#define NUMBERING_SYSTEM_GREKLOW "greklow"
#define NUMBERING_SYSTEM_GUJR "gujr"
#define NUMBERING_SYSTEM_GURU "guru"
#define NUMBERING_SYSTEM_HANIDAYS "hanidays"
#define NUMBERING_SYSTEM_HANIDEC "hanidec"
#define NUMBERING_SYSTEM_HANS "hans"
#define NUMBERING_SYSTEM_HANSFIN "hansfin"
#define NUMBERING_SYSTEM_HANT "hant"
#define NUMBERING_SYSTEM_HANTFIN "hantfin"
#define NUMBERING_SYSTEM_HEBR "hebr"
#define NUMBERING_SYSTEM_HMNG "hmng"
#define NUMBERING_SYSTEM_HMNP "hmnp"
#define NUMBERING_SYSTEM_JAVA "java"
#define NUMBERING_SYSTEM_JPAN "jpan"
#define NUMBERING_SYSTEM_JPANFIN "jpanfin"
#define NUMBERING_SYSTEM_JPANYEAR "jpanyear"
#define NUMBERING_SYSTEM_KALI "kali"
#define NUMBERING_SYSTEM_KAWI "kawi"
#define NUMBERING_SYSTEM_KHMR "khmr"
#define NUMBERING_SYSTEM_KNDA "knda"
#define NUMBERING_SYSTEM_LANA "lana"
#define NUMBERING_SYSTEM_LANATHAM "lanatham"
#define NUMBERING_SYSTEM_LAOO "laoo"
#define NUMBERING_SYSTEM_LATN "latn"
#define NUMBERING_SYSTEM_LEPC "lepc"
#define NUMBERING_SYSTEM_LIMB "limb"
#define NUMBERING_SYSTEM_MATHBOLD "mathbold"
#define NUMBERING_SYSTEM_MATHDBL "mathdbl"
#define NUMBERING_SYSTEM_MATHMONO "mathmono"
#define NUMBERING_SYSTEM_MATHSANB "mathsanb"
#define NUMBERING_SYSTEM_MATHSANS "mathsans"
#define NUMBERING_SYSTEM_MLYM "mlym"
#define NUMBERING_SYSTEM_MODI "modi"
#define NUMBERING_SYSTEM_MONG "mong"
#define NUMBERING_SYSTEM_MROO "mroo"
#define NUMBERING_SYSTEM_MTEI "mtei"
#define NUMBERING_SYSTEM_MYMR "mymr"
#define NUMBERING_SYSTEM_MYMRSHAN "mymrshan"
#define NUMBERING_SYSTEM_MYMRTLNG "mymrtlng"
#define NUMBERING_SYSTEM_NAGM "nagm"
#define NUMBERING_SYSTEM_NATIVE "native"
#define NUMBERING_SYSTEM_NEWA "newa"
#define NUMBERING_SYSTEM_NKOO "nkoo"
#define NUMBERING_SYSTEM_OLCK "olck"
#define NUMBERING_SYSTEM_ORYA "orya"
#define NUMBERING_SYSTEM_OSMA "osma"
#define NUMBERING_SYSTEM_ROHG "rohg"
#define NUMBERING_SYSTEM_ROMAN "roman"
#define NUMBERING_SYSTEM_ROMANLOW "romanlow"
#define NUMBERING_SYSTEM_SAUR "saur"
#define NUMBERING_SYSTEM_SEGMENT "segment"
#define NUMBERING_SYSTEM_SHRD "shrd"
#define NUMBERING_SYSTEM_SIND "sind"
#define NUMBERING_SYSTEM_SINH "sinh"
#define NUMBERING_SYSTEM_SORA "sora"
#define NUMBERING_SYSTEM_SUND "sund"
#define NUMBERING_SYSTEM_TAKR "takr"
#define NUMBERING_SYSTEM_TALU "talu"
#define NUMBERING_SYSTEM_TAML "taml"
#define NUMBERING_SYSTEM_TAMLDEC "tamldec"
#define NUMBERING_SYSTEM_TELU "telu"
#define NUMBERING_SYSTEM_THAI "thai"
#define NUMBERING_SYSTEM_TIBT "tibt"
#define NUMBERING_SYSTEM_TIRH "tirh"
#define NUMBERING_SYSTEM_TNSA "tnsa"
#define NUMBERING_SYSTEM_TRADITIO "traditio"
#define NUMBERING_SYSTEM_VAII "vaii"
#define NUMBERING_SYSTEM_WARA "wara"
#define NUMBERING_SYSTEM_WCHO "wcho"

#define NUMBERING_SYSTEMS_CAPACITY 10

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns an array of numbering systems supported for the given locale. If the
 * locale defines a numbering system using a keyword, the resulting array will
 * have only that numbering system as the locale's preferred supported numbering
 * system.
 *
 * The numbering system parameter should already be allocated on the stack with
 * enough memory to store all the numbering systems. Typically, this should use
 * NUMBERING_SYSTEMS_CAPACITY. For example:
 *
 *     (const char **)malloc(sizeof(const char *) * NUMBERING_SYSTEMS_CAPACITY)
 *
 * @param localeId The locale to check.
 * @param numberingSystems A pointer in which to store the resulting char array
 * of numbering systems.
 *
 * @return The total count of the number of numbering systems stored to the hour
 * cycles array.
 */
int getSupportedNumberingSystems(const char *localeId,
                                 const char **numberingSystems);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_ECMA402_NUMBERING_SYSTEM_H */
