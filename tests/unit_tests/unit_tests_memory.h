#ifndef UNIT_TESTS_MEMORY_H_
#define UNIT_TESTS_MEMORY_H_

/* Standard Includes */

/* Internal Includes */
#include "tests.h"

/* Structures */

/* Constants */
#define MEMORY_HEAP_TEST_SUITE_NAME "memory_heap_test_suite"
#define MEMORY_UTIL_TEST_SUITE_NAME "memory_util_test_suite"

/* Public Function Declaration */

// runs all unit tests associated with the heap of the 'memory' module
Tests_SuiteReturn_t memory_heap_test_suite_run(void);

// runs all unit tests associated with the utility function of the 'memory' module
Tests_SuiteReturn_t memory_util_test_suite_run(void);


#endif