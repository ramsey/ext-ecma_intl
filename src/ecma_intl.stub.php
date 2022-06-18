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
