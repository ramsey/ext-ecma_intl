<?php

namespace Ecma\Test\Intl\Locale;

use Ecma\Intl\Locale\WeekDay;
use Ecma\Intl\Locale\WeekInfo;
use Ecma\Test\Intl\TestCase;
use ReflectionClass;
use ValueError;

class WeekInfoTest extends TestCase
{
    public function testInstantiatesWithArguments(): void
    {
        $weekInfo = new WeekInfo(
            WeekDay::Monday,
            3,
            [WeekDay::Thursday, WeekDay::Saturday],
        );

        $this->assertSame(WeekDay::Monday, $weekInfo->firstDay);
        $this->assertSame(3, $weekInfo->minimalDays);
        $this->assertSame([WeekDay::Thursday, WeekDay::Saturday], $weekInfo->weekend);
    }

    public function testIsMarkedFinal(): void
    {
        $reflect = new ReflectionClass(WeekInfo::class);

        $this->assertTrue($reflect->isFinal());
    }

    public function testThrowsValueErrorForInvalidWeekendValues(): void
    {
        $this->expectException(ValueError::class);
        $this->expectExceptionMessage('Argument $weekend must be an array of values of type ' . WeekDay::class);

        new WeekInfo(
            WeekDay::Monday,
            3,
            [WeekDay::Thursday, 'foo', WeekDay::Saturday],
        );
    }

    public function testAllowsAnEmptyArrayForWeekendValues(): void
    {
        $weekInfo = new WeekInfo(WeekDay::Wednesday, 4, []);

        $this->assertSame(WeekDay::Wednesday, $weekInfo->firstDay);
        $this->assertSame(4, $weekInfo->minimalDays);
        $this->assertSame([], $weekInfo->weekend);
    }
}
