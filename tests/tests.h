#ifndef TEST_H_
#define TEST_H_

/* Standard Includes */
#include "stdint.h"

/* Internal Includes */

/* Structures and types*/

/**
 * @brief Standard return value for a test suite. This assumes that each suite consists of multiple independant tests.
 * 
 */
typedef struct {
    uint32_t total;
    uint32_t passed;
} Tests_SuiteReturn_t;

typedef Tests_SuiteReturn_t (*Tests_SuiteRunner_f)(void);
typedef int (*Tests_TestRunner_f)(void);

/**
 * @brief Represents an individual test suite
 * 
 */
typedef struct {
    char * name;
    Tests_SuiteRunner_f run;
} Tests_SuiteDisplay_t;

/**
 * @brief Represents an individual independant test
 * 
 */
typedef struct {
    char * name;
    Tests_TestRunner_f run;
} Tests_TestDisplay_t;


/* Constants */
extern const char * passFailStr[]; 

/* Public Function Declaration */

/**
 * @brief 
 *  Runs an array of tests and returns the sumed performance as a suite 
 * @note
 *  Tests suite are in no way required to run via this function however, it removes boiler plate code for most use-cases
 * 
 * @param name name of the test suite - this is purely for display purposes
 * @param tests array of tests
 * @param testsLen number of tests
 * @return Tests_SuiteReturn_t the summed performance of tests as a suite
 */
Tests_SuiteReturn_t test_util_suite_run(char * name, Tests_TestDisplay_t * tests, uint32_t testsLen);

#endif