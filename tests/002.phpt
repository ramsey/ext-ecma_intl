--TEST--
Check ecma_intl information in phpinfo()
--EXTENSIONS--
ecma_intl
--SKIPIF--
<?php if (PHP_SAPI !== 'cli') exit('Skipped: This test requires the CLI SAPI.'); ?>
--FILE--
<?php
phpinfo(INFO_MODULES);
?>
--EXPECTF--
%a

ecma_intl

Internationalization Support, Ecma-style (ECMA-402) => enabled
ICU version => %f
ICU Data version => %f
ICU TZData version => %r(\d{4}[a-z]{1})|n\/a%r
ICU Unicode version => %f

%a
