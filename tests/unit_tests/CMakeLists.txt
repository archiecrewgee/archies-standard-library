message("| unit tests |")

target_include_directories(${asl} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${asl} 
    PRIVATE
        unit_tests_memory_io.c   
)

message(STATUS "memory_io")