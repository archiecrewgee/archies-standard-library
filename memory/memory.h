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
#include "stdint.h"

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
 * @brief Defragments the heap stack to byte-pack memory and map
 * 
 */
void defragment(void);

/**
 * @brief copys `size` bytes of memory from the source to the destination pointer
 * 
 * @param dst destination
 * @param src source
 * @param size size of the memory to copy
 */
void copy(void * dst, void * src, size_t size);

/**
 * @brief copys `size` bytes of memory from the source to the destination pointer. 
 *  This opperation is corruption safe and allows memory spaces ot overlap
 * 
 * @param dst destination
 * @param src source
 * @param size size of the memory to copy
 */
void copy_safe(void * dst, void * src, size_t size);

/**
 * @brief swaps too elements of an arbitary size
 * 
 * @param a pointer to element a
 * @param b pointer to element b
 * @param size size of the memory to swap
 */
void swap(void * a, void * b, size_t size);

/**
 * @brief writes size value to `size` bytes of the location pointed to by `dst`
 * 
 * @param dst location to write to
 * @param value value to write to memory 
 * @param size size of the memory to set
 */
void set(void * dst, uint8_t value, size_t size);



#endif