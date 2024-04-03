/* Standard Includes */
#include "stdio.h"
#include "stdint.h"

/* Internal Includes */
#include "tests.h"
#include "unit_tests_memory_io.h"

/* Structures */

/* Constants */

/* Variables */
static Tests_SuiteReturn_t _performance = {
    .totalTests = 0,
    .passedTests = 0,
};

/* Private Function Declaration */
static int test_sanity(void);
static int test_sanity_fail(void);

/* Test Runner */
static Tests_TestDisplay_t _tests[] = {
    {
        .name = "sanity_test",
        .run = test_sanity 
    }, {
        .name = "sanity_test_fail",
        .run = test_sanity_fail
    },
};

/* Public Function Definiton */
Tests_SuiteReturn_t memory_io_test_suite_run(void) {
    _performance.totalTests = sizeof(_tests) / sizeof(*_tests);
    for (int i = 0, pass = 0; i < _performance.totalTests; i++) {
        pass = _tests[i].run() == 0;
        _performance.passedTests += pass;
        printf("\n\t%s | %s.%s", passFailStr[pass], MEMORY_IO_TEST_SUITE_NAME, _tests[i].name);
    }

    return _performance;
}

/* Private Function Definiton */
static int test_sanity(void) {
    return 0;
}


static int test_sanity_fail(void) {
    return 1;
}
