/* Standard Includes */
#include "stdint.h"

/* Internal Includes */
#include "memory_io.h"

#include "macros.h"
#include "memory.h"

/* Structures */

/* Constants */

/* Private Function Declaration */
static uint32_t _byte_to_block_address(MemoryIO_Medium_t * medium, uint32_t address);   // converts a byte address to a block
static uint32_t _block_to_byte_address(MemoryIO_Medium_t * medium, uint32_t address);   // converts a block address to a byte

// updates the current state of the byte-by-byte processor
// byte-by-byte interaction is performed with block processing acting as a state machine:
//  0: start state
//  1. partial interaction (msb offset) 
//  2. complete block interaction
//  3. partial interaction (lsb offset)
//  4. exit state
// initial state is defined as so:
//  1 = address not alligned with block boundry AND NOT remaining length (to read) is less than the size of a block  
//  2 = absence of other states
//  3 = remaining length to process (in bytes) is less than the size of a block
//  4 = no other conditions met AND (current state is [3] OR remaining length is zero) 
// given this from all start positions, noting that 2 state can always go to itself
//  1 -> 2 ->? 3 -> 4
//  2 ->? 3 -> 4
//  3 -> 4
static uint32_t _byte_processor_state_update(MemoryIO_Medium_t * medium, uint32_t remainingLen, uint32_t currentState);
static uint32_t _byte_processor_state_init(MemoryIO_Medium_t * medium, uint32_t startAddress, uint32_t remainingLen);

/* Public Function Definiton */
int memory_io_bytes_set(MemoryIO_Medium_t * medium, uint32_t address, uint8_t * src, uint32_t len) {
    // define blocks to 


    return 0;
}

int memory_io_bytes_get(MemoryIO_Medium_t * medium, uint32_t address, uint8_t * dst, uint32_t len) {
    // introduce local variables
    uint32_t currentBlock = _byte_to_block_address(medium, address);
    uint32_t remainingLen = len, activeLen;
    uint32_t state = _byte_processor_state_init(medium, address, remainingLen);

    // itterate through all blocks 
    while (state < 4) {
        // read current block
        asl_assert_r(medium->read_block(currentBlock, medium->scratch), 1);

        // based on current state...
        switch (state) {
            case 1: // start byte is offset from start of block
                activeLen = medium->block.size - (address % medium->block.size);
                copy(dst, medium->scratch + (address % medium->block.size), activeLen);
                break;
            case 2: // bytes are encapsulated by block
                activeLen = medium->block.size;
                copy(dst, medium->scratch, activeLen);
                break;
            case 3: // bytes aligned with start of block but do not reach end
                activeLen = remainingLen;
                copy(dst, medium->scratch + medium->block.size - remainingLen, activeLen);
                break;
            default:
                break;
        }

        // itterate active block, the remaining length to calculate and the destination pointer
        currentBlock += medium->block.increment;
        remainingLen -= activeLen;
        dst += activeLen;

        state = _byte_processor_state_update(medium, remainingLen, state);
    }

    return 0;
}

int memory_io_blocks_set(MemoryIO_Medium_t * medium, uint32_t address, uint8_t * src, uint32_t len) {
    uint32_t endAddress = address + len;

    // for all blocks write to the memory medium IO functionality (asserting zero value) from the src pointer
    for (; address < endAddress; address += medium->block.increment, src += medium->block.size) {
        asl_assert_r(medium->write_block(address, src), 1);
    }

    return 0;
}

int memory_io_blocks_get(MemoryIO_Medium_t * medium, uint32_t address, uint8_t * dst, uint32_t len) {
    uint32_t endAddress = address + len;

    // for all blocks read from the memory medium IO functionality (asserting zero value) and add to the destination pointer
    for (; address < endAddress; address += medium->block.increment, dst += medium->block.size) {
        asl_assert_r(medium->read_block(address, dst), 1);
    }

    return 0;
}


/* Private Function Definiton */
static uint32_t _byte_to_block_address(MemoryIO_Medium_t * medium, uint32_t address) { return (address / medium->block.size) * medium->block.increment; }
static uint32_t _block_to_byte_address(MemoryIO_Medium_t * medium, uint32_t address) { return (address / medium->block.increment) * medium->block.size; }

static uint32_t _byte_processor_state_update(MemoryIO_Medium_t * medium, uint32_t remainingLen, uint32_t currentState) {
    if (currentState == 3 || remainingLen == 0) {
        return 4;
    } else if (remainingLen < medium->block.size) {
        return 3;
    } 
    // the previous two conditions and setup at initialisation implies: currentState == 1
    return 2;
}

static uint32_t _byte_processor_state_init(MemoryIO_Medium_t * medium, uint32_t startAddress, uint32_t remainingLen) {
    if (remainingLen < medium->block.size) {
        return 3;
    } else if (startAddress % medium->block.size) {
        return 1;
    }

    return 2;
}