--TEST--
Ecma\Intl\supportedValuesOf('collation')
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$collations = \Ecma\Intl\supportedValuesOf('collation');

if (count($collations) > 0) {
    printf("Has support for %d collations.\n", count($collations));
} else {
    echo "Does not support any collations.\n";
}

$tests = [
    'big5han',
    'compat',
    'emoji',
];

foreach ($tests as $test) {
    if (in_array($test, $collations)) {
        printf("Found %s in collation data.\n", $test);
    } else {
        printf("Could not find %s in collation data.\n", $test);
    }
}
?>
--EXPECTF--
Has support for %d collations.
Found big5han in collation data.
Found compat in collation data.
Found emoji in collation data.
