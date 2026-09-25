cmake_minimum_required(VERSION 3.15)

project(Helper VERSION 1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/submodules/configuration/cmake")
include(ProjectOptions)
include(CoverageSupport)

option(COVERAGE "Enable coverage reporting" OFF)

enable_project_options()
enable_project_coverage()

check_project_compiler(
    MSVC_MIN 19.20
    GCC_MIN 10.2
    CLANG_MIN 11.0
    ALLOW_TEGRA_GCC
)

configure_library_kind()

include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/include)

if(NOT TARGET helper)
    add_subdirectory(src)

    add_library(helper ${LIBRARY_KIND} $<TARGET_OBJECTS:HELPER_SRC>)
    target_link_libraries(helper)

    if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
        enable_testing()
        add_subdirectory(test)

        setup_project_coverage(
            TARGET helper
            TEST_TARGET tests
            SOURCES
                "${PROJECT_SOURCE_DIR}/include"
                "${PROJECT_SOURCE_DIR}/src"
        )

    endif()

endif()
