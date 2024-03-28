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
    - block_increment: the increment between memory blocks. For example, a memory block address could be defined as 