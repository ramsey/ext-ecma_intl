--TEST--
Intl\Locale initializes properties with basic locale
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Calendar;
use Ecma\Intl\CaseFirst;
use Ecma\Intl\Collation;
use Ecma\Intl\HourCycle;
use Ecma\Intl\Locale;
use Ecma\Intl\NumberingSystem;

$locale = new Locale('en');

assert($locale->baseName === 'en');
assert($locale->calendar === null);
assert($locale->calendars === [Calendar::Gregory]);
assert($locale->caseFirst === null);
assert($locale->collation === null);
assert($locale->collations === [Collation::Emoji, Collation::Eor]);
assert($locale->hourCycle === null);
assert($locale->hourCycles === [HourCycle::H12]);
assert($locale->numberingSystem === null);
assert($locale->numberingSystems === [NumberingSystem::Latn]);
assert($locale->numeric === false);
assert($locale->region === null);
assert($locale->script === null);
assert($locale->textInfo instanceof Locale\TextInfo);
assert($locale->textInfo->direction === Locale\TextDirection::LeftToRight);
assert($locale->timeZones === null);
assert($locale->weekInfo instanceof Locale\WeekInfo);
assert($locale->weekInfo->firstDay === Locale\WeekDay::Sunday);
assert($locale->weekInfo->minimalDays === 1);
assert($locale->weekInfo->weekend === [Locale\WeekDay::Saturday, Locale\WeekDay::Sunday]);

echo json_encode($locale, JSON_PRETTY_PRINT) . "\n";
?>
--EXPECT--
{
    "baseName": "en",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "en",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": null,
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}
