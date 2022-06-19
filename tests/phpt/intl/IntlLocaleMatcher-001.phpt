--TEST--
Intl\LocaleMatcher has expected values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\LocaleMatcher;

$tests = [
    [
        'localeMatcher' => LocaleMatcher::BestFit,
        'expectedValue' => 'best fit',
    ],
    [
        'localeMatcher' => LocaleMatcher::Lookup,
        'expectedValue' => 'lookup',
    ],
];

foreach ($tests as $test) {
    assert(
        $test['localeMatcher']->value === $test['expectedValue'],
        sprintf('Actual "%s" is not the same as expected "%s"', $test['localeMatcher']->value, $test['expectedValue']),
    );
    echo json_encode($test['localeMatcher']) . "\n";
}
?>
--EXPECT--
"best fit"
"lookup"
