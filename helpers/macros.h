/**
 * This file contains basic macros for simplifying commonly used pieces of code. 
 * Note that consideration should be taken to ensure these are minimally used, transparent in functionality and neccesary
 */
#ifndef MACROS_H_
#define MACROS_H_

/**
 * @brief Assets the given condition resolves to zero. If a non-zero condition is encountered then return the provided value
 * 
 */
#define asl_assert_r(condition, returnValue) {if (condition) { return returnValue; }}

/**
 * @brief Assets the given condition resolves to zero. If a non-zero condition is encountered then return the condition value (assuming it is of int type)
 * 
 */
#define asl_assert_v(condition) {int returnValue = condition; if (returnValue) { return returnValue; }}

/**
 * @brief 
 *  Returns the nuber of elements in an array of a given type
 * @note 
 *  The array length and type must be declared in scope
 * 
 */
#define asl_array_len(array) (sizeof(array) / sizeof(*array))

#endif