--TEST--
Check Ecma\Intl\Exception is a child of \Exception
--EXTENSIONS--
ecma_intl
--FILE--
<?php
var_dump(\Ecma\Intl\Exception::class);
var_dump(get_parent_class(\Ecma\Intl\Exception::class));
?>
--EXPECT--
string(19) "Ecma\Intl\Exception"
string(9) "Exception"
