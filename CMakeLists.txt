cmake_minimum_required(VERSION 3.24.0)

project(algorithm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${MSVC})
    foreach(flag
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
    endif(${flag} MATCHES "/MD")
    endforeach(flag)
    # pass to external projects
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set (CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")
endif()

enable_testing()
set(GTEST_ROOT "external/googletest/googletest" CACHE PATH "Path to googletest")
add_subdirectory("external/googletest")
mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set_target_properties(gtest PROPERTIES FOLDER external)
set_target_properties(gtest_main PROPERTIES FOLDER external)
set_target_properties(gmock PROPERTIES FOLDER external)
set_target_properties(gmock_main PROPERTIES FOLDER external)

include_directories(include)

file(GLOB headers include/*.h)

add_executable(algorithm ${headers} main.cpp)
target_link_libraries(algorithm gtest gmock gtest_main)

add_custom_target(run
    COMMAND algorithm
    DEPENDS algorithm
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
