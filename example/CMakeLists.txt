cmake_minimum_required(VERSION 3.20)

project(test VERSION 1.0 LANGUAGES CXX)

add_executable(test test.cpp)

set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../..")

set(USE_PKG_CONFIG OFF)

if (USE_PKG_CONFIG)
    message(STATUS "Using pkg-config to find MyLibrary")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(MyLibrary REQUIRED mylibrary)
    target_include_directories(test PRIVATE ${MyLibrary_INCLUDE_DIRS})
    target_link_directories(test PRIVATE ${MyLibrary_LIBRARY_DIRS})
    target_link_libraries(test PRIVATE ${MyLibrary_LIBRARIES})
else()
    message(STATUS "Using CMake find_package to find MyLibrary")
    find_package(MyLibrary REQUIRED)
    target_link_libraries(test PRIVATE MyLibrary::MyLibrary)
endif()