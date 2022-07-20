<?php

namespace Ecma\Test\Intl;

use Ecma\Intl\NumberingSystem;
use Ecma\Test\TestCase;

class NumberingSystemTest extends TestCase
{
    /**
     * @dataProvider numberingSystemValuesProvider
     */
    public function testNumberingSystemValues(NumberingSystem $numberingSystem, string $expectedValue): void
    {
        $this->assertSame($expectedValue, $numberingSystem->value);
    }

    /**
     * @return array<array{numberingSystem: NumberingSystem, expectedValue: string}>
     */
    public function numberingSystemValuesProvider(): array
    {
        return [
            [
                'numberingSystem' => NumberingSystem::Adlm,
                'expectedValue' => 'adlm',
            ],
            [
                'numberingSystem' => NumberingSystem::Ahom,
                'expectedValue' => 'ahom',
            ],
            [
                'numberingSystem' => NumberingSystem::Arab,
                'expectedValue' => 'arab',
            ],
            [
                'numberingSystem' => NumberingSystem::Arabext,
                'expectedValue' => 'arabext',
            ],
            [
                'numberingSystem' => NumberingSystem::Armn,
                'expectedValue' => 'armn',
            ],
            [
                'numberingSystem' => NumberingSystem::Armnlow,
                'expectedValue' => 'armnlow',
            ],
            [
                'numberingSystem' => NumberingSystem::Bali,
                'expectedValue' => 'bali',
            ],
            [
                'numberingSystem' => NumberingSystem::Beng,
                'expectedValue' => 'beng',
            ],
            [
                'numberingSystem' => NumberingSystem::Bhks,
                'expectedValue' => 'bhks',
            ],
            [
                'numberingSystem' => NumberingSystem::Brah,
                'expectedValue' => 'brah',
            ],
            [
                'numberingSystem' => NumberingSystem::Cakm,
                'expectedValue' => 'cakm',
            ],
            [
                'numberingSystem' => NumberingSystem::Cham,
                'expectedValue' => 'cham',
            ],
            [
                'numberingSystem' => NumberingSystem::Cyrl,
                'expectedValue' => 'cyrl',
            ],
            [
                'numberingSystem' => NumberingSystem::Deva,
                'expectedValue' => 'deva',
            ],
            [
                'numberingSystem' => NumberingSystem::Diak,
                'expectedValue' => 'diak',
            ],
            [
                'numberingSystem' => NumberingSystem::Ethi,
                'expectedValue' => 'ethi',
            ],
            [
                'numberingSystem' => NumberingSystem::Finance,
                'expectedValue' => 'finance',
            ],
            [
                'numberingSystem' => NumberingSystem::Fullwide,
                'expectedValue' => 'fullwide',
            ],
            [
                'numberingSystem' => NumberingSystem::Geor,
                'expectedValue' => 'geor',
            ],
            [
                'numberingSystem' => NumberingSystem::Gong,
                'expectedValue' => 'gong',
            ],
            [
                'numberingSystem' => NumberingSystem::Gonm,
                'expectedValue' => 'gonm',
            ],
            [
                'numberingSystem' => NumberingSystem::Grek,
                'expectedValue' => 'grek',
            ],
            [
                'numberingSystem' => NumberingSystem::Greklow,
                'expectedValue' => 'greklow',
            ],
            [
                'numberingSystem' => NumberingSystem::Gujr,
                'expectedValue' => 'gujr',
            ],
            [
                'numberingSystem' => NumberingSystem::Guru,
                'expectedValue' => 'guru',
            ],
            [
                'numberingSystem' => NumberingSystem::Hanidays,
                'expectedValue' => 'hanidays',
            ],
            [
                'numberingSystem' => NumberingSystem::Hanidec,
                'expectedValue' => 'hanidec',
            ],
            [
                'numberingSystem' => NumberingSystem::Hans,
                'expectedValue' => 'hans',
            ],
            [
                'numberingSystem' => NumberingSystem::Hansfin,
                'expectedValue' => 'hansfin',
            ],
            [
                'numberingSystem' => NumberingSystem::Hant,
                'expectedValue' => 'hant',
            ],
            [
                'numberingSystem' => NumberingSystem::Hantfin,
                'expectedValue' => 'hantfin',
            ],
            [
                'numberingSystem' => NumberingSystem::Hebr,
                'expectedValue' => 'hebr',
            ],
            [
                'numberingSystem' => NumberingSystem::Hmng,
                'expectedValue' => 'hmng',
            ],
            [
                'numberingSystem' => NumberingSystem::Hmnp,
                'expectedValue' => 'hmnp',
            ],
            [
                'numberingSystem' => NumberingSystem::Java,
                'expectedValue' => 'java',
            ],
            [
                'numberingSystem' => NumberingSystem::Jpan,
                'expectedValue' => 'jpan',
            ],
            [
                'numberingSystem' => NumberingSystem::Jpanfin,
                'expectedValue' => 'jpanfin',
            ],
            [
                'numberingSystem' => NumberingSystem::Jpanyear,
                'expectedValue' => 'jpanyear',
            ],
            [
                'numberingSystem' => NumberingSystem::Kali,
                'expectedValue' => 'kali',
            ],
            [
                'numberingSystem' => NumberingSystem::Kawi,
                'expectedValue' => 'kawi',
            ],
            [
                'numberingSystem' => NumberingSystem::Khmr,
                'expectedValue' => 'khmr',
            ],
            [
                'numberingSystem' => NumberingSystem::Knda,
                'expectedValue' => 'knda',
            ],
            [
                'numberingSystem' => NumberingSystem::Lana,
                'expectedValue' => 'lana',
            ],
            [
                'numberingSystem' => NumberingSystem::Lanatham,
                'expectedValue' => 'lanatham',
            ],
            [
                'numberingSystem' => NumberingSystem::Laoo,
                'expectedValue' => 'laoo',
            ],
            [
                'numberingSystem' => NumberingSystem::Latn,
                'expectedValue' => 'latn',
            ],
            [
                'numberingSystem' => NumberingSystem::Lepc,
                'expectedValue' => 'lepc',
            ],
            [
                'numberingSystem' => NumberingSystem::Limb,
                'expectedValue' => 'limb',
            ],
            [
                'numberingSystem' => NumberingSystem::Mathbold,
                'expectedValue' => 'mathbold',
            ],
            [
                'numberingSystem' => NumberingSystem::Mathdbl,
                'expectedValue' => 'mathdbl',
            ],
            [
                'numberingSystem' => NumberingSystem::Mathmono,
                'expectedValue' => 'mathmono',
            ],
            [
                'numberingSystem' => NumberingSystem::Mathsanb,
                'expectedValue' => 'mathsanb',
            ],
            [
                'numberingSystem' => NumberingSystem::Mathsans,
                'expectedValue' => 'mathsans',
            ],
            [
                'numberingSystem' => NumberingSystem::Mlym,
                'expectedValue' => 'mlym',
            ],
            [
                'numberingSystem' => NumberingSystem::Modi,
                'expectedValue' => 'modi',
            ],
            [
                'numberingSystem' => NumberingSystem::Mong,
                'expectedValue' => 'mong',
            ],
            [
                'numberingSystem' => NumberingSystem::Mroo,
                'expectedValue' => 'mroo',
            ],
            [
                'numberingSystem' => NumberingSystem::Mtei,
                'expectedValue' => 'mtei',
            ],
            [
                'numberingSystem' => NumberingSystem::Mymr,
                'expectedValue' => 'mymr',
            ],
            [
                'numberingSystem' => NumberingSystem::Mymrshan,
                'expectedValue' => 'mymrshan',
            ],
            [
                'numberingSystem' => NumberingSystem::Mymrtlng,
                'expectedValue' => 'mymrtlng',
            ],
            [
                'numberingSystem' => NumberingSystem::Nagm,
                'expectedValue' => 'nagm',
            ],
            [
                'numberingSystem' => NumberingSystem::Native,
                'expectedValue' => 'native',
            ],
            [
                'numberingSystem' => NumberingSystem::Newa,
                'expectedValue' => 'newa',
            ],
            [
                'numberingSystem' => NumberingSystem::Nkoo,
                'expectedValue' => 'nkoo',
            ],
            [
                'numberingSystem' => NumberingSystem::Olck,
                'expectedValue' => 'olck',
            ],
            [
                'numberingSystem' => NumberingSystem::Orya,
                'expectedValue' => 'orya',
            ],
            [
                'numberingSystem' => NumberingSystem::Osma,
                'expectedValue' => 'osma',
            ],
            [
                'numberingSystem' => NumberingSystem::Rohg,
                'expectedValue' => 'rohg',
            ],
            [
                'numberingSystem' => NumberingSystem::Roman,
                'expectedValue' => 'roman',
            ],
            [
                'numberingSystem' => NumberingSystem::Romanlow,
                'expectedValue' => 'romanlow',
            ],
            [
                'numberingSystem' => NumberingSystem::Saur,
                'expectedValue' => 'saur',
            ],
            [
                'numberingSystem' => NumberingSystem::Segment,
                'expectedValue' => 'segment',
            ],
            [
                'numberingSystem' => NumberingSystem::Shrd,
                'expectedValue' => 'shrd',
            ],
            [
                'numberingSystem' => NumberingSystem::Sind,
                'expectedValue' => 'sind',
            ],
            [
                'numberingSystem' => NumberingSystem::Sinh,
                'expectedValue' => 'sinh',
            ],
            [
                'numberingSystem' => NumberingSystem::Sora,
                'expectedValue' => 'sora',
            ],
            [
                'numberingSystem' => NumberingSystem::Sund,
                'expectedValue' => 'sund',
            ],
            [
                'numberingSystem' => NumberingSystem::Takr,
                'expectedValue' => 'takr',
            ],
            [
                'numberingSystem' => NumberingSystem::Talu,
                'expectedValue' => 'talu',
            ],
            [
                'numberingSystem' => NumberingSystem::Taml,
                'expectedValue' => 'taml',
            ],
            [
                'numberingSystem' => NumberingSystem::Tamldec,
                'expectedValue' => 'tamldec',
            ],
            [
                'numberingSystem' => NumberingSystem::Telu,
                'expectedValue' => 'telu',
            ],
            [
                'numberingSystem' => NumberingSystem::Thai,
                'expectedValue' => 'thai',
            ],
            [
                'numberingSystem' => NumberingSystem::Tibt,
                'expectedValue' => 'tibt',
            ],
            [
                'numberingSystem' => NumberingSystem::Tirh,
                'expectedValue' => 'tirh',
            ],
            [
                'numberingSystem' => NumberingSystem::Tnsa,
                'expectedValue' => 'tnsa',
            ],
            [
                'numberingSystem' => NumberingSystem::Traditio,
                'expectedValue' => 'traditio',
            ],
            [
                'numberingSystem' => NumberingSystem::Vaii,
                'expectedValue' => 'vaii',
            ],
            [
                'numberingSystem' => NumberingSystem::Wara,
                'expectedValue' => 'wara',
            ],
            [
                'numberingSystem' => NumberingSystem::Wcho,
                'expectedValue' => 'wcho',
            ],
        ];
    }
}
