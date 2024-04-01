/* Standard Includes */
#include "stdio.h"

/* Internal Includes */
#include "tests.h"
#include "unit_tests_memory_io.h"

/* Structures */

/* Constants */

/* Variables */
Tests_SuiteReturn_t _performance = {
    .totalTests = 0,
    .passedTests = 0,
};

/* Private Function Declaration */

/* Public Function Definiton */
Tests_SuiteReturn_t memory_io_test_suite_run(void) {
    printf("memory_io unit tests");

    // todo add these here

    return _performance;
}

/* Private Function Definiton */

