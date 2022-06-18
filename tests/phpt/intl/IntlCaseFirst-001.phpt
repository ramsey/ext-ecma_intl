--TEST--
Intl\CaseFirst has expected values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\CaseFirst;

$tests = [
    [
        'caseFirst' => CaseFirst::False,
        'expectedValue' => 'false',
    ],
    [
        'caseFirst' => CaseFirst::Lower,
        'expectedValue' => 'lower',
    ],
    [
        'caseFirst' => CaseFirst::Upper,
        'expectedValue' => 'upper',
    ],
];

foreach ($tests as $test) {
    assert(
        $test['caseFirst']->value === $test['expectedValue'],
        sprintf('Actual "%s" is not the same as expected "%s"', $test['caseFirst']->value, $test['expectedValue']),
    );
    echo json_encode($test['caseFirst']) . "\n";
}
?>
--EXPECT--
"false"
"lower"
"upper"
