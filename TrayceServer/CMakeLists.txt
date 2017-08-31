PROJECT(TrayceServer)

SET(TrayceServer_HEADERS
        include/Trayce/Server.h
        )
SET(TrayceServer_SOURCES
        src/Server.cpp
        )

ADD_EXECUTABLE(TrayceServer ${TrayceServer_HEADERS} ${TrayceServer_SOURCES})
TARGET_INCLUDE_DIRECTORIES(TrayceServer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

TARGET_LINK_LIBRARIES(TrayceServer TrayceClientStatic)
TARGET_LINK_LIBRARIES(TrayceServer TrayceCommStatic)