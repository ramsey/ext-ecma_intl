--TEST--
Exception is an interface in Ecma\Intl
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Exception;

echo Exception::class . "\n";
?>
--EXPECT--
Ecma\Intl\Exception
