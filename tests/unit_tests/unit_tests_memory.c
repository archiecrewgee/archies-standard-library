/* Standard Includes */
#include "stdio.h"
#include "stdint.h"

/* Internal Includes */
#include "tests.h"
#include "macros.h"

#include "memory.h"

/* Structures */

/* Constants */

/* Variables */
static Tests_SuiteReturn_t _performance_heap, _performance_util;

/* Private Function Declaration */


/* Test Runner */
static Tests_TestDisplay_t _test_heap[] = {
    {
        .name = "medium_0_block_get",
        .run = test_medium_0_block_get
    }, {
        .name = "medium_0_block_set",
        .run = test_medium_0_block_set
    }, {
        .name = "medium_1_byte_get",
        .run = test_medium_1_byte_get
    }, {
        .name = "medium_1_byte_set",
        .run = test_medium_1_byte_set
    }
};

/* Public Function Definiton */
Tests_SuiteReturn_t memory_heap_test_suite_run(void) {
    _performance_heap.testsTotal = asl_array_len(_test_heap);
    for (int i = 0, pass = 0; i < _performance_heap.testsTotal; i++) {
        pass = _test_heap[i].run() == 0;
        _performance_heap.testsPassed += pass;
        printf("\n\t%s | %s.%s", passFailStr[pass], MEMORY_HEAP_TEST_SUITE_NAME, _test_heap[i].name);
    }

    return _performance_heap;
}

/* Private Function Definiton */
