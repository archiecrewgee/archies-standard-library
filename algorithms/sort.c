/* Standard Includes */
#include "stddef.h"
#include "stdint.h"

/* Internal Includes */
#include "sort.h"
#include "memory.h"

/* Structures */

/* Constants */

/* Private Function Declaration */

/* Public Function Definiton */

/* Private Function Definiton */
void sort_bubble(void * arr, size_t elementSize, uint32_t arrLen, SortBubbleKey_t key) {
    // todo: add swap count
    // todo does this hit the last value
    // declare variables for clarity
    void * element, * other;

    // iterrate through all items in array, exiting once they have been exhausted. Note that then frontmost element is not explored
    while (arrLen != 1) {
        arrLen--;

        // assign pointer to the current element in question
        element = arr + (arrLen * elementSize);

        // until element reaches end of array
        while (element != arr) {
            other = element - elementSize;          // introduce the 'other' element for brevity

            if (!key(element, other)) { break; }    // no swap occurs if key fails so break

            // perform swap and update element 
            swap(element, other, elementSize);
            element = other;
            swaps++;
        }
    }

    return arr;
}