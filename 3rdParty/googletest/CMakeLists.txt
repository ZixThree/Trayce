CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

include(ExternalProject)

FIND_PACKAGE(Threads REQUIRED)

EXTERNALPROJECT_ADD(
        googletest_external
        URL                 https://codeload.github.com/google/googletest/tar.gz/release-1.8.0
        URL_HASH            SHA1=e7e646a6204638fe8e87e165292b8dd9cd4c36ed
        UPDATE_COMMAND      ""
        INSTALL_COMMAND     ""
)

EXTERNALPROJECT_GET_PROPERTY(googletest_external SOURCE_DIR)
SET(_GTEST_INCLUDE_DIR ${SOURCE_DIR}/googletest/include)
SET(_GMOCK_INCLUDE_DIR ${SOURCE_DIR}/googlemock/include)

EXTERNALPROJECT_GET_PROPERTY(googletest_external BINARY_DIR)
SET(_GTEST_LIBRARY_DIR ${BINARY_DIR}/googlemock/gtest)
SET(_GMOCK_LIBRARY_DIR ${BINARY_DIR}/googlemock)

add_library(gtest STATIC IMPORTED GLOBAL)
set_target_properties(
    gtest
    PROPERTIES
        IMPORTED_LOCATION ${_GTEST_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
        INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
        INTERFACE_INCLUDE_DIRECTORIES ${_GTEST_INCLUDE_DIR}
)
add_dependencies(gtest googletest_external)

add_library(gtest_main STATIC IMPORTED GLOBAL)
set_target_properties(
    gtest_main
    PROPERTIES
        IMPORTED_LOCATION ${_GTEST_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
        INTERFACE_LINK_LIBRARIES gtest
        INTERFACE_INCLUDE_DIRECTORIES ${_GTEST_INCLUDE_DIR}
)
add_dependencies(gtest_main googletest_external)

add_library(gmock STATIC IMPORTED GLOBAL)
set_target_properties(
    gmock
    PROPERTIES
        IMPORTED_LOCATION ${_GMOCK_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX}
        INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
        INTERFACE_INCLUDE_DIRECTORIES ${_GMOCK_INCLUDE_DIR}
)
add_dependencies(gmock googletest_external)

add_library(gmock_main STATIC IMPORTED GLOBAL)
set_target_properties(
    gmock_main
    PROPERTIES
        IMPORTED_LOCATION ${_GMOCK_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX}
        INTERFACE_LINK_LIBRARIES gmock
        INTERFACE_INCLUDE_DIRECTORIES ${_GMOCK_INCLUDE_DIR}
)
add_dependencies(gmock_main googletest_external)


FUNCTION(ADD_GTEST NAME)
    SET(OPTIONS)
    SET(ONEVALUEARGS)
    SET(MULTIVALUEARGS)
    MESSAGE(FATAL_ERROR "Not Implemented.")
ENDFUNCTION()
