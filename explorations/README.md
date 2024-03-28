This is a set of interface explorations without consideration of proper project structure, successful items should be shifted to a proper module

# Memory Bridge

The memory bridge exists to abstract and simplify the process of syncing and interacting with different memory paradigms on embedded devices. The example usage would be an MCU that must interface with and sync its FLASH memory, and say two external peripherals.

The goals consist of two stages:

1. Hide the manipulation of memory blocks and bits that must occur on interaction with a given variable
2. Hide the process of defining and sectioning memory

Achieving these goals should reduce the errors related to memory manipulation and simplify scalability of design

nomenclature:
 - parameter: zone of memory that contains a given named value
 - block: minimum readable/writable granularity of a given memory paradigm. For example flash may only be written to in 1kB size pages
 - paradigm: given memory medium (i.e. internal flash, external RTC RAM etc.). These are defined by:
    - block_size: the size (in bytes) of the memory's block
    - block_increment: the increment between memory blocks. For example, a memory block address could be defined as a byte or arbitary offset
 - tag: an arbitary tag given to parameters, parameters with shared tags are grouped


how is memory defined, imagine a json file:

```JSON
"paradigm" : {
    "name" : {
        "block_size" : a,
        "block_increment" : b,
        "total_size" : c,       // in blocks
        "tags" : [
            "tag_0",
            "tag_1",
            // ...
        ]
    },
    // ...
    "internal_flash" : {
        "block_size" : 1024,
        "block_increment" : 1024,
        "tags" : [
            "default_values", "crypt_keys"
        ]
    }
},
"parameter" : {
    "name" : {
        "size" : 10,     // <- in bits
        "tag" : "tag_x",
        // items such as default values and validation parameters should be added here
    },
    // ...
    "lux_sensor_scaler_q16_16" : {
        "size" : 32,
        "tag" : "default_values"
    }
}

```

Some tool should convert from the JSON format to a software usable memory map:

```C
// data structures should exist for tag wise interaction
typedef union {
    struct {
        uint8_t 1_byte_parameter;
        uint8_t reserved_0 [3];
        uint32_t 4_byte_parameter;
        uint8_t N_byte_long_param[14];
        uint8_t reserved_1 [2];
    } data,
    uint8_t raw,
} MyTag_u;  // packed to 1

// paradigm functions are defined by the user
if_write_block(address, dst, src);
if_read_block(address, dst);

// use instance based design
MemParadigm_s internalFlash = {
    .block = {
        size = INTERNAL_FLASH_BLOCK_SIZE,
        increment = INTERNAL_FLASH_BLOCK_INCREMENT,
    },
    .write_block = if_write_block,
    .read_block = if_read_block,
}; 
mem_init(&internalFlash);
// mem_deinit(&internalFlash);

// note that <tag>_<parameter> is a macro that expands to parameter data such as block offset and size, this stops ram space being taken up by constant parameters
mem_parameter_get(&internalFlash, <tag>_<parameter>, &dst);
mem_parameter_set(&internalFlash, <tag>_<parameter>, &dst);
mem_tag_get(&internalFlash, <tag>, &dst);
mem_tag_set(&internalFlash, <tag>, &dst);

// todo should it be: instance, dst, src instead??
```