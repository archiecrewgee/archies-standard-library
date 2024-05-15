/* Standard Includes */
#include "stdio.h"
#include "stdint.h"

/* Internal Includes */
#include "tests.h"
#include "macros.h"

#include "unit_tests_memory.h"
#include "memory.h"

/* Structures */

/* Constants */

/* Variables */
static Tests_SuiteReturn_t _performance_heap, _performance_util;

/* Heap unit tests */
// statically allocated heap memory
static uint8_t _memory[256] = { 0 };

static int unit_test_heap_dynamic_memory_overlap(void) {
    /* Setup */
    set(_memory, 0, sizeof(_memory));
    Memory_Heap_t heap = heap_init(_memory, sizeof(_memory));

    /* Test */
    // allocate variables and write to them
    int32_t * a = allocate(&heap, sizeof(*a));
    *a = INT32_MAX;
    
    int16_t * b = allocate(&heap, sizeof(*b));
    *b = INT16_MIN;

    int * c = allocate(&heap, sizeof(*c));

    // validation is value are the ones they were initially set to despite other variables being set
    return !(*a == INT32_MAX && *b == INT16_MIN);
}

static int unit_test_heap_allocation_limit(void) {
    /* Setup */
    set(_memory, 0, sizeof(_memory));
    Memory_Heap_t heap = heap_init(_memory, sizeof(_memory));

    /* Test - allocate memory up to limit */
    // note that the size of the map is not available by design however, 4 allocations of 64 byte values in a 256 byte array should limit itself to 3
    int passed = 0;
    for (int i = 0; i < 3; i++) {
        if (allocate(&heap, 64)) {
            passed++;
        }
    }

    // attempt to allocate and validate it does not allow this (null ptr return)
    passed += (allocate(&heap, 32) == NULL);
    
    return !(passed == 4);

}

static int unit_test_heap_deallocation_freeing_space(void) {
    return 0;
}

static int unit_test_heap_maximum_capacity(void) {
    return 0;
}

/* Test Runner */
static Tests_TestDisplay_t _tests_heap[] = {
    {
        .name = "dynamic_memory_overlap",
        .run = unit_test_heap_dynamic_memory_overlap
    }, {
        .name = "allocation_limit",
        .run = unit_test_heap_allocation_limit
    }, {
        .name = "deallocation_freeing_space",
        .run = unit_test_heap_deallocation_freeing_space
    }, {
        .name = "maximum_capacity",
        .run = unit_test_heap_maximum_capacity
    }
};

/* Public Function Definiton */
Tests_SuiteReturn_t memory_heap_test_suite_run(void) {
    return test_util_suite_run(MEMORY_HEAP_TEST_SUITE_NAME, _tests_heap, asl_array_len(_tests_heap));
}

/* Private Function Definiton */
