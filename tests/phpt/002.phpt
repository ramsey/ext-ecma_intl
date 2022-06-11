--TEST--
test1() Basic test
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension ecma_intl is loaded and working!
NULL
