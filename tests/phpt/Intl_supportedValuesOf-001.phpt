--TEST--
Intl::supportedValuesOf() returns supported values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl;

$tests = [
    [
        'category' => Intl\Category::Calendar,
        'shouldContain' => ['gregory', 'ethioaa'],
        'shouldNotContain' => ['gregorian', 'ethiopic-amete-alem'],
    ],
    [
        'category' => Intl\Category::Collation,
        'shouldContain' => ['dict', 'gb2312', 'phonebk', 'trad'],
        'shouldNotContain' => ['dictionary', 'gb2312han', 'phonebook', 'traditional'],
    ],
    [
        'category' => Intl\Category::Currency,
        'shouldContain' => ['AUD', 'CAD', 'EUR', 'USD'],
    ],
    [
        'category' => Intl\Category::NumberingSystem,
        'shouldContain' => ['arab', 'fullwide'],
        'shouldNotContain' => ['traditional'],
    ],
    [
        'category' => Intl\Category::TimeZone,
        'shouldContain' => ['America/New_York', 'Asia/Tokyo', 'Europe/Paris', 'GMT', 'UTC'],
    ],
    [
        'category' => Intl\Category::Unit,
        'shouldContain' => ['acre', 'hour', 'meter', 'percent'],
    ],
 ];

foreach ($tests as $test) {
    $values = Intl::supportedValuesOf($test['category']);

    assert(count($values) > 0, sprintf('There are no supported values for "%s"', $test['category']->value));

    foreach ($test['shouldContain'] as $value) {
        assert(
            in_array($value, $values),
            sprintf('Unable to find "%s" in supported values for "%s"', $value, $test['category']->value),
        );
    }

    foreach ($test['shouldNotContain'] ?? [] as $value) {
        assert(
            !in_array($value, $values),
            sprintf('Found unexpected "%s" in supported values for "%s"', $value, $test['category']->value),
        );
    }
    
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
