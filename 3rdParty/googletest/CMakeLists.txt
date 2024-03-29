CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

include(ExternalProject)

FIND_PACKAGE(Threads REQUIRED)

# Investigate:
# * https://stackoverflow.com/questions/9689183/cmake-googletest
# * https://crascit.com/2015/07/25/cmake-gtest/

EXTERNALPROJECT_ADD(
        googletest_external
        URL                 https://codeload.github.com/google/googletest/tar.gz/release-1.8.0
        URL_HASH            SHA1=e7e646a6204638fe8e87e165292b8dd9cd4c36ed
        CMAKE_ARGS          "-Dgtest_force_shared_crt=ON;-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        UPDATE_COMMAND      ""
        INSTALL_COMMAND     ""
)

EXTERNALPROJECT_GET_PROPERTY(googletest_external SOURCE_DIR)
SET(_GTEST_INCLUDE_DIR ${SOURCE_DIR}/googletest/include)
SET(_GMOCK_INCLUDE_DIR ${SOURCE_DIR}/googlemock/include)
FILE(MAKE_DIRECTORY ${_GTEST_INCLUDE_DIR})
FILE(MAKE_DIRECTORY ${_GMOCK_INCLUDE_DIR})

EXTERNALPROJECT_GET_PROPERTY(googletest_external BINARY_DIR)
SET(_GTEST_LIBRARY_DIR ${BINARY_DIR}/googlemock/gtest)
SET(_GMOCK_LIBRARY_DIR ${BINARY_DIR}/googlemock)

SET(_MSVC_CONFIG)
IF(MSVC)
	SET(_MSVC_CONFIG "${CMAKE_CFG_INTDIR}/")
ENDIF()

add_library(gtest STATIC IMPORTED GLOBAL)
set_target_properties(
    gtest
    PROPERTIES
        IMPORTED_LOCATION ${_GTEST_LIBRARY_DIR}/${_MSVC_CONFIG}${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
        INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
        INTERFACE_INCLUDE_DIRECTORIES ${_GTEST_INCLUDE_DIR}
)
add_dependencies(gtest googletest_external)

add_library(gtest_main STATIC IMPORTED GLOBAL)
set_target_properties(
    gtest_main
    PROPERTIES
        IMPORTED_LOCATION ${_GTEST_LIBRARY_DIR}/${_MSVC_CONFIG}${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
        INTERFACE_LINK_LIBRARIES gtest
        INTERFACE_INCLUDE_DIRECTORIES ${_GTEST_INCLUDE_DIR}
)
add_dependencies(gtest_main googletest_external)

add_library(gmock STATIC IMPORTED GLOBAL)
set_target_properties(
    gmock
    PROPERTIES
        IMPORTED_LOCATION ${_GMOCK_LIBRARY_DIR}/${_MSVC_CONFIG}${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX}
        INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
        INTERFACE_INCLUDE_DIRECTORIES ${_GMOCK_INCLUDE_DIR}
)
add_dependencies(gmock googletest_external)

add_library(gmock_main STATIC IMPORTED GLOBAL)
set_target_properties(
    gmock_main
    PROPERTIES
        IMPORTED_LOCATION ${_GMOCK_LIBRARY_DIR}/${_MSVC_CONFIG}${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX}
        INTERFACE_LINK_LIBRARIES gmock
        INTERFACE_INCLUDE_DIRECTORIES ${_GMOCK_INCLUDE_DIR}
)
add_dependencies(gmock_main googletest_external)


FUNCTION(ADD_GTEST)
    SET(OPTIONS PROVIDE_MAIN)
    SET(ONEVALUEARGS TARGET)
    SET(MULTIVALUEARGS SOURCES LIBRARIES DEPENDS)
    CMAKE_PARSE_ARGUMENTS(ADD_GTEST "${OPTIONS}" "${ONEVALUEARGS}" "${MULTIVALUEARGS}" ${ARGN})

    SET(TARGET_NAME gtest_${ADD_GTEST_TARGET})
    ADD_EXECUTABLE(${TARGET_NAME} ${ADD_GTEST_SOURCES})
    TARGET_LINK_LIBRARIES(${TARGET_NAME} gtest)
    TARGET_LINK_LIBRARIES(${TARGET_NAME} ${ADD_GTEST_TARGET})
    IF(ADD_GTEST_PROVIDE_MAIN)
        TARGET_LINK_LIBRARIES(${TARGET_NAME} gtest_main)
    ENDIF()
    IF(ADD_GTEST_LIBRARIES)
        TARGET_LINK_LIBRARIES(${TARGET_NAME} PRIVATE ${ADD_GTEST_LIBRARIES})
    ENDIF()
    IF(ADD_GTEST_DEPENDS)
        ADD_DEPENDENCIES(${TARGET_NAME} ${ADD_GTEST_DEPENDS})
    ENDIF()

    ADD_TEST(NAME ${TARGET_NAME} COMMAND $<TARGET_FILE:${TARGET_NAME}>)

    ADD_CUSTOM_TARGET(
            auto_test_${TARGET_NAME}
            ALL
            COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failure -R ${TARGET_NAME}
            DEPENDS ${ADD_GTEST_TARGET}
    )

ENDFUNCTION()
