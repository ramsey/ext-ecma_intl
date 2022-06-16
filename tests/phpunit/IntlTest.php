<?php

namespace Ecma\Test\Intl;

use Ecma\Intl;
use stdClass;
use ValueError;

class IntlTest extends TestCase
{
    /**
     * @param string[] | string $input
     * @param string[] $expected
     *
     * @dataProvider getCanonicalLocalesProvider
     */
    public function testGetCanonicalLocales(array | string $input, array $expected): void
    {
        $this->assertSame($expected, Intl::getCanonicalLocales($input));
    }

    /**
     * @return array<array{input: string[] | string, expected: string[]}>
     */
    public function getCanonicalLocalesProvider(): array
    {
        return [
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
    }

    /**
     * @dataProvider getCanonicalLocalesThrowsValueErrorForInvalidValuesProvider
     */
    public function testGetCanonicalLocalesThrowsValueErrorForInvalidValues(mixed $input): void
    {
        $this->expectException(ValueError::class);
        $this->expectExceptionMessage(
            'The $locales argument must be type string or an array of type string',
        );

        /** @psalm-suppress MixedArgument */
        Intl::getCanonicalLocales($input); // @phpstan-ignore-line
    }

    /**
     * @return array<array{input: mixed}>
     */
    public function getCanonicalLocalesThrowsValueErrorForInvalidValuesProvider(): array
    {
        return [
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
    }

    /**
     * @param string[] | string $input
     *
     * @dataProvider getCanonicalLocalesThrowsRangeErrorForInvalidLanguageTagsProvider
     */
    public function testGetCanonicalLocalesThrowsRangeErrorForInvalidLanguageTags(
        array | string $input,
        string $expectedInvalidTag = ''
    ): void {
        if (is_string($input) && !$expectedInvalidTag) {
            $expectedInvalidTag = $input;
        }

        $this->expectException(Intl\RangeError::class);
        $this->expectExceptionMessage('invalid language tag: ' . $expectedInvalidTag);

        Intl::getCanonicalLocales($input);
    }

    /**
     * @return array<array{input: string[] | string, expectedInvalidTag?: string}>
     */
    public function getCanonicalLocalesThrowsRangeErrorForInvalidLanguageTagsProvider(): array
    {
        return [
            ['input' => ''],
            ['input' => 'en-latn-us-co-foo'],
            [
                'input' => ['en-US', 'de-DE', 'en-latn-us-co-foo'],
                'expectedInvalidTag' => 'en-latn-us-co-foo',
            ],
        ];
    }
}
