#ifndef SORT_H_
#define SORT_H_

/* Standard Includes */
#include "stdbool.h"
#include "stddef.h"

/* Internal Includes */

/* Structures */

/**
 * @brief 
 *  Defines the comparison function of the bubble sort where A is the element of the list in question and B is the element it is compared to. 
 *  A swap occurs if the function returns true
 * @example 
 *  to sort a list such that the greatest element is at the first element:
 *  bool greater_than(void * a, void * b) {
 *      return *((int *)a) > *((int *) b);
 *  }
 *
 *  int main() {
 *      int array[] = { 0, 2, 5, 3, 7 };
 * 
 *      sort_bubble(array, sizeof(int), sizeof(array) / sizeof(int), greater_than);
 * 
 *      // the new array will not be: 7, 5, 3, 2, 0
 *  }
 * 
 */
typedef bool (SortBubbleKey_t)(void * a, void * b);

/* Constants */

/* Public Function Declaration */

/**
 * @brief Uses a bubble sort to sort, in descending order, an arbitary array of elements according to a key.
 * 
 * @param arr the array of elements to sort
 * @param elementSize the size of each individual element
 * @param arrLen the number of elements in the array
 * @param key the key to sort elements by
 */
void sort_bubble(void * arr, size_t elementSize, uint32_t arrLen, SortBubbleKey_t key);

#endif