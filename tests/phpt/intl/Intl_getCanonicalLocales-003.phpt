--TEST--
Intl::getCanonicalLocales() throws ValueError for invalid values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl;

$tests = [
    ['input' => ''],
    ['input' => 'en-latn-us-co-foo'],
    [
        'input' => ['en-US', 'de-DE', 'en-latn-us-co-foo'],
        'expectedInvalidTag' => 'en-latn-us-co-foo',
    ],
];

$expectedMessage = 'invalid language tag: %s';

foreach ($tests as $test) {
    $expectedInvalidTag = $test['expectedInvalidTag'] ?? '';
    if (is_string($test['input']) && !isset($test['expectedInvalidTag'])) {
        $expectedInvalidTag = $test['input'];
    }
    $thisExpectedMessage = sprintf($expectedMessage, $expectedInvalidTag);
    
    try {
        Intl::getCanonicalLocales($test['input']);
        echo "Nothing thrown\n";
    } catch (\Throwable $throwable) {
        assert(
            get_class($throwable) === Intl\RangeError::class,
            sprintf('%s is not %s', get_class($throwable), Intl\RangeError::class),
        );
        assert(
            $throwable->getMessage() === $thisExpectedMessage,
            sprintf('"%s" is not the expected message "%s"', $throwable->getMessage(), $thisExpectedMessage),
        );
        echo 'ValueError for ' . json_encode($test['input']) . "\n";
    }
}
?>
--EXPECT--
ValueError for ""
ValueError for "en-latn-us-co-foo"
ValueError for ["en-US","de-DE","en-latn-us-co-foo"]
