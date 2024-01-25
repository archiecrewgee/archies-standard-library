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
static uint32_t _mapItems = 0;      // numnber of memory map items. This is the same as the number of allocated pieces of memory
static size_t _heap[HEAP_SIZE];     // heap memory to allocate memory within 
static size_t _remainingSize = HEAP_SIZE;

static size_t * head = _heap;
static size_t * tail = &_heap[HEAP_SIZE - 1];

/* Private Function Declaration */

/* Public Function Definiton */
void * allocate(size_t size) {
    // check available space in the heap, includes the memory requested to be allocated and the map item
    if (size + sizeof(MapItem_t) > _remainingSize) { return NULL; }

    // update remaining size as memory space is now ensured to be available to allocate
    _remainingSize += size + sizeof(MapItem_t);

    // check if heap needs defragmenting
    if (tail - size < head) {
        // todo: defragment
    }

    // offset tail by size of item added
    tail -= size;

    // create dummy store of map item to copy to memory
    MapItem_t newMemory = {
        .location = tail,
        .size = size
    };


    // itterate through the map and find first available map slot
    MapItem_t * p = _heap;
    do {
        // map item slot as null means it is currently unallocated, 
        if (!*((uint8_t *) p)) {
            // copy in new memory and update map head if nessecary
            copy(p, &newMemory, sizeof(MapItem_t));     
            if (p == head) { 
                head += sizeof(MapItem_t); 
            }

            break;
        }
    } while (p++ < head);

    return newMemory.location;
}


void deallocate(void * pointer) {

}

void copy(void * dst, void * src, size_t size) {
    while (size-- != 0) {
        *((uint8_t *) dst++) = *((uint8_t *) src++);
    }
}

void dump_heap() {
    // for (size_t * h = _heap; h < &_heap[HEAP_SIZE]; h++) {
    //     printf("%d", (uint8_t)h %  8);
    //     if (!((uint32_t) h % (uint32_t) 8)) { printf("\n"); }

    //     printf("%02lx ", *h);
    // }
    printf("todo remove me");
}

/* Private Function Definiton */
