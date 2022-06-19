<?php

namespace Ecma\Test\Intl;

use Ecma\Intl\LocaleMatcher;

class LocaleMatcherTest extends TestCase
{
    /**
     * @dataProvider localeMatcherValuesProvider
     */
    public function testLocaleMatcherValues(LocaleMatcher $localeMatcher, string $expectedValue): void
    {
        $this->assertSame($expectedValue, $localeMatcher->value);
    }

    /**
     * @return array<array{localeMatcher: LocaleMatcher, expectedValue: string}>
     */
    public function localeMatcherValuesProvider(): array
    {
        return [
            [
                'localeMatcher' => LocaleMatcher::BestFit,
                'expectedValue' => 'best fit',
            ],
            [
                'localeMatcher' => LocaleMatcher::Lookup,
                'expectedValue' => 'lookup',
            ],
        ];
    }
}
