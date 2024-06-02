/**
 * @file array.h
 * @author Archie David Crew-Gee
 * @brief 
 *  Custom array type that adds a lightweight wrapper for interacting with contiguous memory containing discrete elements of size N (arrays) 
 *  Management of the memory storing the data is the responsibility of the user
 *  To allow certain functionality, the concept of a tail is introduced
 *  This will always be the element interacted with (via array type functionality) found at the highest index
 *  The tail's index may be lowed via the following functionality:
 *      - `shift_left`: will lower by the size of the shift
 *      - `set_size`: tail will be brought in line with specified size
 *      - `pop` functionality: this will always contain a shift
 *  The decision to preserve the 'array' name despite this being an additional feature is to comply with the convention commonly used in C++
 * 
 * @note
 *  No overflow checks are performed in function and this shopuld be managed externally [TODO: use functionality and see how this descision is on a larger scale (I quite like it for the time being though)]
 */
#ifndef ARRAY_H_
#define ARRAY_H_

/* Includes */
#include "stdint.h"

/* Types & Structures */

/**
 * @brief Data structure representing an instance of the array type
 * 
 */
typedef struct {
    void * data;                    // pointer to memory allocated for type
    void * tail;                    // pointer to the final element of the array
    size_t elementSize;             // size of a single discrete element
} CustomTypes_Array_t;

typedef enum {
    SHIFT_LEFT = 0,
    SHIFT_RIGHT,
} CustomTypes_ArrayShiftDir_e;


/* Public Function Declaration */

// Fundamental Functionality //

/**
 * @brief initialises an array instance
 * 
 * @note the instance can be defined seperate from this functionality although, is not recommended 
 * 
 * @param data pointer to allocated memory 
 * @param elementSize size of each discrete element in array
 * @return CustomTypes_Array_t 
 */
CustomTypes_Array_t array_init(void * data, size_t elementSize);

/**
 * @brief Returns a pointer to type at a given array index
 * 
 * @param array pointer to array type instance
 * @param index element's index
 * @return void* value at given index
 */
void * array_at(CustomTypes_Array_t * array, uint32_t index);

/**
 * @brief Writes N elements to the array at a given index
 * 
 * @param array pointer to the array instance
 * @param index index to write to
 * @param src pointer to source data to write
 * @param len number of elements to write to array
 */
void array_set(CustomTypes_Array_t * array, uint32_t index, void * src, uint32_t len);

/**
 * @brief Shifts array data (element wise) left or right by N elements
 * 
 * @note 
 *  This function will update the tail value
 * 
 * @param array pointer to the array instance
 * @param direction direction of the shift (`SHIFT_LEFT`/`SHIFT_RIGHT`)
 * @param elements number of elements to shift by
 */
void array_shift(CustomTypes_Array_t * array, CustomTypes_ArrayShiftDir_e direction, uint32_t elements);

/**
 * @brief inserts N elements into array at the given index
 * 
 * @param array pointer to the array instance
 * @param index index to insert elements at 
 * @param src pointer to the source data
 * @param len number of elements to insert
 */
void array_insert(CustomTypes_Array_t * array, uint32_t index, void * src, uint32_t len);

/**
 * @brief removes N elements from the array
 * 
 * @param array pointer to the array instance
 * @param index index to remove elements from
 * @param len number of elements to remove
 */
void array_pop(CustomTypes_Array_t * array, uint32_t index, uint32_t len);

// Terse Functionality //

#endif