/* Standard Includes */
#include "stddef.h"
#include "stdint.h"
#include "stdio.h"

/* Internal Includes */
#include "memory.h"

/* Structures */
typedef struct {
    void * location;    // location of a piece of memory
    size_t size;        // size of the piece of memory
} MapItem_t;

/* Constants */

/* Internal Variables */
static size_t _heap[HEAP_SIZE];                 // heap memory to allocate memory within 
static size_t _remainingSize = HEAP_SIZE;       // contains the remaining size of the heap
static size_t * _head = _heap;                  // head of the heap; equivilent to the tail of the map
static size_t * _tail = &_heap[HEAP_SIZE - 1];  // tail of the heap; this is equivilent to the start of the last allocated memory. Note that memory is assigned in inverse

/* Private Function Declaration */

/* Public Function Definiton */
void * allocate(size_t size) {
    // check available space in the heap, includes the memory requested to be allocated and the map item
    if (size + sizeof(MapItem_t) > _remainingSize) { return NULL; }

    // update remaining size as memory space is now ensured to be available to allocate
    _remainingSize += size + sizeof(MapItem_t);

    // check if heap needs defragmenting
    if (_tail - size < _head) {
        // todo: defragment
    }

    // offset tail by size of item added
    _tail -= size;

    // create dummy store of map item to copy to memory
    MapItem_t newMemory = {
        .location = _tail,
        .size = size
    };

    // itterate through the map and find first available map slot
    MapItem_t * p = _heap;
    do {
        // map item slot as null means it is currently unallocated
        if (*((uint8_t *) p)) { continue; }
        
        // copy in new memory and update map head if nessecary
        copy(p, &newMemory, sizeof(*p));     
        if (p == _head) { 
            _head += sizeof(*p); 
        }

        break;
    } while (p++ < _head);

    return newMemory.location;
}


void deallocate(void * pointer) {
    // find pointer in map, itterate through map and NULL value of matching pointer
    for(MapItem_t * p = _heap; p < _head; p++) {
        if (p == pointer) { 
            set(p, 0, sizeof(*p));
            _remainingSize -= p->size;  // update size
            break;                      // break and exit
        }
    }
}

void defragment(void) {
    // defragmenting is done in two stages. 
    // the first stage itterates through the map items and pushes them towards the start of the heap, todo: should they be ordered here???
    // the second stage pushes all memory blocks to the end of the heap in order of their proximity to this, i.e. the closest byte to the end of the heap is pushed first
    // it goes without saying that this function also updates the tail and head
    
    // push all map items to start of the heap
    // this is performed with a bubble sort with key [a < b && b != N], NUll is always considered a swap 

}


void copy(void * dst, void * src, size_t size) {
    while (size--) {
        *((uint8_t *) dst++) = *((uint8_t *) src++);
    }
}


void set(void * dst, uint8_t value, size_t size) {
    while (size--) {
        *((uint8_t *) dst++) = value;
    }
}

/* Private Function Definiton */
