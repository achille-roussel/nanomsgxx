project(nnxx)

find_package(nanomsg CONFIG REQUIRED)

IF(!nanomsg_FOUND)
    IF (WIN32)
    # This is not advanced yet, as it does not work for custom install locations.
    # The general directory, however, is found by `find_package`.
    # --> Throw an error, if nanomsg cannot be found
        message(FATAL_ERROR "nanomsg library is required, but not found in standard location.")
    ELSE()
        # on UNIX platforms pkg_config can be used as fallback solution
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(nanomsg REQUIRED nanomsg)
    ENDIF()
ENDIF()

set(CMAKE_INSTALL_BINDIR "bin")
set(CMAKE_INSTALL_INCLUDEDIR "include")
set(CMAKE_INSTALL_LIBDIR "lib")


set(NANOMSG_SRCS ./nanomsg/ext/nnxx_ext.c)

set(NNXX_SRCS   ./nnxx/error.cpp
                ./nnxx/message.cpp
                ./nnxx/message_control.cpp
                ./nnxx/message_istream.cpp
                ./nnxx/message_iterator.cpp
                ./nnxx/message_ostream.cpp
                ./nnxx/message_streambuf.cpp
                ./nnxx/nn.cpp
                ./nnxx/poll.cpp
                ./nnxx/pubsub.cpp
                ./nnxx/reqrep.cpp
                ./nnxx/socket.cpp
                ./nnxx/survey.cpp
                ./nnxx/tcp.cpp
                ./nnxx/timeout.cpp)

set(NNXX_HDRS   ./nnxx/bus.h
                ./nnxx/chrono.h
                ./nnxx/error.h
                ./nnxx/inproc.h
                ./nnxx/ipc.h
                ./nnxx/message.h
                ./nnxx/message_control.h
                ./nnxx/message_istream.h
                ./nnxx/message_iterator.h
                ./nnxx/message_ostream.h
                ./nnxx/message_streambuf.h
                ./nnxx/nn.h
                ./nnxx/pair.h
                ./nnxx/pipeline.h
                ./nnxx/poll.h
                ./nnxx/pubsub.h
                ./nnxx/reqrep.h
                ./nnxx/socket.h
                ./nnxx/survey.h
                ./nnxx/tcp.h
                ./nnxx/timeout.h
                ./nnxx/unittest.h
                ./nnxx/message_istream.hpp
                ./nnxx/message_ostream.hpp
                ./nnxx/message_streambuf.hpp
                ./nnxx/socket.hpp)

if (NNXX_STATIC_LIB)
    add_library(${PROJECT_NAME} STATIC ${NANOMSG_SRCS} ${NNXX_SRCS})
    set(PACKAGE_LINK_LIBRARIES ${PROJECT_NAME})
else()
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    add_library(${PROJECT_NAME} SHARED ${NANOMSG_SRCS} ${NNXX_SRCS})
    set(PACKAGE_LINK_LIBRARIES ${PROJECT_NAME} nanomsg)
    
endif()

add_library(lib::nnxx ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC nanomsg)

target_include_directories(${PROJECT_NAME} PUBLIC   ${NANOMSG_INCLUDE_DIRS} 
                                                    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                                                    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)


# Generate and install CMake package:
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${NNXX_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

include(CMakePackageConfigHelpers)
set(PACKAGE_INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${VERSION}
)
install(EXPORT ${PROJECT_NAME}
        DESTINATION ${PACKAGE_INSTALL_DESTINATION}
)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    VERSION ${VERSION}
    COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION ${PACKAGE_INSTALL_DESTINATION}
    PATH_VARS CMAKE_INSTALL_PREFIX
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    DESTINATION ${PACKAGE_INSTALL_DESTINATION}
)

# Generate and install PkgConfig file:
set(prefix ${CMAKE_INSTALL_PREFIX})
set(libdir ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
CONFIGURE_FILE("../libnnxx.pc.in" "${CMAKE_CURRENT_BINARY_DIR}/libnnxx.pc" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libnnxx.pc" 
        DESTINATION "${libdir}/pkgconfig")