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
#include "stdbool.h"

/* Internal Includes */

/* Structures */

/**
 * @brief 
 *  Heap structure used to allow strongly controlled and limited memory allocation and deallocation.
 *  The heap should be statically allocated and a reference passed to the strucutre
 * @note 
 *  For safe initialisation use `heap_init(ptr, size)` functionality 
 * 
 */
typedef struct {
    uint8_t * heap;         // reference to statically allocated byte array
    size_t sizeTotal;       // size of the heap array
    size_t sizeRemaining;   // remaining size of the heap - always >= tail - heap
    void * head;            // pointer to the current head of the array (allocated memory map end)
    void * tail;            // pointer to the current tail of the array (allocated memory start)
} Memory_Heap_t;

/* Constants */

/* Public Function Declaration */

/**
 * @brief 
 *  safetly defines the heap structure for use in dynamic memory allocation 
 * @note 
 *  the heap array should never be deallocated
 * 
 * @param heapMemory pointer to statically allocated array for storing heap memory
 * @param heapSize total size of the heap - i.e. sizeof(heap)
 * @return Memory_Heap_t defined heap memory structure
 */
Memory_Heap_t heap_init(uint8_t * heapMemory, size_t heapSize);

/**
 * @brief allocates memory of size `size` to a heap. This can be used to preserve information out of scope
 * 
 * @param heap pointer to heap instance 
 * @param size size of the memory to allocate in bytes
 * @return void* pointer to the memory allocated in memory. Returns NULL if no memory could be found
 */
void * allocate(Memory_Heap_t * heap, size_t size);

/**
 * @brief deallocates the memory at the given pointer
 * 
 * @param heap pointer to heap instance 
 * @param pointer pointer to memory previously allocated via the `allocate` function
 */
void deallocate(Memory_Heap_t * heap, void * pointer);

/**
 * @brief Defragments the heap stack to byte-pack memory and map
 * 
 * @param heap pointer to heap instance 
 */
void defragment(Memory_Heap_t * heap);

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
 * @brief swaps two elements of an arbitary size
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

/**
 * @brief Compares two elements of an arbitary size
 * 
 * @param a pointer to the first element
 * @param b pointer to the seconds element
 * @param size size of the memory to compare
 * @return true a and b are identical
 * @return false a and b are not identical
 */
bool compare(void * a, void * b, size_t size);

#endif