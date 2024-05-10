/* Standard Includes */
#include "stddef.h"
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"

/* Internal Includes */
#include "memory.h"
#include "sort.h"

/* Structures */
typedef struct {
    void * location;    // location of a piece of memory
    size_t size;        // size of the piece of memory
} Memory_HeapMapElement_t;

/* Constants */

/* Internal Variables */

/* Private Function Declaration */

/**
 * @brief returns number of map items in the heap memory. This is performed by counting number of non-NULL items up to the head pointer
 * 
 * @param heap pointer to heap instance
 * @return uint32_t number of map items in heap
 */
static uint32_t _number_of_map_items(Memory_Heap_t * heap);


/* Public Function Definiton */
Memory_Heap_t heap_init(uint8_t * heapMemory, size_t heapSize) {
    return (Memory_Heap_t) {
        .heap = heapMemory,
        .sizeTotal = heapSize,
        .sizeRemaining = heapSize,
        .head = heapMemory,
        .tail = &heapMemory[heapSize - 1]
    };
}


void * allocate(Memory_Heap_t * heap, size_t size) {
    // check available space in the heap, includes the memory requested to be allocated and the map item
    if (size + sizeof(Memory_HeapMapElement_t) > heap->sizeRemaining) { return NULL; }

    // update remaining size as memory space is now ensured to be available to allocate
    heap->sizeRemaining -= size + sizeof(Memory_HeapMapElement_t);

    // check if heap needs defragmenting
    if (heap->tail - size < heap->head) {
        defragment(heap);
    }

    // offset tail by size of item added
    heap->tail -= size;

    // create dummy store of map item to copy to memory
    Memory_HeapMapElement_t newMemory = {
        .location = heap->tail,
        .size = size
    };

    // itterate through the map and find first available map slot
    Memory_HeapMapElement_t * p = (Memory_HeapMapElement_t *) heap->heap;
    do {
        // map item slot as null means it is currently unallocated
        if (*((uint8_t *) p)) { continue; }
        
        // copy in new memory and update map head if nessecary
        copy(p, &newMemory, sizeof(*p));     
        if (p == heap->head) { 
            heap->head += sizeof(*p); 
        }

        break;
    } while ((void *) p++ < heap->head);

    return newMemory.location;
}


void deallocate(Memory_Heap_t * heap, void * pointer) {
    // find pointer in map, itterate through map and NULL value of matching pointer
    for(Memory_HeapMapElement_t * p = (Memory_HeapMapElement_t *) heap->heap; (void *) p < heap->head; p++) {
        if (p == pointer) { 
            set(p, 0, sizeof(*p));
            heap->sizeRemaining -= p->size;  // update size
            break;                      // break and exit
        }
    }
}

void defragment(Memory_Heap_t * heap) {
    // defragmenting is done in two stages. 
    // the first stage itterates through the map items and pushes them towards the start of the heap; note that this steps orders the map items according to their proximity to the end
    // the second stage pushes all memory blocks to the end of the heap in order of their proximity to this, i.e. the closest byte to the end of the heap is pushed first
    // it goes without saying that this function also updates the tail and head
    
    // gather total number of memory elements as initial setup
    uint32_t n = _number_of_map_items(heap);

    // push all map items to start of the heap
    // this is performed with a bubble sort with key: n > n-1 && n-1 == NULL [n is distance from end]
    bool key(void * a, void * b) { return *((uint8_t *) b) == 0 && ((Memory_HeapMapElement_t *) a)->location > ((Memory_HeapMapElement_t *) b)->location; }
    sort_bubble(heap->heap, sizeof(Memory_HeapMapElement_t), n, key);
    
    // update head to new map size
    heap->head = heap->heap + (n * sizeof(Memory_HeapMapElement_t));

    // run through all map items and copy items to the back
    heap->tail = &heap->heap[heap->sizeTotal - 1];  // reset tail

    for(Memory_HeapMapElement_t * p = (Memory_HeapMapElement_t *) heap->heap; (void *) p < heap->head; p++) {
        heap->tail -= p->size;
        copy(heap->tail, p->location, p->size);
    }
}


void copy(void * dst, void * src, size_t size) {
    while (size--) {
        *((uint8_t *) dst++) = *((uint8_t *) src++);
    }
}


void copy_safe(void * dst, void * src, size_t size) {
    uint8_t intermediate;
    while (size--) {
        intermediate = *((uint8_t *) src++);
        *((uint8_t *) dst++) = intermediate;
    }
}


void swap(void * a, void * b, size_t size) {
    uint8_t intermediate;
    while (size--) {
        intermediate = *((uint8_t *) a);            // i <- a
        *((uint8_t *) a) = *((uint8_t *) b);        // a <- b
        *((uint8_t *) b) = intermediate;            // b <- i

        a++, b++;
    }
}


void set(void * dst, uint8_t value, size_t size) {
    while (size--) {
        *((uint8_t *) dst++) = value;
    }
}


bool compare(void * a, void * b, size_t size) {
    // itterate through elements until difference is found, default is passing state
    while (size--) {
        if (*((uint8_t *) a++) != *((uint8_t *) b++)) {
            return false;
        }
    }

    return true;
}

/* Private Function Definiton */
static uint32_t _number_of_map_items(Memory_Heap_t * heap) {
    uint32_t sum = 0;
    for(Memory_HeapMapElement_t * p = (Memory_HeapMapElement_t *) heap->heap; (void *) p < heap->head; p++) {
        if (*((uint8_t *) p)) { sum++; }
    }
    return sum;
}