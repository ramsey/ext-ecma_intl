--TEST--
Intl\Locale\WeekInfo is marked "final"
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale\WeekInfo;

$reflect = new ReflectionClass(WeekInfo::class);
assert($reflect->isFinal());

echo WeekInfo::class . " is final\n";
?>
--EXPECT--
Ecma\Intl\Locale\WeekInfo is final
