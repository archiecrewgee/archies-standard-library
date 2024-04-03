/* Standard Includes */
#include "stdio.h"
#include "stdint.h"

/* Internal Includes */
#include "tests.h"
#include "unit_tests_memory_io.h"

#include "memory_io.h"

/* Structures */

/* Constants */

/* Variables */
static Tests_SuiteReturn_t _performance = {
    .testsTotal = 0,
    .testsPassed = 0,
};

/* Private Function Declaration */
static int test_sanity(void);
static int test_sanity_fail(void);

/* Medium 0 tests */
static MemoryIO_Medium_t _medium_0 = {

};

static int test_medium_0_block_set(void);
static int test_medium_0_block_get(void);

/* Test Runner */
static Tests_TestDisplay_t _tests[] = {
    {
        .name = "sanity_test",
        .run = test_sanity 
    }, {
        .name = "sanity_test_fail",
        .run = test_sanity_fail
    }, {
        .name = "medium_0_block_get",
        .run = test_medium_0_block_get
    }, {
        .name = "medium_0_block_set",
        .run = test_medium_0_block_set
    },
};

/* Public Function Definiton */
Tests_SuiteReturn_t memory_io_test_suite_run(void) {
    _performance.testsTotal = sizeof(_tests) / sizeof(*_tests);
    for (int i = 0, pass = 0; i < _performance.testsTotal; i++) {
        pass = _tests[i].run() == 0;
        _performance.testsPassed += pass;
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

static int test_medium_0_block_set(void) {
    return 0;
}

static int test_medium_0_block_get(void) {
    return 0;
}