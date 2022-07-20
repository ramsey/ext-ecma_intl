--TEST--
Intl is marked "final"
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl;

$reflect = new ReflectionClass(Intl::class);
assert($reflect->isFinal());

echo Intl::class . " is final\n";
?>
--EXPECT--
Ecma\Intl is final
