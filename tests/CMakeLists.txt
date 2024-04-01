message("Building tests")

target_include_directories(${asl} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${asl} 
    PRIVATE 
        tests.c
) 

add_subdirectory(unit_tests)