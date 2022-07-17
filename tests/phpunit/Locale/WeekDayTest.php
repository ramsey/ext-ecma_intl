<?php

namespace Ecma\Test\Intl\Locale;

use Ecma\Intl\Locale\WeekDay;
use Ecma\Test\Intl\TestCase;

class WeekDayTest extends TestCase
{
    /**
     * @dataProvider weekDayValuesProvider
     */
    public function testWeekDayValues(WeekDay $weekDay, int $expectedValue): void
    {
        $this->assertSame($expectedValue, $weekDay->value);
    }

    /**
     * @return array<array{weekDay: WeekDay, expectedValue: int}>
     */
    public function weekDayValuesProvider(): array
    {
        return [
            [
                'weekDay' => WeekDay::Monday,
                'expectedValue' => 1,
            ],
            [
                'weekDay' => WeekDay::Tuesday,
                'expectedValue' => 2,
            ],
            [
                'weekDay' => WeekDay::Wednesday,
                'expectedValue' => 3,
            ],
            [
                'weekDay' => WeekDay::Thursday,
                'expectedValue' => 4,
            ],
            [
                'weekDay' => WeekDay::Friday,
                'expectedValue' => 5,
            ],
            [
                'weekDay' => WeekDay::Saturday,
                'expectedValue' => 6,
            ],
            [
                'weekDay' => WeekDay::Sunday,
                'expectedValue' => 7,
            ],
        ];
    }
}
