/* Preamble */
/* Standard Includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// TODO: make own memcpy functions and remove the std string

/* Internal Includes */

/* Structures */

/* Constants */
#define UINT_MAX_32_BIT 0xffffffff

// saturates 64 bit (q32_32) number as a q16_16 32 bit number
static uint32_t _saturate_32_bit(uint64_t n) {
    printf("\n%d", n);
    // shift right 16 bits to remove last 16 floating point bits
    n = n >> 16;    
    printf("\n%d", n);
    // check if value greater than 32 bit max and saturate
    return (n > (uint64_t) UINT_MAX_32_BIT) ?  UINT_MAX_32_BIT : n;
}

// normalise a 32 bit q format number such that it is a 64 bit q32_32
static uint64_t _normalise_32_bit(uint32_t n, uint16_t nPointOffset) {
    uint64_t returnValue = (uint64_t) n;    // create 64 bit storage value
    return returnValue << nPointOffset;     // return 64 bit value shifted by corrected point offset: numSize - (numSize - pOffset) -> pOffset
}

// returns the index of the MSB of number 'n' i.e. 0100 will return 1, 0001 will return 3, 0000 will return 4
static uint8_t _index_msb(uint64_t n) {
    for (uint8_t i = 63; i != 0 ; i--) {
        if ((n >> i) & 1U) {
            return 63 - i;
        }
    }
    return 64;
}
/* Private Function Declaration */
// Divides two unsigned Q point numbers from one another [out = a / b]
uint32_t q_format_divide(uint32_t a, uint32_t b, uint16_t aPointOffset, uint16_t bPointOffset) {
    // correct for divide by zero
    if (b == 0) { return UINT_MAX_32_BIT; }

    // normalise inputs to 64 bit q32_32 numbers
    uint64_t aNorm = _normalise_32_bit(a, aPointOffset);
    uint64_t bNorm = _normalise_32_bit(b, bPointOffset);

    // introduce result
    uint64_t result = 0;

    // align denominator
    uint8_t aMsb = _index_msb(aNorm);
    uint8_t bMsb = _index_msb(bNorm);

    int16_t difference = bMsb - aMsb;
    if (difference >= 0) { bNorm <<= difference; }
    else                 { bNorm >>= -difference; }

    // start at aMsb
    for (uint8_t activeMsb = aMsb; activeMsb < 64; activeMsb++) {
        // if a is equal or greater then it is divisable by current b
        if (aNorm >= bNorm) {
            result += (uint64_t)1 << (uint8_t)(32 + difference - (activeMsb - aMsb));
            aNorm -= bNorm;
            if (aNorm == 0) { break; }
        }
        bNorm >>= 1;
    }

    return _saturate_32_bit(result);
}


/* Public Function Definiton */
int main(void) {
    printf("Hola amigos");
    uint64_t test = 0;

    printf("\n%d", _index_msb((uint64_t)1 << 45));

    printf("\n10 / 5 = %d", q_format_divide((uint32_t) 10, (uint32_t) 5, 32, 32)); 

    printf("\n200 / 400 = %d", q_format_divide((uint32_t) 200, (uint32_t) 400, 32, 32)); 
    printf("\n0.5 / .25 = %d", q_format_divide((uint32_t) 1, (uint32_t) 1, 31, 30));

    printf("\n602.875 / 13.25 = %d", q_format_divide(0x025AE000, 0x000D4000, 16, 16)); 

    return 0;
}

/* Private Function Definiton */