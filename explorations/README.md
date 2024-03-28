This is a set of interface explorations without consideration of proper project structure, successful items should be shifted to a proper module

# Memory Bridge

The memory bridge exists to abstract and simplify the process of syncing and interacting with different memory paradigms on embedded devices. The example usage would be an MCU that must interface with and sync its FLASH memory, and say two external peripherals.

The goals consist of two stages:

1. Hide the manipulation of memory block and bit interaction