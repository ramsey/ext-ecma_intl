<?php

namespace Ecma\Test\Intl\Locale;

use Ecma\Intl\Locale\TextDirection;
use Ecma\Intl\Locale\TextInfo;
use Ecma\Test\Intl\TestCase;
use ReflectionClass;

class TextInfoTest extends TestCase
{
    public function testInstantiatesWithArguments(): void
    {
        $textInfo = new TextInfo(TextDirection::LeftToRight);

        $this->assertSame(TextDirection::LeftToRight, $textInfo->direction);
    }

    public function testIsMarkedFinal(): void
    {
        $reflect = new ReflectionClass(TextInfo::class);

        $this->assertTrue($reflect->isFinal());
    }
}
