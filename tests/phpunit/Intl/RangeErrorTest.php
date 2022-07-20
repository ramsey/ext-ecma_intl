<?php

namespace Ecma\Test\Intl;

use Ecma\Intl\Exception;
use Ecma\Intl\RangeError;
use Ecma\Test\TestCase;
use RuntimeException;
use ValueError;

class RangeErrorTest extends TestCase
{
    public function testRangeErrorIsAChildOfValueError(): void
    {
        $exception = new RangeError();

        $this->assertInstanceOf(ValueError::class, $exception);
    }

    public function testRangeErrorIsAnEcmaIntlException(): void
    {
        $exception = new RangeError();

        $this->assertInstanceOf(Exception::class, $exception);
    }

    public function testRangeErrorThrownAndCaught(): void
    {
        $previous = new RuntimeException('A runtime exception');
        $exception = new RangeError('A range error message', 36, $previous);

        $this->expectException(RangeError::class);
        $this->expectExceptionMessage('A range error message');
        $this->expectExceptionCode(36);

        throw $exception;
    }
}
