if (DEFINED CONFIG_CMAKE_MEMORY_ENABLE)
    message(STATUS "/memory")

    target_include_directories(${asl} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_sources(${asl} PUBLIC memory.c)
endif ()