---
layout: docpage
title: Polling
prev: Sockets
next: Timeouts
prev_page: sockets.html
next_page: timeouts.html
---

The nanomsg C API provides a powerful polling system that is mirrored on POSIX's
polling interface. C++ though doesn't provide any sort of polling interface on
file descriptors in the standard library, so nanomsgxx comes with its own API
for polling on nanomsg sockets instead of integrating with an existing one.  
The wrapper is very small and mostly is syntaxing sugar on top of the C API.

Poll Entries
------------

Polling is done by passing a vector or **nnxx::poll_entry** objects to the
**nnxx::poll** function, such objects are defined as:

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
**nnxx::poll**. They inherit from **nn_pollfd** for compatibility with the C API,
and simply add some useful operations.  
Read [nn_poll](http://nanomsg.org/v0.3/nn_poll.3.html)'s documentation to learn
more about how the polling mechanism works.

Poll
----

**nnxx::poll** is available in different versions that makes it easy to use in
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

The vector returned by **nnxx::poll** has its entries set with whatever events
have been found on the sockets, the entries then should be iterated and checked
to verify which events are available for which socket.  
nanomsgxx comes with two useful functions, **nnxx::recv_ready** and
**nnxx::send_ready**, that return iterable objects that will filter entries that
were makred by **nnxx::poll** as ready for receiving or sending messages.  
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

The C API uses **NN_POLIN** and **NN_POLOUT** as event flags, so nanomsgxx should
have named its constants **nnxx::POLLIN** and **nnxx::POLLOUT**, but these names
are macros defined on POSIX systems supporting the **poll** interface and would
cause compilation to fail. That's why nanomsgxx uses **nnxx::EV_POLLIN** and
**nnxx::EV_POLLOUT** instead.

Timeouts
--------
