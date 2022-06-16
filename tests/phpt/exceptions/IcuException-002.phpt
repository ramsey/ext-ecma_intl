--TEST--
IcuException instantiates
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\IcuException;

$previous = new \Exception('A previous exception');
$icuException = new IcuException('An ICU exception', 36, $previous);

var_export($icuException);
?>
--EXPECTF--
Ecma\Intl\IcuException::__set_state(array(
   'message' => 'An ICU exception',
   'string' => '',
   'code' => 36,
   'file' => '%s/tests/phpt/exceptions/IcuException-002.php',
   'line' => %d,
   'trace' => 
  array (
  ),
   'previous' => 
  Exception::__set_state(array(
     'message' => 'A previous exception',
     'string' => '',
     'code' => 0,
     'file' => '%s/tests/phpt/exceptions/IcuException-002.php',
     'line' => %d,
     'trace' => 
    array (
    ),
     'previous' => NULL,
  )),
))
