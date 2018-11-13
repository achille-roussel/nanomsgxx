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

set(NNXX_HDRS   ./nanomsg/ext/nnxx_ext.h
                ./nnxx/bus.h
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
                ./nnxx/unittest.h)

add_library(${PROJECT_NAME} ${NANOMSG_SRCS} ${NNXX_SRCS})
add_library(lib::nnxx ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC "." ${NANOMSG_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC nanomsg)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${NNXX_HDRS} DESTINATION include/nnxx)