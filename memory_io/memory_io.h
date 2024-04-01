// TODO add a proper explination once kinks have been sorted out, until then see the readme
#ifndef MEMORY_IO_H_
#define MEMORY_IO_H_

/* Standard Includes */
#include "stdint.h"

/* Internal Includes */

/* Structures and Definitions */

/**
 * @brief 
 *  Type defining a generic 'write memory block' function. This interface should remain the same regardless of the memory paradigm.
 *  Non-zero return value is considered a failure
 * @note This function is treated as blocking
 */
typedef int (MemoryIO_WriteBlock_f)(uint32_t blockAddress, uint8_t * src);

/**
 * @brief 
 *  Type defining a generic 'read memory block' function. This interface should remain the same regardless of the memory paradigm. 
 *  Non-zero return value is considered a failure
 * @note This function is treated as blocking
 */
typedef int (MemoryIO_ReadBlock_f)(uint32_t blockAddress, uint8_t * dst);

/**
 * @brief Memory paradigm instance defining the memory paramters and IO function calls. 
 * todo: describe how this should be defined
 * todo: describe why the scratch is described externally
 * 
 */
typedef const struct {
    struct {
        uint32_t size;
        uint32_t increment;
    } block;
    MemoryIO_WriteBlock_f * write_block;
    MemoryIO_ReadBlock_f  * read_block;
    
    uint8_t * scratch;  // this should be allocated dynamically/statically a location in memory of the same size as a given paradigm's block
} MemoryIO_Paradigm_t;

/* Constants */

/* Public Function Declaration */

/**
 * @brief Writes len bytes from src to the given memory paradigm
 * 
 * @param paradigm pointer to memory paradigm instance
 * @param address byte address to be written to
 * @param src pointer to the source data to be written
 * @param len the number of bytes to write
 * @return int return value; 0 on success and 1 on failure (note that a failure is only asserted in the block IO functionality)
 */
int memory_io_bytes_set(MemoryIO_Paradigm_t * paradigm, uint32_t address, uint8_t * src, uint32_t len);

/**
 * @brief Reads len bytes from the given memory paradigm to dst
 * 
 * @param paradigm pointer to memory paradigm instance
 * @param address byte address to be read from
 * @param dst pointer to the dst data to be read to
 * @param len the number of bytes to read
 * @return int return value; 0 on success and 1 on failure (note that a failure is only asserted in the block IO functionality)
 */
int memory_io_bytes_get(MemoryIO_Paradigm_t * paradigm, uint32_t address, uint8_t * dst, uint32_t len);

/**
 * @brief Reads len blocks from the given memory paradigm to dst
 * 
 * @param paradigm pointer to the memory paradigm instance
 * @param address block address to be read from
 * @param dst pointer to the dst data to be read to
 * @param len the number of blocks to read
 * @return int return value; 0 on success and 1 on failure (note that a failure is only asserted in the block IO functionality)
 */
int memory_io_blocks_get(MemoryIO_Paradigm_t * paradigm, uint32_t address, uint8_t * dst, uint32_t len);

/**
 * @brief Writes len blocks from src to the given memory paradigm
 * 
 * @param paradigm pointer to memory paradigm instance
 * @param address block address to be written to
 * @param src pointer to the source data to be written
 * @param len the number of blocks to write
 * @return int return value; 0 on success and 1 on failure (note that a failure is only asserted in the block IO functionality)
 */
int memory_io_blocks_set(MemoryIO_Paradigm_t * paradigm, uint32_t address, uint8_t * src, uint32_t len);

#endif