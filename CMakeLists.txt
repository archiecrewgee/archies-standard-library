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

# TODO: potentially need to set linker language CXX

message("Beginning Project Compilation")

# Set project name #
project("STANDARD_LIBRARY")

# Create the project as an executable #
set(PROJECT_EXECUTABLE ${PROJECT_NAME})
add_executable(${PROJECT_EXECUTABLE} "")

message("Created project executable " ${PROJECT_EXECUTABLE})

# Include sub directories #


# add main.c to executable
target_sources(${PROJECT_EXECUTABLE} PRIVATE main.c)