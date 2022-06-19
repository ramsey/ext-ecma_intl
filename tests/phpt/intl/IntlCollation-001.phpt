--TEST--
Intl\Collation has expected values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Collation;

$tests = [
    [
        'collation' => Collation::Big5han,
        'expectedValue' => 'big5han',
    ],
    [
        'collation' => Collation::Compat,
        'expectedValue' => 'compat',
    ],
    [
        'collation' => Collation::Dict,
        'expectedValue' => 'dict',
    ],
    [
        'collation' => Collation::Direct,
        'expectedValue' => 'direct',
    ],
    [
        'collation' => Collation::Ducet,
        'expectedValue' => 'ducet',
    ],
    [
        'collation' => Collation::Emoji,
        'expectedValue' => 'emoji',
    ],
    [
        'collation' => Collation::Eor,
        'expectedValue' => 'eor',
    ],
    [
        'collation' => Collation::Gb2312,
        'expectedValue' => 'gb2312',
    ],
    [
        'collation' => Collation::Phonebk,
        'expectedValue' => 'phonebk',
    ],
    [
        'collation' => Collation::Phonetic,
        'expectedValue' => 'phonetic',
    ],
    [
        'collation' => Collation::Pinyin,
        'expectedValue' => 'pinyin',
    ],
    [
        'collation' => Collation::Reformed,
        'expectedValue' => 'reformed',
    ],
    [
        'collation' => Collation::Search,
        'expectedValue' => 'search',
    ],
    [
        'collation' => Collation::Searchjl,
        'expectedValue' => 'searchjl',
    ],
    [
        'collation' => Collation::Standard,
        'expectedValue' => 'standard',
    ],
    [
        'collation' => Collation::Stroke,
        'expectedValue' => 'stroke',
    ],
    [
        'collation' => Collation::Trad,
        'expectedValue' => 'trad',
    ],
    [
        'collation' => Collation::Unihan,
        'expectedValue' => 'unihan',
    ],
    [
        'collation' => Collation::Zhuyin,
        'expectedValue' => 'zhuyin',
    ],
];

foreach ($tests as $test) {
    assert(
        $test['collation']->value === $test['expectedValue'],
        sprintf('Actual "%s" is not the same as expected "%s"', $test['collation']->value, $test['expectedValue']),
    );
    echo json_encode($test['collation']) . "\n";
}
?>
--EXPECT--
"big5han"
"compat"
"dict"
"direct"
"ducet"
"emoji"
"eor"
"gb2312"
"phonebk"
"phonetic"
"pinyin"
"reformed"
"search"
"searchjl"
"standard"
"stroke"
"trad"
"unihan"
"zhuyin"
