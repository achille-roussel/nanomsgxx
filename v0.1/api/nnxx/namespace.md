---
layout: v0.1/nnxx

path_prefix: ../../

title: nnxx

info1: The nnxx namespace contains most of the types and symbols of the API,
 it ports all constants of the C API into the namespace, the following table
 shows what nanomsgxx name binds to which nanomsg constant.

info2: The nnxx also provides some extra constants specific to the C++ API.

constants1:
-
 c: AF_SP
 c_location: http://nanomsg.org/v0.3/nn_socket.3.html
 cxx: SP
-
 c: AF_SP_RAW
 c_location: http://nanomsg.org/v0.3/nn_socket.3.html
 cxx: SP_RAW
-
 c: NN_BUS
 c_location: http://nanomsg.org/v0.3/nn_bus.3.html
 cxx: BUS
-
 c: NN_DOMAIN
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: DOMAIN
-
 c: NN_DONTWAIT
 c_location: http://nanomsg.org/v0.3/nn_recv.3.html
 cxx: DONTWAIT
-
 c: NN_IPV4ONLY
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: IPV4ONLY
-
 c: NN_LINGER
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: LINGER
-
 c: NN_MSG
 c_location: http://nanomsg.org/v0.3/nn_send.3.html
 cxx: MSG
-
 c: NN_NS_DOMAIN
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_DOMAIN
-
 c: NN_NS_ERROR
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_ERROR
-
 c: NN_NS_FLAG
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_FLAG
-
 c: NN_NS_LIMIT
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_LIMIT
-
 c: NN_NS_NAMESPACE
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_NAMESPACE
-
 c: NN_NS_OPTION_LEVEL
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_OPTION_LEVEL
-
 c: NN_NS_OPTION_TYPE
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_OPTION_TYPE
-
 c: NN_NS_PROTOCOL
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_PROTOCOL
-
 c: NN_NS_SOCKET_OPTION
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_SOCKET_OPTION
-
 c: NN_NS_TRANSPORT
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_TRANSPORT
-
 c: NN_NS_TRANSPORT_OPTION
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_TRANSPORT_OPTION
-
 c: NN_NS_VERSION
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: NS_VERSION
-
 c: NN_PAIR
 c_location: http://nanomsg.org/v0.3/nn_pair.3.html
 cxx: PAIR
-
 c: NN_POLLIN
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: EV_POLLIN
-
 c: NN_POLLOUT
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: EV_POLLOUT
-
 c: NN_PROTOCOL
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: PROTOCOL
-
 c: NN_PUB
 c_location: http://nanomsg.org/v0.3/nn_pubsub.3.html
 cxx: PUB
-
 c: NN_PULL
 c_location: http://nanomsg.org/v0.3/nn_pipeline.3.html
 cxx: PULL
-
 c: NN_PUSH
 c_location: http://nanomsg.org/v0.3/nn_pipeline.3.html
 cxx: PUSH
-
 c: NN_RCVBUF
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: RCVBUF
-
 c: NN_RCVTIMEO
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: RCVTIMEO
-
 c: NN_RECONNECT_IVL
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: RECONNECT_IVL
-
 c: NN_RECONNECT_IVL_MAX
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: RECONNECT_IVL_MAX
-
 c: NN_REP
 c_location: http://nanomsg.org/v0.3/nn_reqrep.3.html
 cxx: REP
-
 c: NN_REQ
 c_location: http://nanomsg.org/v0.3/nn_reqrep.3.html
 cxx: REQ
-
 c: NN_REQ_RESEND_IVL
 c_location: http://nanomsg.org/v0.3/nn_reqrep.3.html
 cxx: REQ_RESEND_IVL
-
 c: NN_RESPONDENT
 c_location: http://nanomsg.org/v0.3/nn_survey.3.html
 cxx: RESPONDENT
-
 c: NN_SNDBUF
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: SNDBUF
-
 c: NN_SNDPRIO
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: SNDPRIO
-
 c: NN_SNDTIMEO
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: SNDTIMEO
-
 c: NN_SOCKADDR_MAX
 c_location: http://nanomsg.org/v0.3/nn_bind.3.html
 cxx: SOCKADDR_MAX
-
 c: NN_SOCKET_NAME
 c_location: http://nanomsg.org/v0.3/nn_getsockopt.3.html
 cxx: SOCKET_NAME
-
 c: NN_SUB
 c_location: http://nanomsg.org/v0.3/nn_pubsub.3.html
 cxx: SUB
-
 c: NN_SUB_SUBSCRIBE
 c_location: http://nanomsg.org/v0.3/nn_pubsub.3.html
 cxx: SUB_SUBSCRIBE
-
 c: NN_SUB_UNSUBSCRIBE
 c_location: http://nanomsg.org/v0.3/nn_pubsub.3.html
 cxx: SUB_UNSUBSCRIBE
-
 c: NN_SURVEYOR
 c_location: http://nanomsg.org/v0.3/nn_survey.3.html
 cxx: SURVEYOR
-
 c: NN_SURVEYOR_DEADLINE
 c_location: http://nanomsg.org/v0.3/nn_survey.3.html
 cxx: SURVEYOR_DEADLINE
-
 c: NN_TCP_NODELAY
 c_location: http://nanomsg.org/v0.3/nn_tcp.3.html
 cxx: TCP_NODELAY
-
 c: NN_TYPE_INT
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: TYPE_INT
-
 c: NN_TYPE_NONE
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: TYPE_NONE
-
 c: NN_TYPE_STR
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: TYPE_STR
-
 c: NN_UNIT_BOOLEAN
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: UNIT_BOOLEAN
-
 c: NN_UNIT_BYTES
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: UNIT_BYTES
-
 c: NN_UNIT_MILLISECONDS
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: UNIT_MILLISECONDS
-
 c: NN_UNIT_NONE
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: UNIT_NONE
-
 c: NN_UNIT_PRIORITY
 c_location: http://nanomsg.org/v0.3/nn_symbol_info.3.html
 cxx: UNIT_PRIORITY

constants2:
-
 cxx: NO_SIGNAL_ERROR
 info: Flag that prevents functions from throwing an exception when the operation is cancelled by the processing of a signal
-
 cxx: NO_TIMEOUT_ERROR
 info: Flag that prevent functions from throwing an exception when the operation times out
---
