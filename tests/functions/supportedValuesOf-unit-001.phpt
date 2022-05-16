--TEST--
Ecma\Intl\supportedValuesOf('unit')
--XFAIL--
Getting a list of supported unit values is not yet implemented.
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$units = \Ecma\Intl\supportedValuesOf('unit');

if (count($units) > 0) {
    printf("Has support for %d units.\n", count($units));
} else {
    echo "Does not support any units.\n";
}

var_dump($units);

$tests = [
    'acre',
    'hour',
    'percent',
    'yard',
];

foreach ($tests as $test) {
    if (in_array($test, $units)) {
        printf("Found %s in unit data.\n", $test);
    } else {
        printf("Could not find %s in unit data.\n", $test);
    }
}
?>
--EXPECTF--
Has support for %d units.
Found acre in unit data.
Found hour in unit data.
Found percent in unit data.
Found yard in unit data.
