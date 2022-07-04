#include "tests/criterion/test.h"

#include "src/ecma402/localeBuilder.h"

Test(ecma402LocaleBuilder, initializesLocaleBuilderOptionsWithAllNull) {
  ecma402_localeBuilderOptions *options = ecma402_initLocaleBuilderOptions(
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

  ecma402_freeLocaleBuilderOptions(options);
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

  ecma402_localeBuilderOptions *options = ecma402_initLocaleBuilderOptions(
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

  ecma402_freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, buildsLocaleWithoutOptions) {
  ecma402_locale *locale;

  locale = ecma402_buildLocale("en-US", NULL);

  cr_assert_not_null(locale);
  cr_assert(eq(str, locale->id, "en-US"));
  cr_assert(eq(int, locale->length, 5));

  ecma402_freeLocale(locale);
}

Test(ecma402LocaleBuilder, returnsUndWhenLocaleIdIsNull) {
  ecma402_locale *locale;

  locale = ecma402_buildLocale(NULL, NULL);

  cr_assert_not_null(locale);
  cr_assert(eq(str, locale->id, "und"));
  cr_assert(eq(int, locale->length, 3));

  ecma402_freeLocale(locale);
}

Test(ecma402LocaleBuilder, returnsNullWhenLocaleIdIsInvalid) {
  ecma402_locale *locale;

  locale = ecma402_buildLocale("foo_bar", NULL);

  cr_assert_null(locale);
}

Test(ecma402LocaleBuilder, setsCalendarFromOptions) {
  ecma402_locale *locale;
  ecma402_localeBuilderOptions *options;

  options = ecma402_initLocaleBuilderOptions("buddhist", NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL);

  locale = ecma402_buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->calendar, "buddhist"));
  cr_assert(eq(str, locale->id, "en-US-u-ca-buddhist"));
  cr_assert(eq(int, locale->length, 19));

  ecma402_freeLocale(locale);
  ecma402_freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsCaseFirstFromOptions) {
  ecma402_locale *locale;
  ecma402_localeBuilderOptions *options;

  options = ecma402_initLocaleBuilderOptions(NULL, "upper", NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL);

  locale = ecma402_buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->caseFirst, "upper"));
  cr_assert(eq(str, locale->id, "en-US-u-kf-upper"));
  cr_assert(eq(int, locale->length, 16));

  ecma402_freeLocale(locale);
  ecma402_freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsCollationFromOptions) {
  ecma402_locale *locale;
  ecma402_localeBuilderOptions *options;

  options = ecma402_initLocaleBuilderOptions(NULL, NULL, "emoji", NULL, NULL,
                                             NULL, NULL, NULL, NULL);

  locale = ecma402_buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->collation, "emoji"));
  cr_assert(eq(str, locale->id, "en-US-u-co-emoji"));
  cr_assert(eq(int, locale->length, 16));

  ecma402_freeLocale(locale);
  ecma402_freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsHourCycleFromOptions) {
  ecma402_locale *locale;
  ecma402_localeBuilderOptions *options;

  options = ecma402_initLocaleBuilderOptions(NULL, NULL, NULL, "h23", NULL,
                                             NULL, NULL, NULL, NULL);

  locale = ecma402_buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->hourCycle, "h23"));
  cr_assert(eq(str, locale->id, "en-US-u-hc-h23"));
  cr_assert(eq(int, locale->length, 14));

  ecma402_freeLocale(locale);
  ecma402_freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsLanguageFromOptions) {
  ecma402_locale *locale;
  ecma402_localeBuilderOptions *options;

  options = ecma402_initLocaleBuilderOptions(NULL, NULL, NULL, NULL, "es", NULL,
                                             NULL, NULL, NULL);

  locale = ecma402_buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->language, "es"));
  cr_assert(eq(str, locale->id, "es-US"));
  cr_assert(eq(int, locale->length, 5));

  ecma402_freeLocale(locale);
  ecma402_freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsNumberingSystemFromOptions) {
  ecma402_locale *locale;
  ecma402_localeBuilderOptions *options;

  options = ecma402_initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL,
                                             "tibt", NULL, NULL, NULL);

  locale = ecma402_buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->numberingSystem, "tibt"));
  cr_assert(eq(str, locale->id, "en-US-u-nu-tibt"));
  cr_assert(eq(int, locale->length, 15));

  ecma402_freeLocale(locale);
  ecma402_freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsNumericTrueFromOptions) {
  ecma402_locale *locale;
  ecma402_localeBuilderOptions *options;
  bool numeric = true;

  options = ecma402_initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                             &numeric, NULL, NULL);

  locale = ecma402_buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(int, *options->numeric, true));
  cr_assert(eq(str, locale->id, "en-US-u-kn"));
  cr_assert(eq(int, locale->length, 10));

  ecma402_freeLocale(locale);
  ecma402_freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsNumericFalseFromOptions) {
  ecma402_locale *locale;
  ecma402_localeBuilderOptions *options;
  bool numeric = false;

  options = ecma402_initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                             &numeric, NULL, NULL);

  locale = ecma402_buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(int, *options->numeric, false));
  cr_assert(eq(str, locale->id, "en-US-u-kn-false"));
  cr_assert(eq(int, locale->length, 16));

  ecma402_freeLocale(locale);
  ecma402_freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsRegionFromOptions) {
  ecma402_locale *locale;
  ecma402_localeBuilderOptions *options;

  options = ecma402_initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, "CA", NULL);

  locale = ecma402_buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->region, "CA"));
  cr_assert(eq(str, locale->id, "en-CA"));
  cr_assert(eq(int, locale->length, 5));

  ecma402_freeLocale(locale);
  ecma402_freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, setsScriptFromOptions) {
  ecma402_locale *locale;
  ecma402_localeBuilderOptions *options;

  options = ecma402_initLocaleBuilderOptions(NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, "latn");

  locale = ecma402_buildLocale("en-US", options);

  cr_assert_not_null(locale);
  cr_assert(eq(str, options->script, "latn"));
  cr_assert(eq(str, locale->id, "en-Latn-US"));
  cr_assert(eq(int, locale->length, 10));

  ecma402_freeLocale(locale);
  ecma402_freeLocaleBuilderOptions(options);
}

Test(ecma402LocaleBuilder, buildsLocaleFromAllOptions) {
  ecma402_locale *locale;
  ecma402_localeBuilderOptions *options;
  bool numeric = false;

  options =
      ecma402_initLocaleBuilderOptions("gregory", "lower", "phonebk", "h11",
                                       "de", "arab", &numeric, "ch", "cyrl");

  locale = ecma402_buildLocale(NULL, options);

  cr_assert_not_null(locale);
  cr_assert(eq(
      str, locale->id,
      "de-Cyrl-CH-u-ca-gregory-co-phonebk-hc-h11-kf-lower-kn-false-nu-arab"));
  cr_assert(eq(int, locale->length, 67));

  ecma402_freeLocale(locale);
  ecma402_freeLocaleBuilderOptions(options);
}
