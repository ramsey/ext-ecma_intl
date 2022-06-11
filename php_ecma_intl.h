/* ecma_intl extension for PHP (c) 2022 Ben Ramsey <ben@benramsey.com> */

#ifndef PHP_ECMA_INTL_H
# define PHP_ECMA_INTL_H

extern zend_module_entry ecma_intl_module_entry;
# define phpext_ecma_intl_ptr &ecma_intl_module_entry

# define PHP_ECMA_INTL_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_ECMA_INTL)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_ECMA_INTL_H */
