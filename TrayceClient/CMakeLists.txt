PROJECT(TrayceClient)

SET(TrayceClient_HEADERS
        include/Trayce/Trayce.h
        )
SET(TrayceClient_SOURCES
        src/Trayce.cpp
        )

ADD_LIBRARY(TrayceClientStatic STATIC ${TrayceClient_HEADERS} ${TrayceClient_SOURCES})
TARGET_INCLUDE_DIRECTORIES(TrayceClientStatic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#ADD_LIBRARY(TrayceClient SHARED ${TrayceClient_HEADERS} ${TrayceClient_SOURCES})
#TARGET_INCLUDE_DIRECTORIES(TrayceClient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)