/* standard includes */
#include "stdio.h"

/* asl includes */
#include "tests.h"
#include "unit_tests_memory_io.h"

/* Constants */
const char * passFailStr[] = { "fail",  "pass" }; 

/* Testing blocks */
static Tests_SuiteDisplay_t _unitTests[] = {
    (Tests_SuiteDisplay_t) {
        .name = MEMORY_IO_TEST_SUITE_NAME,
        .run = memory_io_test_suite_run,
    },
    // add more tests here
};


int main() {
    printf("Beginning ASL tests...\n");

    printf("\n-- Unit Tests --");
    Tests_SuiteReturn_t result;
    for (int i = 0; i < sizeof(_unitTests) / sizeof(*_unitTests); i++) {
        printf("\nRunning suite: %s", _unitTests[i].name);
        result = _unitTests[i].run();
        printf("\nTests passed: %d / %d (%.1f%%)", result.passedTests, result.totalTests, ((float) result.passedTests) / ((float) result.totalTests) * 100.0);
    }
    
    printf("\nFinished all tests");

    return 0;
}