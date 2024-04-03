#ifndef TEST_H_
#define TEST_H_

/* Standard Includes */
#include "stdint.h"

/* Internal Includes */

/* Structures and types*/
typedef struct {
    uint32_t totalTests;
    uint32_t passedTests;
} Tests_SuiteReturn_t;

typedef Tests_SuiteReturn_t (*Tests_SuiteRunner_f)(void);
typedef int (*Tests_TestRunner_f)(void);

typedef struct {
    char * name;
    Tests_SuiteRunner_f run;
} Tests_SuiteDisplay_t;

typedef struct {
    char * name;
    Tests_TestRunner_f run;
} Tests_TestDisplay_t;


/* Constants */
extern const char * passFailStr[]; 

/* Public Function Declaration */

#endif