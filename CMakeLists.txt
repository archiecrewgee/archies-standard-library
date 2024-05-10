# This is the entrance point for 'Archie's standard library'
# The code below compiles to a stand alone 'main.c' file as the executable 'project executable'
# TODO: make this compile to a library with a specific focus on the headers, explain this all within the file

# Specify minimum CMake version #
cmake_minimum_required(VERSION 3.21)

# set cmake options
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")
set(CMAKE_VERBOSE_BUILD ON CACHE BOOL "ON")

# force depreciation warning off #
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

# set CMakeLists scripts path # 
message("Extending CMake module search path")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Gather KConfig variables for use in CMake #
set(kconfig_path "${CMAKE_CURRENT_SOURCE_DIR}/.config")
include(import_kconfig)
import_kconfig("CONFIG_CMAKE" ${kconfig_path}) 
message(STATUS "gathered KConfig variables at path: " ${kconfig_path})


# Set project name #
project("asl")

# Begin project compilation #
message("Beginning Project Compilation")

# Create the project as an executable #
set(asl ${PROJECT_NAME})
add_executable(${asl} "")

message("Created project executable: " ${asl})

# Include sub directories #
add_subdirectory(helpers)
add_subdirectory(algorithms)
add_subdirectory(memory)
add_subdirectory(memory_io)

# add debugging mainc.c to executable or tests
if (DEFINED CONFIG_CMAKE_TESTS_ENABLE)
    add_subdirectory(tests)
else ()
    target_sources(${asl} PRIVATE main.c)
endif ()