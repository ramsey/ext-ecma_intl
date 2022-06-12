--TEST--
RangeError is a child of \ValueError
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Exception;
use Ecma\Intl\RangeError;

echo RangeError::class . "\n";
echo get_parent_class(RangeError::class) . "\n";
var_export(is_subclass_of(RangeError::class, Exception::class));
?>
--EXPECT--
Ecma\Intl\RangeError
ValueError
true
