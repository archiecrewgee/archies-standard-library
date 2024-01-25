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
static uint32_t _mapItems = 0;      // numnber of memory map items. This is the same as the number of allocated pieces of memory
static size_t _heap[HEAP_SIZE];     // heap memory to allocate memory within 
static size_t _remainingSize = HEAP_SIZE;


/* Private Function Declaration */

/* Public Function Definiton */
void * allocate(size_t size) {
    // check available space, includes memory allocated and the map item
    if (size + sizeof(MapItem_t) > _remainingSize) { return NULL; }

    // create dummy store of map item to copy to memory
    MapItem_t newMemory = {
        .location = NULL,
        .size = size
    };
    
    // itterate though map; find the first available map slot and applicable memory slot closest to the back of the heap
    for (uint32_t i = 0; i < _mapItems; i++) {
        // map item slot as null means it is currently unallocated
        if (_heap[i * sizeof(MapItem_t)] == NULL) {
            // copy in new map item
            copy()
        }

        // 


    }

    // append item to the map
    
    _mapSize
}


void deallocate(void * pointer) {

}


void copy(void * dst, void * src, size_t size) {
    while (size != 0) {
        *((size_t *) dst++) = *((size_t * ) src++);
        size =- 1;
    }
}

/* Private Function Definiton */
