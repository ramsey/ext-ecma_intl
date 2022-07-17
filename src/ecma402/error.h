/*
   +----------------------------------------------------------------------+
   | ecma_intl extension for PHP                                          |
   | Internationalization Support, Ecma-style (ECMA-402)                  |
   +----------------------------------------------------------------------+
   | Copyright (c) Ben Ramsey <ben@benramsey.com>                         |
   |                                                                      |
   | Licensed under the MIT License (the "License"); you may not use this |
   | file except in compliance with the License. You may obtain a copy of |
   | the License at                                                       |
   |                                                                      |
   |     https://opensource.org/licenses/MIT                              |
   |                                                                      |
   | Unless required by applicable law or agreed to in writing, software  |
   | distributed under the License IS PROVIDED "AS IS", WITHOUT WARRANTY  |
   | OF ANY KIND, EXPRESS OR IMPLIED. See the License for the specific    |
   | language governing permissions and limitations under the License.    |
   +----------------------------------------------------------------------+
*/

#ifndef ECMA_INTL_ECMA402_ERROR_H
#define ECMA_INTL_ECMA402_ERROR_H

#include "src/common.h"

#include <stdbool.h>
#include <unicode/utypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Error status codes.
 */
typedef enum ecmaErrorCode {
  /**
   * No error or warning.
   */
  ZERO_ERROR = 0,

  /**
   * Engine errors.
   */
  MEMORY_ALLOCATION_ERROR = 100,

  /**
   * Application errors.
   */
  GENERAL_ERROR = 200,
  ICU_ERROR,
  INVALID_CALENDAR,
  INVALID_CASE_FIRST,
  INVALID_COLLATION,
  INVALID_HOUR_CYCLE,
  INVALID_LANGUAGE,
  INVALID_LOCALE_ID,
  INVALID_NUMBERING_SYSTEM,
  INVALID_REGION,
  INVALID_SCRIPT,

} ecmaErrorCode;

/**
 * Error status indicator.
 */
typedef struct errorStatus {
  /**
   * Error status of this library, if any. This should be initialized to
   * ZERO_ERROR.
   */
  ecmaErrorCode ecma;

  /**
   * Error status of the ICU library, if any. This should be initialized to
   * U_ZERO_ERROR.
   */
  UErrorCode icu;

  /**
   * If applicable, an error message with more details.
   */
  const char *errorMessage;

  /**
   * If applicable, the line number where the error occurred.
   */
  int lineNumber;

  /**
   * If applicable, the file name where the error occurred.
   */
  const char *fileName;

} errorStatus;

/**
 * Initializes an errorStatus struct. This also allocates the struct on the
 * stack; free it using freeErrorStatus().
 *
 * @return An error status.
 */
errorStatus *initErrorStatus(void);

/**
 * Frees an errorStatus initialized with initErrorStatus().
 *
 * @param errorStatus The errorStatus to free.
 */
void freeErrorStatus(errorStatus *errorStatus);

/**
 * Checks whether the errorStatus indicates a error.
 */
bool hasError(errorStatus *status);

/**
 * Saves general error information to the errorStatus.
 */
void error(errorStatus *status, const char *errorMessage, const char *fileName,
           int lineNumber);

/**
 * Saves ecmaErrorCode error information to the errorStatus.
 */
void ecmaError(errorStatus *status, ecmaErrorCode errorCode,
               const char *fileName, int lineNumber, const char *errorMessage);

/**
 * Saves ICU UErrorCode error information to the errorStatus.
 */
void icuError(errorStatus *status, UErrorCode errorCode, const char *fileName,
              int lineNumber, const char *errorMessage);

/**
 * Convenience function to record a memory error to the errorStatus.
 */
void memoryError(errorStatus *status, const char *fileName, int lineNumber);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_ECMA402_ERROR_H */
