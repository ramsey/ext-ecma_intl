--TEST--
Intl\Locale throws RangeError for invalid values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Calendar;
use Ecma\Intl\CaseFirst;
use Ecma\Intl\Collation;
use Ecma\Intl\HourCycle;
use Ecma\Intl\Locale;
use Ecma\Intl\NumberingSystem;
use Ecma\Intl\RangeError;

$tests = [
    ['tag' => ''],
    ['tag' => 'de-de_euro'],
    ['tag' => '123'],
    ['tag' => 'en-latn-x'],
    ['tag' => 'zh-cmn-CH'],
    ['tag' => 'i-test'],
    ['tag' => 'ja-jp-jp'],
    ['tag' => 'boguslang'],
    ['tag' => 'und-varzero-var1-vartwo'],
    ['tag' => 'de-1901-1901'],
    ['tag' => 'de-DE-1901-1901'],
    ['tag' => 'hant-cmn-cn'],
    ['tag' => 'zh-cmn-TW'],
    ['tag' => 'en-gb-oed'],
    ['tag' => 'invalid tag'],
    ['tag' => 'invalid tag', 'options' => new Locale\Options()],
    ['tag' => '', 'options' => new Locale\Options()],
    [
        'tag' => 'en',
        'options' => new Locale\Options(language: 'invalid language'),
        'message' => 'language is not a well-formed language value',
    ],
    [
        'tag' => 'und',
        'options' => new Locale\Options(language: ''),
        'message' => 'language is not a well-formed language value',
    ],
    [
        'tag' => 'en',
        'options' => new Locale\Options(region: 'Great Britain'),
        'message' => 'region is not a well-formed region value',
    ],
    [
        'tag' => 'und',
        'options' => new Locale\Options(region: ''),
        'message' => 'region is not a well-formed region value',
    ],
    [
        'tag' => 'en',
        'options' => new Locale\Options(script: 'invalid'),
        'message' => 'script is not a well-formed script value',
    ],
    [
        'tag' => 'und',
        'options' => new Locale\Options(script: ''),
        'message' => 'script is not a well-formed script value',
    ],
];

foreach ($tests as $test) {
    $message = $test['message'] ?? null;
    if ($message === null) {
        $message = 'invalid language tag: ' . $test['tag'];
    }

    $error = null;
    
    try {
        new Locale($test['tag'], $test['options'] ?? null);
    } catch (RangeError $error) {
        echo $error->getMessage() . "\n"; 
    }
 
    assert(
        $error instanceof RangeError,
        sprintf(
            'Expected RangeError; got %s',
            gettype($error),
        ),
    );
    assert(
        $error->getMessage() === $message,
        sprintf(
            'Message "%s" does not match expected "%s"',
            $error->getMessage(),
            $message,
        ),
    );
}
?>
--EXPECT--
invalid language tag: 
invalid language tag: de-de_euro
invalid language tag: 123
invalid language tag: en-latn-x
invalid language tag: zh-cmn-CH
invalid language tag: i-test
invalid language tag: ja-jp-jp
invalid language tag: boguslang
invalid language tag: und-varzero-var1-vartwo
invalid language tag: de-1901-1901
invalid language tag: de-DE-1901-1901
invalid language tag: hant-cmn-cn
invalid language tag: zh-cmn-TW
invalid language tag: en-gb-oed
invalid language tag: invalid tag
invalid language tag: invalid tag
invalid language tag: 
language is not a well-formed language value
language is not a well-formed language value
region is not a well-formed region value
region is not a well-formed region value
script is not a well-formed script value
script is not a well-formed script value
