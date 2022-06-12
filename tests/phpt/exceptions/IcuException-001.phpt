--TEST--
IcuException is a child of \RuntimeException
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Exception;
use Ecma\Intl\IcuException;

echo IcuException::class . "\n";
echo get_parent_class(IcuException::class) . "\n";
var_export(is_subclass_of(IcuException::class, Exception::class));
?>
--EXPECT--
Ecma\Intl\IcuException
RuntimeException
true
