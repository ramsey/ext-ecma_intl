--TEST--
Intl::getCanonicalLocales() canonicalizes locales
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl;

$tests = [
    [
        'input' => 'en-US',
        'expected' => ['en-US'],
    ],
    [
        'input' => ['en-US', 'de-DE'],
        'expected' => ['en-US', 'de-DE'],
    ],
    [
        'input' => ['en-US', 'de-DE', 'es-MX', 'fr-FR'],
        'expected' => ['en-US', 'de-DE', 'es-MX', 'fr-FR'],
    ],
    [
        'input' => ['_US', 'und-US', '_Latn', 'und-latn', 'zh-hakka', 'zh-cmn-CH-u-co-pinyin'],
        'expected' => ['und-US', 'und-US', 'und-Latn', 'und-Latn', 'hak', 'cmn-CH-u-co-pinyin'],
    ],
    [
        'input' => [],
        'expected' => [],
    ],
    [
        'input' => ['en_us', 'de_de'],
        'expected' => ['en-US', 'de-DE'],
    ],
    [
        'input' => 'en-latn-us',
        'expected' => ['en-Latn-US'],
    ],
    [
        'input' => 'en-blah-foo-x-baz',
        'expected' => ['en-Blah'],
    ],
    [
        'input' => 'zh-cmn-Hans-CN-boont-u-kf-lower-co-trad-kn-false-ca-buddhist-nu-latn-hc-h24',
        'expected' => ['cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-false-nu-latn'],
    ],
    [
        'input' => 'cmn_Hans_CN_BOONT@calendar=buddhist;colcasefirst=lower;collation=traditional;colnumeric=no;hours=h24;numbers=latn',
        'expected' => ['cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-false-nu-latn'],
    ],
];

foreach ($tests as $test) {
    $result = Intl::getCanonicalLocales($test['input']);
    assert($result === $test['expected']);
    echo json_encode($result) . "\n";
}
?>
--EXPECT--
["en-US"]
["en-US","de-DE"]
["en-US","de-DE","es-MX","fr-FR"]
["und-US","und-US","und-Latn","und-Latn","hak","cmn-CH-u-co-pinyin"]
[]
["en-US","de-DE"]
["en-Latn-US"]
["en-Blah"]
["cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-false-nu-latn"]
["cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-false-nu-latn"]
