---
layout: v0.1/cpppage
title: nnxx::message
index_page: ../../index.html
prev_page: ../../api.html
---

Messages wrap around memory buffers that can be used to send and receive
messages using zero-copy optimizations.

```c++
#include <nnxx/message.h>
```

```c++
class message
```

```c++
typedef void const * const_pointer;
typedef void       * pointer;
typedef char       * iterator;
typedef char const * const_iterator;
typedef size_t       size_type;
```

#### Constructors

```c++
message::message() noexcept;
message::message(message &&m) noexcept;
message::message(message const &) = delete;
explicit message::message(size_type size, int type = 0);
```

The default constructor creates an empty message with no pre-allocated memory
buffer, you should use the constructor that accepts a size as first argument
to force the message to allocate a memory buffer.

Message objects are [move constructible](http://en.cppreference.com/w/cpp/language/move_constructor)
but not [copy constructible](http://en.cppreference.com/w/cpp/language/copy_constructor).

**Arguments**

- **size** size of the internal buffer
- **type** type of the internal buffer

*See also: [nn_allocmsg](http://nanomsg.org/v0.3/nn_allocmsg.3.html)
[nn_freemsg](http://nanomsg.org/v0.3/nn_freemsg.3.html)*

#### Operations

```c++
message &message::operator=(message &&m) noexcept;
message &message::operator=(message const &) = delete;
```

Message objects support [move assignment](http://en.cppreference.com/w/cpp/language/move_operator)
but not [copy assignment](http://en.cppreference.com/w/cpp/language/as_operator).

```c++
message::operator bool () const noexcept;
```

Message object can be evaluated to a boolean to check if they are wrapping
around a memory buffer.

**Return**

- **true** or **false** whether the message object wraps around a memory buffer or not.

```c++
std::ostream &operator<<(std::ostream &os, const message &m);
```

#### Iterators

Message objects provide a STL-compatible interface for iterating over the bytes
of the contents of the wrapped memory buffer, one byte at a time.

*See also: [std::begin](http://en.cppreference.com/w/cpp/iterator/begin)
[std::end](http://en.cppreference.com/w/cpp/iterator/end)*

```c++
iterator begin() noexcept;
const_iterator begin() const noexcept;
```

**Return**

- An iterator pointing to the start of the wrapped memory buffer.

```c++
iterator end() noexcept;
const_iterator end() const noexcept;
```

**Return**

- An iterator pointing to the end of the wrapped memory buffer.

#### Functions

```c++
void message::detach() noexcept;
```

Detaches the message object from the memory buffer it manages. The memory buffer
wont' be automatically released anymore. The program is expected to free the
buffer previously obtained by a call to the **data** member function to avoid
memory leaks.

```c++
message::pointer data() noexcept;
message::const_pointer message::data() const noexcept;
```

**Return**

- A pointer to the managed memory buffer.

```c++
bool message::empty() const noexcept;
```

**Return**

- **true** if the object doesn't manage any memory buffer, **false** otherwise.

```c++
size_type message::size() const noexcept;
```

**Return**

- The size of the managed memory buffer, will be zero if the object doesn't wrap
around anything.

```c++
void message::swap(message &m) noexcept;
void swap(message &m1, message &m2) noexcept;
```

**Arguments**

- **m**, **m1**, **m2** The objects to swap contents between.
