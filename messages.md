---
layout: docpage
title: 2. Messages
prev: Design
next: Sockets
prev_page: design.html
next_page: sockets.html
---

nanomsg is all about passing messages around from nodes to others, so nanomsgxx
provides abstractions to make managing such messages easy and efficient.  
This chapter introduces the different abstraction types that allows you to deal
with messages in nanomsgxx.

Message
-------

Messages passed from and to sockets are represented by the [nnxx::message](api/nnxx/message.html)
type, it features:

- automatic memory management
- zero-copy operations when sending and recveiving on sockets

Every memory buffer managed by a [nnxx::message](api/nnxx/message.html) object is allocated and freed
using the [nn_allocmsg](http://nanomsg.org/v0.3/nn_allocmsg.3.html) and
[nn_freemsg](http://nanomsg.org/v0.3/nn_freemsg.3.html) functions of the nanomsg
C API.  
Here's an example of how you could use a [nnxx::message](api/nnxx/message.html) instance:

```c++
void forward_message(nxx::socket &from, nnxx::socket &to)
{
  nnxx::message m;

  // These operations don't copy the message, it's simply passed around.
  m = from.recv();
  to.send(std::move(m));

  // Could also be made shorter:
  // to.send(recv.from());
}
```

Messages are very useful objects for managing memory buffers but they don't
provide any interface to work with these buffers. Standard C++ defines the
iostream interface for this purpose, and nanomsgxx messages come along with
input and output streams that provide compatibility with existing standard
C++ code.

Message Output Stream
---------------------

Output streams are useful for abstracting away the support on which we write
formatted data to, if we want to build a message to send it over a socket we
can use such stream to do so.  
Instances of [nnxx::message_ostream](api/nnxx/message_ostream.html) are designed for this use case, here's
an example:

```c++
void send_hello_world_42(nnxx::socket &s)
{
  nnxx::message_ostream os;

  // Simply use the object like any standard output stream.
  os << "Hello World ";
  os << 42;

  // Get an instance of nnxx::message and send it through the socket,
  // the connected peer will receive "Hello World 42".
  s.send(os.msg());
}
```

Message Input Stream
--------------------

When receiving a message from a socket we can use parsers based on standard C++
streams to read the data. nanomsgxx provides the [nnxx::message_istream](api/nnxx/message_istream.html) type,
here's a usage example:

```c++
std::vector<int> recv_int_vector(nnxx::socket &s)
{
  // Build a new input stream from a received message.
  std::message_istream is { s.recv() };

  // Use a standard input stream iterator to read all integers.
  std::istream_iterator<int> begin { is };
  std::istream_iterator<int> end   {    };

  // It's that easy ;)
  return { begin, end };
}
```

Message Control
---------------

When using nanomsg raw sockets ([nnxx::SP&#95;RAW](api/nnxx/namespace.thml#SP_RAW)), messages can be associated
with control headers that provide meta informations relative to the underlying
protocol (routing for example).  
In the basic C API provides the [nn_sendmsg](http://nanomsg.org/v0.3/nn_sendmsg.3.html)
and [nn_recvmsg](http://nanomsg.org/v0.3/nn_recvmsg.3.html) for this purpose,
which lets us retrieve the control information within the **nn_msghdr** object
we pass to these functions.

This feature is abstracted in nanomsgxx with the [nnxx::message_control](api/nnxx/message_control.html) type,
which we can get or set and receiving and sending messages, this is particulary
useful when dealing with [nnxx::REP](api/nnxx/namespace.html#REP) sockets if we want to handle requests in
parallel.

```c++
nnxx::socket s { nnxx::SP_RAW, nnxx::REP };

// ...

nnxx::message_control ctl1;
nnxx::message_control ctl2;
nnxx::message req1;
nnxx::message req2;
int flags = 0;

// Receiving messages and associated control headers.
req1 = s.recv(flags, ctl1);
req2 = s.recv(flags, ctl2);

// ...

// Sending responses in different order, it's a raw socket, we're not bound
// to follow the end-to-end enforcements of simple sockets.
s.send(std::move(rep2), flags, std::move(ctl2));
s.send(std::move(rep1), flags, std::move(ctl1));
```
