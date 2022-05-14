--TEST--
Ecma\Intl\getCanonicalLocales() with string
--EXTENSIONS--
ecma_intl
--FILE--
<?php
var_dump(\Ecma\Intl\getCanonicalLocales('en-US'));
var_dump(\Ecma\Intl\getCanonicalLocales('de-DE'));
var_dump(\Ecma\Intl\getCanonicalLocales('fr-FR'));
?>
--EXPECT--
array(1) {
  [0]=>
  string(5) "en-US"
}
array(1) {
  [0]=>
  string(5) "de-DE"
}
array(1) {
  [0]=>
  string(5) "fr-FR"
}
