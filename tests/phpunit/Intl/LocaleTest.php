<?php

namespace Ecma\Test\Intl;

use Ecma\Intl\Calendar;
use Ecma\Intl\CaseFirst;
use Ecma\Intl\Collation;
use Ecma\Intl\HourCycle;
use Ecma\Intl\Locale;
use Ecma\Intl\NumberingSystem;
use Ecma\Intl\RangeError;
use Ecma\Test\TestCase;

class LocaleTest extends TestCase
{
    public function testInitializesPropertiesWithBasicLocale(): void
    {
        $locale = new Locale('en');

        $this->assertSame('en', $locale->baseName);
        $this->assertNull($locale->calendar);
        $this->assertSame([Calendar::Gregory], $locale->calendars);
        $this->assertNull($locale->caseFirst);
        $this->assertNull($locale->collation);
        $this->assertSame([Collation::Emoji, Collation::Eor], $locale->collations);
        $this->assertNull($locale->hourCycle);
        $this->assertSame([HourCycle::H12], $locale->hourCycles);
        $this->assertNull($locale->numberingSystem);
        $this->assertSame([NumberingSystem::Latn], $locale->numberingSystems);
        $this->assertFalse($locale->numeric);
        $this->assertNull($locale->region);
        $this->assertNull($locale->script);
        $this->assertInstanceOf(Locale\TextInfo::class, $locale->textInfo);
        $this->assertSame(Locale\TextDirection::LeftToRight, $locale->textInfo->direction);
        $this->assertNull($locale->timeZones);
        $this->assertInstanceOf(Locale\WeekInfo::class, $locale->weekInfo);
        $this->assertSame(Locale\WeekDay::Sunday, $locale->weekInfo->firstDay);
        $this->assertSame(1, $locale->weekInfo->minimalDays);
        $this->assertSame([Locale\WeekDay::Saturday, Locale\WeekDay::Sunday], $locale->weekInfo->weekend);
    }

    /**
     * @dataProvider throwsRangeErrorForInvalidValuesProvider
     */
    public function testThrowsRangeErrorForInvalidValues(
        string $tag,
        ?Locale\Options $options = null,
        ?string $message = null,
    ): void {
        if ($message === null) {
            $message = 'invalid language tag: ' . $tag;
        }

        $this->expectException(RangeError::class);
        $this->expectExceptionMessage($message);

        new Locale($tag, $options);
    }

    /**
     * @return array<array{tag: string, options?: Locale\Options | null, message?: string | null}>
     */
    public function throwsRangeErrorForInvalidValuesProvider(): array
    {
        return [
            ['tag' => ''],
            ['tag' => 'de-de_euro'],
            ['tag' => '123'],
            ['tag' => 'en-latn-x'],
            ['tag' => 'zh-cmn-CH'],
            ['tag' => 'i-test'],
            ['tag' => 'ja-jp-jp'],
            ['tag' => 'boguslang'],
            ['tag' => 'und-varzero-var1-vartwo'],
            ['tag' => 'de-1901-1901'],
            ['tag' => 'de-DE-1901-1901'],
            ['tag' => 'hant-cmn-cn'],
            ['tag' => 'zh-cmn-TW'],
            ['tag' => 'en-gb-oed'],
            ['tag' => 'invalid tag'],
            ['tag' => 'invalid tag', 'options' => new Locale\Options()],
            ['tag' => '', 'options' => new Locale\Options()],
            [
                'tag' => 'en',
                'options' => new Locale\Options(language: 'invalid language'),
                'message' => 'language is not a well-formed language value',
            ],
            [
                'tag' => 'und',
                'options' => new Locale\Options(language: ''),
                'message' => 'language is not a well-formed language value',
            ],
            [
                'tag' => 'en',
                'options' => new Locale\Options(region: 'Great Britain'),
                'message' => 'region is not a well-formed region value',
            ],
            [
                'tag' => 'und',
                'options' => new Locale\Options(region: ''),
                'message' => 'region is not a well-formed region value',
            ],
            [
                'tag' => 'en',
                'options' => new Locale\Options(script: 'invalid'),
                'message' => 'script is not a well-formed script value',
            ],
            [
                'tag' => 'und',
                'options' => new Locale\Options(script: ''),
                'message' => 'script is not a well-formed script value',
            ],
        ];
    }

    /**
     * @dataProvider tagsAndOptionsProvider
     */
    public function testTagsAndOptions(string $tag, string $expected, ?Locale\Options $options = null): void
    {
        $locale = new Locale($tag, $options);

        $this->assertSame($expected, $locale->toString());
        $this->assertSame($expected, (string) $locale);
        $this->assertMatchesJsonSnapshot($locale);
    }

    /**
     * @dataProvider tagsAndOptionsProvider
     */
    public function testMaximize(string $tag, string $expected, ?Locale\Options $options = null): void
    {
        $locale = new Locale($tag, $options);
        $maximizedLocale = $locale->maximize();

        $this->assertNotSame($locale, $maximizedLocale);
        $this->assertMatchesJsonSnapshot($maximizedLocale);
    }

    /**
     * @dataProvider tagsAndOptionsProvider
     */
    public function testMinimize(string $tag, string $expected, ?Locale\Options $options = null): void
    {
        $locale = new Locale($tag, $options);
        $minimizedLocale = $locale->minimize();

        $this->assertNotSame($locale, $minimizedLocale);
        $this->assertMatchesJsonSnapshot($minimizedLocale);
    }

    /**
     * @return array<array{tag: string, expected: string, options?: Locale\Options}>
     */
    public function tagsAndOptionsProvider(): array
    {
        return [
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
    }
}
