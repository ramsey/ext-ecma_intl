/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: a8d240892b2bf497289b3dc6a9140d83bad63704 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Ecma_Intl_getCanonicalLocales, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_MASK(0, locales, MAY_BE_ARRAY|MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Ecma_Intl_supportedValuesOf, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, category, Ecma\\Intl\\Category, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Ecma_Intl___construct, 0, 0, 0)
ZEND_END_ARG_INFO()


ZEND_METHOD(Ecma_Intl, getCanonicalLocales);
ZEND_METHOD(Ecma_Intl, supportedValuesOf);
ZEND_METHOD(Ecma_Intl, __construct);


static const zend_function_entry class_Ecma_Intl_methods[] = {
	ZEND_ME(Ecma_Intl, getCanonicalLocales, arginfo_class_Ecma_Intl_getCanonicalLocales, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Ecma_Intl, supportedValuesOf, arginfo_class_Ecma_Intl_supportedValuesOf, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Ecma_Intl, __construct, arginfo_class_Ecma_Intl___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_Category_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_Exception_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_IcuException_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_RangeError_methods[] = {
	ZEND_FE_END
};

static zend_class_entry *register_class_Ecma_Intl(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Ecma", "Intl", class_Ecma_Intl_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_Category(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("Ecma\\Intl\\Category", IS_STRING, class_Ecma_Intl_Category_methods);

	zval enum_case_Calendar_value;
	zend_string *enum_case_Calendar_value_str = zend_string_init("calendar", sizeof("calendar") - 1, 1);
	ZVAL_STR(&enum_case_Calendar_value, enum_case_Calendar_value_str);
	zend_enum_add_case_cstr(class_entry, "Calendar", &enum_case_Calendar_value);

	zval enum_case_Collation_value;
	zend_string *enum_case_Collation_value_str = zend_string_init("collation", sizeof("collation") - 1, 1);
	ZVAL_STR(&enum_case_Collation_value, enum_case_Collation_value_str);
	zend_enum_add_case_cstr(class_entry, "Collation", &enum_case_Collation_value);

	zval enum_case_Currency_value;
	zend_string *enum_case_Currency_value_str = zend_string_init("currency", sizeof("currency") - 1, 1);
	ZVAL_STR(&enum_case_Currency_value, enum_case_Currency_value_str);
	zend_enum_add_case_cstr(class_entry, "Currency", &enum_case_Currency_value);

	zval enum_case_NumberingSystem_value;
	zend_string *enum_case_NumberingSystem_value_str = zend_string_init("numberingSystem", sizeof("numberingSystem") - 1, 1);
	ZVAL_STR(&enum_case_NumberingSystem_value, enum_case_NumberingSystem_value_str);
	zend_enum_add_case_cstr(class_entry, "NumberingSystem", &enum_case_NumberingSystem_value);

	zval enum_case_TimeZone_value;
	zend_string *enum_case_TimeZone_value_str = zend_string_init("timeZone", sizeof("timeZone") - 1, 1);
	ZVAL_STR(&enum_case_TimeZone_value, enum_case_TimeZone_value_str);
	zend_enum_add_case_cstr(class_entry, "TimeZone", &enum_case_TimeZone_value);

	zval enum_case_Unit_value;
	zend_string *enum_case_Unit_value_str = zend_string_init("unit", sizeof("unit") - 1, 1);
	ZVAL_STR(&enum_case_Unit_value, enum_case_Unit_value_str);
	zend_enum_add_case_cstr(class_entry, "Unit", &enum_case_Unit_value);

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_Exception(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Ecma\\Intl", "Exception", class_Ecma_Intl_Exception_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_IcuException(zend_class_entry *class_entry_RuntimeException, zend_class_entry *class_entry_Ecma_Intl_Exception)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Ecma\\Intl", "IcuException", class_Ecma_Intl_IcuException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	zend_class_implements(class_entry, 1, class_entry_Ecma_Intl_Exception);

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_RangeError(zend_class_entry *class_entry_ValueError, zend_class_entry *class_entry_Ecma_Intl_Exception)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Ecma\\Intl", "RangeError", class_Ecma_Intl_RangeError_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_ValueError);
	zend_class_implements(class_entry, 1, class_entry_Ecma_Intl_Exception);

	return class_entry;
}
