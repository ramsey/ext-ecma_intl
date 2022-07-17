--TEST--
Intl\Locale\WeekInfo allows an empty array for weekend values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale\WeekDay;
use Ecma\Intl\Locale\WeekInfo;

$weekInfo = new WeekInfo(WeekDay::Tuesday, 5, []);

assert(WeekDay::Tuesday === $weekInfo->firstDay);
assert(5 === $weekInfo->minimalDays);
assert([] === $weekInfo->weekend);

echo json_encode($weekInfo->firstDay) . "\n";
echo json_encode($weekInfo->minimalDays) . "\n";
echo json_encode($weekInfo->weekend) . "\n";
?>
--EXPECT--
2
5
[]
