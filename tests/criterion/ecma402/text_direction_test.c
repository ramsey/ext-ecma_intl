#include "src/ecma402/text_direction.h"
#include "tests/criterion/test.h"

#define TEST_SUITE ecma402TextDirection

Test(TEST_SUITE, getsDefaultTextDirectionForUnknownLocale) {
  textDirection direction;

  direction = getTextDirection("foo");

  cr_assert(eq(int, direction, LEFT_TO_RIGHT));
}

Test(TEST_SUITE, getsDefaultTextDirectionForEnUs) {
  textDirection direction;
  direction = getTextDirection("en-US");
  cr_assert(eq(int, direction, LEFT_TO_RIGHT));
}

Test(TEST_SUITE, getsDefaultTextDirectionForFaIr) {
  textDirection direction;
  direction = getTextDirection("fa-IR");
  cr_assert(eq(int, direction, RIGHT_TO_LEFT));
}
