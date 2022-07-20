--TEST--
Intl\HourCycle has expected values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\HourCycle;

$tests = [
    [
        'hourCycle' => HourCycle::H11,
        'expectedValue' => 'h11',
    ],
    [
        'hourCycle' => HourCycle::H12,
        'expectedValue' => 'h12',
    ],
    [
        'hourCycle' => HourCycle::H23,
        'expectedValue' => 'h23',
    ],
    [
        'hourCycle' => HourCycle::H24,
        'expectedValue' => 'h24',
    ],
];

foreach ($tests as $test) {
    assert(
        $test['hourCycle']->value === $test['expectedValue'],
        sprintf('Actual "%s" is not the same as expected "%s"', $test['hourCycle']->value, $test['expectedValue']),
    );
    echo json_encode($test['hourCycle']) . "\n";
}
?>
--EXPECT--
"h11"
"h12"
"h23"
"h24"
