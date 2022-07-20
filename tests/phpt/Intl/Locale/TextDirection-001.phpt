--TEST--
Intl\Locale\TextDirection has expected values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale\TextDirection;

$tests = [
    [
        'textDirection' => TextDirection::BottomToTop,
        'expectedValue' => 'btt',
    ],
    [
        'textDirection' => TextDirection::LeftToRight,
        'expectedValue' => 'ltr',
    ],
    [
        'textDirection' => TextDirection::RightToLeft,
        'expectedValue' => 'rtl',
    ],
    [
        'textDirection' => TextDirection::TopToBottom,
        'expectedValue' => 'ttb',
    ],
];

foreach ($tests as $test) {
    assert(
        $test['textDirection']->value === $test['expectedValue'],
        sprintf('Actual "%s" is not the same as expected "%s"', $test['textDirection']->value, $test['expectedValue']),
    );
    echo json_encode($test['textDirection']) . "\n";
}
?>
--EXPECT--
"btt"
"ltr"
"rtl"
"ttb"
