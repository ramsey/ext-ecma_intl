--TEST--
Intl\Locale\TextInfo instantiates with arguments
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale\TextDirection;
use Ecma\Intl\Locale\TextInfo;

$textInfo = new TextInfo(TextDirection::LeftToRight);
assert($textInfo->direction === TextDirection::LeftToRight);

echo json_encode($textInfo->direction->value) . "\n";
?>
--EXPECT--
"ltr"
