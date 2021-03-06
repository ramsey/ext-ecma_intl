#include "src/php/support/numbering_system.h"
#include "tests/criterion/test.h"

#define TEST_SUITE phpSupportNumberingSystem

ParameterizedTestParameters(TEST_SUITE, getsNumberingSystemCaseNameForValue) {
  START_BASIC_TEST_PARAMS(92)

  BASIC_TEST("adlm", "Adlm")
  BASIC_TEST("ahom", "Ahom")
  BASIC_TEST("arab", "Arab")
  BASIC_TEST("arabext", "Arabext")
  BASIC_TEST("armn", "Armn")
  BASIC_TEST("armnlow", "Armnlow")
  BASIC_TEST("bali", "Bali")
  BASIC_TEST("beng", "Beng")
  BASIC_TEST("bhks", "Bhks")
  BASIC_TEST("brah", "Brah")
  BASIC_TEST("cakm", "Cakm")
  BASIC_TEST("cham", "Cham")
  BASIC_TEST("cyrl", "Cyrl")
  BASIC_TEST("deva", "Deva")
  BASIC_TEST("diak", "Diak")
  BASIC_TEST("ethi", "Ethi")
  BASIC_TEST("finance", "Finance")
  BASIC_TEST("fullwide", "Fullwide")
  BASIC_TEST("geor", "Geor")
  BASIC_TEST("gong", "Gong")
  BASIC_TEST("gonm", "Gonm")
  BASIC_TEST("grek", "Grek")
  BASIC_TEST("greklow", "Greklow")
  BASIC_TEST("gujr", "Gujr")
  BASIC_TEST("guru", "Guru")
  BASIC_TEST("hanidays", "Hanidays")
  BASIC_TEST("hanidec", "Hanidec")
  BASIC_TEST("hans", "Hans")
  BASIC_TEST("hansfin", "Hansfin")
  BASIC_TEST("hant", "Hant")
  BASIC_TEST("hantfin", "Hantfin")
  BASIC_TEST("hebr", "Hebr")
  BASIC_TEST("hmng", "Hmng")
  BASIC_TEST("hmnp", "Hmnp")
  BASIC_TEST("java", "Java")
  BASIC_TEST("jpan", "Jpan")
  BASIC_TEST("jpanfin", "Jpanfin")
  BASIC_TEST("jpanyear", "Jpanyear")
  BASIC_TEST("kali", "Kali")
  BASIC_TEST("kawi", "Kawi")
  BASIC_TEST("khmr", "Khmr")
  BASIC_TEST("knda", "Knda")
  BASIC_TEST("lana", "Lana")
  BASIC_TEST("lanatham", "Lanatham")
  BASIC_TEST("laoo", "Laoo")
  BASIC_TEST("latn", "Latn")
  BASIC_TEST("lepc", "Lepc")
  BASIC_TEST("limb", "Limb")
  BASIC_TEST("mathbold", "Mathbold")
  BASIC_TEST("mathdbl", "Mathdbl")
  BASIC_TEST("mathmono", "Mathmono")
  BASIC_TEST("mathsanb", "Mathsanb")
  BASIC_TEST("mathsans", "Mathsans")
  BASIC_TEST("mlym", "Mlym")
  BASIC_TEST("modi", "Modi")
  BASIC_TEST("mong", "Mong")
  BASIC_TEST("mroo", "Mroo")
  BASIC_TEST("mtei", "Mtei")
  BASIC_TEST("mymr", "Mymr")
  BASIC_TEST("mymrshan", "Mymrshan")
  BASIC_TEST("mymrtlng", "Mymrtlng")
  BASIC_TEST("nagm", "Nagm")
  BASIC_TEST("native", "Native")
  BASIC_TEST("newa", "Newa")
  BASIC_TEST("nkoo", "Nkoo")
  BASIC_TEST("olck", "Olck")
  BASIC_TEST("orya", "Orya")
  BASIC_TEST("osma", "Osma")
  BASIC_TEST("rohg", "Rohg")
  BASIC_TEST("roman", "Roman")
  BASIC_TEST("romanlow", "Romanlow")
  BASIC_TEST("saur", "Saur")
  BASIC_TEST("segment", "Segment")
  BASIC_TEST("shrd", "Shrd")
  BASIC_TEST("sind", "Sind")
  BASIC_TEST("sinh", "Sinh")
  BASIC_TEST("sora", "Sora")
  BASIC_TEST("sund", "Sund")
  BASIC_TEST("takr", "Takr")
  BASIC_TEST("talu", "Talu")
  BASIC_TEST("taml", "Taml")
  BASIC_TEST("tamldec", "Tamldec")
  BASIC_TEST("telu", "Telu")
  BASIC_TEST("thai", "Thai")
  BASIC_TEST("tibt", "Tibt")
  BASIC_TEST("tirh", "Tirh")
  BASIC_TEST("tnsa", "Tnsa")
  BASIC_TEST("traditio", "Traditio")
  BASIC_TEST("vaii", "Vaii")
  BASIC_TEST("wara", "Wara")
  BASIC_TEST("wcho", "Wcho")
  BASIC_TEST("foo", NULL)
  BASIC_TEST(NULL, NULL)

  END_BASIC_TEST_PARAMS;
}

BASIC_PARAMETERIZED_TEST(getsNumberingSystemCaseNameForValue,
                         getNumberingSystemCaseName)
