#include <php.h>

PHP_FUNCTION(test1) {
  ZEND_PARSE_PARAMETERS_NONE();

  php_printf("The extension %s is loaded and working!\r\n", "ecma_intl");
}

PHP_FUNCTION(test2) {
  char *var = "World";
  size_t var_len = sizeof("World") - 1;
  zend_string *retval;

  ZEND_PARSE_PARAMETERS_START(0, 1)
  Z_PARAM_OPTIONAL
  Z_PARAM_STRING(var, var_len)
  ZEND_PARSE_PARAMETERS_END();

  retval = strpprintf(0, "Hello %s", var);

  RETURN_STR(retval);
}