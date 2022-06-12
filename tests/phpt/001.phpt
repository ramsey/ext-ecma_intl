--TEST--
Check if ecma_intl is loaded
--EXTENSIONS--
ecma_intl
--FILE--
<?php
var_export(extension_loaded('ecma_intl'));
?>
--EXPECT--
true
