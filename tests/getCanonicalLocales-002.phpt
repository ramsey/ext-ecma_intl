--TEST--
Ecma\Intl\getCanonicalLocales() with empty array
--EXTENSIONS--
ecma_intl
--FILE--
<?php
var_dump(\Ecma\Intl\getCanonicalLocales([]));
?>
--EXPECT--
array(0) {
}

