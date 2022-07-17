<?php

/**
 * ecma_intl extension for PHP
 * Internationalization Support, Ecma-style (ECMA-402)
 *
 * Copyright (c) Ben Ramsey <ben@benramsey.com>
 *
 * Licensed under the MIT License (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *     https://opensource.org/licenses/MIT
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License IS PROVIDED "AS IS", WITHOUT WARRANTY
 * OF ANY KIND, EXPRESS OR IMPLIED. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 * @generate-class-entries
 */

namespace Ecma
{
    final class Intl
    {
        /**
         * Returns an array of canonical locale names for the input locale(s)
         *
         * @link https://tc39.es/ecma402/#sec-intl.getcanonicallocales ECMA-402: Intl.getCanoncialLocales
         * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/getCanonicalLocales MDN: Intl.getCanonicalLocales()
         *
         * @param string[]|string $locales
         *
         * @return string[]
         */
        public static function getCanonicalLocales(array|string $locales): array
        {
        }

        /**
         * Returns an array containing the values for the given category (i.e.,
         * calendar, collation, currency, numbering system, etc.) that are
         * supported by this implementation
         *
         * @link https://tc39.es/proposal-intl-enumeration/#sec-intl.supportedvaluesof Intl Enumeration API Specification
         * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/supportedValuesOf MDN: Intl.supportedValuesOf()
         *
         * @return string[]
         */
        public static function supportedValuesOf(Intl\Category $category): array
        {
        }

        /**
         * Intl may not be instantiated
         */
        private function __construct()
        {
        }
    }
}

namespace Ecma\Intl
{
    /**
     * Values for calendar (ca) options
     *
     * @link https://github.com/unicode-org/cldr/blob/main/common/bcp47/calendar.xml Unicode CLDR calendar values
     */
    enum Calendar: string
    {
        case Buddhist = 'buddhist';
        case Chinese = 'chinese';
        case Coptic = 'coptic';
        case Dangi = 'dangi';
        case Ethioaa = 'ethioaa';
        case Ethiopic = 'ethiopic';
        case Gregory = 'gregory';
        case Hebrew = 'hebrew';
        case Indian = 'indian';
        case Islamic = 'islamic';
        case IslamicCivil = 'islamic-civil';
        case IslamicRgsa = 'islamic-rgsa';
        case IslamicTbla = 'islamic-tbla';
        case IslamicUmalqura = 'islamic-umalqura';
        case Iso8601 = 'iso8601';
        case Japanese = 'japanese';
        case Persian = 'persian';
        case Roc = 'roc';
    }

    /**
     * Values categories supported by this implementation
     *
     * @see \Ecma\Intl::supportedValuesOf()
     */
    enum Category: string
    {
        case Calendar = 'calendar';
        case Collation = 'collation';
        case Currency = 'currency';
        case NumberingSystem = 'numberingSystem';
        case TimeZone = 'timeZone';
        case Unit = 'unit';
    }

    /**
     * Values for case first (kf) options
     *
     * When used with the caseFirst option (or the "kf" language tag parameter),
     * these values determine whether to sort by upper case or lower case first.
     * The default (i.e., "false") is to use the locale's default sorting.
     *
     * @link https://www.unicode.org/reports/tr35/tr35-collation.html#table-collation-settings Collation Settings
     */
    enum CaseFirst: string
    {
        case False = 'false';
        case Lower = 'lower';
        case Upper = 'upper';
    }

    /**
     * Values for collation (co) options
     *
     * @link https://github.com/unicode-org/cldr/blob/main/common/bcp47/collation.xml Unicode CLDR collation values
     */
    enum Collation: string
    {
        case Big5han = 'big5han';
        case Compat = 'compat';
        case Dict = 'dict';
        case Direct = 'direct';
        case Ducet = 'ducet';
        case Emoji = 'emoji';
        case Eor = 'eor';
        case Gb2312 = 'gb2312';
        case Phonebk = 'phonebk';
        case Phonetic = 'phonetic';
        case Pinyin = 'pinyin';
        case Reformed = 'reformed';
        case Search = 'search';
        case Searchjl = 'searchjl';
        case Standard = 'standard';
        case Stroke = 'stroke';
        case Trad = 'trad';
        case Unihan = 'unihan';
        case Zhuyin = 'zhuyin';
    }

    /**
     * Exception is the base interface for ecma_intl errors and exceptions
     */
    interface Exception
    {
    }

    /**
     * Common formatting options used throughout ECMA-402
     */
    enum Formatting: string
    {
        case Long = 'long';
        case Narrow = 'narrow';
        case Short = 'short';
    }

    /**
     * Values for hour cycle (hc) options
     *
     * @link https://www.unicode.org/reports/tr35/#UnicodeHourCycleIdentifier Unicode Hour Cycle Identifier
     */
    enum HourCycle: string
    {
        case H11 = 'h11';
        case H12 = 'h12';
        case H23 = 'h23';
        case H24 = 'h24';
    }

    /**
     * An IcuException occurs when the underlying ICU library raises an error
     * that ecma_intl cannot handle
     */
    class IcuException extends \RuntimeException implements Exception
    {
    }

    /**
     * A Locale represents a Unicode locale identifier
     *
     * @link https://tc39.es/ecma402/#locale-objects ECMA-402: Locale Objects
     * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Locale MDN: Intl.Locale
     * @link https://tc39.es/proposal-intl-locale-info/ Intl Locale Info Proposal
     */
    class Locale implements \Stringable
    {
        /**
         * The Unicode language identifier
         *
         * The base name is the language tag without extensions. Its structure
         * is defined in
         * {@link https://www.unicode.org/reports/tr35/#31-unicode-language-identifier UTS #35, Section 3.1}.
         */
        public readonly string $baseName;

        /**
         * The locale's calendar part, if available
         *
         * This is available when `ca` is present in the language tag or
         * `calendar` is set on the options object.
         */
        public readonly ?Calendar $calendar;

        /**
         * Calendar identifiers preferred for the locale
         *
         * If the calendar is provided as part of the language tag or the
         * options object, this defaults to that calendar value. Otherwise,
         * it consists of a list of calendar identifiers, sorted in descending
         * preference of those in common use for the locale.
         *
         * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.calendars Intl Locale Info Proposal
         *
         * @var Calendar[]
         */
        public readonly array $calendars;

        /**
         * Whether case is taken into account for the locale's collation rules,
         * if available
         *
         * This is available when `kf` is present in the language tag or
         * `caseFirst` is set on the options object.
         */
        public readonly ?CaseFirst $caseFirst;

        /**
         * The collation type for the locale, if available
         *
         * This is available when `co` is present in the language tag or
         * `collation` is set on the options object.
         */
        public readonly ?Collation $collation;

        /**
         * Collation types preferred for the locale
         *
         * If the collation is provided as part of the language tag or the
         * options object, this defaults to that collation value. Otherwise,
         * it consists of a list of collation identifiers, sorted in descending
         * preference of those in common use for the locale.
         *
         * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.collations Intl Locale Info Proposal
         *
         * @var Collation[]
         */
        public readonly array $collations;

        /**
         * The time keeping convention used by the locale, if available
         *
         * This is available when `hc` is present in the language tag or
         * `hourCycle` is set on the options object.
         */
        public readonly ?HourCycle $hourCycle;

        /**
         * Hour cycles preferred for the locale
         *
         * If the hour cycle is provided as part of the language tag or the
         * options object, this defaults to that hour cycle value. Otherwise,
         * it consists of a list of hour cycle identifiers, sorted in descending
         * preference of those in common use for the locale.
         *
         * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.hourCycles Intl Locale Info Proposal
         *
         * @var HourCycle[]
         */
        public readonly array $hourCycles;

        /**
         * The language associated with the locale, if available
         */
        public readonly ?string $language;

        /**
         * The numbering system used by the locale, if available
         *
         * This is available when `nu` is present in the language tag or
         * `numberingSystem` is set on the options object.
         */
        public readonly ?NumberingSystem $numberingSystem;

        /**
         * Numbering system identifiers preferred for the locale
         *
         * If the numbering system is provided as part of the language tag or
         * the options object, this defaults to that numbering system value.
         * Otherwise, it consists of a list of numbering system identifiers,
         * sorted in descending preference of those in common use for the
         * locale.
         *
         * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.numberingSystems Intl Locale Info Proposal
         *
         * @var NumberingSystem[]
         */
        public readonly array $numberingSystems;

        /**
         * Whether the locale has special collation handling for numeric
         * characters
         *
         * If true, the locale will take numeric characters into account when
         * collating and sorting strings. This means sequences of decimal digits
         * will be compared as numbers, so, for example, "A-21" will be less
         * than "A-123."
         */
        public readonly bool $numeric;

        /**
         * The region associated with the locale, if available
         */
        public readonly ?string $region;

        /**
         * The script associated with the locale, if available
         */
        public readonly ?string $script;

        /**
         * Information about the layout of text in the locale
         *
         * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.textInfo Intl Locale Info Proposal
         */
        public readonly Locale\TextInfo $textInfo;

        /**
         * An array of time zone identifiers associated with the locale
         *
         * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.timeZones Intl Locale Info Proposal
         *
         * @var string[]
         */
        public readonly ?array $timeZones;

        /**
         * Information about days of the week for the locale
         *
         * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.weekInfo Intl Locale Info Proposal
         * @link https://www.unicode.org/reports/tr35/tr35-dates.html#Date_Patterns_Week_Elements UTS 35: Week Elements
         */
        public readonly Locale\WeekInfo $weekInfo;

        /**
         * A Locale represents a Unicode locale identifier
         *
         * @link https://tc39.es/ecma402/#locale-objects ECMA-402: Locale Objects
         * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Locale MDN: Intl.Locale
         * @link https://tc39.es/proposal-intl-locale-info/ Intl Locale Info Proposal
         *
         * @param string $tag The language tag (or locale identifier)
         * @param Locale\Options|null $options Additional options to apply to
         *     the language tag
         */
        public function __construct(string $tag, ?Locale\Options $options = null)
        {
        }

        /**
         * Returns a string representation of the full locale identifier
         */
        public function __toString(): string
        {
        }

        /**
         * Returns a new Locale with the most likely subtag values for
         * language, script, and region, based on the existing values
         *
         * @link https://www.unicode.org/reports/tr35/#Likely_Subtags UTS #35: Likely Subtags
         */
        public function maximize(): Locale
        {
        }

        /**
         * Returns a new Locale removing the most likely subtag values
         *
         * @link https://www.unicode.org/reports/tr35/#Likely_Subtags UTS #35: Likely Subtags
         */
        public function minimize(): Locale
        {
        }

        /**
         * Returns a string representation of the full locale identifier
         *
         * @implementation-alias Ecma\Intl\Locale::__toString
         */
        public function toString(): string
        {
        }
    }

    /**
     * Locale matching algorithms for use in locale negotiation
     *
     * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl#locale_negotiation MDN: Locale negotiation
     */
    enum LocaleMatcher: string
    {
        case BestFit = 'best fit';
        case Lookup = 'lookup';
    }

    /**
     * Values for numbering system (nu) options
     *
     * @link https://github.com/unicode-org/cldr/blob/main/common/bcp47/number.xml Unicode CLDR numbering system values
     */
    enum NumberingSystem: string
    {
        case Adlm = 'adlm';
        case Ahom = 'ahom';
        case Arab = 'arab';
        case Arabext = 'arabext';
        case Armn = 'armn';
        case Armnlow = 'armnlow';
        case Bali = 'bali';
        case Beng = 'beng';
        case Bhks = 'bhks';
        case Brah = 'brah';
        case Cakm = 'cakm';
        case Cham = 'cham';
        case Cyrl = 'cyrl';
        case Deva = 'deva';
        case Diak = 'diak';
        case Ethi = 'ethi';
        case Finance = 'finance';
        case Fullwide = 'fullwide';
        case Geor = 'geor';
        case Gong = 'gong';
        case Gonm = 'gonm';
        case Grek = 'grek';
        case Greklow = 'greklow';
        case Gujr = 'gujr';
        case Guru = 'guru';
        case Hanidays = 'hanidays';
        case Hanidec = 'hanidec';
        case Hans = 'hans';
        case Hansfin = 'hansfin';
        case Hant = 'hant';
        case Hantfin = 'hantfin';
        case Hebr = 'hebr';
        case Hmng = 'hmng';
        case Hmnp = 'hmnp';
        case Java = 'java';
        case Jpan = 'jpan';
        case Jpanfin = 'jpanfin';
        case Jpanyear = 'jpanyear';
        case Kali = 'kali';
        case Kawi = 'kawi';
        case Khmr = 'khmr';
        case Knda = 'knda';
        case Lana = 'lana';
        case Lanatham = 'lanatham';
        case Laoo = 'laoo';
        case Latn = 'latn';
        case Lepc = 'lepc';
        case Limb = 'limb';
        case Mathbold = 'mathbold';
        case Mathdbl = 'mathdbl';
        case Mathmono = 'mathmono';
        case Mathsanb = 'mathsanb';
        case Mathsans = 'mathsans';
        case Mlym = 'mlym';
        case Modi = 'modi';
        case Mong = 'mong';
        case Mroo = 'mroo';
        case Mtei = 'mtei';
        case Mymr = 'mymr';
        case Mymrshan = 'mymrshan';
        case Mymrtlng = 'mymrtlng';
        case Nagm = 'nagm';
        case Native = 'native';
        case Newa = 'newa';
        case Nkoo = 'nkoo';
        case Olck = 'olck';
        case Orya = 'orya';
        case Osma = 'osma';
        case Rohg = 'rohg';
        case Roman = 'roman';
        case Romanlow = 'romanlow';
        case Saur = 'saur';
        case Segment = 'segment';
        case Shrd = 'shrd';
        case Sind = 'sind';
        case Sinh = 'sinh';
        case Sora = 'sora';
        case Sund = 'sund';
        case Takr = 'takr';
        case Talu = 'talu';
        case Taml = 'taml';
        case Tamldec = 'tamldec';
        case Telu = 'telu';
        case Thai = 'thai';
        case Tibt = 'tibt';
        case Tirh = 'tirh';
        case Tnsa = 'tnsa';
        case Traditio = 'traditio';
        case Vaii = 'vaii';
        case Wara = 'wara';
        case Wcho = 'wcho';
    }

    /**
     * RangeError indicates a value is not within the set or range of allowed
     * values
     *
     * This error is analogous to RangeError in JavaScript and extends
     * ValueError, which is the closest analogue in PHP.
     *
     * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/RangeError RangeError in JavaScript
     */
    class RangeError extends \ValueError implements Exception
    {
    }
}

namespace Ecma\Intl\Locale
{
    /**
     * Configuration for the locale
     *
     * Any property set on the Options object passed to the Locale's
     * constructor will override the same properties on the language tag passed
     * to the Locale.
     *
     * @link https://tc39.es/ecma402/#sec-intl-locale-constructor ECMA-402: The Intl.Locale Constructor
     * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Locale/Locale MDN: Intl.Locale() constructor
     */
    class Options
    {
        /**
         * The calendar to use with the locale
         */
        public ?\Ecma\Intl\Calendar $calendar = null;

        /**
         * The case sorting algorithm to use with the locale
         */
        public ?\Ecma\Intl\CaseFirst $caseFirst = null;

        /**
         * The collation algorithm to use with the locale
         */
        public ?\Ecma\Intl\Collation $collation = null;

        /**
         * The hour cycle to use with the locale
         */
        public ?\Ecma\Intl\HourCycle $hourCycle = null;

        /**
         * The locale's language (e.g., "en", "fr", "pt", "ja")
         */
        public ?string $language = null;

        /**
         * The locale's numbering system
         */
        public ?\Ecma\Intl\NumberingSystem $numberingSystem = null;

        /**
         * Whether to sort a sequence of decimal digits with its numeric value
         * (i.e, "A-21" < "A-123")
         */
        public ?bool $numeric = null;

        /**
         * The locale's region (e.g., "US", "CA", "BR", "JP")
         */
        public ?string $region = null;

        /**
         * The locale's script (e.g., "Latn", "Cyrl")
         */
        public ?string $script = null;

        /**
         * Configuration for the locale
         *
         * Any property set on the Options object passed to the Locale's
         * constructor will override the same properties on the language tag passed
         * to the Locale.
         *
         * @link https://tc39.es/ecma402/#sec-intl-locale-constructor ECMA-402: The Intl.Locale Constructor
         * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Locale/Locale MDN: Intl.Locale() constructor
         *
         * @param \Ecma\Intl\Calendar|null $calendar The calendar to use with
         *     the locale
         * @param \Ecma\Intl\CaseFirst|null $caseFirst The case sorting
         *     algorithm to use with the locale
         * @param \Ecma\Intl\Collation|null $collation The collation algorithm
         *     to use with the locale
         * @param \Ecma\Intl\HourCycle|null $hourCycle The hour cycle to use
         *     with the locale
         * @param string|null $language The locale's language (e.g., "en", "fr",
         *     "pt", "ja")
         * @param \Ecma\Intl\NumberingSystem|null $numberingSystem The locale's
         *     numbering system
         * @param bool|null $numeric Whether to sort a sequence of decimal
         *     digits with its numeric value (i.e, "A-21" < "A-123")
         * @param string|null $region The locale's region (e.g., "US", "CA",
         *     "BR", "JP")
         * @param string|null $script The locale's script (e.g., "Latn", "Cyrl")
         */
        public function __construct(
            ?\Ecma\Intl\Calendar $calendar = null,
            ?\Ecma\Intl\CaseFirst $caseFirst = null,
            ?\Ecma\Intl\Collation $collation = null,
            ?\Ecma\Intl\HourCycle $hourCycle = null,
            ?string $language = null,
            ?\Ecma\Intl\NumberingSystem $numberingSystem = null,
            ?bool $numeric = null,
            ?string $region = null,
            ?string $script = null,
        ) {
        }
    }

    /**
     * The character direction of a locale
     */
    enum TextDirection: string
    {
        case BottomToTop = 'btt';
        case LeftToRight = 'ltr';
        case RightToLeft = 'rtl';
        case TopToBottom = 'ttb';
    }

    /**
     * Locale information associated with data specified in UTS 35's Layout
     * Elements
     *
     * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.textInfo Intl Locale Info Proposal
     * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Locale/textInfo MDN: Intl.Locale.prototype.textInfo
     * @link https://www.unicode.org/reports/tr35/tr35-general.html#Layout_Elements UTS 35: Layout Elements
     */
    final class TextInfo
    {
        /**
         * The ordering of characters for the locale
         */
        public readonly TextDirection $direction;

        /**
         * Locale information associated with data specified in UTS 35's Layout
         * Elements
         *
         * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.textInfo Intl Locale Info Proposal
         * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Locale/textInfo MDN: Intl.Locale.prototype.textInfo
         * @link https://www.unicode.org/reports/tr35/tr35-general.html#Layout_Elements UTS 35: Layout Elements
         *
         * @param TextDirection $direction The ordering of characters for the locale
         */
        public function __construct(TextDirection $direction)
        {
        }
    }

    /**
     * Days of the week
     *
     * Each case is mapped to an integer value corresponding to the values
     * defined in {@link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.weekInfo WeekInfo Record Fields}.
     */
    enum WeekDay: int
    {
        case Monday = 1;
        case Tuesday = 2;
        case Wednesday = 3;
        case Thursday = 4;
        case Friday = 5;
        case Saturday = 6;
        case Sunday = 7;
    }

    /**
     * Locale information associated with data specified in UTS 35's Week
     * Elements
     *
     * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.weekInfo Intl Locale Info Proposal
     * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Locale/weekInfo MDN: Intl.Locale.prototype.weekInfo
     * @link https://www.unicode.org/reports/tr35/tr35-dates.html#Date_Patterns_Week_Elements UTS 35: Week Elements
     */
    final class WeekInfo
    {
        /**
         * The first day of the week in the locale
         */
        public readonly WeekDay $firstDay;

        /**
         * The number of days required for the first week of a month or year
         * in the locale
         */
        public readonly int $minimalDays;

        /**
         * The days of the week that are considered weekend days in the locale
         *
         * Note that the number of days in a weekend are different in each
         * locale and may not be contiguous.
         *
         * @var WeekDay[] $weekend
         */
        public readonly array $weekend;

        /**
         * Locale information associated with data specified in UTS 35's Week
         * Elements
         *
         * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.weekInfo Intl Locale Info Proposal
         * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Locale/weekInfo MDN: Intl.Locale.prototype.weekInfo
         * @link https://www.unicode.org/reports/tr35/tr35-dates.html#Date_Patterns_Week_Elements UTS 35: Week Elements
         *
         * @param WeekDay $firstDay The first day of the week in the locale
         * @param int $minimalDays The number of days required for the first
         *     week of a month or year in the locale
         * @param WeekDay[] $weekend The days of the week that are considered
         *     weekend days in the locale
         */
        public function __construct(WeekDay $firstDay, int $minimalDays, array $weekend)
        {
        }
    }
}
