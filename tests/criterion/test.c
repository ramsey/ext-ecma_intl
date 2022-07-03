#include "test.h"

char *test_strdup(const char *str) {
  char *ptr = cr_malloc(strlen(str) + 1);
  if (ptr) {
    strcpy(ptr, str);
  }
  return ptr;
}

void test_freeStrings(struct criterion_test_params *crp) {
  char **strings = (char **)crp->params;
  for (size_t i = 0; i < crp->length; ++i) {
    cr_free(strings[i]);
  }
  cr_free(strings);
}
