if (DEFINED CONFIG_CMAKE_ALGORITHMS_ENABLE)
    message(STATUS "/algorithms")

    target_include_directories(${asl} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_sources(${asl} 
        PUBLIC 
            sort.c
    )
endif ()