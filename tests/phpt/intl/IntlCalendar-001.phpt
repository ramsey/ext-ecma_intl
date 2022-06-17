--TEST--
Intl\Calendar has expected values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Calendar;

$tests = [
    [
        'calendar' => Calendar::Buddhist,
        'expectedValue' => 'buddhist',
    ],
    [
        'calendar' => Calendar::Chinese,
        'expectedValue' => 'chinese',
    ],
    [
        'calendar' => Calendar::Coptic,
        'expectedValue' => 'coptic',
    ],
    [
        'calendar' => Calendar::Dangi,
        'expectedValue' => 'dangi',
    ],
    [
        'calendar' => Calendar::Ethioaa,
        'expectedValue' => 'ethioaa',
    ],
    [
        'calendar' => Calendar::Ethiopic,
        'expectedValue' => 'ethiopic',
    ],
    [
        'calendar' => Calendar::Gregory,
        'expectedValue' => 'gregory',
    ],
    [
        'calendar' => Calendar::Hebrew,
        'expectedValue' => 'hebrew',
    ],
    [
        'calendar' => Calendar::Indian,
        'expectedValue' => 'indian',
    ],
    [
        'calendar' => Calendar::Islamic,
        'expectedValue' => 'islamic',
    ],
    [
        'calendar' => Calendar::IslamicCivil,
        'expectedValue' => 'islamic-civil',
    ],
    [
        'calendar' => Calendar::IslamicRgsa,
        'expectedValue' => 'islamic-rgsa',
    ],
    [
        'calendar' => Calendar::IslamicTbla,
        'expectedValue' => 'islamic-tbla',
    ],
    [
        'calendar' => Calendar::IslamicUmalqura,
        'expectedValue' => 'islamic-umalqura',
    ],
    [
        'calendar' => Calendar::Iso8601,
        'expectedValue' => 'iso8601',
    ],
    [
        'calendar' => Calendar::Japanese,
        'expectedValue' => 'japanese',
    ],
    [
        'calendar' => Calendar::Persian,
        'expectedValue' => 'persian',
    ],
    [
        'calendar' => Calendar::Roc,
        'expectedValue' => 'roc',
    ],
];

foreach ($tests as $test) {
    assert(
        $test['calendar']->value === $test['expectedValue'],
        sprintf('Actual "%s" is not the same as expected "%s"', $test['calendar']->value, $test['expectedValue']),
    );
    echo json_encode($test['calendar']) . "\n";
}
?>
--EXPECT--
"buddhist"
"chinese"
"coptic"
"dangi"
"ethioaa"
"ethiopic"
"gregory"
"hebrew"
"indian"
"islamic"
"islamic-civil"
"islamic-rgsa"
"islamic-tbla"
"islamic-umalqura"
"iso8601"
"japanese"
"persian"
"roc"
