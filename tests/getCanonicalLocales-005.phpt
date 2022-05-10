--TEST--
Ecma\Intl\getCanonicalLocales() throws exceptions for invalid language tags
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$tests = [
    ['en-latn-us-co-foo'],
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
RangeException: Invalid language tag: "en-latn-us-co-foo"
