/* standard includes */
#include "stdio.h"

/* asl includes */
#include "tests.h"

#include "unit_tests_memory_io.h"
#include "unit_tests_memory.h"

/* Constants */
const char * passFailStr[] = { "\033[0;31mfail\033[0;0m",  "\033[0;32mpass\033[0;0m" }; 

/* Testing blocks */
static Tests_SuiteDisplay_t _unitTests[] = {
    {
        .name = MEMORY_IO_TEST_SUITE_NAME,
        .run = memory_io_test_suite_run,
    }, {
        .name = MEMORY_HEAP_TEST_SUITE_NAME,
        .run = memory_heap_test_suite_run,
    }
    // add more tests here
};

#define NUM_UNIT_TEST_SUITES (sizeof(_unitTests) / sizeof(*_unitTests))


/* Entrance Function */
int main() {
    printf("Beginning ASL tests...\n");

    printf("\n-- Unit Tests --");
    Tests_SuiteReturn_t resultUnitTests[NUM_UNIT_TEST_SUITES] = { 0 };
    
    // runner loop
    for (int i = 0; i < NUM_UNIT_TEST_SUITES; i++) {
        printf("\nRunning suite: %s", _unitTests[i].name);
        resultUnitTests[i] = _unitTests[i].run();
        printf("\nTests passed: %d/%d (%.1f%%)", resultUnitTests[i].passed, resultUnitTests[i].total, ((float) resultUnitTests[i].passed) / ((float) resultUnitTests[i].total) * 100.0);
    }

    // summary loop
    printf("\nFinished %d unit tests", NUM_UNIT_TEST_SUITES);
    uint32_t passCountUnitTests = 0;
    for (int i = 0, pass; i < NUM_UNIT_TEST_SUITES; i++) {
        pass = resultUnitTests[i].passed == resultUnitTests[i].total;
        passCountUnitTests += pass;
        printf("\n\t%s | %s | %d/%d tests passed (%.1f%%)", passFailStr[pass], _unitTests[i].name, resultUnitTests[i].passed, resultUnitTests[i].total, ((float) resultUnitTests[i].passed) / ((float) resultUnitTests[i].total) * 100.0);
    }
    printf("\n%s | %d/%d suites passed (%.1f%%)", passFailStr[passCountUnitTests == NUM_UNIT_TEST_SUITES], passCountUnitTests, NUM_UNIT_TEST_SUITES, ((float) passCountUnitTests) / ((float) NUM_UNIT_TEST_SUITES) * 100.0);

    printf("\nFinished all tests");

    return 0;
}

/* Public Function Definition */ 
Tests_SuiteReturn_t test_util_suite_run(char * name, Tests_TestDisplay_t * tests, uint32_t testsLen) {
    // introduce local variables
    Tests_SuiteReturn_t result = { 
        .passed = 0,
        .total = testsLen,
    }; 
    uint32_t pass = 0;

    // itterate through all tests in suite and run, documenting performance
    for (int i = 0; i < result.total; i++) {
        pass = (tests[i].run() == 0);

        result.passed += pass;
        printf("\n\t%s | %s.%s", passFailStr[pass], name, tests[i].name);
    }

    return result;
}