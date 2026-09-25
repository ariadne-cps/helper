cmake_minimum_required(VERSION 3.15)

project(Helper VERSION 1.0)

include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/configuration/cmake/ProjectOptions.cmake")

setup_project()

include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/include)

if(NOT TARGET helper)
    add_subdirectory(src)

    add_library(helper ${LIBRARY_KIND} $<TARGET_OBJECTS:HELPER_SRC>)
    set_target_properties(helper PROPERTIES OUTPUT_NAME "ariadne-helper")
    target_link_libraries(helper)

    setup_standalone_project_tests(
        TARGET helper
        TEST_DIRECTORY test
        TEST_TARGET tests
        SOURCES
            "${PROJECT_SOURCE_DIR}/include"
            "${PROJECT_SOURCE_DIR}/src"
    )

endif()
