/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: fd1f522dc5f9bd7b0a52acb31a8d37e2620645f8 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Ecma_Intl_getCanonicalLocales, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_MASK(0, locales, MAY_BE_ARRAY|MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Ecma_Intl_getSupportedLocales, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(getCanonicalLocales);
ZEND_FUNCTION(getSupportedLocales);


static const zend_function_entry ext_functions[] = {
	ZEND_NS_FE("Ecma\\Intl", getCanonicalLocales, arginfo_Ecma_Intl_getCanonicalLocales)
	ZEND_NS_FE("Ecma\\Intl", getSupportedLocales, arginfo_Ecma_Intl_getSupportedLocales)
	ZEND_FE_END
};
