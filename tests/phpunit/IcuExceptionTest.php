<?php

namespace Ecma\Test\Intl;

use Ecma\Intl\Exception;
use Ecma\Intl\IcuException;
use LogicException;
use RuntimeException;

class IcuExceptionTest extends TestCase
{
    public function testIcuExceptionIsAChildOfRuntimeException(): void
    {
        $exception = new IcuException();

        $this->assertInstanceOf(RuntimeException::class, $exception);
    }

    public function testIcuExceptionIsAnEcmaIntlException(): void
    {
        $exception = new IcuException();

        $this->assertInstanceOf(Exception::class, $exception);
    }

    public function testIcuExceptionThrownAndCaught(): void
    {
        $previous = new LogicException('A logic exception');
        $exception = new IcuException('An ICU exception message', 42, $previous);

        $this->expectException(IcuException::class);
        $this->expectExceptionMessage('An ICU exception message');
        $this->expectExceptionCode(42);
        $this->expectExceptionObject($exception);

        throw $exception;
    }
}
