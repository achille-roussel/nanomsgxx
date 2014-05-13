---
layout: v0.1/api
title: API Reference
info: Here's the reference documentation for the nanomsgxx API,
 it contains detailed description of each type and symbols provided
 by the library, as well as some code examples... enjoy!

sections:
-
 title: Namespaces
 elements:
 - 
  title: nnxx
  info: Contains most of the symbols and types
  location: api/nnxx/namespace.html
 -
  title: nnxx::this_thread
  info: Contains symbols that have thread-local behaviors
  location: api/nnxx/this_thread/namespace.html

-
 title: Types
 elements:
 -
  title: message
  info: Message abstraction for zero-copy
  location: api/nnxx/message.html
 -
  title: message_control
  info: Protocol dependant control data
  location: api/nnxx/message_control.html
 -
  title: message_istream
  info: Parse messages using standard input streams
  location: api/nnxx/message_istream.html
 -
  title: message_ostream
  info: Format messages using standard input streams
  location: api/nnxx/message_ostream.html
 -
  title: message_streambuf
  info: Stream buffer for message input and output streams
  location: api/nnxx/message_streambuf.html
 -
  title: poll_entry
  info: Objects used to poll events on sockets
  location: api/nnxx/poll_entry.html
 -
  title: poll_vector
  info: Vector of poll_entry objects
  location: api/nnxx/poll_vector.html
 -
  title: ready_iterator
  info: Iterate over poll events marked as ready for reading or writing
  location: api/nnxx/ready_iterator.html
 -
  title: ready_sequence
  info: Proxy object generating a begin and end ready_iterator
  location: api/nnxx/ready_sequence.html
 -
  title: signal_error
  info: Exception thrown when an operation is interrupted by a signal
  location: api/nnxx/signal_error.html
 -
  title: socket
  info: Abstraction of nanomsg sockets
  location: api/nnxx/socket.html
 -
  title: symbol_properties
  info: Representation of a nanomsg symbol
  location: api/nnxx/symbol_properties.html
 -
  title: term_error
  info: Exception thrown when the nanomsg library is terminating
  location: api/nnxx/term_error.html
 -
  title: timeout_error
  info: Exception thrown when an operation times out
  location: api/nnxx/timeout_error.html
 -
  title: with_linger
  info: Scope-based linger timeout setter
  location: api/nnxx/with_linger.html
 -
  title: with_recv_timeout
  info: Scope-based receive timeout setter
  location: api/nnxx/with_recv_timeout.html
 -
  title: with_send_timeout
  info: Scope-based send timeout setter
  location: api/nnxx/with_send_timeout.html

-
 title: Functions
 elements:
 -
  title: c_str
  info: Convert types to c-string representations
  location: api/nnxx/c_str.html
 -
  title: device
  info: Sets up a proxy routing messages from a socket to another
  location: api/nnxx/device.html
 -
  title: get_linger
  info: Gets the linger timeout on a socket
  location: api/nnxx/get_linger.html
 -
  title: get_recv_timeout
  info: Gets the receive timeout on a socket
  location: api/nnxx/get_recv_timeout.html
 -
  title: get_resend_interval
  info: Gets the resend timeout on a socket
  location: api/nnxx/.html
 -
  title: get_send_timeout
  info: Gets the send timeout on a socket
  location: api/nnxx/get_send_timeout.html
 -
  title: get_surveyor_deadline
  info: Gets the surveyor timeout on a socket
  location: api/nnxx/get_surveyor_deadline.html
 -
  title: poll
  info: Polls for events available on sockets
  location: api/nnxx/poll.html
 -
  title: recv_ready
  info: Helper function creating a sequence of poll_entry marked as ready for receive operations
  location: api/nnxx/recv_ready.html
 -
  title: send_ready
  info: Helper function creating a sequence of poll_entry marked as ready for send operations
  location: api/nnxx/send_ready.html
 -
  title: set_linger
  info: Sets the linger timeout on a socket
  location: api/nnxx/set_linger.html
 -
  title: set_recv_timeout
  info: Sets the receive timeout on a socket
  location: api/nnxx/set_recv_timeout.html
 -
  title: set_resend_interval
  info: Sets the resend timeout on a socket
  location: api/nnxx/.html
 -
  title: set_send_timeout
  info: Sets the send timeout on a socket
  location: api/nnxx/set_send_timeout.html
 -
  title: set_surveyor_deadline
  info: Sets the surveyor timeout on a socket
  location: api/nnxx/set_surveyor_deadline.html
 -
  title: strerror
  info: Returns a human-readable representation of an error code
  location: api/nnxx/strerror.html
 -
  title: subscribe
  info: Subscribe a SUB socket to a topic
  location: api/nnxx/subscribe.html
 -
  title: symbol
  info: Returns informations on a nanomsg symbol
  location: api/nnxx/symbol.html
 -
  title: term
  info: Force all ongoing and future nanomsg operations to abort and throw a term_error
  location: api/nnxx/term.html
 -
  title: unsubscribe
  info: Unsubscribes a SUB socket from a topic
  location: api/nnxx/unsubscribe.html
 -
  title: this_thread::get_errno
  info: Gets the current error status on the calling thread
  location: api/nnxx/this_thread/get_errno.html
 -
  title: this_thread::get_errc
  info: Gets the current error status on the calling thread
  location: api/nnxx/this_thread/get_errc.html
---

