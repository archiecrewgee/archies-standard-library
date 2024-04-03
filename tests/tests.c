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

#define NUM_UNIT_TEST_SUITES (sizeof(_unitTests) / sizeof(*_unitTests))


int main() {
    printf("Beginning ASL tests...\n");

    printf("\n-- Unit Tests --");
    Tests_SuiteReturn_t resultUnitTests[NUM_UNIT_TEST_SUITES] = { 0 };
    
    // runner loop
    for (int i = 0; i < NUM_UNIT_TEST_SUITES; i++) {
        printf("\nRunning suite: %s", _unitTests[i].name);
        resultUnitTests[i] = _unitTests[i].run();
        printf("\nTests passed: %d/%d (%.1f%%)", resultUnitTests[i].testsPassed, resultUnitTests[i].testsTotal, ((float) resultUnitTests[i].testsPassed) / ((float) resultUnitTests[i].testsTotal) * 100.0);
    }

    // summary loop
    printf("\nFinished %d unit tests", NUM_UNIT_TEST_SUITES);
    uint32_t passCountUnitTests = 0;
    for (int i = 0, pass; i < NUM_UNIT_TEST_SUITES; i++) {
        pass = resultUnitTests[i].testsPassed == resultUnitTests[i].testsTotal;
        passCountUnitTests += pass;
        printf("\n\t%s | %s | %d/%d tests passed (%.1f%%)", passFailStr[pass], _unitTests[i].name, resultUnitTests[i].testsPassed, resultUnitTests[i].testsTotal, ((float) resultUnitTests[i].testsPassed) / ((float) resultUnitTests[i].testsTotal) * 100.0);
    }
    printf("\n%s | %d/%d suites passed (%.1f%%)", passFailStr[passCountUnitTests == NUM_UNIT_TEST_SUITES], passCountUnitTests, NUM_UNIT_TEST_SUITES, ((float) passCountUnitTests) / ((float) NUM_UNIT_TEST_SUITES) * 100.0);

    printf("\nFinished all tests");

    return 0;
}