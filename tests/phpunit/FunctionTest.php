<?php

declare(strict_types=1);

namespace Ecma\Test\Intl;

class FunctionTest extends TestCase
{
    public function testTest1(): void
    {
        $this->expectOutputString("The extension ecma_intl is loaded and working!\r\n");

        test1();
    }

    public function testTest2WithoutInput(): void
    {
        $this->assertSame('Hello World', test2());
    }

    public function testTest2WithInput(): void
    {
        $this->assertSame('Hello PHP', test2('PHP'));
    }
}