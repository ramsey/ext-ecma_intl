--TEST--
Intl::getCanonicalLocales() throws ValueError for invalid values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl;

$tests = [
    ['input' => [null]],
    ['input' => [1234]],
    ['input' => [1234.56]],
    ['input' => [true]],
    ['input' => [false]],
    ['input' => [0]],
    ['input' => [['en-US']]],
    ['input' => [new stdClass()]],
    ['input' => ['en-US', 123, 'de-DE']],
];

$expectedMessage = 'The $locales argument must be type string or an array of type string';

foreach ($tests as $test) {
    try {
        Intl::getCanonicalLocales($test['input']);
        echo "Nothing thrown\n";
    } catch (\Throwable $throwable) {
        assert(
            get_class($throwable) === \ValueError::class,
            sprintf('%s is not %s', get_class($throwable), \ValueError::class),
        );
        assert(
            $throwable->getMessage() === $expectedMessage,
            sprintf('"%s" is not the expected message "%s"', $throwable->getMessage(), $expectedMessage),
        );
        echo 'ValueError for ' . json_encode($test['input']) . "\n";
    }
}
?>
--EXPECT--
ValueError for [null]
ValueError for [1234]
ValueError for [1234.56]
ValueError for [true]
ValueError for [false]
ValueError for [0]
ValueError for [["en-US"]]
ValueError for [{}]
ValueError for ["en-US",123,"de-DE"]
