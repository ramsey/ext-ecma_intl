--TEST--
Ecma\Intl\supportedLocales() returns an array of BCP 47 locales
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$supportedLocales = \Ecma\Intl\getSupportedLocales();

var_dump(is_array($supportedLocales));
var_dump(count($supportedLocales) > 0);

// If everything in the supported locales array is a string and contains only
// the characters we expect, then this should be an empty array.
var_dump(
    array_filter(
        $supportedLocales,
        fn ($value) => !is_string($value) || !preg_match('/^[a-z0-9\-]+$/i', $value),
    ),
);
?>
--EXPECT--
bool(true)
bool(true)
array(0) {
}
