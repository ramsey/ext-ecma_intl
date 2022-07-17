#include "src/ecma402/collation.h"
#include "tests/criterion/test.h"

#define TEST_SUITE ecma402Collation

Test(TEST_SUITE, getsSupportedCollationsFromCollationKeyword) {
  const char **collations;
  int collationCount;

  collations =
      (const char **)malloc(sizeof(const char *) * COLLATIONS_CAPACITY);
  collationCount = getSupportedCollations("de-DE-u-co-dict", collations);

  cr_assert(eq(int, collationCount, 1));
  cr_assert(eq(str, (char *)collations[0], "dict"));

  for (int i = 0; i < collationCount; i++) {
    free((void *)collations[i]);
  }
  free(collations);
}

Test(TEST_SUITE, getsDefaultSupportedCollationsForLocale) {
  const char **collations;
  int collationCount;

  collations =
      (const char **)malloc(sizeof(const char *) * COLLATIONS_CAPACITY);
  collationCount = getSupportedCollations("de-DE", collations);

  cr_assert(eq(int, collationCount, 3));
  cr_assert(eq(str, (char *)collations[0], "phonebk"));
  cr_assert(eq(str, (char *)collations[1], "emoji"));
  cr_assert(eq(str, (char *)collations[2], "eor"));

  for (int i = 0; i < collationCount; i++) {
    free((void *)collations[i]);
  }
  free(collations);
}
