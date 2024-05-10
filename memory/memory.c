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
} MapItem_t;

/* Constants */

/* Internal Variables */
static uint8_t _heap[HEAP_SIZE];                 // heap memory to allocate memory within 
static size_t _remainingSize = HEAP_SIZE;       // contains the remaining size of the heap
static void * _head = _heap;                  // head of the heap; equivilent to the tail of the map
static void * _tail = &_heap[HEAP_SIZE - 1];  // tail of the heap; this is equivilent to the start of the last allocated memory. Note that memory is assigned in inverse

/* Private Function Declaration */
/**
 * @brief returns number of map items in the heap memory. This is performed by counting number of non-NULL items up to the head pointer
 * 
 * @return uint32_t number of map items in heap
 */
static uint32_t _number_of_map_items();


/* Public Function Definiton */
void * allocate(size_t size) {
    // check available space in the heap, includes the memory requested to be allocated and the map item
    if (size + sizeof(MapItem_t) > _remainingSize) { return NULL; }

    // update remaining size as memory space is now ensured to be available to allocate
    _remainingSize -= size + sizeof(MapItem_t);

    // check if heap needs defragmenting
    if (_tail - size < _head) {
        defragment();
    }

    // offset tail by size of item added
    _tail -= size;

    // create dummy store of map item to copy to memory
    MapItem_t newMemory = {
        .location = _tail,
        .size = size
    };

    // itterate through the map and find first available map slot
    MapItem_t * p = (MapItem_t *) _heap;
    do {
        // map item slot as null means it is currently unallocated
        if (*((uint8_t *) p)) { continue; }
        
        // copy in new memory and update map head if nessecary
        copy(p, &newMemory, sizeof(*p));     
        if (p == _head) { 
            _head += sizeof(*p); 
        }

        break;
    } while ((void *) p++ < _head);

    return newMemory.location;
}


void deallocate(void * pointer) {
    // find pointer in map, itterate through map and NULL value of matching pointer
    for(MapItem_t * p = (MapItem_t *) _heap; (void *) p < _head; p++) {
        if (p == pointer) { 
            set(p, 0, sizeof(*p));
            _remainingSize -= p->size;  // update size
            break;                      // break and exit
        }
    }
}

void defragment(void) {
    // defragmenting is done in two stages. 
    // the first stage itterates through the map items and pushes them towards the start of the heap; note that this steps orders the map items according to their proximity to the end
    // the second stage pushes all memory blocks to the end of the heap in order of their proximity to this, i.e. the closest byte to the end of the heap is pushed first
    // it goes without saying that this function also updates the tail and head
    
    // gather total number of memory elements as initial setup
    uint32_t n = _number_of_map_items();

    // push all map items to start of the heap
    // this is performed with a bubble sort with key: n > n-1 && n-1 == NULL [n is distance from end]
    bool key(void * a, void * b) { return *((uint8_t *) b) == 0 && ((MapItem_t *) a)->location > ((MapItem_t *) b)->location; }
    sort_bubble(_heap, sizeof(MapItem_t), n, key);
    
    // update head to new map size
    _head = _heap + (n * sizeof(MapItem_t));

    // run through all map items and copy items to the back
    _tail = &_heap[HEAP_SIZE - 1];  // reset tail

    for(MapItem_t * p = (MapItem_t *) _heap; (void *) p < _head; p++) {
        _tail -= p->size;
        copy(_tail, p->location, p->size);
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
static uint32_t _number_of_map_items() {
    uint32_t sum = 0;
    for(MapItem_t * p = (MapItem_t *) _heap; (void *) p < _head; p++) {
        if (*((uint8_t *) p)) { sum++; }
    }
    return sum;
}