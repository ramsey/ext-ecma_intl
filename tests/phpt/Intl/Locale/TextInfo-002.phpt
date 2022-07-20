--TEST--
Intl\Locale\TextInfo is marked "final"
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale\TextInfo;

$reflect = new ReflectionClass(TextInfo::class);
assert($reflect->isFinal());

echo TextInfo::class . " is final\n";
?>
--EXPECT--
Ecma\Intl\Locale\TextInfo is final
