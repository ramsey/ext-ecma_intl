--TEST--
Intl\Locale tags and options (for ICU 70.1 and later)
--EXTENSIONS--
ecma_intl
--SKIPIF--
<?php if (version_compare(ECMA_INTL_ICU_VERSION, '70.1', '<')) exit('SKIP ICU version 70.1 and later required'); ?>
--FILE--
<?php
use Ecma\Intl\Calendar;
use Ecma\Intl\CaseFirst;
use Ecma\Intl\Collation;
use Ecma\Intl\HourCycle;
use Ecma\Intl\Locale;
use Ecma\Intl\NumberingSystem;
use Ecma\Intl\RangeError;

$tests = [
    ['tag' => 'en', 'expected' => 'en'],
    ['tag' => 'en-us', 'expected' => 'en-US'],
    ['tag' => 'und-US', 'expected' => 'und-US'],
    ['tag' => 'und-latn', 'expected' => 'und-Latn'],
    ['tag' => 'en-US-posix', 'expected' => 'en-US-u-va-posix'],
    ['tag' => 'kok-IN', 'expected' => 'kok-IN'],
    ['tag' => 'en_us', 'expected' => 'en-US'],
    ['tag' => 'art-lojban', 'expected' => 'jbo'],
    ['tag' => 'zh-hakka', 'expected' => 'hak'],
    ['tag' => 'zh-cmn-CH-u-co-pinyin', 'expected' => 'cmn-CH-u-co-pinyin'],
    ['tag' => 'xxx-yy', 'expected' => 'xxx-YY'],
    ['tag' => 'fr-234', 'expected' => 'fr-234'],
    ['tag' => 'i-default', 'expected' => 'en-x-i-default'],
    ['tag' => 'bogus', 'expected' => 'bogus'],
    ['tag' => 'EN-lATN-us', 'expected' => 'en-Latn-US'],
    ['tag' => 'und-variant-1234', 'expected' => 'und-1234-variant'],
    ['tag' => 'ja-9876-5432', 'expected' => 'ja-5432-9876'],
    ['tag' => 'en-US-varianta-variantb', 'expected' => 'en-US-varianta-variantb'],
    ['tag' => 'en-US-variantb-varianta', 'expected' => 'en-US-varianta-variantb'],
    ['tag' => 'sl-rozaj-1994-biske', 'expected' => 'sl-1994-biske-rozaj'],
    ['tag' => 'sl-biske-1994-rozaj', 'expected' => 'sl-1994-biske-rozaj'],
    ['tag' => 'sl-1994-rozaj-biske', 'expected' => 'sl-1994-biske-rozaj'],
    ['tag' => 'sl-rozaj-biske-1994', 'expected' => 'sl-1994-biske-rozaj'],
    ['tag' => 'en-fonipa-scouse', 'expected' => 'en-fonipa-scouse'],
    ['tag' => 'en-scouse-fonipa', 'expected' => 'en-fonipa-scouse'],
    ['tag' => 'en-u-ca-gregory', 'expected' => 'en-u-ca-gregory'],
    ['tag' => 'en-U-cu-USD', 'expected' => 'en-u-cu-usd'],
    ['tag' => 'en-US-u-va-posix', 'expected' => 'en-US-u-va-posix'],
    ['tag' => 'en-us-u-ca-gregory-va-posix', 'expected' => 'en-US-u-ca-gregory-va-posix'],
    ['tag' => 'en-us-posix-u-va-posix', 'expected' => 'en-US-u-va-posix'],
    ['tag' => 'en-us-u-va-posix2', 'expected' => 'en-US-u-va-posix2'],
    ['tag' => 'en-us-vari1-u-va-posix', 'expected' => 'en-US-vari1-u-va-posix'],
    ['tag' => 'ar-x-1-2-3', 'expected' => 'ar-x-1-2-3'],
    ['tag' => 'fr-u-nu-latn-cu-eur', 'expected' => 'fr-u-cu-eur-nu-latn'],
    ['tag' => 'de-k-kext-u-co-phonebk-nu-latn', 'expected' => 'de-k-kext-u-co-phonebk-nu-latn'],
    ['tag' => 'en-us-u-tz-usnyc', 'expected' => 'en-US-u-tz-usnyc'],
    ['tag' => 'und-a-abc-def', 'expected' => 'und-a-abc-def'],
    ['tag' => 'zh-u-ca-chinese-x-u-ca-chinese', 'expected' => 'zh-u-ca-chinese-x-u-ca-chinese'],
    ['tag' => 'en-US-u-attr1-attr2-ca-gregory', 'expected' => 'en-US-u-attr1-attr2-ca-gregory'],
    ['tag' => 'sr-u-kn', 'expected' => 'sr-u-kn'],
    ['tag' => 'de-u-kn-co-phonebk', 'expected' => 'de-u-co-phonebk-kn'],
    ['tag' => 'de@collation=phonebook;colnumeric=yes', 'expected' => 'de-u-co-phonebk-kn'],
    ['tag' => 'en-u-attr2-attr1-kn-kb', 'expected' => 'en-u-attr1-attr2-kb-kn'],
    [
        'tag' => 'ja-u-ijkl-efgh-abcd-ca-japanese-xx-yyy-zzz-kn',
        'expected' => 'ja-u-abcd-efgh-ijkl-ca-japanese-kn-xx-yyy-zzz',
    ],
    [
        'tag' => 'de-u-xc-xphonebk-co-phonebk-ca-buddhist-mo-very-lo-'
            . 'extensi-xd-that-de-should-vc-probably-xz-killthebuffer',
        'expected' => 'de-u-ca-buddhist-co-phonebk-de-should-lo-extensi-'
            . 'mo-very-vc-probably-xc-xphonebk-xd-that-xz',
    ],
    [
        'tag' => 'de@calendar=buddhist;collation=phonebook;de=should;'
            . 'lo=extensi;mo=very;vc=probably;xc=xphonebk;xd=that;xz=yes',
        'expected' => 'de-u-ca-buddhist-co-phonebk-de-should-lo-extensi'
            . '-mo-very-vc-probably-xc-xphonebk-xd-that-xz',
    ],
    ['tag' => 'en-a-bbb-a-ccc', 'expected' => 'en-a-bbb'],
    ['tag' => 'en-a-bar-u-baz', 'expected' => 'en-a-bar-u-baz'],
    ['tag' => 'en-a-bar-u-baz-x-u-foo', 'expected' => 'en-a-bar-u-baz-x-u-foo'],
    ['tag' => 'en-u-baz', 'expected' => 'en-u-baz'],
    ['tag' => 'en-u-baz-ca-islamic-civil', 'expected' => 'en-u-baz-ca-islamic-civil'],
    ['tag' => 'en-a-bar-u-ca-islamic-civil-x-u-foo', 'expected' => 'en-a-bar-u-ca-islamic-civil-x-u-foo'],
    [
        'tag' => 'en-a-bar-u-baz-ca-islamic-civil-x-u-foo',
        'expected' => 'en-a-bar-u-baz-ca-islamic-civil-x-u-foo',
    ],
    ['tag' => 'und-Arab-u-em-emoji', 'expected' => 'und-Arab-u-em-emoji'],
    ['tag' => 'und-Latn-u-em-emoji', 'expected' => 'und-Latn-u-em-emoji'],
    ['tag' => 'und-Latn-DE-u-em-emoji', 'expected' => 'und-Latn-DE-u-em-emoji'],
    ['tag' => 'und-Zzzz-DE-u-em-emoji', 'expected' => 'und-Zzzz-DE-u-em-emoji'],
    ['tag' => 'zh-u-ca-chinese-ca-gregory', 'expected' => 'zh-u-ca-chinese'],
    ['tag' => 'zh-u-ca-gregory-co-pinyin-ca-chinese', 'expected' => 'zh-u-ca-gregory-co-pinyin'],
    [
        'tag' => 'de-latn-DE-1901-u-co-phonebk-co-pinyin-ca-gregory',
        'expected' => 'de-Latn-DE-1901-u-ca-gregory-co-phonebk',
    ],
    ['tag' => 'th-u-kf-nu-thai-kf-false', 'expected' => 'th-u-kf-nu-thai'],
    ['tag' => 'i-navajo', 'expected' => 'nv'],
    ['tag' => 'i-navajo-a-foo', 'expected' => 'nv-a-foo'],
    ['tag' => 'i-navajo-latn-us', 'expected' => 'nv-Latn-US'],
    ['tag' => 'sgn-br', 'expected' => 'sgn-BR'],
    ['tag' => 'sgn-br-u-co-phonebk', 'expected' => 'bzs-u-co-phonebk'],
    ['tag' => 'ja-latn-hepburn-heploc', 'expected' => 'ja-Latn-hepburn-heploc'],
    ['tag' => 'ja-latn-hepburn-heploc-u-ca-japanese', 'expected' => 'ja-Latn-alalc97-u-ca-japanese'],
    ['tag' => 'en-a-bcde-0-fgh', 'expected' => 'en-0-fgh-a-bcde'],
    ['tag' => 'en-US', 'expected' => 'en-US', 'options' => new Locale\Options()],
    ['tag' => 'en', 'expected' => 'en-GB', 'options' => new Locale\Options(region: 'GB')],
    [
        'tag' => 'en-Latn-US',
        'expected' => 'fr-Cyrl-CA',
        'options' => new Locale\Options(
            language: 'fr',
            region: 'CA',
            script: 'Cyrl',
        ),
    ],
    [
        'tag' => 'und',
        'expected' => 'en-Latn-US-u-ca-gregory-co-emoji-hc-h23-kf-upper-kn-nu-latn',
        'options' => new Locale\Options(
            calendar: Calendar::Gregory,
            caseFirst: CaseFirst::Upper,
            collation: Collation::Emoji,
            hourCycle: HourCycle::H23,
            language: 'en',
            numberingSystem: NumberingSystem::Latn,
            numeric: true,
            region: 'US',
            script: 'Latn',
        ),
    ],
    [
        'tag' => 'ar',
        'expected' => 'ar-Latn-CA-u-ca-dangi-co-phonebk-hc-h11-kf-lower-kn-false-nu-traditio',
        'options' => new Locale\Options(
            calendar: Calendar::Dangi,
            caseFirst: CaseFirst::Lower,
            collation: Collation::Phonebk,
            hourCycle: HourCycle::H11,
            numberingSystem: NumberingSystem::Traditio,
            numeric: false,
            region: 'CA',
            script: 'latn',
        ),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-u-ca-buddhist',
        'options' => new Locale\Options(calendar: Calendar::Buddhist),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-u-kf-lower',
        'options' => new Locale\Options(caseFirst: CaseFirst::Lower),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-u-kf-false',
        'options' => new Locale\Options(caseFirst: CaseFirst::False),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-u-co-phonebk',
        'options' => new Locale\Options(collation: Collation::Phonebk),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-u-hc-h11',
        'options' => new Locale\Options(hourCycle: HourCycle::H11),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-u-hc-h12',
        'options' => new Locale\Options(hourCycle: HourCycle::H12),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-u-hc-h23',
        'options' => new Locale\Options(hourCycle: HourCycle::H23),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-u-hc-h24',
        'options' => new Locale\Options(hourCycle: HourCycle::H24),
    ],
    [
        'tag' => 'und',
        'expected' => 'fr',
        'options' => new Locale\Options(language: 'fr'),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-u-nu-thai',
        'options' => new Locale\Options(numberingSystem: NumberingSystem::Thai),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-u-kn',
        'options' => new Locale\Options(numeric: true),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-u-kn-false',
        'options' => new Locale\Options(numeric: false),
    ],
    [
        'tag' => 'und',
        'expected' => 'und-ES',
        'options' => new Locale\Options(region: 'ES'),
    ],
    ['tag' => 'de', 'expected' => 'de'],
    ['tag' => 'de-Latn-US', 'expected' => 'de-Latn-US'],
    ['tag' => 'sr', 'expected' => 'sr'],
    ['tag' => 'sr-Cyrl-RS', 'expected' => 'sr-Cyrl-RS'],
    ['tag' => 'zh_Hans', 'expected' => 'zh-Hans'],
    ['tag' => 'zh-Hant-TW', 'expected' => 'zh-Hant-TW'],
];

foreach ($tests as $test) {
    $locale = new Locale($test['tag'], $test['options'] ?? null);
    $maximizedLocale = $locale->maximize();
    $minimizedLocale = $locale->minimize();

    assert($test['expected'] === $locale->toString());
    assert($test['expected'] === (string) $locale);
    assert($maximizedLocale !== $locale);
    assert($minimizedLocale !== $locale);

    echo "Original: $locale\n\n";
    echo json_encode($locale, JSON_PRETTY_PRINT) . "\n\n";
    
    echo str_repeat('-', 72) . "\n\n";
    echo "Maximized: $maximizedLocale\n\n";
    echo json_encode($maximizedLocale, JSON_PRETTY_PRINT) . "\n\n";
    
    echo str_repeat('-', 72) . "\n\n";
    echo "Minimized: $minimizedLocale\n\n";
    echo json_encode($minimizedLocale, JSON_PRETTY_PRINT) . "\n\n";
    
    echo str_repeat('=', 72) . "\n\n";
}
?>
--EXPECT--
Original: en

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

------------------------------------------------------------------------

Maximized: en-Latn-US

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en

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

========================================================================

Original: en-US

{
    "baseName": "en-US",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en

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

========================================================================

Original: und-US

{
    "baseName": "und-US",
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
    "language": null,
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en

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

========================================================================

Original: und-Latn

{
    "baseName": "und-Latn",
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
    "language": null,
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": null,
    "script": "Latn",
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

------------------------------------------------------------------------

Maximized: en-Latn-US

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en

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

========================================================================

Original: en-US-u-va-posix

{
    "baseName": "en-US-u-va-posix",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US-u-va-posix

{
    "baseName": "en-Latn-US-u-va-posix",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-va-posix

{
    "baseName": "en-u-va-posix",
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

========================================================================

Original: kok-IN

{
    "baseName": "kok-IN",
    "calendar": null,
    "calendars": [
        "gregory",
        "indian"
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
    "language": "kok",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "IN",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Calcutta"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: kok-Deva-IN

{
    "baseName": "kok-Deva-IN",
    "calendar": null,
    "calendars": [
        "gregory",
        "indian"
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
    "language": "kok",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "IN",
    "script": "Deva",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Calcutta"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: kok

{
    "baseName": "kok",
    "calendar": null,
    "calendars": [
        "gregory",
        "indian"
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
    "language": "kok",
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
            7
        ]
    }
}

========================================================================

Original: en-US

{
    "baseName": "en-US",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en

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

========================================================================

Original: jbo

{
    "baseName": "jbo",
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
        "h23"
    ],
    "language": "jbo",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: jbo-Latn-001

{
    "baseName": "jbo-Latn-001",
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
        "h23"
    ],
    "language": "jbo",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "001",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "CET",
        "CST6CDT",
        "EET",
        "EST5EDT",
        "Etc\/GMT",
        "Etc\/GMT+1",
        "Etc\/GMT+10",
        "Etc\/GMT+11",
        "Etc\/GMT+12",
        "Etc\/GMT+2",
        "Etc\/GMT+3",
        "Etc\/GMT+4",
        "Etc\/GMT+5",
        "Etc\/GMT+6",
        "Etc\/GMT+7",
        "Etc\/GMT+8",
        "Etc\/GMT+9",
        "Etc\/GMT-1",
        "Etc\/GMT-10",
        "Etc\/GMT-11",
        "Etc\/GMT-12",
        "Etc\/GMT-13",
        "Etc\/GMT-14",
        "Etc\/GMT-2",
        "Etc\/GMT-3",
        "Etc\/GMT-4",
        "Etc\/GMT-5",
        "Etc\/GMT-6",
        "Etc\/GMT-7",
        "Etc\/GMT-8",
        "Etc\/GMT-9",
        "Etc\/UTC",
        "Factory",
        "MET",
        "MST7MDT",
        "PST8PDT",
        "SystemV\/AST4",
        "SystemV\/AST4ADT",
        "SystemV\/CST6",
        "SystemV\/CST6CDT",
        "SystemV\/EST5",
        "SystemV\/EST5EDT",
        "SystemV\/HST10",
        "SystemV\/MST7",
        "SystemV\/MST7MDT",
        "SystemV\/PST8",
        "SystemV\/PST8PDT",
        "SystemV\/YST9",
        "SystemV\/YST9YDT",
        "WET"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: jbo

{
    "baseName": "jbo",
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
        "h23"
    ],
    "language": "jbo",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: hak

{
    "baseName": "hak",
    "calendar": null,
    "calendars": [
        "gregory",
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "hak",
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

------------------------------------------------------------------------

Maximized: hak-Hans-CN

{
    "baseName": "hak-Hans-CN",
    "calendar": null,
    "calendars": [
        "gregory",
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "hak",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "CN",
    "script": "Hans",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Shanghai",
        "Asia\/Urumqi"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: hak

{
    "baseName": "hak",
    "calendar": null,
    "calendars": [
        "gregory",
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "hak",
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

========================================================================

Original: cmn-CH-u-co-pinyin

{
    "baseName": "cmn-CH",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "pinyin",
    "collations": [
        "pinyin"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "cmn",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "CH",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Zurich"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: cmn-CH-u-co-pinyin

{
    "baseName": "cmn-CH",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "pinyin",
    "collations": [
        "pinyin"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "cmn",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "CH",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Zurich"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: cmn-CH-u-co-pinyin

{
    "baseName": "cmn-CH",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "pinyin",
    "collations": [
        "pinyin"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "cmn",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "CH",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Zurich"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: xxx-YY

{
    "baseName": "xxx-YY",
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
        "h23"
    ],
    "language": "xxx",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "YY",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: xxx-YY

{
    "baseName": "xxx-YY",
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
        "h23"
    ],
    "language": "xxx",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "YY",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: xxx-YY

{
    "baseName": "xxx-YY",
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
        "h23"
    ],
    "language": "xxx",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "YY",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: fr-234

{
    "baseName": "fr-234",
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
        "h23"
    ],
    "language": "fr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "234",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: fr-Latn-234

{
    "baseName": "fr-Latn-234",
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
        "h23"
    ],
    "language": "fr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "234",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: fr-234

{
    "baseName": "fr-234",
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
        "h23"
    ],
    "language": "fr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "234",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: en-x-i-default

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

------------------------------------------------------------------------

Maximized: en-Latn-US-x-i-default

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-x-i-default

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

========================================================================

Original: bogus

{
    "baseName": "bogus",
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
        "h23"
    ],
    "language": "bogus",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: bogus

{
    "baseName": "bogus",
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
        "h23"
    ],
    "language": "bogus",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: bogus

{
    "baseName": "bogus",
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
        "h23"
    ],
    "language": "bogus",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: en-Latn-US

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en

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

========================================================================

Original: und-1234-variant

{
    "baseName": "und-1234-variant",
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
    "language": null,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-1234-variant

{
    "baseName": "en-Latn-US-1234-variant",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-1234-variant

{
    "baseName": "en-1234-variant",
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

========================================================================

Original: ja-5432-9876

{
    "baseName": "ja-5432-9876",
    "calendar": null,
    "calendars": [
        "gregory",
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
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

------------------------------------------------------------------------

Maximized: ja-Jpan-JP-5432-9876

{
    "baseName": "ja-Jpan-JP-5432-9876",
    "calendar": null,
    "calendars": [
        "gregory",
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "JP",
    "script": "Jpan",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Tokyo"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: ja-5432-9876

{
    "baseName": "ja-5432-9876",
    "calendar": null,
    "calendars": [
        "gregory",
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
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

========================================================================

Original: en-US-varianta-variantb

{
    "baseName": "en-US-varianta-variantb",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US-varianta-variantb

{
    "baseName": "en-Latn-US-varianta-variantb",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-varianta-variantb

{
    "baseName": "en-varianta-variantb",
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

========================================================================

Original: en-US-varianta-variantb

{
    "baseName": "en-US-varianta-variantb",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US-varianta-variantb

{
    "baseName": "en-Latn-US-varianta-variantb",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-varianta-variantb

{
    "baseName": "en-varianta-variantb",
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

========================================================================

Original: sl-1994-biske-rozaj

{
    "baseName": "sl-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: sl-Latn-SI-1994-biske-rozaj

{
    "baseName": "sl-Latn-SI-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "SI",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Ljubljana"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: sl-1994-biske-rozaj

{
    "baseName": "sl-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: sl-1994-biske-rozaj

{
    "baseName": "sl-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: sl-Latn-SI-1994-biske-rozaj

{
    "baseName": "sl-Latn-SI-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "SI",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Ljubljana"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: sl-1994-biske-rozaj

{
    "baseName": "sl-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: sl-1994-biske-rozaj

{
    "baseName": "sl-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: sl-Latn-SI-1994-biske-rozaj

{
    "baseName": "sl-Latn-SI-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "SI",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Ljubljana"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: sl-1994-biske-rozaj

{
    "baseName": "sl-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: sl-1994-biske-rozaj

{
    "baseName": "sl-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: sl-Latn-SI-1994-biske-rozaj

{
    "baseName": "sl-Latn-SI-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "SI",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Ljubljana"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: sl-1994-biske-rozaj

{
    "baseName": "sl-1994-biske-rozaj",
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
        "h23"
    ],
    "language": "sl",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: en-fonipa-scouse

{
    "baseName": "en-fonipa-scouse",
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

------------------------------------------------------------------------

Maximized: en-Latn-US-fonipa-scouse

{
    "baseName": "en-Latn-US-fonipa-scouse",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-fonipa-scouse

{
    "baseName": "en-fonipa-scouse",
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

========================================================================

Original: en-fonipa-scouse

{
    "baseName": "en-fonipa-scouse",
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

------------------------------------------------------------------------

Maximized: en-Latn-US-fonipa-scouse

{
    "baseName": "en-Latn-US-fonipa-scouse",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-fonipa-scouse

{
    "baseName": "en-fonipa-scouse",
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

========================================================================

Original: en-u-ca-gregory

{
    "baseName": "en",
    "calendar": "gregory",
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-ca-gregory

{
    "baseName": "en-Latn-US",
    "calendar": "gregory",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-ca-gregory

{
    "baseName": "en",
    "calendar": "gregory",
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

========================================================================

Original: en-u-cu-usd

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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-cu-usd

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-cu-usd

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

========================================================================

Original: en-US-u-va-posix

{
    "baseName": "en-US-u-va-posix",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US-u-va-posix

{
    "baseName": "en-Latn-US-u-va-posix",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-va-posix

{
    "baseName": "en-u-va-posix",
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

========================================================================

Original: en-US-u-ca-gregory-va-posix

{
    "baseName": "en-US-u-va-posix",
    "calendar": "gregory",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US-u-ca-gregory-va-posix

{
    "baseName": "en-Latn-US-u-va-posix",
    "calendar": "gregory",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-ca-gregory-va-posix

{
    "baseName": "en-u-va-posix",
    "calendar": "gregory",
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

========================================================================

Original: en-US-u-va-posix

{
    "baseName": "en-US-u-va-posix",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US-u-va-posix

{
    "baseName": "en-Latn-US-u-va-posix",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-va-posix

{
    "baseName": "en-u-va-posix",
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

========================================================================

Original: en-US-u-va-posix2

{
    "baseName": "en-US",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US-u-va-posix2

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-va-posix2

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

========================================================================

Original: en-US-vari1-u-va-posix

{
    "baseName": "en-US-vari1",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US-vari1-u-va-posix

{
    "baseName": "en-Latn-US-vari1",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-vari1-u-va-posix

{
    "baseName": "en-vari1",
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

========================================================================

Original: ar-x-1-2-3

{
    "baseName": "ar",
    "calendar": null,
    "calendars": [
        "gregory",
        "coptic",
        "islamic",
        "islamic-civil",
        "islamic-tbla"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "compat",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "ar",
    "numberingSystem": null,
    "numberingSystems": [
        "arab"
    ],
    "numeric": false,
    "region": null,
    "script": null,
    "textInfo": {
        "direction": "rtl"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 6,
        "minimalDays": 1,
        "weekend": [
            5,
            6
        ]
    }
}

------------------------------------------------------------------------

Maximized: ar-Arab-EG-x-1-2-3

{
    "baseName": "ar-Arab-EG",
    "calendar": null,
    "calendars": [
        "gregory",
        "coptic",
        "islamic",
        "islamic-civil",
        "islamic-tbla"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "compat",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "ar",
    "numberingSystem": null,
    "numberingSystems": [
        "arab"
    ],
    "numeric": false,
    "region": "EG",
    "script": "Arab",
    "textInfo": {
        "direction": "rtl"
    },
    "timeZones": [
        "Africa\/Cairo"
    ],
    "weekInfo": {
        "firstDay": 6,
        "minimalDays": 1,
        "weekend": [
            5,
            6
        ]
    }
}

------------------------------------------------------------------------

Minimized: ar-x-1-2-3

{
    "baseName": "ar",
    "calendar": null,
    "calendars": [
        "gregory",
        "coptic",
        "islamic",
        "islamic-civil",
        "islamic-tbla"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "compat",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "ar",
    "numberingSystem": null,
    "numberingSystems": [
        "arab"
    ],
    "numeric": false,
    "region": null,
    "script": null,
    "textInfo": {
        "direction": "rtl"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 6,
        "minimalDays": 1,
        "weekend": [
            5,
            6
        ]
    }
}

========================================================================

Original: fr-u-cu-eur-nu-latn

{
    "baseName": "fr",
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
        "h23"
    ],
    "language": "fr",
    "numberingSystem": "latn",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: fr-Latn-FR-u-cu-eur-nu-latn

{
    "baseName": "fr-Latn-FR",
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
        "h23"
    ],
    "language": "fr",
    "numberingSystem": "latn",
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "FR",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Paris"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: fr-u-cu-eur-nu-latn

{
    "baseName": "fr",
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
        "h23"
    ],
    "language": "fr",
    "numberingSystem": "latn",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: de-k-kext-u-co-phonebk-nu-latn

{
    "baseName": "de",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": "latn",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: de-Latn-DE-k-kext-u-co-phonebk-nu-latn

{
    "baseName": "de-Latn-DE",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": "latn",
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "DE",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: de-k-kext-u-co-phonebk-nu-latn

{
    "baseName": "de",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": "latn",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: en-US-u-tz-usnyc

{
    "baseName": "en-US",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US-u-tz-usnyc

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-tz-usnyc

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

========================================================================

Original: und-a-abc-def

{
    "baseName": "und",
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
    "language": null,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-a-abc-def

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-a-abc-def

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

========================================================================

Original: zh-u-ca-chinese-x-u-ca-chinese

{
    "baseName": "zh",
    "calendar": "chinese",
    "calendars": [
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "pinyin",
        "big5han",
        "gb2312",
        "stroke",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
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

------------------------------------------------------------------------

Maximized: zh-Hans-CN-u-ca-chinese-x-u-ca-chinese

{
    "baseName": "zh-Hans-CN",
    "calendar": "chinese",
    "calendars": [
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "pinyin",
        "big5han",
        "gb2312",
        "stroke",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "CN",
    "script": "Hans",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Shanghai",
        "Asia\/Urumqi"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: zh-u-ca-chinese-x-u-ca-chinese

{
    "baseName": "zh",
    "calendar": "chinese",
    "calendars": [
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "pinyin",
        "big5han",
        "gb2312",
        "stroke",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
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

========================================================================

Original: en-US-u-attr1-attr2-ca-gregory

{
    "baseName": "en-US",
    "calendar": "gregory",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US-u-attr1-attr2-ca-gregory

{
    "baseName": "en-Latn-US",
    "calendar": "gregory",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-attr1-attr2-ca-gregory

{
    "baseName": "en",
    "calendar": "gregory",
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

========================================================================

Original: sr-u-kn

{
    "baseName": "sr",
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
        "h23"
    ],
    "language": "sr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": null,
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: sr-Cyrl-RS-u-kn

{
    "baseName": "sr-Cyrl-RS",
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
        "h23"
    ],
    "language": "sr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": "RS",
    "script": "Cyrl",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Belgrade"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: sr-u-kn

{
    "baseName": "sr",
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
        "h23"
    ],
    "language": "sr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": null,
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: de-u-co-phonebk-kn

{
    "baseName": "de",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": null,
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: de-Latn-DE-u-co-phonebk-kn

{
    "baseName": "de-Latn-DE",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": "DE",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: de-u-co-phonebk-kn

{
    "baseName": "de",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": null,
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: de-u-co-phonebk-kn

{
    "baseName": "de",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": null,
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: de-Latn-DE-u-co-phonebk-kn

{
    "baseName": "de-Latn-DE",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": "DE",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: de-u-co-phonebk-kn

{
    "baseName": "de",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": null,
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: en-u-attr1-attr2-kb-kn

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
    "numeric": true,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-attr1-attr2-kb-kn

{
    "baseName": "en-Latn-US",
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
    "numeric": true,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-attr1-attr2-kb-kn

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
    "numeric": true,
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

========================================================================

Original: ja-u-abcd-efgh-ijkl-ca-japanese-kn-xx-yyy-zzz

{
    "baseName": "ja",
    "calendar": "japanese",
    "calendars": [
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
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

------------------------------------------------------------------------

Maximized: ja-Jpan-JP-u-abcd-efgh-ijkl-ca-japanese-kn-xx-yyy-zzz

{
    "baseName": "ja-Jpan-JP",
    "calendar": "japanese",
    "calendars": [
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": "JP",
    "script": "Jpan",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Tokyo"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: ja-u-abcd-efgh-ijkl-ca-japanese-kn-xx-yyy-zzz

{
    "baseName": "ja",
    "calendar": "japanese",
    "calendars": [
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
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

========================================================================

Original: de-u-ca-buddhist-co-phonebk-de-should-lo-extensi-mo-very-vc-probably-xc-xphonebk-xd-that-xz

{
    "baseName": "de",
    "calendar": "buddhist",
    "calendars": [
        "buddhist"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: de-Latn-DE-u-ca-buddhist-co-phonebk-de-should-lo-extensi-mo-very-vc-probably-xc-xphonebk-xd-that-xz

{
    "baseName": "de-Latn-DE",
    "calendar": "buddhist",
    "calendars": [
        "buddhist"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "DE",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: de-u-ca-buddhist-co-phonebk-de-should-lo-extensi-mo-very-vc-probably-xc-xphonebk-xd-that-xz

{
    "baseName": "de",
    "calendar": "buddhist",
    "calendars": [
        "buddhist"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: de-u-ca-buddhist-co-phonebk-de-should-lo-extensi-mo-very-vc-probably-xc-xphonebk-xd-that-xz

{
    "baseName": "de",
    "calendar": "buddhist",
    "calendars": [
        "buddhist"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: de-Latn-DE-u-ca-buddhist-co-phonebk-de-should-lo-extensi-mo-very-vc-probably-xc-xphonebk-xd-that-xz

{
    "baseName": "de-Latn-DE",
    "calendar": "buddhist",
    "calendars": [
        "buddhist"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "DE",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: de-u-ca-buddhist-co-phonebk-de-should-lo-extensi-mo-very-vc-probably-xc-xphonebk-xd-that-xz

{
    "baseName": "de",
    "calendar": "buddhist",
    "calendars": [
        "buddhist"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: en-a-bbb

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

------------------------------------------------------------------------

Maximized: en-Latn-US-a-bbb

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-a-bbb

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

========================================================================

Original: en-a-bar-u-baz

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

------------------------------------------------------------------------

Maximized: en-Latn-US-a-bar-u-baz

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-a-bar-u-baz

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

========================================================================

Original: en-a-bar-u-baz-x-u-foo

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

------------------------------------------------------------------------

Maximized: en-Latn-US-a-bar-u-baz-x-u-foo

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-a-bar-u-baz-x-u-foo

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

========================================================================

Original: en-u-baz

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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-baz

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-baz

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

========================================================================

Original: en-u-baz-ca-islamic-civil

{
    "baseName": "en",
    "calendar": "islamic-civil",
    "calendars": [
        "islamic-civil"
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-baz-ca-islamic-civil

{
    "baseName": "en-Latn-US",
    "calendar": "islamic-civil",
    "calendars": [
        "islamic-civil"
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-baz-ca-islamic-civil

{
    "baseName": "en",
    "calendar": "islamic-civil",
    "calendars": [
        "islamic-civil"
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

========================================================================

Original: en-a-bar-u-ca-islamic-civil-x-u-foo

{
    "baseName": "en",
    "calendar": "islamic-civil",
    "calendars": [
        "islamic-civil"
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

------------------------------------------------------------------------

Maximized: en-Latn-US-a-bar-u-ca-islamic-civil-x-u-foo

{
    "baseName": "en-Latn-US",
    "calendar": "islamic-civil",
    "calendars": [
        "islamic-civil"
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-a-bar-u-ca-islamic-civil-x-u-foo

{
    "baseName": "en",
    "calendar": "islamic-civil",
    "calendars": [
        "islamic-civil"
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

========================================================================

Original: en-a-bar-u-baz-ca-islamic-civil-x-u-foo

{
    "baseName": "en",
    "calendar": "islamic-civil",
    "calendars": [
        "islamic-civil"
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

------------------------------------------------------------------------

Maximized: en-Latn-US-a-bar-u-baz-ca-islamic-civil-x-u-foo

{
    "baseName": "en-Latn-US",
    "calendar": "islamic-civil",
    "calendars": [
        "islamic-civil"
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-a-bar-u-baz-ca-islamic-civil-x-u-foo

{
    "baseName": "en",
    "calendar": "islamic-civil",
    "calendars": [
        "islamic-civil"
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

========================================================================

Original: und-Arab-u-em-emoji

{
    "baseName": "und-Arab",
    "calendar": null,
    "calendars": [
        "gregory",
        "coptic",
        "islamic",
        "islamic-civil",
        "islamic-tbla"
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
    "language": null,
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": null,
    "script": "Arab",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 6,
        "minimalDays": 1,
        "weekend": [
            5,
            6
        ]
    }
}

------------------------------------------------------------------------

Maximized: ar-Arab-EG-u-em-emoji

{
    "baseName": "ar-Arab-EG",
    "calendar": null,
    "calendars": [
        "gregory",
        "coptic",
        "islamic",
        "islamic-civil",
        "islamic-tbla"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "compat",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "ar",
    "numberingSystem": null,
    "numberingSystems": [
        "arab"
    ],
    "numeric": false,
    "region": "EG",
    "script": "Arab",
    "textInfo": {
        "direction": "rtl"
    },
    "timeZones": [
        "Africa\/Cairo"
    ],
    "weekInfo": {
        "firstDay": 6,
        "minimalDays": 1,
        "weekend": [
            5,
            6
        ]
    }
}

------------------------------------------------------------------------

Minimized: ar-u-em-emoji

{
    "baseName": "ar",
    "calendar": null,
    "calendars": [
        "gregory",
        "coptic",
        "islamic",
        "islamic-civil",
        "islamic-tbla"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "compat",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "ar",
    "numberingSystem": null,
    "numberingSystems": [
        "arab"
    ],
    "numeric": false,
    "region": null,
    "script": null,
    "textInfo": {
        "direction": "rtl"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 6,
        "minimalDays": 1,
        "weekend": [
            5,
            6
        ]
    }
}

========================================================================

Original: und-Latn-u-em-emoji

{
    "baseName": "und-Latn",
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
    "language": null,
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": null,
    "script": "Latn",
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-em-emoji

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-em-emoji

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

========================================================================

Original: und-Latn-DE-u-em-emoji

{
    "baseName": "und-Latn-DE",
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
        "h23"
    ],
    "language": null,
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "DE",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: de-Latn-DE-u-em-emoji

{
    "baseName": "de-Latn-DE",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "phonebk",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "DE",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: de-u-em-emoji

{
    "baseName": "de",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "phonebk",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: und-Zzzz-DE-u-em-emoji

{
    "baseName": "und-Zzzz-DE",
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
        "h23"
    ],
    "language": null,
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "DE",
    "script": "Zzzz",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: de-Latn-DE-u-em-emoji

{
    "baseName": "de-Latn-DE",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "phonebk",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "DE",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: de-u-em-emoji

{
    "baseName": "de",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "phonebk",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: zh-u-ca-chinese

{
    "baseName": "zh",
    "calendar": "chinese",
    "calendars": [
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "pinyin",
        "big5han",
        "gb2312",
        "stroke",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
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

------------------------------------------------------------------------

Maximized: zh-Hans-CN-u-ca-chinese

{
    "baseName": "zh-Hans-CN",
    "calendar": "chinese",
    "calendars": [
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "pinyin",
        "big5han",
        "gb2312",
        "stroke",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "CN",
    "script": "Hans",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Shanghai",
        "Asia\/Urumqi"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: zh-u-ca-chinese

{
    "baseName": "zh",
    "calendar": "chinese",
    "calendars": [
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "pinyin",
        "big5han",
        "gb2312",
        "stroke",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
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

========================================================================

Original: zh-u-ca-gregory-co-pinyin

{
    "baseName": "zh",
    "calendar": "gregory",
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "pinyin",
    "collations": [
        "pinyin"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
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

------------------------------------------------------------------------

Maximized: zh-Hans-CN-u-ca-gregory-co-pinyin

{
    "baseName": "zh-Hans-CN",
    "calendar": "gregory",
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "pinyin",
    "collations": [
        "pinyin"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "CN",
    "script": "Hans",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Shanghai",
        "Asia\/Urumqi"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: zh-u-ca-gregory-co-pinyin

{
    "baseName": "zh",
    "calendar": "gregory",
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "pinyin",
    "collations": [
        "pinyin"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
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

========================================================================

Original: de-Latn-DE-1901-u-ca-gregory-co-phonebk

{
    "baseName": "de-Latn-DE-1901",
    "calendar": "gregory",
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "DE",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: de-Latn-DE-1901-u-ca-gregory-co-phonebk

{
    "baseName": "de-Latn-DE-1901",
    "calendar": "gregory",
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "DE",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: de-1901-u-ca-gregory-co-phonebk

{
    "baseName": "de-1901",
    "calendar": "gregory",
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: th-u-kf-nu-thai

{
    "baseName": "th",
    "calendar": null,
    "calendars": [
        "buddhist",
        "gregory"
    ],
    "caseFirst": "upper",
    "collation": null,
    "collations": [
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "th",
    "numberingSystem": "thai",
    "numberingSystems": [
        "thai"
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

------------------------------------------------------------------------

Maximized: th-Thai-TH-u-kf-nu-thai

{
    "baseName": "th-Thai-TH",
    "calendar": null,
    "calendars": [
        "buddhist",
        "gregory"
    ],
    "caseFirst": "upper",
    "collation": null,
    "collations": [
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "th",
    "numberingSystem": "thai",
    "numberingSystems": [
        "thai"
    ],
    "numeric": false,
    "region": "TH",
    "script": "Thai",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Bangkok"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: th-u-kf-nu-thai

{
    "baseName": "th",
    "calendar": null,
    "calendars": [
        "buddhist",
        "gregory"
    ],
    "caseFirst": "upper",
    "collation": null,
    "collations": [
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "th",
    "numberingSystem": "thai",
    "numberingSystems": [
        "thai"
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

========================================================================

Original: nv

{
    "baseName": "nv",
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
    "language": "nv",
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

------------------------------------------------------------------------

Maximized: nv-Latn-US

{
    "baseName": "nv-Latn-US",
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
    "language": "nv",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: nv

{
    "baseName": "nv",
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
    "language": "nv",
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

========================================================================

Original: nv-a-foo

{
    "baseName": "nv",
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
    "language": "nv",
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

------------------------------------------------------------------------

Maximized: nv-Latn-US-a-foo

{
    "baseName": "nv-Latn-US",
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
    "language": "nv",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: nv-a-foo

{
    "baseName": "nv",
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
    "language": "nv",
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

========================================================================

Original: nv-Latn-US

{
    "baseName": "nv-Latn-US",
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
    "language": "nv",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: nv-Latn-US

{
    "baseName": "nv-Latn-US",
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
    "language": "nv",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: nv

{
    "baseName": "nv",
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
    "language": "nv",
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

========================================================================

Original: sgn-BR

{
    "baseName": "sgn-BR",
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
        "h23"
    ],
    "language": "sgn",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "BR",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Araguaina",
        "America\/Bahia",
        "America\/Belem",
        "America\/Boa_Vista",
        "America\/Campo_Grande",
        "America\/Cuiaba",
        "America\/Eirunepe",
        "America\/Fortaleza",
        "America\/Maceio",
        "America\/Manaus",
        "America\/Noronha",
        "America\/Porto_Velho",
        "America\/Recife",
        "America\/Rio_Branco",
        "America\/Santarem",
        "America\/Sao_Paulo"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: sgn-BR

{
    "baseName": "sgn-BR",
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
        "h23"
    ],
    "language": "sgn",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "BR",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Araguaina",
        "America\/Bahia",
        "America\/Belem",
        "America\/Boa_Vista",
        "America\/Campo_Grande",
        "America\/Cuiaba",
        "America\/Eirunepe",
        "America\/Fortaleza",
        "America\/Maceio",
        "America\/Manaus",
        "America\/Noronha",
        "America\/Porto_Velho",
        "America\/Recife",
        "America\/Rio_Branco",
        "America\/Santarem",
        "America\/Sao_Paulo"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: sgn-BR

{
    "baseName": "sgn-BR",
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
        "h23"
    ],
    "language": "sgn",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "BR",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Araguaina",
        "America\/Bahia",
        "America\/Belem",
        "America\/Boa_Vista",
        "America\/Campo_Grande",
        "America\/Cuiaba",
        "America\/Eirunepe",
        "America\/Fortaleza",
        "America\/Maceio",
        "America\/Manaus",
        "America\/Noronha",
        "America\/Porto_Velho",
        "America\/Recife",
        "America\/Rio_Branco",
        "America\/Santarem",
        "America\/Sao_Paulo"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: bzs-u-co-phonebk

{
    "baseName": "bzs",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "bzs",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: bzs-u-co-phonebk

{
    "baseName": "bzs",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "bzs",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: bzs-u-co-phonebk

{
    "baseName": "bzs",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "bzs",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: ja-Latn-hepburn-heploc

{
    "baseName": "ja-Latn-hepburn-heploc",
    "calendar": null,
    "calendars": [
        "gregory",
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": null,
    "script": "Latn",
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

------------------------------------------------------------------------

Maximized: ja-Latn-JP-hepburn-heploc

{
    "baseName": "ja-Latn-JP-hepburn-heploc",
    "calendar": null,
    "calendars": [
        "gregory",
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "JP",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Tokyo"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: ja-Latn-hepburn-heploc

{
    "baseName": "ja-Latn-hepburn-heploc",
    "calendar": null,
    "calendars": [
        "gregory",
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": null,
    "script": "Latn",
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

========================================================================

Original: ja-Latn-alalc97-u-ca-japanese

{
    "baseName": "ja-Latn-alalc97",
    "calendar": "japanese",
    "calendars": [
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": null,
    "script": "Latn",
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

------------------------------------------------------------------------

Maximized: ja-Latn-JP-alalc97-u-ca-japanese

{
    "baseName": "ja-Latn-JP-alalc97",
    "calendar": "japanese",
    "calendars": [
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "JP",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Tokyo"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: ja-Latn-alalc97-u-ca-japanese

{
    "baseName": "ja-Latn-alalc97",
    "calendar": "japanese",
    "calendars": [
        "japanese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "unihan",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "ja",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": null,
    "script": "Latn",
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

========================================================================

Original: en-0-fgh-a-bcde

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

------------------------------------------------------------------------

Maximized: en-Latn-US-0-fgh-a-bcde

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-0-fgh-a-bcde

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

========================================================================

Original: en-US

{
    "baseName": "en-US",
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
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en

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

========================================================================

Original: en-GB

{
    "baseName": "en-GB",
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
        "h23"
    ],
    "language": "en",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "GB",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/London"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-GB

{
    "baseName": "en-Latn-GB",
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
        "h23"
    ],
    "language": "en",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "GB",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/London"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-GB

{
    "baseName": "en-GB",
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
        "h23"
    ],
    "language": "en",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "GB",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/London"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: fr-Cyrl-CA

{
    "baseName": "fr-Cyrl-CA",
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
        "h23"
    ],
    "language": "fr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "CA",
    "script": "Cyrl",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Blanc-Sablon",
        "America\/Cambridge_Bay",
        "America\/Coral_Harbour",
        "America\/Creston",
        "America\/Dawson",
        "America\/Dawson_Creek",
        "America\/Edmonton",
        "America\/Fort_Nelson",
        "America\/Glace_Bay",
        "America\/Goose_Bay",
        "America\/Halifax",
        "America\/Inuvik",
        "America\/Iqaluit",
        "America\/Moncton",
        "America\/Montreal",
        "America\/Nipigon",
        "America\/Pangnirtung",
        "America\/Rainy_River",
        "America\/Rankin_Inlet",
        "America\/Regina",
        "America\/Resolute",
        "America\/St_Johns",
        "America\/Swift_Current",
        "America\/Thunder_Bay",
        "America\/Toronto",
        "America\/Vancouver",
        "America\/Whitehorse",
        "America\/Winnipeg",
        "America\/Yellowknife"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: fr-Cyrl-CA

{
    "baseName": "fr-Cyrl-CA",
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
        "h23"
    ],
    "language": "fr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "CA",
    "script": "Cyrl",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Blanc-Sablon",
        "America\/Cambridge_Bay",
        "America\/Coral_Harbour",
        "America\/Creston",
        "America\/Dawson",
        "America\/Dawson_Creek",
        "America\/Edmonton",
        "America\/Fort_Nelson",
        "America\/Glace_Bay",
        "America\/Goose_Bay",
        "America\/Halifax",
        "America\/Inuvik",
        "America\/Iqaluit",
        "America\/Moncton",
        "America\/Montreal",
        "America\/Nipigon",
        "America\/Pangnirtung",
        "America\/Rainy_River",
        "America\/Rankin_Inlet",
        "America\/Regina",
        "America\/Resolute",
        "America\/St_Johns",
        "America\/Swift_Current",
        "America\/Thunder_Bay",
        "America\/Toronto",
        "America\/Vancouver",
        "America\/Whitehorse",
        "America\/Winnipeg",
        "America\/Yellowknife"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: fr-Cyrl-CA

{
    "baseName": "fr-Cyrl-CA",
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
        "h23"
    ],
    "language": "fr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "CA",
    "script": "Cyrl",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Blanc-Sablon",
        "America\/Cambridge_Bay",
        "America\/Coral_Harbour",
        "America\/Creston",
        "America\/Dawson",
        "America\/Dawson_Creek",
        "America\/Edmonton",
        "America\/Fort_Nelson",
        "America\/Glace_Bay",
        "America\/Goose_Bay",
        "America\/Halifax",
        "America\/Inuvik",
        "America\/Iqaluit",
        "America\/Moncton",
        "America\/Montreal",
        "America\/Nipigon",
        "America\/Pangnirtung",
        "America\/Rainy_River",
        "America\/Rankin_Inlet",
        "America\/Regina",
        "America\/Resolute",
        "America\/St_Johns",
        "America\/Swift_Current",
        "America\/Thunder_Bay",
        "America\/Toronto",
        "America\/Vancouver",
        "America\/Whitehorse",
        "America\/Winnipeg",
        "America\/Yellowknife"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: en-Latn-US-u-ca-gregory-co-emoji-hc-h23-kf-upper-kn-nu-latn

{
    "baseName": "en-Latn-US",
    "calendar": "gregory",
    "calendars": [
        "gregory"
    ],
    "caseFirst": "upper",
    "collation": "emoji",
    "collations": [
        "emoji"
    ],
    "hourCycle": "h23",
    "hourCycles": [
        "h23"
    ],
    "language": "en",
    "numberingSystem": "latn",
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: en-Latn-US-u-ca-gregory-co-emoji-hc-h23-kf-upper-kn-nu-latn

{
    "baseName": "en-Latn-US",
    "calendar": "gregory",
    "calendars": [
        "gregory"
    ],
    "caseFirst": "upper",
    "collation": "emoji",
    "collations": [
        "emoji"
    ],
    "hourCycle": "h23",
    "hourCycles": [
        "h23"
    ],
    "language": "en",
    "numberingSystem": "latn",
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-ca-gregory-co-emoji-hc-h23-kf-upper-kn-nu-latn

{
    "baseName": "en",
    "calendar": "gregory",
    "calendars": [
        "gregory"
    ],
    "caseFirst": "upper",
    "collation": "emoji",
    "collations": [
        "emoji"
    ],
    "hourCycle": "h23",
    "hourCycles": [
        "h23"
    ],
    "language": "en",
    "numberingSystem": "latn",
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
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

========================================================================

Original: ar-Latn-CA-u-ca-dangi-co-phonebk-hc-h11-kf-lower-kn-false-nu-traditio

{
    "baseName": "ar-Latn-CA",
    "calendar": "dangi",
    "calendars": [
        "dangi"
    ],
    "caseFirst": "lower",
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": "h11",
    "hourCycles": [
        "h11"
    ],
    "language": "ar",
    "numberingSystem": "traditio",
    "numberingSystems": [
        "traditio"
    ],
    "numeric": false,
    "region": "CA",
    "script": "Latn",
    "textInfo": {
        "direction": "rtl"
    },
    "timeZones": [
        "America\/Blanc-Sablon",
        "America\/Cambridge_Bay",
        "America\/Coral_Harbour",
        "America\/Creston",
        "America\/Dawson",
        "America\/Dawson_Creek",
        "America\/Edmonton",
        "America\/Fort_Nelson",
        "America\/Glace_Bay",
        "America\/Goose_Bay",
        "America\/Halifax",
        "America\/Inuvik",
        "America\/Iqaluit",
        "America\/Moncton",
        "America\/Montreal",
        "America\/Nipigon",
        "America\/Pangnirtung",
        "America\/Rainy_River",
        "America\/Rankin_Inlet",
        "America\/Regina",
        "America\/Resolute",
        "America\/St_Johns",
        "America\/Swift_Current",
        "America\/Thunder_Bay",
        "America\/Toronto",
        "America\/Vancouver",
        "America\/Whitehorse",
        "America\/Winnipeg",
        "America\/Yellowknife"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: ar-Latn-CA-u-ca-dangi-co-phonebk-hc-h11-kf-lower-kn-false-nu-traditio

{
    "baseName": "ar-Latn-CA",
    "calendar": "dangi",
    "calendars": [
        "dangi"
    ],
    "caseFirst": "lower",
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": "h11",
    "hourCycles": [
        "h11"
    ],
    "language": "ar",
    "numberingSystem": "traditio",
    "numberingSystems": [
        "traditio"
    ],
    "numeric": false,
    "region": "CA",
    "script": "Latn",
    "textInfo": {
        "direction": "rtl"
    },
    "timeZones": [
        "America\/Blanc-Sablon",
        "America\/Cambridge_Bay",
        "America\/Coral_Harbour",
        "America\/Creston",
        "America\/Dawson",
        "America\/Dawson_Creek",
        "America\/Edmonton",
        "America\/Fort_Nelson",
        "America\/Glace_Bay",
        "America\/Goose_Bay",
        "America\/Halifax",
        "America\/Inuvik",
        "America\/Iqaluit",
        "America\/Moncton",
        "America\/Montreal",
        "America\/Nipigon",
        "America\/Pangnirtung",
        "America\/Rainy_River",
        "America\/Rankin_Inlet",
        "America\/Regina",
        "America\/Resolute",
        "America\/St_Johns",
        "America\/Swift_Current",
        "America\/Thunder_Bay",
        "America\/Toronto",
        "America\/Vancouver",
        "America\/Whitehorse",
        "America\/Winnipeg",
        "America\/Yellowknife"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: ar-Latn-CA-u-ca-dangi-co-phonebk-hc-h11-kf-lower-kn-false-nu-traditio

{
    "baseName": "ar-Latn-CA",
    "calendar": "dangi",
    "calendars": [
        "dangi"
    ],
    "caseFirst": "lower",
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": "h11",
    "hourCycles": [
        "h11"
    ],
    "language": "ar",
    "numberingSystem": "traditio",
    "numberingSystems": [
        "traditio"
    ],
    "numeric": false,
    "region": "CA",
    "script": "Latn",
    "textInfo": {
        "direction": "rtl"
    },
    "timeZones": [
        "America\/Blanc-Sablon",
        "America\/Cambridge_Bay",
        "America\/Coral_Harbour",
        "America\/Creston",
        "America\/Dawson",
        "America\/Dawson_Creek",
        "America\/Edmonton",
        "America\/Fort_Nelson",
        "America\/Glace_Bay",
        "America\/Goose_Bay",
        "America\/Halifax",
        "America\/Inuvik",
        "America\/Iqaluit",
        "America\/Moncton",
        "America\/Montreal",
        "America\/Nipigon",
        "America\/Pangnirtung",
        "America\/Rainy_River",
        "America\/Rankin_Inlet",
        "America\/Regina",
        "America\/Resolute",
        "America\/St_Johns",
        "America\/Swift_Current",
        "America\/Thunder_Bay",
        "America\/Toronto",
        "America\/Vancouver",
        "America\/Whitehorse",
        "America\/Winnipeg",
        "America\/Yellowknife"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: und-u-ca-buddhist

{
    "baseName": "und",
    "calendar": "buddhist",
    "calendars": [
        "buddhist"
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
    "language": null,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-ca-buddhist

{
    "baseName": "en-Latn-US",
    "calendar": "buddhist",
    "calendars": [
        "buddhist"
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-ca-buddhist

{
    "baseName": "en",
    "calendar": "buddhist",
    "calendars": [
        "buddhist"
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

========================================================================

Original: und-u-kf-lower

{
    "baseName": "und",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": "lower",
    "collation": null,
    "collations": [
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": null,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-kf-lower

{
    "baseName": "en-Latn-US",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": "lower",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-kf-lower

{
    "baseName": "en",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": "lower",
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

========================================================================

Original: und-u-kf-false

{
    "baseName": "und",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": "false",
    "collation": null,
    "collations": [
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": null,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-kf-false

{
    "baseName": "en-Latn-US",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": "false",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-kf-false

{
    "baseName": "en",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": "false",
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

========================================================================

Original: und-u-co-phonebk

{
    "baseName": "und",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": null,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-co-phonebk

{
    "baseName": "en-Latn-US",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-co-phonebk

{
    "baseName": "en",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": "phonebk",
    "collations": [
        "phonebk"
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

========================================================================

Original: und-u-hc-h11

{
    "baseName": "und",
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
    "hourCycle": "h11",
    "hourCycles": [
        "h11"
    ],
    "language": null,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-hc-h11

{
    "baseName": "en-Latn-US",
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
    "hourCycle": "h11",
    "hourCycles": [
        "h11"
    ],
    "language": "en",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-hc-h11

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
    "hourCycle": "h11",
    "hourCycles": [
        "h11"
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

========================================================================

Original: und-u-hc-h12

{
    "baseName": "und",
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
    "hourCycle": "h12",
    "hourCycles": [
        "h12"
    ],
    "language": null,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-hc-h12

{
    "baseName": "en-Latn-US",
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
    "hourCycle": "h12",
    "hourCycles": [
        "h12"
    ],
    "language": "en",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-hc-h12

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
    "hourCycle": "h12",
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

========================================================================

Original: und-u-hc-h23

{
    "baseName": "und",
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
    "hourCycle": "h23",
    "hourCycles": [
        "h23"
    ],
    "language": null,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-hc-h23

{
    "baseName": "en-Latn-US",
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
    "hourCycle": "h23",
    "hourCycles": [
        "h23"
    ],
    "language": "en",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-hc-h23

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
    "hourCycle": "h23",
    "hourCycles": [
        "h23"
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

========================================================================

Original: und-u-hc-h24

{
    "baseName": "und",
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
    "hourCycle": "h24",
    "hourCycles": [
        "h24"
    ],
    "language": null,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-hc-h24

{
    "baseName": "en-Latn-US",
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
    "hourCycle": "h24",
    "hourCycles": [
        "h24"
    ],
    "language": "en",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-hc-h24

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
    "hourCycle": "h24",
    "hourCycles": [
        "h24"
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

========================================================================

Original: fr

{
    "baseName": "fr",
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
        "h23"
    ],
    "language": "fr",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: fr-Latn-FR

{
    "baseName": "fr-Latn-FR",
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
        "h23"
    ],
    "language": "fr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "FR",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Paris"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: fr

{
    "baseName": "fr",
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
        "h23"
    ],
    "language": "fr",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: und-u-nu-thai

{
    "baseName": "und",
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
    "language": null,
    "numberingSystem": "thai",
    "numberingSystems": [
        "thai"
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-nu-thai

{
    "baseName": "en-Latn-US",
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
    "numberingSystem": "thai",
    "numberingSystems": [
        "thai"
    ],
    "numeric": false,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-nu-thai

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
    "numberingSystem": "thai",
    "numberingSystems": [
        "thai"
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

========================================================================

Original: und-u-kn

{
    "baseName": "und",
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
    "language": null,
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": true,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-kn

{
    "baseName": "en-Latn-US",
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
    "numeric": true,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-kn

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
    "numeric": true,
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

========================================================================

Original: und-u-kn-false

{
    "baseName": "und",
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
    "language": null,
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

------------------------------------------------------------------------

Maximized: en-Latn-US-u-kn-false

{
    "baseName": "en-Latn-US",
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
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: en-u-kn-false

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

========================================================================

Original: und-ES

{
    "baseName": "und-ES",
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
        "h23"
    ],
    "language": null,
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "ES",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Africa\/Ceuta",
        "Atlantic\/Canary",
        "Europe\/Madrid"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: es-Latn-ES

{
    "baseName": "es-Latn-ES",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "trad",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "es",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "ES",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Africa\/Ceuta",
        "Atlantic\/Canary",
        "Europe\/Madrid"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: es

{
    "baseName": "es",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "trad",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "es",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: de

{
    "baseName": "de",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "phonebk",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: de-Latn-DE

{
    "baseName": "de-Latn-DE",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "phonebk",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "DE",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Berlin",
        "Europe\/Busingen"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: de

{
    "baseName": "de",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "phonebk",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "de",
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
        "firstDay": 1,
        "minimalDays": 4,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: de-Latn-US

{
    "baseName": "de-Latn-US",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "phonebk",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: de-Latn-US

{
    "baseName": "de-Latn-US",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "phonebk",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": "Latn",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: de-US

{
    "baseName": "de-US",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "phonebk",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "de",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "US",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "America\/Adak",
        "America\/Anchorage",
        "America\/Boise",
        "America\/Chicago",
        "America\/Denver",
        "America\/Detroit",
        "America\/Indiana\/Knox",
        "America\/Indiana\/Marengo",
        "America\/Indiana\/Petersburg",
        "America\/Indiana\/Tell_City",
        "America\/Indiana\/Vevay",
        "America\/Indiana\/Vincennes",
        "America\/Indiana\/Winamac",
        "America\/Indianapolis",
        "America\/Juneau",
        "America\/Kentucky\/Monticello",
        "America\/Los_Angeles",
        "America\/Louisville",
        "America\/Menominee",
        "America\/Metlakatla",
        "America\/New_York",
        "America\/Nome",
        "America\/North_Dakota\/Beulah",
        "America\/North_Dakota\/Center",
        "America\/North_Dakota\/New_Salem",
        "America\/Phoenix",
        "America\/Sitka",
        "America\/Yakutat",
        "Pacific\/Honolulu"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: sr

{
    "baseName": "sr",
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
        "h23"
    ],
    "language": "sr",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: sr-Cyrl-RS

{
    "baseName": "sr-Cyrl-RS",
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
        "h23"
    ],
    "language": "sr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "RS",
    "script": "Cyrl",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Belgrade"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: sr

{
    "baseName": "sr",
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
        "h23"
    ],
    "language": "sr",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: sr-Cyrl-RS

{
    "baseName": "sr-Cyrl-RS",
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
        "h23"
    ],
    "language": "sr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "RS",
    "script": "Cyrl",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Belgrade"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: sr-Cyrl-RS

{
    "baseName": "sr-Cyrl-RS",
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
        "h23"
    ],
    "language": "sr",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "RS",
    "script": "Cyrl",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Europe\/Belgrade"
    ],
    "weekInfo": {
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: sr

{
    "baseName": "sr",
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
        "h23"
    ],
    "language": "sr",
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
        "firstDay": 1,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================

Original: zh-Hans

{
    "baseName": "zh-Hans",
    "calendar": null,
    "calendars": [
        "gregory",
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "pinyin",
        "big5han",
        "gb2312",
        "stroke",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": null,
    "script": "Hans",
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

------------------------------------------------------------------------

Maximized: zh-Hans-CN

{
    "baseName": "zh-Hans-CN",
    "calendar": null,
    "calendars": [
        "gregory",
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "pinyin",
        "big5han",
        "gb2312",
        "stroke",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "CN",
    "script": "Hans",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Shanghai",
        "Asia\/Urumqi"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: zh

{
    "baseName": "zh",
    "calendar": null,
    "calendars": [
        "gregory",
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "pinyin",
        "big5han",
        "gb2312",
        "stroke",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h23"
    ],
    "language": "zh",
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

========================================================================

Original: zh-Hant-TW

{
    "baseName": "zh-Hant-TW",
    "calendar": null,
    "calendars": [
        "gregory",
        "roc",
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "stroke",
        "big5han",
        "gb2312",
        "pinyin",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "zh",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "TW",
    "script": "Hant",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Taipei"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Maximized: zh-Hant-TW

{
    "baseName": "zh-Hant-TW",
    "calendar": null,
    "calendars": [
        "gregory",
        "roc",
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "stroke",
        "big5han",
        "gb2312",
        "pinyin",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "zh",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "TW",
    "script": "Hant",
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Taipei"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

------------------------------------------------------------------------

Minimized: zh-TW

{
    "baseName": "zh-TW",
    "calendar": null,
    "calendars": [
        "gregory",
        "roc",
        "chinese"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "stroke",
        "big5han",
        "gb2312",
        "pinyin",
        "unihan",
        "zhuyin",
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "zh",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": "TW",
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": [
        "Asia\/Taipei"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}

========================================================================
