#include "test.h"

char *testStrdup(const char *str) {
  char *ptr = cr_malloc(strlen(str) + 1);
  if (ptr) {
    strcpy(ptr, str);
  }
  return ptr;
}

int addBasicTest(basicTestParams *tests, int index, const char *input,
                 const char *expected) {
  if (input == NULL) {
    tests[index].input = NULL;
  } else {
    tests[index].input = testStrdup(input);
  }

  if (expected == NULL) {
    tests[index].expected = NULL;
  } else {
    tests[index].expected = testStrdup(expected);
  }

  return ++index;
}

void freeBasicTestParams(struct criterion_test_params *crp) {
  basicTestParams *params = (basicTestParams *)crp->params;

  for (size_t i = 0; i < crp->length; ++i) {
    if (params[i].input) {
      cr_free(params[i].input);
    }

    if (params[i].expected) {
      cr_free(params[i].expected);
    }
  }

  cr_free(params);
}

void testFreeStrings(struct criterion_test_params *crp) {
  char **strings = (char **)crp->params;
  for (size_t i = 0; i < crp->length; ++i) {
    cr_free(strings[i]);
  }
  cr_free(strings);
}
