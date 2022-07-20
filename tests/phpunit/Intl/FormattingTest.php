<?php

namespace Ecma\Test\Intl;

use Ecma\Intl\Formatting;
use Ecma\Test\TestCase;

class FormattingTest extends TestCase
{
    /**
     * @dataProvider formattingValuesProvider
     */
    public function testFormattingValues(Formatting $formatting, string $expectedValue): void
    {
        $this->assertSame($expectedValue, $formatting->value);
    }

    /**
     * @return array<array{formatting: Formatting, expectedValue: string}>
     */
    public function formattingValuesProvider(): array
    {
        return [
            [
                'formatting' => Formatting::Long,
                'expectedValue' => 'long',
            ],
            [
                'formatting' => Formatting::Narrow,
                'expectedValue' => 'narrow',
            ],
            [
                'formatting' => Formatting::Short,
                'expectedValue' => 'short',
            ],
        ];
    }
}
