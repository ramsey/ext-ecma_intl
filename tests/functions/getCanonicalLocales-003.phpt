--TEST--
Ecma\Intl\getCanonicalLocales() when array contains non-string values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$tests = [
    [null],
    [1234],
    [12.34],
    [true],
    [false],
    [0],
    [['en-US', 'nl-NL']],
    [new \stdClass()],
    ['en-US', 123, 'de-DE'],
];

foreach ($tests as $test) {
    try {
        \Ecma\Intl\getCanonicalLocales($test);
    } catch (\Throwable $t) {
        echo $t::class . ': ' . $t->getMessage() . "\n";
        continue;
    }

    echo "Did not catch exception for test with value: \n";
    var_dump($test);
}
?>
--EXPECT--
InvalidArgumentException: The $locales argument must be type string or an array of type string
InvalidArgumentException: The $locales argument must be type string or an array of type string
InvalidArgumentException: The $locales argument must be type string or an array of type string
InvalidArgumentException: The $locales argument must be type string or an array of type string
InvalidArgumentException: The $locales argument must be type string or an array of type string
InvalidArgumentException: The $locales argument must be type string or an array of type string
InvalidArgumentException: The $locales argument must be type string or an array of type string
InvalidArgumentException: The $locales argument must be type string or an array of type string
InvalidArgumentException: The $locales argument must be type string or an array of type string
