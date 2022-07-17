#include "src/ecma402/numbering_system.h"
#include "tests/criterion/test.h"

#define TEST_SUITE ecma402NumberingSystem

Test(TEST_SUITE, getsSupportedNumberingSystemsFromNumberingSystemKeyword) {
  const char **numberingSystems;
  int numberingSystemCount;

  numberingSystems =
      (const char **)malloc(sizeof(const char *) * NUMBERING_SYSTEMS_CAPACITY);
  numberingSystemCount =
      getSupportedNumberingSystems("fa-IR-u-nu-traditio", numberingSystems);

  cr_assert(eq(int, numberingSystemCount, 1));
  cr_assert(eq(str, (char *)numberingSystems[0], "traditio"));

  for (int i = 0; i < numberingSystemCount; i++) {
    free((void *)numberingSystems[i]);
  }
  free(numberingSystems);
}

Test(TEST_SUITE, getsDefaultSupportedNumberingSystemsForLocale) {
  const char **numberingSystems;
  int numberingSystemCount;

  numberingSystems =
      (const char **)malloc(sizeof(const char *) * NUMBERING_SYSTEMS_CAPACITY);
  numberingSystemCount =
      getSupportedNumberingSystems("fa-IR", numberingSystems);

  cr_assert(eq(int, numberingSystemCount, 1));
  cr_assert(eq(str, (char *)numberingSystems[0], "arabext"));

  for (int i = 0; i < numberingSystemCount; i++) {
    free((void *)numberingSystems[i]);
  }
  free(numberingSystems);
}
