cmake_minimum_required(VERSION 3.20)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(MY_LIB_NAME MyLibrary)

add_library(${MY_LIB_NAME} SHARED
    src/mylibrary.cpp
    include/mylibrary.h
)

target_include_directories(${MY_LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_definitions(${MY_LIB_NAME} PRIVATE BUILDING_MY_LIBRARY)

target_compile_features(${MY_LIB_NAME} PUBLIC cxx_std_17)

install(TARGETS ${MY_LIB_NAME}
    EXPORT ${MY_LIB_NAME}Targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT ${MY_LIB_NAME}Targets
    FILE ${MY_LIB_NAME}Targets.cmake
    NAMESPACE ${MY_LIB_NAME}::
    DESTINATION lib/cmake/${MY_LIB_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${MY_LIB_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/MyLibraryConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${MY_LIB_NAME}Config.cmake"
    INSTALL_DESTINATION lib/cmake/${MY_LIB_NAME}
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/MyLibrary.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${MY_LIB_NAME}.pc"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${MY_LIB_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${MY_LIB_NAME}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${MY_LIB_NAME}Config.cmake"
    DESTINATION lib/cmake/${MY_LIB_NAME}
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${MY_LIB_NAME}.pc"
    DESTINATION lib/pkgconfig
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/example/"
    DESTINATION share/${MY_LIB_NAME}/example
)

set(CPACK_GENERATOR "ZIP")
set(CPACK_STRIP_FILES ON)
include(CPack)