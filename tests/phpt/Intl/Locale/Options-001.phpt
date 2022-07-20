--TEST--
Intl\Locale\Options sets options via constructor
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Calendar;
use Ecma\Intl\CaseFirst;
use Ecma\Intl\Collation;
use Ecma\Intl\HourCycle;
use Ecma\Intl\Locale\Options;
use Ecma\Intl\NumberingSystem;

$tests = [
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

foreach ($tests as $test) {
    $options = new Options(...$test['args']);

    foreach ($options as $property => $value) {
        assert(
            ($test['args'][$property] ?? null) === $value,
            sprintf(
                '%s is not the expected value %s; got %s',
                $property,
                var_export($test['args'][$property] ?? null, true),
                var_export($value, true),
            )
        );
    }
    
    echo json_encode($options) . "\n";
}
?>
--EXPECT--
{"calendar":null,"caseFirst":null,"collation":null,"hourCycle":null,"language":null,"numberingSystem":null,"numeric":null,"region":null,"script":null}
{"calendar":null,"caseFirst":null,"collation":null,"hourCycle":null,"language":null,"numberingSystem":null,"numeric":null,"region":null,"script":null}
{"calendar":"gregory","caseFirst":"upper","collation":"emoji","hourCycle":"h23","language":"en","numberingSystem":"latn","numeric":true,"region":"US","script":"Latn"}
{"calendar":"buddhist","caseFirst":null,"collation":null,"hourCycle":null,"language":null,"numberingSystem":null,"numeric":null,"region":null,"script":null}
{"calendar":null,"caseFirst":null,"collation":"big5han","hourCycle":null,"language":null,"numberingSystem":null,"numeric":null,"region":null,"script":null}
{"calendar":null,"caseFirst":"false","collation":null,"hourCycle":null,"language":null,"numberingSystem":null,"numeric":null,"region":null,"script":null}
{"calendar":null,"caseFirst":null,"collation":null,"hourCycle":"h11","language":null,"numberingSystem":null,"numeric":null,"region":null,"script":null}
{"calendar":null,"caseFirst":null,"collation":null,"hourCycle":null,"language":"fr","numberingSystem":null,"numeric":null,"region":null,"script":null}
{"calendar":null,"caseFirst":null,"collation":null,"hourCycle":null,"language":null,"numberingSystem":"arab","numeric":null,"region":null,"script":null}
{"calendar":null,"caseFirst":null,"collation":null,"hourCycle":null,"language":null,"numberingSystem":null,"numeric":false,"region":null,"script":null}
{"calendar":null,"caseFirst":null,"collation":null,"hourCycle":null,"language":null,"numberingSystem":null,"numeric":null,"region":"BR","script":null}
{"calendar":null,"caseFirst":null,"collation":null,"hourCycle":null,"language":null,"numberingSystem":null,"numeric":null,"region":null,"script":"Cyrl"}
