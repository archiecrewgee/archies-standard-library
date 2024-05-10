# archies_standard_library

Experimental project for testing small software libraries.

# build system

 * flat folder structure per module
 * kconfig enable per module 
 * compiles to library with public headers
 * test compilation done with test flag
 * modules may have dependancies <- corrected for in kconfig
 * top level main.c for debugging during development
 * may or may not exist in dockerfile as consideration but effort should only be exerted to ensure it works in environment
 * build scripts
 * configure scripts
 * compilation selection and cmake processing should occur at the same directory level 
 * obvs could use testing framework like gmock but tinycrypt had a nice int return build thing going which i actually really enjoyed so will try unit tests with that

# setup 

# files

# todo
We really need a basic return type functionality: maybe an asl_types. Until then we'll use int <- this change should come along with the proper structuring 
add instance based heap in memory
actually do the array type
    maybe make general buffer with fifo, stack design and basic array; what about linked lists???


    TALK ABOUT AVOIDING CONSTS IN STRUCTS TO GIVE USER FREEDOm