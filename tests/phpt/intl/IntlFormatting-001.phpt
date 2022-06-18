--TEST--
Intl\Formatting has expected values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Formatting;

$tests = [
    [
        'formatting' => Formatting::Long,
        'expectedValue' => 'long',
    ],
    [
        'formatting' => Formatting::Narrow,
        'expectedValue' => 'narrow',
    ],
    [
        'formatting' => Formatting::Short,
        'expectedValue' => 'short',
    ],
];

foreach ($tests as $test) {
    assert(
        $test['formatting']->value === $test['expectedValue'],
        sprintf('Actual "%s" is not the same as expected "%s"', $test['formatting']->value, $test['expectedValue']),
    );
    echo json_encode($test['formatting']) . "\n";
}
?>
--EXPECT--
"long"
"narrow"
"short"
