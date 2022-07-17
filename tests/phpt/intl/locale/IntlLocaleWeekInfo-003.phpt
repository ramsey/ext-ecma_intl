--TEST--
Intl\Locale\WeekInfo throws ValueError for invalid weekend values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale\WeekDay;
use Ecma\Intl\Locale\WeekInfo;

new WeekInfo(WeekDay::Monday, 3, [WeekDay::Thursday, 'foo', WeekDay::Saturday]);
?>
--EXPECTF--
Fatal error: Uncaught ValueError: Argument $weekend must be an array of values of type Ecma\Intl\Locale\WeekDay %s
Stack trace:
#0 %s/tests/phpt/intl/locale/IntlLocaleWeekInfo-003.php(5): Ecma\Intl\Locale\WeekInfo->__construct(Object(Ecma\Intl\Locale\WeekDay), 3, Array)
#1 {main}
  thrown in %s/tests/phpt/intl/locale/IntlLocaleWeekInfo-003.php on line %d
