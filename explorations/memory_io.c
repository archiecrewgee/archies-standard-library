/* Standard Includes */
#include "stdint.h"

/* Internal Includes */
#include "memory_io.h"

/* Structures */

/* Constants */

/* Private Function Declaration */
static uint32_t _byte_to_block_address(MemoryIO_Paradigm_t * paradigm, uint32_t address);   // converts a byte address to a block
static uint32_t _block_to_byte_address(MemoryIO_Paradigm_t * paradigm, uint32_t address);   // converts a block address to a byte


/* Public Function Definiton */
int memory_io_bytes_set(MemoryIO_Paradigm_t * paradigm, uint32_t address, uint8_t * src, uint32_t len) {
    // define blocks to 


    return 0;
}

int memory_io_bytes_get(MemoryIO_Paradigm_t * paradigm, uint32_t address, uint8_t * dst, uint32_t len) {
    // introduce variables for clarity
    const uint32_t  startBlock =  _byte_to_block_address(paradigm, address),
                    endBlock = _byte_to_block_address(paradigm, address + len);

    // for all blocks...
    for (uint32_t activeBlock = startBlock; activeBlock <= endBlock; activeBlock += paradigm->block.increment, dst += paradigm->block.size) {

    }


    return 0;
}

/* Private Function Definiton */
static uint32_t _byte_to_block_address(MemoryIO_Paradigm_t * paradigm, uint32_t address) { return (address / paradigm->block.size) * paradigm->block.increment; }
static uint32_t _block_to_byte_address(MemoryIO_Paradigm_t * paradigm, uint32_t address) { return (address / paradigm->block.increment) * paradigm->block.size; }
