#ifndef ARRAY_TYPE_H_
#define ARRAY_TYPE_H_

/* Preamble */
/*
    The array type (Array_t) is a lightweight overhead to the standard array in C.
    It exists as an object and uses the additional overhead to produce more complex functions in an 
    intuitive manner.
    The array object is built around a continuous structure of elements with a maximum length. There is 
    also an active tail that matches the greatest index of the active elements. This is not guarunteed 
    as there is inevitably some logic that will cause this to be thrown off.
    The internal data of the array object should never be directly accessed. It still exists publically 
    to provide the user with a more full sense of what makes up the object.
    The array type object is created with 'malloc' and, as such, must be freed from memory after use. 
    To ensure all data is removed, the 'destroy_array_t()' function should be called.
    # TODO: come back with a proper explanation and a 'readme.md' file
*/

/* Standard Includes */
#include <stdint.h>

/* Internal Includes */

/* Structures */
typedef struct _Array_t {
    uint16_t elementSize;   // size of each element of the array (in bytes)
    uint16_t maxLength;     // maximum number of elements in the aray
    uint16_t activeTail;    // index of the most offset active element
    void *   data;          // pointer to the data of the array
} Array_t;

/* Constants */

/* Public Function Declaration */
// initialisation/destruction functions
// initialise array element
Array_t * array_init(uint16_t numberOfElements, uint16_t elementSize);

// destroy array element
void array_destroy(Array_t * self);

// interaction functions
// fill a given buffer with N number of elements from a given index
Array_t * array_get(const Array_t *const self, uint16_t index, uint16_t numberOfElements, void *const fillBuffer);

// write a given buffer if N elements to an index
Array_t * array_set(Array_t *const self, uint16_t index, uint16_t numberOfElements, const void *const setBuffer);

/* Additional functions
    overwrite
    pop
    append
    conccenate
    element wise opperation

 */

// flow control

#endif