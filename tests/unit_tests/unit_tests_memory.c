/* Standard Includes */
#include "stdio.h"
#include "stdint.h"

/* Internal Includes */
#include "tests.h"
#include "macros.h"

#include "unit_tests_memory.h"

/* Structures */

/* Constants */

/* Variables */
static Tests_SuiteReturn_t _performance_heap, _performance_util;

/* Private Function Declaration */
int sanity_test(void) {
    return 0;
}

/* Test Runner */
static Tests_TestDisplay_t _tests_heap[] = {
    {
        .name = "sanity_test",
        .run = sanity_test
    },
};

/* Public Function Definiton */
Tests_SuiteReturn_t memory_heap_test_suite_run(void) {
    return test_util_suite_run(MEMORY_HEAP_TEST_SUITE_NAME, _tests_heap, asl_array_len(_tests_heap));
}

/* Private Function Definiton */
