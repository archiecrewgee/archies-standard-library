/**
 * @file memory.h
 * @author Archie David Crew-Gee
 * @brief 
 *  Heap management works by statically allocating a heap defined by the `HEAP_SIZE` parameter. 
 *  Memory in the heap is defined by a map that contains a given pieces location and size.
 *  On allocating memory, a map item will be created defining the value and a heap location will be allocated. 
 *  Deallocating memory results in the map item being reset to NULL. 
 * 
 */
#ifndef MEMORY_H_
#define MEMORY_H_

/* Standard Includes */
#include "stddef.h"

/* Internal Includes */

/* Structures */

/* Constants */
// heap size in bytes
#define HEAP_SIZE 255

/* Public Function Declaration */

/**
 * @brief allocates memory of size `size` to a heap. This can be used to preserve information out of scope
 * 
 * @param size size of the memory to allocate in bytes
 * @return void* pointer to the memory allocated in memory. Returns NULL if no memory could be found
 */
void * allocate(size_t size);

/**
 * @brief deallocates the memory at the given pointer
 * 
 * @param pointer pointer previously allocated by the `allocate` function
 */
void deallocate(void * pointer);


/**
 * @brief Copys `size` bytes of memory from the source to the destination pointer
 * 
 * @param dst destination
 * @param src source
 * @param size size of the memory to copy
 */
void copy(void * dst, void * src, size_t size);

#endif