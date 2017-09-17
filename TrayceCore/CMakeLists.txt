PROJECT(TrayceCore)

SET(TrayceCore_HEADERS
        include/Trayce/Time/DateTime.h
        include/Trayce/Time/TimePoint.h
        include/Trayce/Time/TimeSpan.h
        include/Trayce/LogService.h
        )
SET(TrayceCore_SOURCES
        src/LogService.cpp
        src/InternalData.h
        )

ADD_LIBRARY(TrayceCore STATIC ${TrayceCore_HEADERS} ${TrayceCore_SOURCES})
TARGET_INCLUDE_DIRECTORIES(TrayceCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

ADD_SUBDIRECTORY(tests)