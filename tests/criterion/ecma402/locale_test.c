#include "tests/criterion/test.h"

#include "src/ecma402/locale.h"

Test(ecma402Locale, initWithNullLocaleReturnsNull) {
  cr_assert_null(ecma402_initLocale(NULL));
}

Test(ecma402Locale, initWithEmptyLocaleReturnsNull) {
  cr_assert_null(ecma402_initLocale(""));
}

Test(ecma402Locale, initWithLocale) {
  ecma402_locale *locale;
  char *localeId = "en-US";

  locale = ecma402_initLocale(localeId);

  cr_assert_not_null(locale);
  cr_assert(eq(str, locale->id, "en-US"));
  cr_assert(eq(int, locale->length, 5));
  cr_assert(ne(ptr, locale->id, localeId));

  ecma402_freeLocale(locale);
}
