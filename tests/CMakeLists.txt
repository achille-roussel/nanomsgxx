project(nnxx_tests)
include(CTest)

add_executable(test_message ./test_message.cpp)
target_link_libraries(test_message nnxx)
add_test(NAME message COMMAND $<TARGET_FILE:test_message>)

add_executable(test_message_istream ./test_message_istream.cpp)
target_link_libraries(test_message_istream nnxx)
add_test(NAME message_istream COMMAND $<TARGET_FILE:test_message_istream>)

add_executable(test_message_ostream ./test_message_ostream.cpp)
target_link_libraries(test_message_ostream nnxx)
add_test(NAME message_ostream COMMAND $<TARGET_FILE:test_message_ostream>)

add_executable(test_nnxx_ext ./test_nnxx_ext.cpp)
target_link_libraries(test_nnxx_ext nnxx)
add_test(NAME nnxx_ext COMMAND $<TARGET_FILE:test_nnxx_ext>)

add_executable(test_pair ./test_pair.cpp)
target_link_libraries(test_pair nnxx)
add_test(NAME pair COMMAND $<TARGET_FILE:test_pair>)

add_executable(test_pipeline ./test_pipeline.cpp)
target_link_libraries(test_pipeline nnxx)
add_test(NAME pipeline COMMAND $<TARGET_FILE:test_pipeline>)

add_executable(test_poll ./test_poll.cpp)
target_link_libraries(test_poll nnxx)
add_test(NAME poll COMMAND $<TARGET_FILE:test_poll>)

add_executable(test_pubsub ./test_pubsub.cpp)
target_link_libraries(test_pubsub nnxx)
add_test(NAME pubsub COMMAND $<TARGET_FILE:test_pubsub>)

add_executable(test_readme ./test_readme.cpp)
target_link_libraries(test_readme nnxx)
add_test(NAME readme COMMAND $<TARGET_FILE:test_readme>)

add_executable(test_reqrep ./test_reqrep.cpp)
target_link_libraries(test_reqrep nnxx)
add_test(NAME reqrep COMMAND $<TARGET_FILE:test_reqrep>)

add_executable(test_reqrep_multi ./test_reqrep_multi.cpp)
target_link_libraries(test_reqrep_multi nnxx)
add_test(NAME reqrep_multi COMMAND $<TARGET_FILE:test_reqrep_multi>)

add_executable(test_socket ./test_socket.cpp)
target_link_libraries(test_socket nnxx)
add_test(NAME socket COMMAND $<TARGET_FILE:test_socket>)

add_executable(test_survey ./test_survey.cpp)
target_link_libraries(test_survey nnxx)
add_test(NAME survey COMMAND $<TARGET_FILE:test_survey>)

add_executable(test_timeout ./test_timeout.cpp)
target_link_libraries(test_timeout nnxx)
add_test(NAME timeout COMMAND $<TARGET_FILE:test_timeout>)

