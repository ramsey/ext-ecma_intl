<?php

namespace Ecma\Test\Intl;

use Ecma\Intl\Collation;

class CollationTest extends TestCase
{
    /**
     * @dataProvider collationValuesProvider
     */
    public function testCollationValues(Collation $collation, string $expectedValue): void
    {
        $this->assertSame($expectedValue, $collation->value);
    }

    /**
     * @return array<array{collation: Collation, expectedValue: string}>
     */
    public function collationValuesProvider(): array
    {
        return [
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
    }
}
