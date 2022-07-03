#include "src/common.h"
#include "src/ecma402/units.h"

#include <criterion/criterion.h>

#include <criterion/new/assert.h>
#include <unicode/errorcode.h>
#include <unicode/uenum.h>

Test(ecma402Units, units1) {
  UEnumeration *values = NULL;
  UErrorCode status = U_ZERO_ERROR;
  const char **units = NULL;
  char *identifier;
  int identifierLen, counter = 0;

  units = (const char **)malloc(sizeof(char *) * 200);
  values = icuGetMeasurementUnits(units, &status);

  int count = uenum_count(values, &status);
  uenum_reset(values, &status);

  for (int i = 0; i < count; i++) {
    identifier = (char *)uenum_next(values, &identifierLen, &status);
    counter++;
  }

  uenum_close(values);

  if (units) {
    free(units);
  }

  // We don't care about the values enumerated over, since we aren't testing
  // what the ICU library returns. Rather, we only care that looped over more
  // than zero values.
  cr_assert(gt(int, counter, 0));
};
