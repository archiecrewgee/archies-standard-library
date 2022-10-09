/* Standard Includes */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Internal Includes */
#include "array_type.h"

/* Structures */

/* Constants */

/* Private Function Declaration */

/* Public Function Definiton */
// initialise array element
Array_t * array_init(uint16_t numberOfElements, uint16_t elementSize) {
    // allocate memory for array - allocation success check performed in the same line
    Array_t * self = (Array_t *)calloc(1, sizeof(self)); if (self == NULL) { return NULL; }

    // allocate memory for data - allocation success check performed in the same line
    void * data = calloc(elementSize, numberOfElements); if (data == NULL) { return NULL; }

    // initialise array elements - activeTail already set to zero by calloc
    self->maxLength   = numberOfElements;
    self->elementSize = elementSize;
    self->data        = data;

    // return self
    return self;
}

// destroy array element
void array_destroy(Array_t * self) {
    // free data array
    free(self->data) // TODO: check free will free a given size, I feel like it might just do the void pointer

    // free array type
    free(self);
}

// interaction functions
// fill a given buffer with N number of elements from a given index
Array_t * array_get(Array_t * self, uint16_t index, uint16_t numberOfElements, void * fillBuffer) {
    // check the index (plus the number of elements being collected) is within the buffer max length
    if (index + numberOfElements > self->maxLength) { return NULL; }

    // copy the memory  
    memcpy(fillBUffer)


}

// write a given buffer if N elements to an index
Array_t * array_set(Array_t * self, uint16_t index, uint16_t numberOfElements, void * setBuffer);

/* Private Function Definiton */