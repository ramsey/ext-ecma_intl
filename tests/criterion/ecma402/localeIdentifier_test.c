#include "tests/criterion/test.h"

#include "src/ecma402/localeIdentifier.h"

Test(ecma402LocaleIdentifier, initWithNullLocaleReturnsNull) {
  cr_assert_null(initLocaleIdentifier(NULL));
}

Test(ecma402LocaleIdentifier, initWithEmptyLocaleReturnsNull) {
  cr_assert_null(initLocaleIdentifier(""));
}

Test(ecma402LocaleIdentifier, initWithLocale) {
  localeIdentifier *locale;
  char *localeId = "en-US";

  locale = initLocaleIdentifier(localeId);

  cr_assert_not_null(locale);
  cr_assert(eq(str, locale->id, "en-US"));
  cr_assert(eq(int, locale->length, 5));
  cr_assert(ne(ptr, locale->id, localeId));

  freeLocaleIdentifier(locale);
}
