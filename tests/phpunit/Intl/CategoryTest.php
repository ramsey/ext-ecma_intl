<?php

namespace Ecma\Test\Intl;

use Ecma\Intl\Category;
use Ecma\Test\TestCase;

class CategoryTest extends TestCase
{
    /**
     * @dataProvider categoryValuesProvider
     */
    public function testCategoryValues(Category $category, string $expectedValue): void
    {
        $this->assertSame($expectedValue, $category->value);
    }

    /**
     * @return array<array{category: Category, expectedValue: string}>
     */
    public function categoryValuesProvider(): array
    {
        return [
            [
                'category' => Category::Calendar,
                'expectedValue' => 'calendar',
            ],
            [
                'category' => Category::Collation,
                'expectedValue' => 'collation',
            ],
            [
                'category' => Category::Currency,
                'expectedValue' => 'currency',
            ],
            [
                'category' => Category::NumberingSystem,
                'expectedValue' => 'numberingSystem',
            ],
            [
                'category' => Category::TimeZone,
                'expectedValue' => 'timeZone',
            ],
            [
                'category' => Category::Unit,
                'expectedValue' => 'unit',
            ],
        ];
    }
}
