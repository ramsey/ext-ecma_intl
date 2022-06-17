--TEST--
Intl\Category has expected values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Category;

$tests = [
    [
        'category' => Category::Calendar,
        'expectedValue' => 'calendar',
    ],
    [
        'category' => Category::Collation,
        'expectedValue' => 'collation',
    ],
    [
        'category' => Category::Currency,
        'expectedValue' => 'currency',
    ],
    [
        'category' => Category::NumberingSystem,
        'expectedValue' => 'numberingSystem',
    ],
    [
        'category' => Category::TimeZone,
        'expectedValue' => 'timeZone',
    ],
    [
        'category' => Category::Unit,
        'expectedValue' => 'unit',
    ],
];

foreach ($tests as $test) {
    assert($test['category']->value === $test['expectedValue']);
    echo json_encode($test['category']) . "\n";
}
?>
--EXPECT--
"calendar"
"collation"
"currency"
"numberingSystem"
"timeZone"
"unit"
