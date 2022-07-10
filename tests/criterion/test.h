#ifndef ECMA_INTL_TEST_H
#define ECMA_INTL_TEST_H

#include <criterion/criterion.h>

#include <criterion/new/assert.h>
#include <criterion/parameterized.h>

#include "src/common.h"

#define BASIC_PARAMETERIZED_TEST(name, function)                               \
  ParameterizedTest(basicTestParams *test, TEST_SUITE, name) {                 \
    const char *caseName = function(test->input);                              \
    if (test->expected == NULL) {                                              \
      cr_assert_null(caseName);                                                \
    } else {                                                                   \
      cr_assert(eq(str, (char *)caseName, test->expected),                     \
                "Expected case \"%s\" for value \"%s\"; got \"%s\"",           \
                test->expected, test->input, caseName);                        \
    }                                                                          \
  }

#define START_BASIC_TEST_PARAMS(testCount)                                     \
  basicTestParams *tests;                                                      \
  int index = 0;                                                               \
  tests = cr_malloc(testCount * sizeof(basicTestParams));

#define BASIC_TEST(input, expected)                                            \
  index = addBasicTest(tests, index, input, expected);

#define END_BASIC_TEST_PARAMS                                                  \
  return cr_make_param_array(basicTestParams, tests, index, freeBasicTestParams)

typedef struct basicTestParams basicTestParams;

struct basicTestParams {
  char *input;
  char *expected;
};

char *testStrdup(const char *str);
int addBasicTest(basicTestParams *tests, int index, const char *input,
                 const char *expected);
void freeBasicTestParams(struct criterion_test_params *crp);
void testFreeStrings(struct criterion_test_params *crp);

#endif /* ECMA_INTL_TEST_H */
