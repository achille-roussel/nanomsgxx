project(nnxx_tests)
include(CTest)

message(STATUS ${EXECUTABLE_OUTPUT_PATH})

add_executable(test_message ./test_message.cpp)
target_link_libraries(test_message nnxx)
add_test(message ${EXECUTABLE_OUTPUT_PATH}/test_message)

add_executable(test_message_istream ./test_message_istream.cpp)
target_link_libraries(test_message_istream nnxx)
add_test(message_istream ${EXECUTABLE_OUTPUT_PATH}/test_message_istream)

add_executable(test_message_ostream ./test_message_ostream.cpp)
target_link_libraries(test_message_ostream nnxx)
add_test(message_ostream ${EXECUTABLE_OUTPUT_PATH}/test_message_ostream)

add_executable(test_nnxx_ext ./test_nnxx_ext.cpp)
target_link_libraries(test_nnxx_ext nnxx)
add_test(nnxx_ext ${EXECUTABLE_OUTPUT_PATH}/test_nnxx_ext)

add_executable(test_pair ./test_pair.cpp)
target_link_libraries(test_pair nnxx)
add_test(pair ${EXECUTABLE_OUTPUT_PATH}/test_pair)

add_executable(test_pipeline ./test_pipeline.cpp)
target_link_libraries(test_pipeline nnxx)
add_test(pipeline ${EXECUTABLE_OUTPUT_PATH}/test_pipeline)

add_executable(test_poll ./test_poll.cpp)
target_link_libraries(test_poll nnxx)
add_test(poll ${EXECUTABLE_OUTPUT_PATH}/test_poll)

add_executable(test_pubsub ./test_pubsub.cpp)
target_link_libraries(test_pubsub nnxx)
add_test(pubsub ${EXECUTABLE_OUTPUT_PATH}/test_pubsub)

add_executable(test_readme ./test_readme.cpp)
target_link_libraries(test_readme nnxx)
add_test(readme ${EXECUTABLE_OUTPUT_PATH}/test_readme)

add_executable(test_reqrep ./test_reqrep.cpp)
target_link_libraries(test_reqrep nnxx)
add_test(reqrep ${EXECUTABLE_OUTPUT_PATH}/test_reqrep)

add_executable(test_reqrep_multi ./test_reqrep_multi.cpp)
target_link_libraries(test_reqrep_multi nnxx)
add_test(reqrep_multi ${EXECUTABLE_OUTPUT_PATH}/test_reqrep_multi)

add_executable(test_socket ./test_socket.cpp)
target_link_libraries(test_socket nnxx)
add_test(socket ${EXECUTABLE_OUTPUT_PATH}/test_socket)

add_executable(test_survey ./test_survey.cpp)
target_link_libraries(test_survey nnxx)
add_test(survey ${EXECUTABLE_OUTPUT_PATH}/test_survey)

add_executable(test_timeout ./test_timeout.cpp)
target_link_libraries(test_timeout nnxx)
add_test(timeout ${EXECUTABLE_OUTPUT_PATH}/test_timeout)

