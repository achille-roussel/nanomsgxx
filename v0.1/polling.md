---
layout: docpage
title: 4. Polling
prev: Sockets
next: API Reference
prev_page: sockets.html
next_page: api.html
---

The nanomsg C API provides a powerful polling system that is mirrored on POSIX's
polling interface. C++ though doesn't have any sort of interface for polling
events on file descriptors in the standard library, so nanomsgxx comes with its
own API for polling on nanomsg sockets instead of integrating with an existing one.  
The wrapper is very small and mostly is syntaxing sugar on top of the C API.

Poll Entries
------------

Polling is done by passing a vector or [nnxx::poll_entry](api/nnxx/poll_entry.html) objects to the
[nnxx::poll](api/nnxx/poll.html) function, such objects are defined as:

```c++
class poll_entry : public pollfd {
public:
  poll_entry() noexcept;
  poll_entry(int s, int ev) noexcept;
  poll_entry(socket &s, int ev) noexcept;

  void clear() noexcept;
  void set(int s, int ev) noexcept;
  void set(socket &s, int ev) noexcept;

  bool is(const socket &s) const noexcept;
  bool recv_ready() const noexcept;
  bool send_ready() const noexcept;
};
```

They are simple descriptors associtating sockets to a set of events that we wnat
to wait for and will get filled with events that happened while calling
[nnxx::poll](api/nnxx/poll.html). They inherit from **nn_pollfd** for compatibility with the C API,
and simply add some useful operations.  
Read [nn_poll](http://nanomsg.org/v0.3/nn_poll.3.html)'s documentation to learn
more about how the polling mechanism works.

Poll
----

[nnxx::poll](api/nnxx/poll.html) is available in different versions that makes it easy to use in
multiple situations. The two main interfaces are as follow:

```
poll_vector  poll(poll_vector &&, <optional timeout>, <optional flags>);
poll_vector &poll(poll_vector  &, <optional timeout>, <optional flags>);
```

The first version accepts a temporary vector object that is used for polling
the entries it contains and will be returned by the function with a move
operation, so no extra memory will be allocated.  

The second version accepts a reference to a vector object allocated somewhere
else in the program. Based on the use case one may find useful to use one
version or the other.

The vector returned by [nnxx::poll](api/nnxx/poll.html) has its entries set with whatever events
have been found on the sockets, the entries then should be iterated and checked
to verify which events are available for which socket.  
nanomsgxx comes with two useful functions, [nnxx::recv_ready](api/nnxx/recv_ready) and
[nnxx::send_ready](api/nnxx/send_ready), that return iterable objects that will filter entries that
were makred by [nnxx::poll](api/nnxx/poll.html) as ready for receiving or sending messages.  
Here's an usage example:

```c++
nnxx::socket s1 { /* ... */ };
nnxx::socket s2 { /* ... */ };

// ...

// Polling the socket, nnxx::poll_vector can be initialized from a
// std::initializer_list<nnxx::poll_entry>
nnxx::poll_vector entries = nnxx::poll({
    { s1, nnxx::EV_POLLIN },
    { s2, nnxx::EV_POLLIN | nnxx::EV_POLLOUT },
  });

for (auto e : nnxx::recv_ready(entries)) {
  // All entries enumerated here won't block on a receive operation.
}

for (auto e : nnxx::send_ready(entries)) {
  // All entries enumerated here won't block on a send operation.
}
```

**Note**

The C API uses [NN_POLIN](http://nanomsg.org/v0.3/nn_poll.3.html) and
[NN_POLOUT](http://nanomsg.org/v0.3/nn_poll.3.html) as event flags, so nanomsgxx should
have named its constants **nnxx::POLLIN** and **nnxx::POLLOUT**, but these names
are macros defined on POSIX systems supporting the **poll** interface and would
cause compilation to fail. That's why nanomsgxx uses [nnxx::EV_POLLIN](api/nnxx/namespace.html#EV_POLLIN)
and [nnxx::EV_POLLOUT](api/nnxx/namespace.html#EV_POLLOUT) instead.

Timeouts
--------

Polling is by nature a blocking operation, so the API has to provides a way to
set a timeout that will give the hand back to the program in case nothing 
happens for a while because we may have to do some other things once in a while.

As described in the [design](design.html) section, exceptions are used to report
timeouts in the nanomsgxx API.  
A timeout can be specified as second argument to
the [nnxx::poll](api/nnxx/poll.html) function, it may be give as a
[std::chrono::duration](http://en.cppreference.com/w/cpp/chrono/duration) (if we
want to set *how long* the function should wait), or as a
[std::chrono::time_point](http://en.cppreference.com/w/cpp/chrono/time_point)
(if we want to set *when* the function should return).  
Here's how we'd handle a timeout:

```c++
nnxx::poll_vector entries;

// ...

try {
  // Polls for events, waits at most one second.
  entries = nnxx::poll({
      { s1, nnxx::EV_POLLIN },
      { s2, nnxx::EV_POLLIN | nnxx::EV_POLLOUT },
    },
    std::chrono::seconds(1));
}
catch (const nnxx::timeout_error &) {
  // Nothing happened for more than one second.
}
```
