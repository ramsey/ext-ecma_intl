<?php

namespace Ecma\Test\Intl\Locale;

use Ecma\Intl\Locale\TextDirection;
use Ecma\Test\Intl\TestCase;

class TextDirectionTest extends TestCase
{
    /**
     * @dataProvider textDirectionValuesProvider
     */
    public function testTextDirectionValues(TextDirection $textDirection, string $expectedValue): void
    {
        $this->assertSame($expectedValue, $textDirection->value);
    }

    /**
     * @return array<array{textDirection: TextDirection, expectedValue: string}>
     */
    public function textDirectionValuesProvider(): array
    {
        return [
            [
                'textDirection' => TextDirection::BottomToTop,
                'expectedValue' => 'btt',
            ],
            [
                'textDirection' => TextDirection::LeftToRight,
                'expectedValue' => 'ltr',
            ],
            [
                'textDirection' => TextDirection::RightToLeft,
                'expectedValue' => 'rtl',
            ],
            [
                'textDirection' => TextDirection::TopToBottom,
                'expectedValue' => 'ttb',
            ],
        ];
    }
}
