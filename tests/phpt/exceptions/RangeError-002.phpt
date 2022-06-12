--TEST--
RangeError instantiates
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\RangeError;

$previous = new \Exception('A previous exception');
$rangeError = new RangeError('A range error', 32, $previous);

var_export($rangeError);
?>
--EXPECTF--
Ecma\Intl\RangeError::__set_state(array(
   'message' => 'A range error',
   'string' => '',
   'code' => 32,
   'file' => '%s/tests/phpt/exceptions/RangeError-002.php',
   'line' => %d,
   'trace' => 
  array (
  ),
   'previous' => 
  Exception::__set_state(array(
     'message' => 'A previous exception',
     'string' => '',
     'code' => 0,
     'file' => '%s/tests/phpt/exceptions/RangeError-002.php',
     'line' => %d,
     'trace' => 
    array (
    ),
     'previous' => NULL,
  )),
))
