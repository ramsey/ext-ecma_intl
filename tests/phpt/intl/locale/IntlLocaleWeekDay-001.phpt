--TEST--
Intl\Locale\WeekDay has expected values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale\WeekDay;

$tests = [
    [
        'weekDay' => WeekDay::Monday,
        'expectedValue' => 1,
    ],
    [
        'weekDay' => WeekDay::Tuesday,
        'expectedValue' => 2,
    ],
    [
        'weekDay' => WeekDay::Wednesday,
        'expectedValue' => 3,
    ],
    [
        'weekDay' => WeekDay::Thursday,
        'expectedValue' => 4,
    ],
    [
        'weekDay' => WeekDay::Friday,
        'expectedValue' => 5,
    ],
    [
        'weekDay' => WeekDay::Saturday,
        'expectedValue' => 6,
    ],
    [
        'weekDay' => WeekDay::Sunday,
        'expectedValue' => 7,
    ],
];

foreach ($tests as $test) {
    assert(
        $test['weekDay']->value === $test['expectedValue'],
        sprintf('Actual "%s" is not the same as expected "%s"', $test['weekDay']->value, $test['expectedValue']),
    );
    echo json_encode($test['weekDay']) . "\n";
}
?>
--EXPECT--
1
2
3
4
5
6
7
