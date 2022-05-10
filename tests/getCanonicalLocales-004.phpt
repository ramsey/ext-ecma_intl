--TEST--
Ecma\Intl\getCanonicalLocales() canonicalizes to BCP47 language tags
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$tests = [
    ['en_us', 'de_de'],
    ['en-latn-us'],
    ['en-blah-foo-x-baz'],
    ['zh-cmn-Hans-CN-boont-u-kf-lower-co-trad-kn-false-ca-buddhist-nu-latn-hc-h24'],
    ['cmn_Hans_CN_BOONT@calendar=buddhist;colcasefirst=lower;collation=traditional;colnumeric=no;hours=h24;numbers=latn'],
];

foreach ($tests as $test) {
    var_dump(\Ecma\Intl\getCanonicalLocales($test));
}
?>
--EXPECT--
array(2) {
  [0]=>
  string(5) "en-US"
  [1]=>
  string(5) "de-DE"
}
array(1) {
  [0]=>
  string(10) "en-Latn-US"
}
array(1) {
  [0]=>
  string(7) "en-Blah"
}
array(1) {
  [0]=>
  string(72) "cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-false-nu-latn"
}
array(1) {
  [0]=>
  string(72) "cmn-Hans-CN-boont-u-ca-buddhist-co-trad-hc-h24-kf-lower-kn-false-nu-latn"
}
