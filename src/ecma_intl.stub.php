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
        public static function getCanonicalLocales(array|string $locales): array {}

        /**
         * Intl may not be instantiated
         */
        private function __construct() {}
    }
}

namespace Ecma\Intl
{
    /**
     * Exception is the base interface for ecma_intl errors and exceptions
     */
    interface Exception
    {
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
