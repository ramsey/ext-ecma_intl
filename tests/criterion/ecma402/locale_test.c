#include "tests/criterion/test.h"

#include "src/ecma402/locale.h"

#define TEST_SUITE ecma402Locale

Test(TEST_SUITE, initializesEmptyLocale) {
  locale *locale;

  locale = initEmptyLocale();

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert_null(locale->baseName);
  cr_assert_null(locale->calendar);
  cr_assert_null(locale->caseFirst);
  cr_assert_null(locale->collation);
  cr_assert_null(locale->hourCycle);
  cr_assert_null(locale->language);
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, false));
  cr_assert_null(locale->region);
  cr_assert_null(locale->script);

  cr_assert_not_null(locale->status);
  cr_assert(eq(int, locale->status->ecma, 0));
  cr_assert(eq(int, locale->status->icu, 0));
  cr_assert_null(locale->status->errorMessage);
  cr_assert(eq(int, locale->status->lineNumber, 0));
  cr_assert_null(locale->status->fileName);

  freeLocale(locale);
}

Test(TEST_SUITE, initWithNullLocaleReturnsNull) {
  cr_assert_null(initLocale(NULL));
}

Test(TEST_SUITE, initializesWithBasicLocale) {
  locale *locale;
  char *localeId = "en_us";

  locale = initLocale(localeId);

  cr_assert_not_null(locale);

  cr_assert(eq(str, locale->originalId, "en_us"));
  cr_assert(ne(ptr, locale->originalId, localeId));

  cr_assert(eq(str, locale->id, "en-US"));
  cr_assert(ne(ptr, locale->id, localeId));

  cr_assert(eq(str, locale->baseName, "en-US"));
  cr_assert_null(locale->calendar);
  cr_assert_null(locale->caseFirst);
  cr_assert_null(locale->collation);
  cr_assert_null(locale->hourCycle);
  cr_assert(eq(str, locale->language, "en"));
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, 0));
  cr_assert(eq(str, locale->region, "US"));
  cr_assert_null(locale->script);

  freeLocale(locale);
}

Test(TEST_SUITE, initializesWithFullLocale) {
  locale *locale;
  char *localeId =
      "en-Latn-US-u-ca-gregory-nu-latn-kf-upper-co-phonebk-kn-true-hc-h23";

  locale = initLocale(localeId);

  cr_assert_not_null(locale);

  cr_assert(
      eq(str, locale->originalId,
         "en-Latn-US-u-ca-gregory-nu-latn-kf-upper-co-phonebk-kn-true-hc-h23"));
  cr_assert(ne(ptr, locale->originalId, localeId));

  cr_assert(
      eq(str, locale->id,
         "en-Latn-US-u-ca-gregory-co-phonebk-hc-h23-kf-upper-kn-nu-latn"));
  cr_assert(ne(ptr, locale->id, localeId));

  cr_assert(eq(str, locale->baseName, "en-Latn-US"));
  cr_assert(eq(str, locale->calendar, "gregory"));
  cr_assert(eq(str, locale->caseFirst, "upper"));
  cr_assert(eq(str, locale->collation, "phonebk"));
  cr_assert(eq(str, locale->hourCycle, "h23"));
  cr_assert(eq(str, locale->language, "en"));
  cr_assert(eq(str, locale->numberingSystem, "latn"));
  cr_assert(eq(int, locale->numeric, 1));
  cr_assert(eq(str, locale->region, "US"));
  cr_assert(eq(str, locale->script, "Latn"));

  freeLocale(locale);
}

Test(TEST_SUITE, initializesWithLanguageOnly) {
  locale *locale;
  char *localeId = "en";

  locale = initLocale(localeId);

  cr_assert_not_null(locale);

  cr_assert(eq(str, locale->originalId, "en"));
  cr_assert(ne(ptr, locale->originalId, localeId));

  cr_assert(eq(str, locale->id, "en"));
  cr_assert(ne(ptr, locale->id, localeId));

  cr_assert(eq(str, locale->baseName, "en"));
  cr_assert_null(locale->calendar);
  cr_assert_null(locale->caseFirst);
  cr_assert_null(locale->collation);
  cr_assert_null(locale->hourCycle);
  cr_assert(eq(str, locale->language, "en"));
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, 0));
  cr_assert_null(locale->region);
  cr_assert_null(locale->script);

  freeLocale(locale);
}

Test(TEST_SUITE, initializesWithRegionOnly) {
  locale *locale;
  char *localeId = "_US";

  locale = initLocale(localeId);

  cr_assert_not_null(locale);

  cr_assert(eq(str, locale->originalId, "_US"));
  cr_assert(ne(ptr, locale->originalId, localeId));

  cr_assert(eq(str, locale->id, "und-US"));
  cr_assert(ne(ptr, locale->id, localeId));

  cr_assert(eq(str, locale->baseName, "und-US"));
  cr_assert_null(locale->calendar);
  cr_assert_null(locale->caseFirst);
  cr_assert_null(locale->collation);
  cr_assert_null(locale->hourCycle);
  cr_assert(eq(str, locale->language, "und"));
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, 0));
  cr_assert(eq(str, locale->region, "US"));
  cr_assert_null(locale->script);

  freeLocale(locale);
}

Test(TEST_SUITE, initializesWithScriptOnly) {
  locale *locale;
  char *localeId = "_latn";

  locale = initLocale(localeId);

  cr_assert_not_null(locale);

  cr_assert(eq(str, locale->originalId, "_latn"));
  cr_assert(ne(ptr, locale->originalId, localeId));

  cr_assert(eq(str, locale->id, "und-Latn"));
  cr_assert(ne(ptr, locale->id, localeId));

  cr_assert(eq(str, locale->baseName, "und-Latn"));
  cr_assert_null(locale->calendar);
  cr_assert_null(locale->caseFirst);
  cr_assert_null(locale->collation);
  cr_assert_null(locale->hourCycle);
  cr_assert(eq(str, locale->language, "und"));
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, 0));
  cr_assert_null(locale->region);
  cr_assert(eq(str, locale->script, "Latn"));

  freeLocale(locale);
}

Test(TEST_SUITE, initializesWithEmptyString) {
  locale *locale;
  char *localeId = "";

  locale = initLocale(localeId);

  cr_assert_not_null(locale);

  cr_assert(ne(ptr, locale->originalId, ""));
  cr_assert(ne(ptr, locale->originalId, localeId));

  cr_assert(eq(str, locale->id, "und"));
  cr_assert(ne(ptr, locale->id, localeId));

  cr_assert(eq(str, locale->baseName, "und"));
  cr_assert_null(locale->calendar);
  cr_assert_null(locale->caseFirst);
  cr_assert_null(locale->collation);
  cr_assert_null(locale->hourCycle);
  cr_assert(eq(str, locale->language, "und"));
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, 0));
  cr_assert_null(locale->region);
  cr_assert_null(locale->script);

  freeLocale(locale);
}

Test(TEST_SUITE, createsEmptyLocaleWithAnEcmaError) {
  locale *locale;

  locale = localeWithEcmaError(INVALID_LOCALE_ID, "foobar.c", 12,
                               "A test error message");

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert_null(locale->baseName);
  cr_assert_null(locale->calendar);
  cr_assert_null(locale->caseFirst);
  cr_assert_null(locale->collation);
  cr_assert_null(locale->hourCycle);
  cr_assert_null(locale->language);
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, false));
  cr_assert_null(locale->region);
  cr_assert_null(locale->script);

  cr_assert_not_null(locale->status);
  cr_assert(eq(int, locale->status->ecma, INVALID_LOCALE_ID));
  cr_assert(eq(int, locale->status->icu, 0));
  cr_assert(
      eq(str, (char *)locale->status->errorMessage, "A test error message"));
  cr_assert(eq(int, locale->status->lineNumber, 12));
  cr_assert(eq(str, (char *)locale->status->fileName, "foobar.c"));

  freeLocale(locale);
}
