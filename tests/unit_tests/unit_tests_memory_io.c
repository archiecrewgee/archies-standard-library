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
/* Medium 0 tests */
// simple piece of memory with byte alligned and sized blocks 
static uint8_t _medium_0_memory[1024] = { 0 };
static uint8_t _medium_0_scratch;

static int _medium_0_write(uint32_t address, uint8_t * src) {
    copy(&_medium_0_memory[address], src, 1);
    return 0;
}

static int _medium_0_read(uint32_t address, uint8_t * dst) {
    copy(dst, &_medium_0_memory[address], 1);
    return 0;
}

static MemoryIO_Medium_t _medium_0 = {
    .block = {
        .size = 1,
        .increment = 1,
    },
    .write_block = _medium_0_write,
    .read_block = _medium_0_read,

    .scratch = &_medium_0_scratch,
};

static int test_medium_0_block_set(void);
static int test_medium_0_block_get(void);


/* Medium 1 tests */
// memory with 4 byte block and 1 byte increment
static uint8_t _medium_1_memory[1024] = { 0 };
static uint8_t _medium_1_scratch[4] = { 0 };

static int _medium_1_write(uint32_t address, uint8_t * src) {
    copy(&_medium_1_memory[address * 4], src, 4);
    return 0;
}

static int _medium_1_read(uint32_t address, uint8_t * dst) {
    copy(dst, &_medium_1_memory[address * 4], 4);
    return 0;
}

static MemoryIO_Medium_t _medium_1 = {
    .block = {
        .size = 4,
        .increment = 1,
    },
    .write_block = _medium_1_write,
    .read_block = _medium_1_read,

    .scratch = _medium_1_scratch,
};

static int test_medium_1_byte_get(void);
static int test_medium_1_byte_set(void);


/* Test Runner */
static Tests_TestDisplay_t _tests[] = {
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
static int test_medium_0_block_set(void) {
    char testStr[] = "hello world";
    int testsPassed = 0;
    
    set(_medium_0_memory, 0, sizeof(_medium_0_memory));

    memory_io_blocks_set(&_medium_0, 0, testStr, sizeof(testStr));
    testsPassed += compare(&_medium_0_memory[0], testStr, sizeof(testStr));

    memory_io_blocks_set(&_medium_0, 50, testStr, sizeof(testStr));
    testsPassed += compare(&_medium_0_memory[50], testStr, sizeof(testStr));

    return !(testsPassed == 2);
}

static int test_medium_0_block_get(void) {
    char testStr[16];

    set(_medium_0_memory, 0, sizeof(_medium_0_memory));

    copy(&_medium_0_memory[40], "hello world", 12);
    memory_io_blocks_get(&_medium_0, 40, testStr, 12);
    
    return !compare(testStr, "hello world", 12);
}

static int test_medium_1_byte_get(void) {
    // note that block is size 4 but increments with 1... therefore
    int testsPassed = 0;

    // basic alignment
    char testStr[] = "this is a 21B string", compStr[21] = { 0 };

    copy(&_medium_1_memory[16 * 4], testStr, sizeof(testStr));
    memory_io_bytes_get(&_medium_1, 16 * 4, compStr, sizeof(testStr));

    testsPassed += compare(testStr, compStr, sizeof(testStr));
    printf("\n%d, %s | %s", testsPassed, testStr, compStr);
    
    // offset

    return !(testsPassed == 1);
}
static int test_medium_1_byte_set(void) {
    return 0;
}
