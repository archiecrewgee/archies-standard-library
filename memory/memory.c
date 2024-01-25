/* Standard Includes */
#include "stddef.h"
#include "stdint.h"

/* Internal Includes */
#include "memory.h"

/* Structures */
typedef struct {
    void * location;    // location of a piece of memory
    size_t size;        // size of the piece of memory
} MapItem_t;

/* Constants */

/* Internal Variables */
static uint32_t _mapSize = 0;      // size of memory map that defines contents of heap
static size_t _heap[HEAP_SIZE];    // heap memory to allocate memory within 
static uint32_t _remainingSize = HEAP_SIZE;


/* Private Function Declaration */

/* Public Function Definiton */
void * allocate(size_t size) {
    // check available space, includes memory allocated and the map item
    if (size + sizeof(MapItem_t) > _remainingSize) { return NULL; }

    // creat

}


void deallocate(void * pointer) {

}


/* Private Function Definiton */
