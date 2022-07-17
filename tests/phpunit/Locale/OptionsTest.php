<?php

namespace Ecma\Test\Intl\Locale;

use Ecma\Intl\Calendar;
use Ecma\Intl\CaseFirst;
use Ecma\Intl\Collation;
use Ecma\Intl\HourCycle;
use Ecma\Intl\Locale\Options;
use Ecma\Intl\NumberingSystem;
use Ecma\Test\Intl\TestCase;

/**
 * @psalm-type OptionsArray = array{calendar?: Calendar|null, caseFirst?: CaseFirst|null, collation?: Collation|null, hourCycle?: HourCycle|null, language?: string|null, numberingSystem?: NumberingSystem|null, numeric?: bool|null, region?: string|null, script?: string|null}
 */
class OptionsTest extends TestCase
{
    /**
     * @param OptionsArray $args
     *
     * @dataProvider optionsProvider
     */
    public function testSetsOptionsViaConstructor(array $args): void
    {
        $options = new Options(...$args);

        /**
         * @var string $property
         * @var mixed $value
         *
         * @psalm-suppress RawObjectIteration
         * @phpstan-ignore-next-line
         */
        foreach ($options as $property => $value) {
            $this->assertSame($args[$property] ?? null, $value);
        }
    }

    /**
     * @param OptionsArray $args
     *
     * @dataProvider optionsProvider
     */
    public function testSetsOptionsViaProperties(array $args): void
    {
        $options = new Options();

        /**
         * @var string $property
         * @var mixed $value
         */
        foreach ($args as $property => $value) {
            $options->$property = $value;
        }

        /**
         * @var string $property
         * @var mixed $value
         *
         * @psalm-suppress RawObjectIteration
         * @phpstan-ignore-next-line
         */
        foreach ($options as $property => $value) {
            $this->assertSame($args[$property] ?? null, $value);
        }
    }

    /**
     * @return array<array{args: OptionsArray}>
     */
    public function optionsProvider(): array
    {
        return [
            [
                'args' => [],
            ],
            [
                'args' => [
                    'calendar' => null,
                    'caseFirst' => null,
                    'collation' => null,
                    'hourCycle' => null,
                    'language' => null,
                    'numberingSystem' => null,
                    'numeric' => null,
                    'region' => null,
                    'script' => null,
                ],
            ],
            [
                'args' => [
                    'calendar' => Calendar::Gregory,
                    'caseFirst' => CaseFirst::Upper,
                    'collation' => Collation::Emoji,
                    'hourCycle' => HourCycle::H23,
                    'language' => 'en',
                    'numberingSystem' => NumberingSystem::Latn,
                    'numeric' => true,
                    'region' => 'US',
                    'script' => 'Latn',
                ],
            ],
            [
                'args' => ['calendar' => Calendar::Buddhist],
            ],
            [
                'args' => ['collation' => Collation::Big5han],
            ],
            [
                'args' => ['caseFirst' => CaseFirst::False],
            ],
            [
                'args' => ['hourCycle' => HourCycle::H11],
            ],
            [
                'args' => ['language' => 'fr'],
            ],
            [
                'args' => ['numberingSystem' => NumberingSystem::Arab],
            ],
            [
                'args' => ['numeric' => false],
            ],
            [
                'args' => ['region' => 'BR'],
            ],
            [
                'args' => ['script' => 'Cyrl'],
            ],
        ];
    }
}
