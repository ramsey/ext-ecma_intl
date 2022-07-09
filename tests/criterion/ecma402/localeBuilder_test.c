#include "tests/criterion/test.h"

#include "src/ecma402/localeBuilder.h"

Test(ecma402LocaleBuilder, initializesLocaleBuilderOptionsWithAllNull) {
  localeBuilderOptions *options = initLocaleBuilderOptions(
      NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

  cr_assert_null(options->calendar);
  cr_assert_null(options->caseFirst);
  cr_assert_null(options->collation);
  cr_assert_null(options->hourCycle);
  cr_assert_null(options->language);
  cr_assert_null(options->numberingSystem);
  cr_assert_null(options->numeric);
  cr_assert_null(options->region);
  cr_assert_null(options->script);

  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, initializesLocaleBuilderOptionsWithAllValues) {
  char *calendar = "buddhist";
  char *caseFirst = "upper";
  char *collation = "emoji";
  char *hourCycle = "h23";
  char *language = "en";
  char *numberingSystem = "thai";
  bool *numeric;
  char *region = "CA";
  char *script = "Latn";

  bool numericValue = true;
  numeric = &numericValue;

  localeBuilderOptions *options = initLocaleBuilderOptions(
      calendar, caseFirst, collation, hourCycle, language, numberingSystem,
      numeric, region, script);

  cr_assert(eq(str, options->calendar, "buddhist"));
  cr_assert(eq(str, options->caseFirst, "upper"));
  cr_assert(eq(str, options->collation, "emoji"));
  cr_assert(eq(str, options->hourCycle, "h23"));
  cr_assert(eq(str, options->language, "en"));
  cr_assert(eq(str, options->numberingSystem, "thai"));
  cr_assert(eq(int, *options->numeric, 1));
  cr_assert(eq(str, options->region, "CA"));
  cr_assert(eq(str, options->script, "Latn"));

  /* The pointers should be copied and NOT pointing to the same thing. */
  cr_assert(ne(ptr, options->calendar, calendar));
  cr_assert(ne(ptr, options->caseFirst, caseFirst));
  cr_assert(ne(ptr, options->collation, collation));
  cr_assert(ne(ptr, options->hourCycle, hourCycle));
  cr_assert(ne(ptr, options->language, language));
  cr_assert(ne(ptr, options->numberingSystem, numberingSystem));
  cr_assert(ne(ptr, options->numeric, numeric));
  cr_assert(ne(ptr, options->region, region));
  cr_assert(ne(ptr, options->script, script));

  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, buildsLocaleWithoutOptions) {
  localeIdentifier *locale;

  locale = buildLocale("en-US", NULL);

  cr_assert_not_null(locale);
  cr_assert(eq(str, locale->id, "en-US"));
  cr_assert(eq(int, locale->length, 5));

  freeLocaleIdentifier(locale);
}

Test(ecma402LocaleBuilder, returnsUndWhenLocaleIdIsNull) {
  localeIdentifier *locale;

  locale = buildLocale(NULL, NULL);

  cr_assert_not_null(locale);
  cr_assert(eq(str, locale->id, "und"));
  cr_assert(eq(int, locale->length, 3));

  freeLocaleIdentifier(locale);
}

Test(ecma402LocaleBuilder, returnsNullWhenLocaleIdIsInvalid) {
  localeIdentifier *locale;

  locale = buildLocale("foo_bar", NULL);

  cr_assert_null(locale);
}

Test(ecma402LocaleBuilder, setsCalendarFromOptions) {
  localeIdentifier *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions("buddhist", NULL, NULL, NULL, NULL, NULL,
                                     NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->calendar, "buddhist"));
  cr_assert(eq(str, locale->id, "en-US-u-ca-buddhist"));
  cr_assert(eq(int, locale->length, 19));

  freeLocaleIdentifier(locale);
  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsCaseFirstFromOptions) {
  localeIdentifier *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, "upper", NULL, NULL, NULL, NULL,
                                     NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->caseFirst, "upper"));
  cr_assert(eq(str, locale->id, "en-US-u-kf-upper"));
  cr_assert(eq(int, locale->length, 16));

  freeLocaleIdentifier(locale);
  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsCollationFromOptions) {
  localeIdentifier *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, "emoji", NULL, NULL, NULL,
                                     NULL, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->collation, "emoji"));
  cr_assert(eq(str, locale->id, "en-US-u-co-emoji"));
  cr_assert(eq(int, locale->length, 16));

  freeLocaleIdentifier(locale);
  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsHourCycleFromOptions) {
  localeIdentifier *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, "h23", NULL, NULL, NULL,
                                     NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->hourCycle, "h23"));
  cr_assert(eq(str, locale->id, "en-US-u-hc-h23"));
  cr_assert(eq(int, locale->length, 14));

  freeLocaleIdentifier(locale);
  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsLanguageFromOptions) {
  localeIdentifier *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, "es", NULL, NULL,
                                     NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->language, "es"));
  cr_assert(eq(str, locale->id, "es-US"));
  cr_assert(eq(int, locale->length, 5));

  freeLocaleIdentifier(locale);
  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsNumberingSystemFromOptions) {
  localeIdentifier *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, "tibt", NULL,
                                     NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->numberingSystem, "tibt"));
  cr_assert(eq(str, locale->id, "en-US-u-nu-tibt"));
  cr_assert(eq(int, locale->length, 15));

  freeLocaleIdentifier(locale);
  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsNumericTrueFromOptions) {
  localeIdentifier *locale;
  localeBuilderOptions *options;
  bool numeric = true;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                     &numeric, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(int, *options->numeric, true));
  cr_assert(eq(str, locale->id, "en-US-u-kn"));
  cr_assert(eq(int, locale->length, 10));

  freeLocaleIdentifier(locale);
  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsNumericFalseFromOptions) {
  localeIdentifier *locale;
  localeBuilderOptions *options;
  bool numeric = false;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                     &numeric, NULL, NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(int, *options->numeric, false));
  cr_assert(eq(str, locale->id, "en-US-u-kn-false"));
  cr_assert(eq(int, locale->length, 16));

  freeLocaleIdentifier(locale);
  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsRegionFromOptions) {
  localeIdentifier *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                     "CA", NULL);

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->region, "CA"));
  cr_assert(eq(str, locale->id, "en-CA"));
  cr_assert(eq(int, locale->length, 5));

  freeLocaleIdentifier(locale);
  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsScriptFromOptions) {
  localeIdentifier *locale;
  localeBuilderOptions *options;

  options = initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                     NULL, "latn");

  locale = buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->script, "latn"));
  cr_assert(eq(str, locale->id, "en-Latn-US"));
  cr_assert(eq(int, locale->length, 10));

  freeLocaleIdentifier(locale);
  freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, buildsLocaleFromAllOptions) {
  localeIdentifier *locale;
  localeBuilderOptions *options;
  bool numeric = false;

  options = initLocaleBuilderOptions("gregory", "lower", "phonebk", "h11", "de",
                                     "arab", &numeric, "ch", "cyrl");

  locale = buildLocale(NULL, options);

  cr_assert_not_null(locale);
  cr_assert(eq(
      str, locale->id,
      "de-Cyrl-CH-u-ca-gregory-co-phonebk-hc-h11-kf-lower-kn-false-nu-arab"));
  cr_assert(eq(int, locale->length, 67));

  freeLocaleIdentifier(locale);
  freeLocaleBuilderOptions(options);
}
