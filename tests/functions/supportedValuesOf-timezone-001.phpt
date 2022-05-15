--TEST--
Ecma\Intl\supportedValuesOf('timeZone')
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$timeZones = \Ecma\Intl\supportedValuesOf('timeZone');

if (count($timeZones) > 0) {
    printf("Has support for %d time zones.\n", count($timeZones));
} else {
    echo "Does not support any time zones.\n";
}

$tests = [
    'America/New_York',
    'Asia/Tokyo',
    'Europe/Paris',
    'GMT',
    'UTC',
];

foreach ($tests as $test) {
    if (in_array($test, $timeZones)) {
        printf("Found %s in time zone data.\n", $test);
    } else {
        printf("Could not find %s in time zone data.\n", $test);
    }
}
?>
--EXPECTF--
Has support for %d time zones.
Found America/New_York in time zone data.
Found Asia/Tokyo in time zone data.
Found Europe/Paris in time zone data.
Found GMT in time zone data.
Found UTC in time zone data.
