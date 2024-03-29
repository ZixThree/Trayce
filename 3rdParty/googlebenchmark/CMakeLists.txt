CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

include(ExternalProject)

FIND_PACKAGE(Threads REQUIRED)

# Enable LTO: -DBENCHMARK_ENABLE_LTO=true

EXTERNALPROJECT_ADD(
        googlebenchmark_external
        URL             https://codeload.github.com/google/benchmark/tar.gz/v1.2.0
        URL_HASH        SHA1=5f26619848c59ddc354e2d51e2f196d2a6ddb189
        CMAKE_ARGS      "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        UPDATE_COMMAND  ""
        INSTALL_COMMAND ""
)

EXTERNALPROJECT_GET_PROPERTY(googlebenchmark_external SOURCE_DIR)
SET(_GBENCHMARK_INCLUDE_DIR ${SOURCE_DIR}/include)
FILE(MAKE_DIRECTORY ${_GBENCHMARK_INCLUDE_DIR})

EXTERNALPROJECT_GET_PROPERTY(googlebenchmark_external BINARY_DIR)
SET(_GBENCHMARK_LIBRARY_DIR ${BINARY_DIR}/src)

SET(_GBENCHMARK_EXTRA_LIBRARIES
        )
IF(MSVC)
    SET(_GBENCHMARK_EXTRA_LIBRARIES Shlwapi.lib)
ENDIF()

ADD_LIBRARY(gbenchmark STATIC IMPORTED GLOBAL)
SET_TARGET_PROPERTIES(
        gbenchmark
        PROPERTIES
            IMPORTED_LOCATION ${_GBENCHMARK_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}benchmark${CMAKE_STATIC_LIBRARY_SUFFIX}
            INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT};${_GBENCHMARK_EXTRA_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES ${_GBENCHMARK_INCLUDE_DIR}
)
ADD_DEPENDENCIES(gbenchmark googlebenchmark_external)
