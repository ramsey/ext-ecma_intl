#include "tests/criterion/test.h"

#include "src/ecma402/localeIdentifier.h"

#define TEST_SUITE ecma402LocaleIdentifier

Test(TEST_SUITE, initWithNullLocaleReturnsNull) {
  cr_assert_null(initLocaleIdentifier(NULL));
}

Test(TEST_SUITE, initWithEmptyLocaleReturnsNull) {
  cr_assert_null(initLocaleIdentifier(""));
}

Test(TEST_SUITE, initWithLocale) {
  localeIdentifier *locale;
  char *localeId = "en-US";

  locale = initLocaleIdentifier(localeId);

  cr_assert_not_null(locale);
  cr_assert(eq(str, locale->id, "en-US"));
  cr_assert(eq(int, locale->length, 5));
  cr_assert(ne(ptr, locale->id, localeId));

  freeLocaleIdentifier(locale);
}
