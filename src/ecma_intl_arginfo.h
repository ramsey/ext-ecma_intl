/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: f61bd29454a9ffb9d2b059997d11890216706e2d */

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


static const zend_function_entry class_Ecma_Intl_Calendar_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_Category_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_CaseFirst_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_Collation_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_Exception_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_Formatting_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_HourCycle_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_IcuException_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_NumberingSystem_methods[] = {
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

static zend_class_entry *register_class_Ecma_Intl_Calendar(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("Ecma\\Intl\\Calendar", IS_STRING, class_Ecma_Intl_Calendar_methods);

	zval enum_case_Buddhist_value;
	zend_string *enum_case_Buddhist_value_str = zend_string_init("buddhist", sizeof("buddhist") - 1, 1);
	ZVAL_STR(&enum_case_Buddhist_value, enum_case_Buddhist_value_str);
	zend_enum_add_case_cstr(class_entry, "Buddhist", &enum_case_Buddhist_value);

	zval enum_case_Chinese_value;
	zend_string *enum_case_Chinese_value_str = zend_string_init("chinese", sizeof("chinese") - 1, 1);
	ZVAL_STR(&enum_case_Chinese_value, enum_case_Chinese_value_str);
	zend_enum_add_case_cstr(class_entry, "Chinese", &enum_case_Chinese_value);

	zval enum_case_Coptic_value;
	zend_string *enum_case_Coptic_value_str = zend_string_init("coptic", sizeof("coptic") - 1, 1);
	ZVAL_STR(&enum_case_Coptic_value, enum_case_Coptic_value_str);
	zend_enum_add_case_cstr(class_entry, "Coptic", &enum_case_Coptic_value);

	zval enum_case_Dangi_value;
	zend_string *enum_case_Dangi_value_str = zend_string_init("dangi", sizeof("dangi") - 1, 1);
	ZVAL_STR(&enum_case_Dangi_value, enum_case_Dangi_value_str);
	zend_enum_add_case_cstr(class_entry, "Dangi", &enum_case_Dangi_value);

	zval enum_case_Ethioaa_value;
	zend_string *enum_case_Ethioaa_value_str = zend_string_init("ethioaa", sizeof("ethioaa") - 1, 1);
	ZVAL_STR(&enum_case_Ethioaa_value, enum_case_Ethioaa_value_str);
	zend_enum_add_case_cstr(class_entry, "Ethioaa", &enum_case_Ethioaa_value);

	zval enum_case_Ethiopic_value;
	zend_string *enum_case_Ethiopic_value_str = zend_string_init("ethiopic", sizeof("ethiopic") - 1, 1);
	ZVAL_STR(&enum_case_Ethiopic_value, enum_case_Ethiopic_value_str);
	zend_enum_add_case_cstr(class_entry, "Ethiopic", &enum_case_Ethiopic_value);

	zval enum_case_Gregory_value;
	zend_string *enum_case_Gregory_value_str = zend_string_init("gregory", sizeof("gregory") - 1, 1);
	ZVAL_STR(&enum_case_Gregory_value, enum_case_Gregory_value_str);
	zend_enum_add_case_cstr(class_entry, "Gregory", &enum_case_Gregory_value);

	zval enum_case_Hebrew_value;
	zend_string *enum_case_Hebrew_value_str = zend_string_init("hebrew", sizeof("hebrew") - 1, 1);
	ZVAL_STR(&enum_case_Hebrew_value, enum_case_Hebrew_value_str);
	zend_enum_add_case_cstr(class_entry, "Hebrew", &enum_case_Hebrew_value);

	zval enum_case_Indian_value;
	zend_string *enum_case_Indian_value_str = zend_string_init("indian", sizeof("indian") - 1, 1);
	ZVAL_STR(&enum_case_Indian_value, enum_case_Indian_value_str);
	zend_enum_add_case_cstr(class_entry, "Indian", &enum_case_Indian_value);

	zval enum_case_Islamic_value;
	zend_string *enum_case_Islamic_value_str = zend_string_init("islamic", sizeof("islamic") - 1, 1);
	ZVAL_STR(&enum_case_Islamic_value, enum_case_Islamic_value_str);
	zend_enum_add_case_cstr(class_entry, "Islamic", &enum_case_Islamic_value);

	zval enum_case_IslamicCivil_value;
	zend_string *enum_case_IslamicCivil_value_str = zend_string_init("islamic-civil", sizeof("islamic-civil") - 1, 1);
	ZVAL_STR(&enum_case_IslamicCivil_value, enum_case_IslamicCivil_value_str);
	zend_enum_add_case_cstr(class_entry, "IslamicCivil", &enum_case_IslamicCivil_value);

	zval enum_case_IslamicRgsa_value;
	zend_string *enum_case_IslamicRgsa_value_str = zend_string_init("islamic-rgsa", sizeof("islamic-rgsa") - 1, 1);
	ZVAL_STR(&enum_case_IslamicRgsa_value, enum_case_IslamicRgsa_value_str);
	zend_enum_add_case_cstr(class_entry, "IslamicRgsa", &enum_case_IslamicRgsa_value);

	zval enum_case_IslamicTbla_value;
	zend_string *enum_case_IslamicTbla_value_str = zend_string_init("islamic-tbla", sizeof("islamic-tbla") - 1, 1);
	ZVAL_STR(&enum_case_IslamicTbla_value, enum_case_IslamicTbla_value_str);
	zend_enum_add_case_cstr(class_entry, "IslamicTbla", &enum_case_IslamicTbla_value);

	zval enum_case_IslamicUmalqura_value;
	zend_string *enum_case_IslamicUmalqura_value_str = zend_string_init("islamic-umalqura", sizeof("islamic-umalqura") - 1, 1);
	ZVAL_STR(&enum_case_IslamicUmalqura_value, enum_case_IslamicUmalqura_value_str);
	zend_enum_add_case_cstr(class_entry, "IslamicUmalqura", &enum_case_IslamicUmalqura_value);

	zval enum_case_Iso8601_value;
	zend_string *enum_case_Iso8601_value_str = zend_string_init("iso8601", sizeof("iso8601") - 1, 1);
	ZVAL_STR(&enum_case_Iso8601_value, enum_case_Iso8601_value_str);
	zend_enum_add_case_cstr(class_entry, "Iso8601", &enum_case_Iso8601_value);

	zval enum_case_Japanese_value;
	zend_string *enum_case_Japanese_value_str = zend_string_init("japanese", sizeof("japanese") - 1, 1);
	ZVAL_STR(&enum_case_Japanese_value, enum_case_Japanese_value_str);
	zend_enum_add_case_cstr(class_entry, "Japanese", &enum_case_Japanese_value);

	zval enum_case_Persian_value;
	zend_string *enum_case_Persian_value_str = zend_string_init("persian", sizeof("persian") - 1, 1);
	ZVAL_STR(&enum_case_Persian_value, enum_case_Persian_value_str);
	zend_enum_add_case_cstr(class_entry, "Persian", &enum_case_Persian_value);

	zval enum_case_Roc_value;
	zend_string *enum_case_Roc_value_str = zend_string_init("roc", sizeof("roc") - 1, 1);
	ZVAL_STR(&enum_case_Roc_value, enum_case_Roc_value_str);
	zend_enum_add_case_cstr(class_entry, "Roc", &enum_case_Roc_value);

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

static zend_class_entry *register_class_Ecma_Intl_CaseFirst(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("Ecma\\Intl\\CaseFirst", IS_STRING, class_Ecma_Intl_CaseFirst_methods);

	zval enum_case_False_value;
	zend_string *enum_case_False_value_str = zend_string_init("false", sizeof("false") - 1, 1);
	ZVAL_STR(&enum_case_False_value, enum_case_False_value_str);
	zend_enum_add_case_cstr(class_entry, "False", &enum_case_False_value);

	zval enum_case_Lower_value;
	zend_string *enum_case_Lower_value_str = zend_string_init("lower", sizeof("lower") - 1, 1);
	ZVAL_STR(&enum_case_Lower_value, enum_case_Lower_value_str);
	zend_enum_add_case_cstr(class_entry, "Lower", &enum_case_Lower_value);

	zval enum_case_Upper_value;
	zend_string *enum_case_Upper_value_str = zend_string_init("upper", sizeof("upper") - 1, 1);
	ZVAL_STR(&enum_case_Upper_value, enum_case_Upper_value_str);
	zend_enum_add_case_cstr(class_entry, "Upper", &enum_case_Upper_value);

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_Collation(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("Ecma\\Intl\\Collation", IS_STRING, class_Ecma_Intl_Collation_methods);

	zval enum_case_Big5han_value;
	zend_string *enum_case_Big5han_value_str = zend_string_init("big5han", sizeof("big5han") - 1, 1);
	ZVAL_STR(&enum_case_Big5han_value, enum_case_Big5han_value_str);
	zend_enum_add_case_cstr(class_entry, "Big5han", &enum_case_Big5han_value);

	zval enum_case_Compat_value;
	zend_string *enum_case_Compat_value_str = zend_string_init("compat", sizeof("compat") - 1, 1);
	ZVAL_STR(&enum_case_Compat_value, enum_case_Compat_value_str);
	zend_enum_add_case_cstr(class_entry, "Compat", &enum_case_Compat_value);

	zval enum_case_Dict_value;
	zend_string *enum_case_Dict_value_str = zend_string_init("dict", sizeof("dict") - 1, 1);
	ZVAL_STR(&enum_case_Dict_value, enum_case_Dict_value_str);
	zend_enum_add_case_cstr(class_entry, "Dict", &enum_case_Dict_value);

	zval enum_case_Direct_value;
	zend_string *enum_case_Direct_value_str = zend_string_init("direct", sizeof("direct") - 1, 1);
	ZVAL_STR(&enum_case_Direct_value, enum_case_Direct_value_str);
	zend_enum_add_case_cstr(class_entry, "Direct", &enum_case_Direct_value);

	zval enum_case_Ducet_value;
	zend_string *enum_case_Ducet_value_str = zend_string_init("ducet", sizeof("ducet") - 1, 1);
	ZVAL_STR(&enum_case_Ducet_value, enum_case_Ducet_value_str);
	zend_enum_add_case_cstr(class_entry, "Ducet", &enum_case_Ducet_value);

	zval enum_case_Emoji_value;
	zend_string *enum_case_Emoji_value_str = zend_string_init("emoji", sizeof("emoji") - 1, 1);
	ZVAL_STR(&enum_case_Emoji_value, enum_case_Emoji_value_str);
	zend_enum_add_case_cstr(class_entry, "Emoji", &enum_case_Emoji_value);

	zval enum_case_Eor_value;
	zend_string *enum_case_Eor_value_str = zend_string_init("eor", sizeof("eor") - 1, 1);
	ZVAL_STR(&enum_case_Eor_value, enum_case_Eor_value_str);
	zend_enum_add_case_cstr(class_entry, "Eor", &enum_case_Eor_value);

	zval enum_case_Gb2312_value;
	zend_string *enum_case_Gb2312_value_str = zend_string_init("gb2312", sizeof("gb2312") - 1, 1);
	ZVAL_STR(&enum_case_Gb2312_value, enum_case_Gb2312_value_str);
	zend_enum_add_case_cstr(class_entry, "Gb2312", &enum_case_Gb2312_value);

	zval enum_case_Phonebk_value;
	zend_string *enum_case_Phonebk_value_str = zend_string_init("phonebk", sizeof("phonebk") - 1, 1);
	ZVAL_STR(&enum_case_Phonebk_value, enum_case_Phonebk_value_str);
	zend_enum_add_case_cstr(class_entry, "Phonebk", &enum_case_Phonebk_value);

	zval enum_case_Phonetic_value;
	zend_string *enum_case_Phonetic_value_str = zend_string_init("phonetic", sizeof("phonetic") - 1, 1);
	ZVAL_STR(&enum_case_Phonetic_value, enum_case_Phonetic_value_str);
	zend_enum_add_case_cstr(class_entry, "Phonetic", &enum_case_Phonetic_value);

	zval enum_case_Pinyin_value;
	zend_string *enum_case_Pinyin_value_str = zend_string_init("pinyin", sizeof("pinyin") - 1, 1);
	ZVAL_STR(&enum_case_Pinyin_value, enum_case_Pinyin_value_str);
	zend_enum_add_case_cstr(class_entry, "Pinyin", &enum_case_Pinyin_value);

	zval enum_case_Reformed_value;
	zend_string *enum_case_Reformed_value_str = zend_string_init("reformed", sizeof("reformed") - 1, 1);
	ZVAL_STR(&enum_case_Reformed_value, enum_case_Reformed_value_str);
	zend_enum_add_case_cstr(class_entry, "Reformed", &enum_case_Reformed_value);

	zval enum_case_Search_value;
	zend_string *enum_case_Search_value_str = zend_string_init("search", sizeof("search") - 1, 1);
	ZVAL_STR(&enum_case_Search_value, enum_case_Search_value_str);
	zend_enum_add_case_cstr(class_entry, "Search", &enum_case_Search_value);

	zval enum_case_Searchjl_value;
	zend_string *enum_case_Searchjl_value_str = zend_string_init("searchjl", sizeof("searchjl") - 1, 1);
	ZVAL_STR(&enum_case_Searchjl_value, enum_case_Searchjl_value_str);
	zend_enum_add_case_cstr(class_entry, "Searchjl", &enum_case_Searchjl_value);

	zval enum_case_Standard_value;
	zend_string *enum_case_Standard_value_str = zend_string_init("standard", sizeof("standard") - 1, 1);
	ZVAL_STR(&enum_case_Standard_value, enum_case_Standard_value_str);
	zend_enum_add_case_cstr(class_entry, "Standard", &enum_case_Standard_value);

	zval enum_case_Stroke_value;
	zend_string *enum_case_Stroke_value_str = zend_string_init("stroke", sizeof("stroke") - 1, 1);
	ZVAL_STR(&enum_case_Stroke_value, enum_case_Stroke_value_str);
	zend_enum_add_case_cstr(class_entry, "Stroke", &enum_case_Stroke_value);

	zval enum_case_Trad_value;
	zend_string *enum_case_Trad_value_str = zend_string_init("trad", sizeof("trad") - 1, 1);
	ZVAL_STR(&enum_case_Trad_value, enum_case_Trad_value_str);
	zend_enum_add_case_cstr(class_entry, "Trad", &enum_case_Trad_value);

	zval enum_case_Unihan_value;
	zend_string *enum_case_Unihan_value_str = zend_string_init("unihan", sizeof("unihan") - 1, 1);
	ZVAL_STR(&enum_case_Unihan_value, enum_case_Unihan_value_str);
	zend_enum_add_case_cstr(class_entry, "Unihan", &enum_case_Unihan_value);

	zval enum_case_Zhuyin_value;
	zend_string *enum_case_Zhuyin_value_str = zend_string_init("zhuyin", sizeof("zhuyin") - 1, 1);
	ZVAL_STR(&enum_case_Zhuyin_value, enum_case_Zhuyin_value_str);
	zend_enum_add_case_cstr(class_entry, "Zhuyin", &enum_case_Zhuyin_value);

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_Exception(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Ecma\\Intl", "Exception", class_Ecma_Intl_Exception_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_Formatting(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("Ecma\\Intl\\Formatting", IS_STRING, class_Ecma_Intl_Formatting_methods);

	zval enum_case_Long_value;
	zend_string *enum_case_Long_value_str = zend_string_init("long", sizeof("long") - 1, 1);
	ZVAL_STR(&enum_case_Long_value, enum_case_Long_value_str);
	zend_enum_add_case_cstr(class_entry, "Long", &enum_case_Long_value);

	zval enum_case_Narrow_value;
	zend_string *enum_case_Narrow_value_str = zend_string_init("narrow", sizeof("narrow") - 1, 1);
	ZVAL_STR(&enum_case_Narrow_value, enum_case_Narrow_value_str);
	zend_enum_add_case_cstr(class_entry, "Narrow", &enum_case_Narrow_value);

	zval enum_case_Short_value;
	zend_string *enum_case_Short_value_str = zend_string_init("short", sizeof("short") - 1, 1);
	ZVAL_STR(&enum_case_Short_value, enum_case_Short_value_str);
	zend_enum_add_case_cstr(class_entry, "Short", &enum_case_Short_value);

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_HourCycle(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("Ecma\\Intl\\HourCycle", IS_STRING, class_Ecma_Intl_HourCycle_methods);

	zval enum_case_H11_value;
	zend_string *enum_case_H11_value_str = zend_string_init("h11", sizeof("h11") - 1, 1);
	ZVAL_STR(&enum_case_H11_value, enum_case_H11_value_str);
	zend_enum_add_case_cstr(class_entry, "H11", &enum_case_H11_value);

	zval enum_case_H12_value;
	zend_string *enum_case_H12_value_str = zend_string_init("h12", sizeof("h12") - 1, 1);
	ZVAL_STR(&enum_case_H12_value, enum_case_H12_value_str);
	zend_enum_add_case_cstr(class_entry, "H12", &enum_case_H12_value);

	zval enum_case_H23_value;
	zend_string *enum_case_H23_value_str = zend_string_init("h23", sizeof("h23") - 1, 1);
	ZVAL_STR(&enum_case_H23_value, enum_case_H23_value_str);
	zend_enum_add_case_cstr(class_entry, "H23", &enum_case_H23_value);

	zval enum_case_H24_value;
	zend_string *enum_case_H24_value_str = zend_string_init("h24", sizeof("h24") - 1, 1);
	ZVAL_STR(&enum_case_H24_value, enum_case_H24_value_str);
	zend_enum_add_case_cstr(class_entry, "H24", &enum_case_H24_value);

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

static zend_class_entry *register_class_Ecma_Intl_NumberingSystem(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("Ecma\\Intl\\NumberingSystem", IS_STRING, class_Ecma_Intl_NumberingSystem_methods);

	zval enum_case_Adlm_value;
	zend_string *enum_case_Adlm_value_str = zend_string_init("adlm", sizeof("adlm") - 1, 1);
	ZVAL_STR(&enum_case_Adlm_value, enum_case_Adlm_value_str);
	zend_enum_add_case_cstr(class_entry, "Adlm", &enum_case_Adlm_value);

	zval enum_case_Ahom_value;
	zend_string *enum_case_Ahom_value_str = zend_string_init("ahom", sizeof("ahom") - 1, 1);
	ZVAL_STR(&enum_case_Ahom_value, enum_case_Ahom_value_str);
	zend_enum_add_case_cstr(class_entry, "Ahom", &enum_case_Ahom_value);

	zval enum_case_Arab_value;
	zend_string *enum_case_Arab_value_str = zend_string_init("arab", sizeof("arab") - 1, 1);
	ZVAL_STR(&enum_case_Arab_value, enum_case_Arab_value_str);
	zend_enum_add_case_cstr(class_entry, "Arab", &enum_case_Arab_value);

	zval enum_case_Arabext_value;
	zend_string *enum_case_Arabext_value_str = zend_string_init("arabext", sizeof("arabext") - 1, 1);
	ZVAL_STR(&enum_case_Arabext_value, enum_case_Arabext_value_str);
	zend_enum_add_case_cstr(class_entry, "Arabext", &enum_case_Arabext_value);

	zval enum_case_Armn_value;
	zend_string *enum_case_Armn_value_str = zend_string_init("armn", sizeof("armn") - 1, 1);
	ZVAL_STR(&enum_case_Armn_value, enum_case_Armn_value_str);
	zend_enum_add_case_cstr(class_entry, "Armn", &enum_case_Armn_value);

	zval enum_case_Armnlow_value;
	zend_string *enum_case_Armnlow_value_str = zend_string_init("armnlow", sizeof("armnlow") - 1, 1);
	ZVAL_STR(&enum_case_Armnlow_value, enum_case_Armnlow_value_str);
	zend_enum_add_case_cstr(class_entry, "Armnlow", &enum_case_Armnlow_value);

	zval enum_case_Bali_value;
	zend_string *enum_case_Bali_value_str = zend_string_init("bali", sizeof("bali") - 1, 1);
	ZVAL_STR(&enum_case_Bali_value, enum_case_Bali_value_str);
	zend_enum_add_case_cstr(class_entry, "Bali", &enum_case_Bali_value);

	zval enum_case_Beng_value;
	zend_string *enum_case_Beng_value_str = zend_string_init("beng", sizeof("beng") - 1, 1);
	ZVAL_STR(&enum_case_Beng_value, enum_case_Beng_value_str);
	zend_enum_add_case_cstr(class_entry, "Beng", &enum_case_Beng_value);

	zval enum_case_Bhks_value;
	zend_string *enum_case_Bhks_value_str = zend_string_init("bhks", sizeof("bhks") - 1, 1);
	ZVAL_STR(&enum_case_Bhks_value, enum_case_Bhks_value_str);
	zend_enum_add_case_cstr(class_entry, "Bhks", &enum_case_Bhks_value);

	zval enum_case_Brah_value;
	zend_string *enum_case_Brah_value_str = zend_string_init("brah", sizeof("brah") - 1, 1);
	ZVAL_STR(&enum_case_Brah_value, enum_case_Brah_value_str);
	zend_enum_add_case_cstr(class_entry, "Brah", &enum_case_Brah_value);

	zval enum_case_Cakm_value;
	zend_string *enum_case_Cakm_value_str = zend_string_init("cakm", sizeof("cakm") - 1, 1);
	ZVAL_STR(&enum_case_Cakm_value, enum_case_Cakm_value_str);
	zend_enum_add_case_cstr(class_entry, "Cakm", &enum_case_Cakm_value);

	zval enum_case_Cham_value;
	zend_string *enum_case_Cham_value_str = zend_string_init("cham", sizeof("cham") - 1, 1);
	ZVAL_STR(&enum_case_Cham_value, enum_case_Cham_value_str);
	zend_enum_add_case_cstr(class_entry, "Cham", &enum_case_Cham_value);

	zval enum_case_Cyrl_value;
	zend_string *enum_case_Cyrl_value_str = zend_string_init("cyrl", sizeof("cyrl") - 1, 1);
	ZVAL_STR(&enum_case_Cyrl_value, enum_case_Cyrl_value_str);
	zend_enum_add_case_cstr(class_entry, "Cyrl", &enum_case_Cyrl_value);

	zval enum_case_Deva_value;
	zend_string *enum_case_Deva_value_str = zend_string_init("deva", sizeof("deva") - 1, 1);
	ZVAL_STR(&enum_case_Deva_value, enum_case_Deva_value_str);
	zend_enum_add_case_cstr(class_entry, "Deva", &enum_case_Deva_value);

	zval enum_case_Diak_value;
	zend_string *enum_case_Diak_value_str = zend_string_init("diak", sizeof("diak") - 1, 1);
	ZVAL_STR(&enum_case_Diak_value, enum_case_Diak_value_str);
	zend_enum_add_case_cstr(class_entry, "Diak", &enum_case_Diak_value);

	zval enum_case_Ethi_value;
	zend_string *enum_case_Ethi_value_str = zend_string_init("ethi", sizeof("ethi") - 1, 1);
	ZVAL_STR(&enum_case_Ethi_value, enum_case_Ethi_value_str);
	zend_enum_add_case_cstr(class_entry, "Ethi", &enum_case_Ethi_value);

	zval enum_case_Finance_value;
	zend_string *enum_case_Finance_value_str = zend_string_init("finance", sizeof("finance") - 1, 1);
	ZVAL_STR(&enum_case_Finance_value, enum_case_Finance_value_str);
	zend_enum_add_case_cstr(class_entry, "Finance", &enum_case_Finance_value);

	zval enum_case_Fullwide_value;
	zend_string *enum_case_Fullwide_value_str = zend_string_init("fullwide", sizeof("fullwide") - 1, 1);
	ZVAL_STR(&enum_case_Fullwide_value, enum_case_Fullwide_value_str);
	zend_enum_add_case_cstr(class_entry, "Fullwide", &enum_case_Fullwide_value);

	zval enum_case_Geor_value;
	zend_string *enum_case_Geor_value_str = zend_string_init("geor", sizeof("geor") - 1, 1);
	ZVAL_STR(&enum_case_Geor_value, enum_case_Geor_value_str);
	zend_enum_add_case_cstr(class_entry, "Geor", &enum_case_Geor_value);

	zval enum_case_Gong_value;
	zend_string *enum_case_Gong_value_str = zend_string_init("gong", sizeof("gong") - 1, 1);
	ZVAL_STR(&enum_case_Gong_value, enum_case_Gong_value_str);
	zend_enum_add_case_cstr(class_entry, "Gong", &enum_case_Gong_value);

	zval enum_case_Gonm_value;
	zend_string *enum_case_Gonm_value_str = zend_string_init("gonm", sizeof("gonm") - 1, 1);
	ZVAL_STR(&enum_case_Gonm_value, enum_case_Gonm_value_str);
	zend_enum_add_case_cstr(class_entry, "Gonm", &enum_case_Gonm_value);

	zval enum_case_Grek_value;
	zend_string *enum_case_Grek_value_str = zend_string_init("grek", sizeof("grek") - 1, 1);
	ZVAL_STR(&enum_case_Grek_value, enum_case_Grek_value_str);
	zend_enum_add_case_cstr(class_entry, "Grek", &enum_case_Grek_value);

	zval enum_case_Greklow_value;
	zend_string *enum_case_Greklow_value_str = zend_string_init("greklow", sizeof("greklow") - 1, 1);
	ZVAL_STR(&enum_case_Greklow_value, enum_case_Greklow_value_str);
	zend_enum_add_case_cstr(class_entry, "Greklow", &enum_case_Greklow_value);

	zval enum_case_Gujr_value;
	zend_string *enum_case_Gujr_value_str = zend_string_init("gujr", sizeof("gujr") - 1, 1);
	ZVAL_STR(&enum_case_Gujr_value, enum_case_Gujr_value_str);
	zend_enum_add_case_cstr(class_entry, "Gujr", &enum_case_Gujr_value);

	zval enum_case_Guru_value;
	zend_string *enum_case_Guru_value_str = zend_string_init("guru", sizeof("guru") - 1, 1);
	ZVAL_STR(&enum_case_Guru_value, enum_case_Guru_value_str);
	zend_enum_add_case_cstr(class_entry, "Guru", &enum_case_Guru_value);

	zval enum_case_Hanidays_value;
	zend_string *enum_case_Hanidays_value_str = zend_string_init("hanidays", sizeof("hanidays") - 1, 1);
	ZVAL_STR(&enum_case_Hanidays_value, enum_case_Hanidays_value_str);
	zend_enum_add_case_cstr(class_entry, "Hanidays", &enum_case_Hanidays_value);

	zval enum_case_Hanidec_value;
	zend_string *enum_case_Hanidec_value_str = zend_string_init("hanidec", sizeof("hanidec") - 1, 1);
	ZVAL_STR(&enum_case_Hanidec_value, enum_case_Hanidec_value_str);
	zend_enum_add_case_cstr(class_entry, "Hanidec", &enum_case_Hanidec_value);

	zval enum_case_Hans_value;
	zend_string *enum_case_Hans_value_str = zend_string_init("hans", sizeof("hans") - 1, 1);
	ZVAL_STR(&enum_case_Hans_value, enum_case_Hans_value_str);
	zend_enum_add_case_cstr(class_entry, "Hans", &enum_case_Hans_value);

	zval enum_case_Hansfin_value;
	zend_string *enum_case_Hansfin_value_str = zend_string_init("hansfin", sizeof("hansfin") - 1, 1);
	ZVAL_STR(&enum_case_Hansfin_value, enum_case_Hansfin_value_str);
	zend_enum_add_case_cstr(class_entry, "Hansfin", &enum_case_Hansfin_value);

	zval enum_case_Hant_value;
	zend_string *enum_case_Hant_value_str = zend_string_init("hant", sizeof("hant") - 1, 1);
	ZVAL_STR(&enum_case_Hant_value, enum_case_Hant_value_str);
	zend_enum_add_case_cstr(class_entry, "Hant", &enum_case_Hant_value);

	zval enum_case_Hantfin_value;
	zend_string *enum_case_Hantfin_value_str = zend_string_init("hantfin", sizeof("hantfin") - 1, 1);
	ZVAL_STR(&enum_case_Hantfin_value, enum_case_Hantfin_value_str);
	zend_enum_add_case_cstr(class_entry, "Hantfin", &enum_case_Hantfin_value);

	zval enum_case_Hebr_value;
	zend_string *enum_case_Hebr_value_str = zend_string_init("hebr", sizeof("hebr") - 1, 1);
	ZVAL_STR(&enum_case_Hebr_value, enum_case_Hebr_value_str);
	zend_enum_add_case_cstr(class_entry, "Hebr", &enum_case_Hebr_value);

	zval enum_case_Hmng_value;
	zend_string *enum_case_Hmng_value_str = zend_string_init("hmng", sizeof("hmng") - 1, 1);
	ZVAL_STR(&enum_case_Hmng_value, enum_case_Hmng_value_str);
	zend_enum_add_case_cstr(class_entry, "Hmng", &enum_case_Hmng_value);

	zval enum_case_Hmnp_value;
	zend_string *enum_case_Hmnp_value_str = zend_string_init("hmnp", sizeof("hmnp") - 1, 1);
	ZVAL_STR(&enum_case_Hmnp_value, enum_case_Hmnp_value_str);
	zend_enum_add_case_cstr(class_entry, "Hmnp", &enum_case_Hmnp_value);

	zval enum_case_Java_value;
	zend_string *enum_case_Java_value_str = zend_string_init("java", sizeof("java") - 1, 1);
	ZVAL_STR(&enum_case_Java_value, enum_case_Java_value_str);
	zend_enum_add_case_cstr(class_entry, "Java", &enum_case_Java_value);

	zval enum_case_Jpan_value;
	zend_string *enum_case_Jpan_value_str = zend_string_init("jpan", sizeof("jpan") - 1, 1);
	ZVAL_STR(&enum_case_Jpan_value, enum_case_Jpan_value_str);
	zend_enum_add_case_cstr(class_entry, "Jpan", &enum_case_Jpan_value);

	zval enum_case_Jpanfin_value;
	zend_string *enum_case_Jpanfin_value_str = zend_string_init("jpanfin", sizeof("jpanfin") - 1, 1);
	ZVAL_STR(&enum_case_Jpanfin_value, enum_case_Jpanfin_value_str);
	zend_enum_add_case_cstr(class_entry, "Jpanfin", &enum_case_Jpanfin_value);

	zval enum_case_Jpanyear_value;
	zend_string *enum_case_Jpanyear_value_str = zend_string_init("jpanyear", sizeof("jpanyear") - 1, 1);
	ZVAL_STR(&enum_case_Jpanyear_value, enum_case_Jpanyear_value_str);
	zend_enum_add_case_cstr(class_entry, "Jpanyear", &enum_case_Jpanyear_value);

	zval enum_case_Kali_value;
	zend_string *enum_case_Kali_value_str = zend_string_init("kali", sizeof("kali") - 1, 1);
	ZVAL_STR(&enum_case_Kali_value, enum_case_Kali_value_str);
	zend_enum_add_case_cstr(class_entry, "Kali", &enum_case_Kali_value);

	zval enum_case_Kawi_value;
	zend_string *enum_case_Kawi_value_str = zend_string_init("kawi", sizeof("kawi") - 1, 1);
	ZVAL_STR(&enum_case_Kawi_value, enum_case_Kawi_value_str);
	zend_enum_add_case_cstr(class_entry, "Kawi", &enum_case_Kawi_value);

	zval enum_case_Khmr_value;
	zend_string *enum_case_Khmr_value_str = zend_string_init("khmr", sizeof("khmr") - 1, 1);
	ZVAL_STR(&enum_case_Khmr_value, enum_case_Khmr_value_str);
	zend_enum_add_case_cstr(class_entry, "Khmr", &enum_case_Khmr_value);

	zval enum_case_Knda_value;
	zend_string *enum_case_Knda_value_str = zend_string_init("knda", sizeof("knda") - 1, 1);
	ZVAL_STR(&enum_case_Knda_value, enum_case_Knda_value_str);
	zend_enum_add_case_cstr(class_entry, "Knda", &enum_case_Knda_value);

	zval enum_case_Lana_value;
	zend_string *enum_case_Lana_value_str = zend_string_init("lana", sizeof("lana") - 1, 1);
	ZVAL_STR(&enum_case_Lana_value, enum_case_Lana_value_str);
	zend_enum_add_case_cstr(class_entry, "Lana", &enum_case_Lana_value);

	zval enum_case_Lanatham_value;
	zend_string *enum_case_Lanatham_value_str = zend_string_init("lanatham", sizeof("lanatham") - 1, 1);
	ZVAL_STR(&enum_case_Lanatham_value, enum_case_Lanatham_value_str);
	zend_enum_add_case_cstr(class_entry, "Lanatham", &enum_case_Lanatham_value);

	zval enum_case_Laoo_value;
	zend_string *enum_case_Laoo_value_str = zend_string_init("laoo", sizeof("laoo") - 1, 1);
	ZVAL_STR(&enum_case_Laoo_value, enum_case_Laoo_value_str);
	zend_enum_add_case_cstr(class_entry, "Laoo", &enum_case_Laoo_value);

	zval enum_case_Latn_value;
	zend_string *enum_case_Latn_value_str = zend_string_init("latn", sizeof("latn") - 1, 1);
	ZVAL_STR(&enum_case_Latn_value, enum_case_Latn_value_str);
	zend_enum_add_case_cstr(class_entry, "Latn", &enum_case_Latn_value);

	zval enum_case_Lepc_value;
	zend_string *enum_case_Lepc_value_str = zend_string_init("lepc", sizeof("lepc") - 1, 1);
	ZVAL_STR(&enum_case_Lepc_value, enum_case_Lepc_value_str);
	zend_enum_add_case_cstr(class_entry, "Lepc", &enum_case_Lepc_value);

	zval enum_case_Limb_value;
	zend_string *enum_case_Limb_value_str = zend_string_init("limb", sizeof("limb") - 1, 1);
	ZVAL_STR(&enum_case_Limb_value, enum_case_Limb_value_str);
	zend_enum_add_case_cstr(class_entry, "Limb", &enum_case_Limb_value);

	zval enum_case_Mathbold_value;
	zend_string *enum_case_Mathbold_value_str = zend_string_init("mathbold", sizeof("mathbold") - 1, 1);
	ZVAL_STR(&enum_case_Mathbold_value, enum_case_Mathbold_value_str);
	zend_enum_add_case_cstr(class_entry, "Mathbold", &enum_case_Mathbold_value);

	zval enum_case_Mathdbl_value;
	zend_string *enum_case_Mathdbl_value_str = zend_string_init("mathdbl", sizeof("mathdbl") - 1, 1);
	ZVAL_STR(&enum_case_Mathdbl_value, enum_case_Mathdbl_value_str);
	zend_enum_add_case_cstr(class_entry, "Mathdbl", &enum_case_Mathdbl_value);

	zval enum_case_Mathmono_value;
	zend_string *enum_case_Mathmono_value_str = zend_string_init("mathmono", sizeof("mathmono") - 1, 1);
	ZVAL_STR(&enum_case_Mathmono_value, enum_case_Mathmono_value_str);
	zend_enum_add_case_cstr(class_entry, "Mathmono", &enum_case_Mathmono_value);

	zval enum_case_Mathsanb_value;
	zend_string *enum_case_Mathsanb_value_str = zend_string_init("mathsanb", sizeof("mathsanb") - 1, 1);
	ZVAL_STR(&enum_case_Mathsanb_value, enum_case_Mathsanb_value_str);
	zend_enum_add_case_cstr(class_entry, "Mathsanb", &enum_case_Mathsanb_value);

	zval enum_case_Mathsans_value;
	zend_string *enum_case_Mathsans_value_str = zend_string_init("mathsans", sizeof("mathsans") - 1, 1);
	ZVAL_STR(&enum_case_Mathsans_value, enum_case_Mathsans_value_str);
	zend_enum_add_case_cstr(class_entry, "Mathsans", &enum_case_Mathsans_value);

	zval enum_case_Mlym_value;
	zend_string *enum_case_Mlym_value_str = zend_string_init("mlym", sizeof("mlym") - 1, 1);
	ZVAL_STR(&enum_case_Mlym_value, enum_case_Mlym_value_str);
	zend_enum_add_case_cstr(class_entry, "Mlym", &enum_case_Mlym_value);

	zval enum_case_Modi_value;
	zend_string *enum_case_Modi_value_str = zend_string_init("modi", sizeof("modi") - 1, 1);
	ZVAL_STR(&enum_case_Modi_value, enum_case_Modi_value_str);
	zend_enum_add_case_cstr(class_entry, "Modi", &enum_case_Modi_value);

	zval enum_case_Mong_value;
	zend_string *enum_case_Mong_value_str = zend_string_init("mong", sizeof("mong") - 1, 1);
	ZVAL_STR(&enum_case_Mong_value, enum_case_Mong_value_str);
	zend_enum_add_case_cstr(class_entry, "Mong", &enum_case_Mong_value);

	zval enum_case_Mroo_value;
	zend_string *enum_case_Mroo_value_str = zend_string_init("mroo", sizeof("mroo") - 1, 1);
	ZVAL_STR(&enum_case_Mroo_value, enum_case_Mroo_value_str);
	zend_enum_add_case_cstr(class_entry, "Mroo", &enum_case_Mroo_value);

	zval enum_case_Mtei_value;
	zend_string *enum_case_Mtei_value_str = zend_string_init("mtei", sizeof("mtei") - 1, 1);
	ZVAL_STR(&enum_case_Mtei_value, enum_case_Mtei_value_str);
	zend_enum_add_case_cstr(class_entry, "Mtei", &enum_case_Mtei_value);

	zval enum_case_Mymr_value;
	zend_string *enum_case_Mymr_value_str = zend_string_init("mymr", sizeof("mymr") - 1, 1);
	ZVAL_STR(&enum_case_Mymr_value, enum_case_Mymr_value_str);
	zend_enum_add_case_cstr(class_entry, "Mymr", &enum_case_Mymr_value);

	zval enum_case_Mymrshan_value;
	zend_string *enum_case_Mymrshan_value_str = zend_string_init("mymrshan", sizeof("mymrshan") - 1, 1);
	ZVAL_STR(&enum_case_Mymrshan_value, enum_case_Mymrshan_value_str);
	zend_enum_add_case_cstr(class_entry, "Mymrshan", &enum_case_Mymrshan_value);

	zval enum_case_Mymrtlng_value;
	zend_string *enum_case_Mymrtlng_value_str = zend_string_init("mymrtlng", sizeof("mymrtlng") - 1, 1);
	ZVAL_STR(&enum_case_Mymrtlng_value, enum_case_Mymrtlng_value_str);
	zend_enum_add_case_cstr(class_entry, "Mymrtlng", &enum_case_Mymrtlng_value);

	zval enum_case_Nagm_value;
	zend_string *enum_case_Nagm_value_str = zend_string_init("nagm", sizeof("nagm") - 1, 1);
	ZVAL_STR(&enum_case_Nagm_value, enum_case_Nagm_value_str);
	zend_enum_add_case_cstr(class_entry, "Nagm", &enum_case_Nagm_value);

	zval enum_case_Native_value;
	zend_string *enum_case_Native_value_str = zend_string_init("native", sizeof("native") - 1, 1);
	ZVAL_STR(&enum_case_Native_value, enum_case_Native_value_str);
	zend_enum_add_case_cstr(class_entry, "Native", &enum_case_Native_value);

	zval enum_case_Newa_value;
	zend_string *enum_case_Newa_value_str = zend_string_init("newa", sizeof("newa") - 1, 1);
	ZVAL_STR(&enum_case_Newa_value, enum_case_Newa_value_str);
	zend_enum_add_case_cstr(class_entry, "Newa", &enum_case_Newa_value);

	zval enum_case_Nkoo_value;
	zend_string *enum_case_Nkoo_value_str = zend_string_init("nkoo", sizeof("nkoo") - 1, 1);
	ZVAL_STR(&enum_case_Nkoo_value, enum_case_Nkoo_value_str);
	zend_enum_add_case_cstr(class_entry, "Nkoo", &enum_case_Nkoo_value);

	zval enum_case_Olck_value;
	zend_string *enum_case_Olck_value_str = zend_string_init("olck", sizeof("olck") - 1, 1);
	ZVAL_STR(&enum_case_Olck_value, enum_case_Olck_value_str);
	zend_enum_add_case_cstr(class_entry, "Olck", &enum_case_Olck_value);

	zval enum_case_Orya_value;
	zend_string *enum_case_Orya_value_str = zend_string_init("orya", sizeof("orya") - 1, 1);
	ZVAL_STR(&enum_case_Orya_value, enum_case_Orya_value_str);
	zend_enum_add_case_cstr(class_entry, "Orya", &enum_case_Orya_value);

	zval enum_case_Osma_value;
	zend_string *enum_case_Osma_value_str = zend_string_init("osma", sizeof("osma") - 1, 1);
	ZVAL_STR(&enum_case_Osma_value, enum_case_Osma_value_str);
	zend_enum_add_case_cstr(class_entry, "Osma", &enum_case_Osma_value);

	zval enum_case_Rohg_value;
	zend_string *enum_case_Rohg_value_str = zend_string_init("rohg", sizeof("rohg") - 1, 1);
	ZVAL_STR(&enum_case_Rohg_value, enum_case_Rohg_value_str);
	zend_enum_add_case_cstr(class_entry, "Rohg", &enum_case_Rohg_value);

	zval enum_case_Roman_value;
	zend_string *enum_case_Roman_value_str = zend_string_init("roman", sizeof("roman") - 1, 1);
	ZVAL_STR(&enum_case_Roman_value, enum_case_Roman_value_str);
	zend_enum_add_case_cstr(class_entry, "Roman", &enum_case_Roman_value);

	zval enum_case_Romanlow_value;
	zend_string *enum_case_Romanlow_value_str = zend_string_init("romanlow", sizeof("romanlow") - 1, 1);
	ZVAL_STR(&enum_case_Romanlow_value, enum_case_Romanlow_value_str);
	zend_enum_add_case_cstr(class_entry, "Romanlow", &enum_case_Romanlow_value);

	zval enum_case_Saur_value;
	zend_string *enum_case_Saur_value_str = zend_string_init("saur", sizeof("saur") - 1, 1);
	ZVAL_STR(&enum_case_Saur_value, enum_case_Saur_value_str);
	zend_enum_add_case_cstr(class_entry, "Saur", &enum_case_Saur_value);

	zval enum_case_Segment_value;
	zend_string *enum_case_Segment_value_str = zend_string_init("segment", sizeof("segment") - 1, 1);
	ZVAL_STR(&enum_case_Segment_value, enum_case_Segment_value_str);
	zend_enum_add_case_cstr(class_entry, "Segment", &enum_case_Segment_value);

	zval enum_case_Shrd_value;
	zend_string *enum_case_Shrd_value_str = zend_string_init("shrd", sizeof("shrd") - 1, 1);
	ZVAL_STR(&enum_case_Shrd_value, enum_case_Shrd_value_str);
	zend_enum_add_case_cstr(class_entry, "Shrd", &enum_case_Shrd_value);

	zval enum_case_Sind_value;
	zend_string *enum_case_Sind_value_str = zend_string_init("sind", sizeof("sind") - 1, 1);
	ZVAL_STR(&enum_case_Sind_value, enum_case_Sind_value_str);
	zend_enum_add_case_cstr(class_entry, "Sind", &enum_case_Sind_value);

	zval enum_case_Sinh_value;
	zend_string *enum_case_Sinh_value_str = zend_string_init("sinh", sizeof("sinh") - 1, 1);
	ZVAL_STR(&enum_case_Sinh_value, enum_case_Sinh_value_str);
	zend_enum_add_case_cstr(class_entry, "Sinh", &enum_case_Sinh_value);

	zval enum_case_Sora_value;
	zend_string *enum_case_Sora_value_str = zend_string_init("sora", sizeof("sora") - 1, 1);
	ZVAL_STR(&enum_case_Sora_value, enum_case_Sora_value_str);
	zend_enum_add_case_cstr(class_entry, "Sora", &enum_case_Sora_value);

	zval enum_case_Sund_value;
	zend_string *enum_case_Sund_value_str = zend_string_init("sund", sizeof("sund") - 1, 1);
	ZVAL_STR(&enum_case_Sund_value, enum_case_Sund_value_str);
	zend_enum_add_case_cstr(class_entry, "Sund", &enum_case_Sund_value);

	zval enum_case_Takr_value;
	zend_string *enum_case_Takr_value_str = zend_string_init("takr", sizeof("takr") - 1, 1);
	ZVAL_STR(&enum_case_Takr_value, enum_case_Takr_value_str);
	zend_enum_add_case_cstr(class_entry, "Takr", &enum_case_Takr_value);

	zval enum_case_Talu_value;
	zend_string *enum_case_Talu_value_str = zend_string_init("talu", sizeof("talu") - 1, 1);
	ZVAL_STR(&enum_case_Talu_value, enum_case_Talu_value_str);
	zend_enum_add_case_cstr(class_entry, "Talu", &enum_case_Talu_value);

	zval enum_case_Taml_value;
	zend_string *enum_case_Taml_value_str = zend_string_init("taml", sizeof("taml") - 1, 1);
	ZVAL_STR(&enum_case_Taml_value, enum_case_Taml_value_str);
	zend_enum_add_case_cstr(class_entry, "Taml", &enum_case_Taml_value);

	zval enum_case_Tamldec_value;
	zend_string *enum_case_Tamldec_value_str = zend_string_init("tamldec", sizeof("tamldec") - 1, 1);
	ZVAL_STR(&enum_case_Tamldec_value, enum_case_Tamldec_value_str);
	zend_enum_add_case_cstr(class_entry, "Tamldec", &enum_case_Tamldec_value);

	zval enum_case_Telu_value;
	zend_string *enum_case_Telu_value_str = zend_string_init("telu", sizeof("telu") - 1, 1);
	ZVAL_STR(&enum_case_Telu_value, enum_case_Telu_value_str);
	zend_enum_add_case_cstr(class_entry, "Telu", &enum_case_Telu_value);

	zval enum_case_Thai_value;
	zend_string *enum_case_Thai_value_str = zend_string_init("thai", sizeof("thai") - 1, 1);
	ZVAL_STR(&enum_case_Thai_value, enum_case_Thai_value_str);
	zend_enum_add_case_cstr(class_entry, "Thai", &enum_case_Thai_value);

	zval enum_case_Tibt_value;
	zend_string *enum_case_Tibt_value_str = zend_string_init("tibt", sizeof("tibt") - 1, 1);
	ZVAL_STR(&enum_case_Tibt_value, enum_case_Tibt_value_str);
	zend_enum_add_case_cstr(class_entry, "Tibt", &enum_case_Tibt_value);

	zval enum_case_Tirh_value;
	zend_string *enum_case_Tirh_value_str = zend_string_init("tirh", sizeof("tirh") - 1, 1);
	ZVAL_STR(&enum_case_Tirh_value, enum_case_Tirh_value_str);
	zend_enum_add_case_cstr(class_entry, "Tirh", &enum_case_Tirh_value);

	zval enum_case_Tnsa_value;
	zend_string *enum_case_Tnsa_value_str = zend_string_init("tnsa", sizeof("tnsa") - 1, 1);
	ZVAL_STR(&enum_case_Tnsa_value, enum_case_Tnsa_value_str);
	zend_enum_add_case_cstr(class_entry, "Tnsa", &enum_case_Tnsa_value);

	zval enum_case_Traditio_value;
	zend_string *enum_case_Traditio_value_str = zend_string_init("traditio", sizeof("traditio") - 1, 1);
	ZVAL_STR(&enum_case_Traditio_value, enum_case_Traditio_value_str);
	zend_enum_add_case_cstr(class_entry, "Traditio", &enum_case_Traditio_value);

	zval enum_case_Vaii_value;
	zend_string *enum_case_Vaii_value_str = zend_string_init("vaii", sizeof("vaii") - 1, 1);
	ZVAL_STR(&enum_case_Vaii_value, enum_case_Vaii_value_str);
	zend_enum_add_case_cstr(class_entry, "Vaii", &enum_case_Vaii_value);

	zval enum_case_Wara_value;
	zend_string *enum_case_Wara_value_str = zend_string_init("wara", sizeof("wara") - 1, 1);
	ZVAL_STR(&enum_case_Wara_value, enum_case_Wara_value_str);
	zend_enum_add_case_cstr(class_entry, "Wara", &enum_case_Wara_value);

	zval enum_case_Wcho_value;
	zend_string *enum_case_Wcho_value_str = zend_string_init("wcho", sizeof("wcho") - 1, 1);
	ZVAL_STR(&enum_case_Wcho_value, enum_case_Wcho_value_str);
	zend_enum_add_case_cstr(class_entry, "Wcho", &enum_case_Wcho_value);

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
