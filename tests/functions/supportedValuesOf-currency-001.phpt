--TEST--
Ecma\Intl\supportedValuesOf('currency')
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$currencies = \Ecma\Intl\supportedValuesOf('currency');

if (count($currencies) > 0) {
    printf("Has support for %d currencies.\n", count($currencies));
} else {
    echo "Does not support any currencies.\n";
}

$tests = [
    'AUD',
    'CAD',
    'EUR',
    'USD',
];

foreach ($tests as $test) {
    if (in_array($test, $currencies)) {
        printf("Found %s in currency data.\n", $test);
    } else {
        printf("Could not find %s in currency data.\n", $test);
    }
}
?>
--EXPECTF--
Has support for %d currencies.
Found AUD in currency data.
Found CAD in currency data.
Found EUR in currency data.
Found USD in currency data.
