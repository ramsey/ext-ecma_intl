<?php

namespace Ecma\Test\Intl;

use Ecma\Intl\HourCycle;

class HourCycleTest extends TestCase
{
    /**
     * @dataProvider hourCycleValuesProvider
     */
    public function testHourCycleValues(HourCycle $hourCycle, string $expectedValue): void
    {
        $this->assertSame($expectedValue, $hourCycle->value);
    }

    /**
     * @return array<array{hourCycle: HourCycle, expectedValue: string}>
     */
    public function hourCycleValuesProvider(): array
    {
        return [
            [
                'hourCycle' => HourCycle::H11,
                'expectedValue' => 'h11',
            ],
            [
                'hourCycle' => HourCycle::H12,
                'expectedValue' => 'h12',
            ],
            [
                'hourCycle' => HourCycle::H23,
                'expectedValue' => 'h23',
            ],
            [
                'hourCycle' => HourCycle::H24,
                'expectedValue' => 'h24',
            ],
        ];
    }
}
