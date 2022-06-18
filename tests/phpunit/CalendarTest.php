<?php

namespace Ecma\Test\Intl;

use Ecma\Intl\Calendar;

use function json_encode;

class CalendarTest extends TestCase
{
    /**
     * @dataProvider calendarValuesProvider
     */
    public function testCalendarValues(Calendar $calendar, string $expectedValue): void
    {
        $this->assertSame($expectedValue, $calendar->value);
    }

    /**
     * @return array<array{calendar: Calendar, expectedValue: string}>
     */
    public function calendarValuesProvider(): array
    {
        return [
            [
                'calendar' => Calendar::Buddhist,
                'expectedValue' => 'buddhist',
            ],
            [
                'calendar' => Calendar::Chinese,
                'expectedValue' => 'chinese',
            ],
            [
                'calendar' => Calendar::Coptic,
                'expectedValue' => 'coptic',
            ],
            [
                'calendar' => Calendar::Dangi,
                'expectedValue' => 'dangi',
            ],
            [
                'calendar' => Calendar::Ethioaa,
                'expectedValue' => 'ethioaa',
            ],
            [
                'calendar' => Calendar::Ethiopic,
                'expectedValue' => 'ethiopic',
            ],
            [
                'calendar' => Calendar::Gregory,
                'expectedValue' => 'gregory',
            ],
            [
                'calendar' => Calendar::Hebrew,
                'expectedValue' => 'hebrew',
            ],
            [
                'calendar' => Calendar::Indian,
                'expectedValue' => 'indian',
            ],
            [
                'calendar' => Calendar::Islamic,
                'expectedValue' => 'islamic',
            ],
            [
                'calendar' => Calendar::IslamicCivil,
                'expectedValue' => 'islamic-civil',
            ],
            [
                'calendar' => Calendar::IslamicRgsa,
                'expectedValue' => 'islamic-rgsa',
            ],
            [
                'calendar' => Calendar::IslamicTbla,
                'expectedValue' => 'islamic-tbla',
            ],
            [
                'calendar' => Calendar::IslamicUmalqura,
                'expectedValue' => 'islamic-umalqura',
            ],
            [
                'calendar' => Calendar::Iso8601,
                'expectedValue' => 'iso8601',
            ],
            [
                'calendar' => Calendar::Japanese,
                'expectedValue' => 'japanese',
            ],
            [
                'calendar' => Calendar::Persian,
                'expectedValue' => 'persian',
            ],
            [
                'calendar' => Calendar::Roc,
                'expectedValue' => 'roc',
            ],
        ];
    }
}
