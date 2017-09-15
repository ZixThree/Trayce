PROJECT(TrayceComm)

SET(TrayceComm_HEADERS
        include/Trayce/Comm/Comm.h
        include/Trayce/Comm/Socket.h
        )

SET(TrayceComm_SOURCES_Windows
        src/SocketImpl.Windows.cpp
        )

SET(TrayceComm_SOURCES
        src/Comm.cpp
        src/Socket.cpp
        src/SocketImpl.h
        src/InternalData.h
        ${TrayceComm_SOURCES_Windows}
        )

ADD_LIBRARY(TrayceCommStatic STATIC ${TrayceComm_HEADERS} ${TrayceComm_SOURCES})
TARGET_INCLUDE_DIRECTORIES(TrayceCommStatic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
TARGET_LINK_LIBRARIES(TrayceCommStatic TrayceCore)
