--TEST--
Ecma\Intl\getCanonicalLocales() with array
--EXTENSIONS--
ecma_intl
--FILE--
<?php
var_dump(\Ecma\Intl\getCanonicalLocales(['en-US']));
var_dump(\Ecma\Intl\getCanonicalLocales(['en-US', 'de-DE']));
var_dump(\Ecma\Intl\getCanonicalLocales(['en-US', 'de-DE', 'es-MX', 'fr-FR']));
?>
--EXPECT--
array(1) {
  [0]=>
  string(5) "en-US"
}
array(2) {
  [0]=>
  string(5) "en-US"
  [1]=>
  string(5) "de-DE"
}
array(4) {
  [0]=>
  string(5) "en-US"
  [1]=>
  string(5) "de-DE"
  [2]=>
  string(5) "es-MX"
  [3]=>
  string(5) "fr-FR"
}
