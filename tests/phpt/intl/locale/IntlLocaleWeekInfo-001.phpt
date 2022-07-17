--TEST--
Intl\Locale\WeekInfo instantiates with arguments
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale\WeekDay;
use Ecma\Intl\Locale\WeekInfo;

$weekInfo = new WeekInfo(WeekDay::Monday, 3, [WeekDay::Thursday, WeekDay::Saturday]);

assert(WeekDay::Monday === $weekInfo->firstDay);
assert(3 === $weekInfo->minimalDays);
assert([WeekDay::Thursday, WeekDay::Saturday] === $weekInfo->weekend);

echo json_encode($weekInfo->firstDay) . "\n";
echo json_encode($weekInfo->minimalDays) . "\n";
echo json_encode($weekInfo->weekend) . "\n";
?>
--EXPECT--
1
3
[4,6]
