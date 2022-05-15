--TEST--
Ecma\Intl\supportedValuesOf() with invalid keys
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$tests = [
    'foo',
    'bar',
];

foreach ($tests as $test) {
    try {
        \Ecma\Intl\supportedValuesOf($test);
    } catch (\Throwable $t) {
        echo $t::class . ': ' . $t->getMessage() . "\n";
        continue;
    }

    echo "Did not catch exception for test with value: \n";
    var_dump($test);
}
?>
--EXPECT--
RangeException: Unknown key for Ecma\Intl\supportedValuesOf()
RangeException: Unknown key for Ecma\Intl\supportedValuesOf()
