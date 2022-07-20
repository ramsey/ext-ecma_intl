#include "tests/criterion/test.h"

#include "src/ecma402/error.h"
#include "src/ecma402/locale.h"

#include <unicode/uloc.h>

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
  cr_assert(eq(int, locale->numeric, false));
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
  cr_assert(eq(int, locale->numeric, true));
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
  cr_assert(eq(int, locale->numeric, false));
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
  cr_assert_null(locale->language);
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, false));
  cr_assert(eq(str, locale->region, "US"));
  cr_assert_null(locale->script);

  freeLocale(locale);
}

Test(TEST_SUITE, initializesWithUndeterminedLanguageAndRegion) {
  locale *locale;
  char *localeId = "und-US";

  locale = initLocale(localeId);

  cr_assert_not_null(locale);

  cr_assert(eq(str, locale->originalId, "und-US"));
  cr_assert(ne(ptr, locale->originalId, localeId));

  cr_assert(eq(str, locale->id, "und-US"));
  cr_assert(ne(ptr, locale->id, localeId));

  cr_assert(eq(str, locale->baseName, "und-US"));
  cr_assert_null(locale->calendar);
  cr_assert_null(locale->caseFirst);
  cr_assert_null(locale->collation);
  cr_assert_null(locale->hourCycle);
  cr_assert_null(locale->language);
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, false));
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
  cr_assert_null(locale->language);
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, false));
  cr_assert_null(locale->region);
  cr_assert(eq(str, locale->script, "Latn"));

  freeLocale(locale);
}

Test(TEST_SUITE, initializesWithEmptyString) {
  locale *locale;
  char *localeId = "";

  locale = initLocale(localeId);

  cr_assert_not_null(locale);

  cr_assert(ne(ptr, locale->originalId, localeId));
  cr_assert(eq(str, locale->originalId, "en-US-u-va-posix"));

  cr_assert(eq(str, locale->id, "en-US-u-va-posix"));
  cr_assert(ne(ptr, locale->id, localeId));

  cr_assert(eq(str, locale->baseName, "en-US-u-va-posix"));
  cr_assert_null(locale->calendar);
  cr_assert_null(locale->caseFirst);
  cr_assert_null(locale->collation);
  cr_assert_null(locale->hourCycle);
  cr_assert(eq(str, locale->language, "en"));
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, false));
  cr_assert(eq(str, locale->region, "US"));
  cr_assert_null(locale->script);

  freeLocale(locale);
}

Test(TEST_SUITE, initializesWithUndeterminedLocale) {
  locale *locale;
  char *localeId = "und";

  locale = initLocale(localeId);

  cr_assert_not_null(locale);

  cr_assert(ne(ptr, locale->originalId, localeId));
  cr_assert(eq(str, locale->originalId, "en-US-u-va-posix"));

  cr_assert(eq(str, locale->id, "en-US-u-va-posix"));
  cr_assert(ne(ptr, locale->id, localeId));

  cr_assert(eq(str, locale->baseName, "en-US-u-va-posix"));
  cr_assert_null(locale->calendar);
  cr_assert_null(locale->caseFirst);
  cr_assert_null(locale->collation);
  cr_assert_null(locale->hourCycle);
  cr_assert(eq(str, locale->language, "en"));
  cr_assert_null(locale->numberingSystem);
  cr_assert(eq(int, locale->numeric, false));
  cr_assert(eq(str, locale->region, "US"));
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

Test(TEST_SUITE, maximizesEmptyStringLocale) {
  locale *locale, *maxLocale;
  char *localeId = "";

  locale = initLocale(localeId);
  maxLocale = maximizeLocale(locale);

  cr_assert_not_null(maxLocale);

  cr_assert(eq(str, maxLocale->originalId, "en-Latn-US-u-va-posix"));
  cr_assert(ne(ptr, maxLocale->originalId, localeId));

  cr_assert(eq(str, maxLocale->id, "en-Latn-US-u-va-posix"));
  cr_assert(ne(ptr, maxLocale->id, localeId));

  cr_assert(eq(str, maxLocale->baseName, "en-Latn-US-u-va-posix"));
  cr_assert_null(maxLocale->calendar);
  cr_assert_null(maxLocale->caseFirst);
  cr_assert_null(maxLocale->collation);
  cr_assert_null(maxLocale->hourCycle);
  cr_assert(eq(str, maxLocale->language, "en"));
  cr_assert_null(maxLocale->numberingSystem);
  cr_assert(eq(int, maxLocale->numeric, false));
  cr_assert(eq(str, maxLocale->region, "US"));
  cr_assert(eq(str, maxLocale->script, "Latn"));

  freeLocale(locale);
  freeLocale(maxLocale);
}

Test(TEST_SUITE, minimizesEmptyStringLocale) {
  locale *locale, *minLocale;
  char *localeId = "";

  locale = initLocale(localeId);
  minLocale = minimizeLocale(locale);

  cr_assert_not_null(minLocale);

  cr_assert(eq(str, minLocale->originalId, "en-u-va-posix"));
  cr_assert(ne(ptr, minLocale->originalId, localeId));

  cr_assert(eq(str, minLocale->id, "en-u-va-posix"));
  cr_assert(ne(ptr, minLocale->id, localeId));

  cr_assert(eq(str, minLocale->baseName, "en-u-va-posix"));
  cr_assert_null(minLocale->calendar);
  cr_assert_null(minLocale->caseFirst);
  cr_assert_null(minLocale->collation);
  cr_assert_null(minLocale->hourCycle);
  cr_assert(eq(str, minLocale->language, "en"));
  cr_assert_null(minLocale->numberingSystem);
  cr_assert(eq(int, minLocale->numeric, false));
  cr_assert_null(minLocale->region);
  cr_assert_null(minLocale->script);

  freeLocale(locale);
  freeLocale(minLocale);
}

Test(TEST_SUITE, errorsWhenTryingToMaximizeWithInvalidLocale) {
  locale *locale, *maxLocale;
  const char *localeId = "invalid locale id";

  locale = initEmptyLocale();
  locale->canonicalId = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  locale->canonicalId = strdup(localeId);

  maxLocale = maximizeLocale(locale);

  cr_assert_not_null(maxLocale);
  cr_assert(eq(int, hasError(maxLocale->status), true));
  cr_assert(eq(int, maxLocale->status->ecma, UNABLE_TO_MAXIMIZE_LOCALE));

  freeLocale(locale);
  freeLocale(maxLocale);
}

Test(TEST_SUITE, errorsWhenTryingToMinimizeWithInvalidLocale) {
  locale *locale, *minLocale;
  const char *localeId = "invalid locale id";

  locale = initEmptyLocale();
  locale->canonicalId = (char *)malloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  locale->canonicalId = strdup(localeId);

  minLocale = minimizeLocale(locale);

  cr_assert_not_null(minLocale);
  cr_assert(eq(int, hasError(minLocale->status), true));
  cr_assert(eq(int, minLocale->status->ecma, UNABLE_TO_MINIMIZE_LOCALE));

  freeLocale(locale);
  freeLocale(minLocale);
}

Test(TEST_SUITE, minimizesAndMaximizesWithVariant) {
  locale *locale, *maxLocale, *minLocale;
  char *localeId = "en-US-u-va-posix";

  locale = initLocale(localeId);
  maxLocale = maximizeLocale(locale);
  minLocale = minimizeLocale(locale);

  cr_assert_not_null(locale);
  cr_assert_not_null(maxLocale);
  cr_assert_not_null(minLocale);

  cr_assert(eq(str, locale->id, "en-US-u-va-posix"));
  cr_assert(eq(str, maxLocale->id, "en-Latn-US-u-va-posix"));
  cr_assert(eq(str, minLocale->id, "en-u-va-posix"));

  freeLocale(locale);
  freeLocale(maxLocale);
  freeLocale(minLocale);
}

Test(TEST_SUITE, minimizesAndMaximizesUndUs) {
  locale *locale, *maxLocale, *minLocale;
  char *localeId = "und-US";

  locale = initLocale(localeId);
  maxLocale = maximizeLocale(locale);
  minLocale = minimizeLocale(locale);

  cr_assert_not_null(locale);
  cr_assert_not_null(maxLocale);
  cr_assert_not_null(minLocale);

  cr_assert(eq(str, locale->id, "und-US"));
  cr_assert(eq(str, maxLocale->id, "en-Latn-US"));
  cr_assert(eq(str, minLocale->id, "en"));

  freeLocale(locale);
  freeLocale(maxLocale);
  freeLocale(minLocale);
}
