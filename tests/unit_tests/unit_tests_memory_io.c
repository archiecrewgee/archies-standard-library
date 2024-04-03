/* Standard Includes */
#include "stdio.h"
#include "stdint.h"

/* Internal Includes */
#include "tests.h"
#include "unit_tests_memory_io.h"

#include "memory.h"
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
// simple piece of memory with byte alligned and sized blocks 
static uint8_t _medium0_memory[1024] = { 0 };

static int medium_0_write(uint32_t address, uint8_t * src) {
    copy(&_medium0_memory[address], src, 1);
    return 0;
}

static int medium_0_read(uint32_t address, uint8_t * dst) {
    copy(dst, &_medium0_memory[address], 1);
    return 0;
}

static uint8_t _medium0_scratch;

static MemoryIO_Medium_t _medium0 = {
    .block = {
        .size = 1,
        .increment = 1,
    },
    .write_block = medium_0_write,
    .read_block = medium_0_read,

    .scratch = &_medium0_scratch,
};

static int test_medium0_block_set(void);
static int test_medium0_block_get(void);

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
        .run = test_medium0_block_get
    }, {
        .name = "medium_0_block_set",
        .run = test_medium0_block_set
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

static int test_medium0_block_set(void) {
    char testStr[] = "hello world";
    int testsPassed = 0;
    
    memory_io_blocks_set(&_medium0, 0, testStr, sizeof(testStr));
    testsPassed += compare(&_medium0_memory[0], testStr, sizeof(testStr));

    memory_io_blocks_set(&_medium0, 50, testStr, sizeof(testStr));
    testsPassed += compare(&_medium0_memory[50], testStr, sizeof(testStr));

    return !(testsPassed == 2);
}

static int test_medium0_block_get(void) {
    return 0;
}