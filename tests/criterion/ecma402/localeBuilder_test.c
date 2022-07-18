#include "tests/criterion/test.h"

#include "src/ecma402/localeBuilder.h"

#define TEST_SUITE ecma402LocaleBuilder

Test(TEST_SUITE, initializesEmptyLocaleBuilderOptions) {
  localeBuilderOptions *options = initEmptyLocaleBuilderOptions();

  cr_assert_null(options->calendar);
  cr_assert_null(options->caseFirst);
  cr_assert_null(options->collation);
  cr_assert_null(options->hourCycle);
  cr_assert_null(options->language);
  cr_assert_null(options->numberingSystem);
  cr_assert(eq(int, options->numeric, NUMERIC_NULL));
  cr_assert_null(options->region);
  cr_assert_null(options->script);

  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, initializesLocaleBuilderOptionsWithAllNull) {
  localeBuilderOptions *options = initLocaleBuilderOptions(
      NULL, NULL, NULL, NULL, NULL, NULL, NUMERIC_NULL, NULL, NULL);

  cr_assert_null(options->calendar);
  cr_assert_null(options->caseFirst);
  cr_assert_null(options->collation);
  cr_assert_null(options->hourCycle);
  cr_assert_null(options->language);
  cr_assert_null(options->numberingSystem);
  cr_assert(eq(int, options->numeric, NUMERIC_NULL));
  cr_assert_null(options->region);
  cr_assert_null(options->script);

  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, initializesLocaleBuilderOptionsWithAllValues) {
  char *calendar = "buddhist";
  char *caseFirst = "upper";
  char *collation = "emoji";
  char *hourCycle = "h23";
  char *language = "en";
  char *numberingSystem = "thai";
  numericValue numeric = NUMERIC_TRUE;
  char *region = "CA";
  char *script = "Latn";

  localeBuilderOptions *options = initLocaleBuilderOptions(
      calendar, caseFirst, collation, hourCycle, language, numberingSystem,
      numeric, region, script);

  cr_assert(eq(str, options->calendar, "buddhist"));
  cr_assert(eq(str, options->caseFirst, "upper"));
  cr_assert(eq(str, options->collation, "emoji"));
  cr_assert(eq(str, options->hourCycle, "h23"));
  cr_assert(eq(str, options->language, "en"));
  cr_assert(eq(str, options->numberingSystem, "thai"));
  cr_assert(eq(int, options->numeric, NUMERIC_TRUE));
  cr_assert(eq(str, options->region, "CA"));
  cr_assert(eq(str, options->script, "Latn"));

  /* The pointers should be copied and NOT pointing to the same thing. */
  cr_assert(ne(ptr, options->calendar, calendar));
  cr_assert(ne(ptr, options->caseFirst, caseFirst));
  cr_assert(ne(ptr, options->collation, collation));
  cr_assert(ne(ptr, options->hourCycle, hourCycle));
  cr_assert(ne(ptr, options->language, language));
  cr_assert(ne(ptr, options->numberingSystem, numberingSystem));
  cr_assert(ne(ptr, options->region, region));
  cr_assert(ne(ptr, options->script, script));

  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, buildsLocaleWithoutOptions) {
  locale *locale;

  locale = buildLocale("en-US", NULL);

  cr_assert_not_null(locale);
  cr_assert(eq(str, locale->id, "en-US"));

  freeLocale(locale);
}

Test(TEST_SUITE, returnsUndWhenLocaleIdIsNull) {
  locale *locale;

  locale = buildLocale(NULL, NULL);

  cr_assert_not_null(locale);
  cr_assert(eq(str, locale->id, "und"));

  freeLocale(locale);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorsWhenLocaleIdIsInvalid) {
  locale *locale;

  locale = buildLocale("foo_bar", NULL);

  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_LOCALE_ID));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
}

Test(TEST_SUITE, setsCalendarFromOptions) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions("buddhist", NULL, NULL, NULL, NULL, NULL,
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->calendar, "buddhist"));
  cr_assert(eq(str, locale->id, "en-US-u-ca-buddhist"));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, setsCaseFirstFromOptions) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, "upper", NULL, NULL, NULL, NULL,
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->caseFirst, "upper"));
  cr_assert(eq(str, locale->id, "en-US-u-kf-upper"));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, setsCollationFromOptions) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, "emoji", NULL, NULL, NULL,
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->collation, "emoji"));
  cr_assert(eq(str, locale->id, "en-US-u-co-emoji"));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, setsHourCycleFromOptions) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, "h23", NULL, NULL,
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->hourCycle, "h23"));
  cr_assert(eq(str, locale->id, "en-US-u-hc-h23"));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, setsLanguageFromOptions) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, "es", NULL,
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->language, "es"));
  cr_assert(eq(str, locale->id, "es-US"));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, setsNumberingSystemFromOptions) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, "tibt",
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->numberingSystem, "tibt"));
  cr_assert(eq(str, locale->id, "en-US-u-nu-tibt"));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, setsNumericTrueFromOptions) {
  locale *locale;
  localeBuilderOptions *options;
  numericValue numeric = NUMERIC_TRUE;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                     numeric, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(int, options->numeric, NUMERIC_TRUE));
  cr_assert(eq(str, locale->id, "en-US-u-kn"));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, setsNumericFalseFromOptions) {
  locale *locale;
  localeBuilderOptions *options;
  numericValue numeric = NUMERIC_FALSE;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                     numeric, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(int, options->numeric, NUMERIC_FALSE));
  cr_assert(eq(str, locale->id, "en-US-u-kn-false"));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, setsRegionFromOptions) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                     NUMERIC_NULL, "CA", NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->region, "CA"));
  cr_assert(eq(str, locale->id, "en-CA"));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, setsScriptFromOptions) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                     NUMERIC_NULL, NULL, "latn");

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->script, "latn"));
  cr_assert(eq(str, locale->id, "en-Latn-US"));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, buildsLocaleFromAllOptions) {
  locale *locale;
  localeBuilderOptions *options;
  numericValue numeric = NUMERIC_FALSE;

  options = initLocaleBuilderOptions("gregory", "lower", "phonebk", "h11", "de",
                                     "arab", numeric, "ch", "cyrl");

  locale = buildLocale(NULL, options);

  cr_assert_not_null(locale);
  cr_assert(eq(
      str, locale->id,
      "de-Cyrl-CH-u-ca-gregory-co-phonebk-hc-h11-kf-lower-kn-false-nu-arab"));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForInvalidCalendar) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions("invalid calendar", NULL, NULL, NULL, NULL,
                                     NULL, NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_CALENDAR));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForEmptyCalendar) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions("", NULL, NULL, NULL, NULL, NULL,
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_CALENDAR));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForInvalidCaseFirst) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, "invalid case first", NULL, NULL,
                                     NULL, NULL, NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_CASE_FIRST));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForEmptyCaseFirst) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, "", NULL, NULL, NULL, NULL,
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_CASE_FIRST));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForInvalidCollation) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, "invalid collation", NULL,
                                     NULL, NULL, NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_COLLATION));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForEmptyCollation) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, "", NULL, NULL, NULL,
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_COLLATION));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForInvalidHourCycle) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, "invalid hour cycle",
                                     NULL, NULL, NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_HOUR_CYCLE));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForEmptyHourCycle) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, "", NULL, NULL,
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_HOUR_CYCLE));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForInvalidLanguage) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, "invalid language",
                                     NULL, NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_LANGUAGE));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForEmptyLanguage) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, "", NULL,
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_LANGUAGE));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForInvalidNumberingSystem) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL,
                                     "invalid numbering system", NUMERIC_NULL,
                                     NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_NUMBERING_SYSTEM));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForEmptyNumberingSystem) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, "",
                                     NUMERIC_NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_NUMBERING_SYSTEM));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForInvalidRegion) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                     NUMERIC_NULL, "invalid region", NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_REGION));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForEmptyRegion) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                     NUMERIC_NULL, "", NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_REGION));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForInvalidScript) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                     NUMERIC_NULL, NULL, "invalid script");

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_SCRIPT));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}

Test(TEST_SUITE, returnsEmptyLocaleWithErrorForEmptyScript) {
  locale *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                     NUMERIC_NULL, NULL, "");

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert_null(locale->id);
  cr_assert(eq(int, hasError(locale->status), true));
  cr_assert(eq(int, locale->status->ecma, INVALID_SCRIPT));
  cr_assert(eq(int, locale->status->icu, 0));

  freeLocale(locale);
  freeLocaleBuilderOptions(options);
}
