/* standard includes */
#include "stdio.h"

/* asl includes */
#include "tests.h"
#include "unit_tests_memory_io.h"

/* Testing blocks */
typedef Tests_SuiteReturn_t (*Tests_SuiteRunner_f)(void);

typedef struct {
    char * name;
    Tests_SuiteRunner_f run;
} Tests_Display_t;

Tests_Display_t _unitTests[] = {
    (Tests_Display_t) {
        .name = "memory_io",
        .run = memory_io_test_suite_run,
    },
    // add more tests here
};


int main() {
    printf("Beginning tests\n");

    printf("\n-- Unit Tests --");
    printf("\nwhats going on here");
    Tests_SuiteReturn_t result;
    for (int i = 0; i < sizeof(_unitTests) / sizeof(*_unitTests); i++) {
        printf("\nRunning unit test: %s", _unitTests[i].name);
        result = _unitTests[i].run();
        printf("\n\t%d / %d tests passed", result.passedTests, result.totalTests);
    }
    
    printf("\nFinished all tests");

    return 0;
}