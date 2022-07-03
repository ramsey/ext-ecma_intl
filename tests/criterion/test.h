#ifndef ECMA_INTL_TEST_H
#define ECMA_INTL_TEST_H

#include <criterion/criterion.h>

#include <criterion/new/assert.h>
#include <criterion/parameterized.h>

#include "src/common.h"

char *test_strdup(const char *str);
void test_freeStrings(struct criterion_test_params *crp);

#endif /* ECMA_INTL_TEST_H */
