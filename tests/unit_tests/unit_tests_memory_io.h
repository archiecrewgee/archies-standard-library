#ifndef UNIT_TESTS_MEMORY_IO_H_
#define UNIT_TESTS_MEMORY_IO_H_

/* Standard Includes */

/* Internal Includes */
#include "tests.h"

/* Structures */

/* Constants */
#define MEMORY_IO_TEST_SUITE_NAME "memory_io_test_suite"

/* Public Function Declaration */

// runs all unit tests associated with 'memory_io' module
Tests_SuiteReturn_t memory_io_test_suite_run(void);

#endif