PROJECT(TrayceCore)

SET(TrayceCore_HEADERS
        include/Trayce/LogService.h
        include/Trayce/Time.h
        )
SET(TrayceCore_SOURCES
        src/LogService.cpp
        src/InternalData.h
        )

ADD_LIBRARY(TrayceCore STATIC ${TrayceCore_HEADERS} ${TrayceCore_SOURCES})
TARGET_INCLUDE_DIRECTORIES(TrayceCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

ADD_SUBDIRECTORY(tests)