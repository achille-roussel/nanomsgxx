cmake_minimum_required(VERSION 3.5)

option (NNXX_STATIC_LIB "Build static library instead of shared library." OFF)
option (NNXX_TESTS "Build and run tests for nanomsgxx." ON)


set(VERSION_MAJOR    0)
set(VERSION_MINOR    1)
set(VERSION_PATCH    0)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

project(nanomsgxx VERSION ${VERSION})

# project wide C++ options and include direcories:
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})



add_subdirectory(src)
if(NNXX_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(NNXX_TESTS)

