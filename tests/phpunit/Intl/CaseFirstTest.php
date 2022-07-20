<?php

namespace Ecma\Test\Intl;

use Ecma\Intl\CaseFirst;
use Ecma\Test\TestCase;

class CaseFirstTest extends TestCase
{
    /**
     * @dataProvider caseFirstValuesProvider
     */
    public function testCaseFirstValues(CaseFirst $caseFirst, string $expectedValue): void
    {
        $this->assertSame($expectedValue, $caseFirst->value);
    }

    /**
     * @return array<array{caseFirst: CaseFirst, expectedValue: string}>
     */
    public function caseFirstValuesProvider(): array
    {
        return [
            [
                'caseFirst' => CaseFirst::False,
                'expectedValue' => 'false',
            ],
            [
                'caseFirst' => CaseFirst::Lower,
                'expectedValue' => 'lower',
            ],
            [
                'caseFirst' => CaseFirst::Upper,
                'expectedValue' => 'upper',
            ],
        ];
    }
}
