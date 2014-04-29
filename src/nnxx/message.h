#ifndef NNXX_MESSAGE_H
#define NNXX_MESSAGE_H

#include <nnxx/nn.h>

namespace nnxx {

  class message {
  public:
    typedef void const * const_pointer;
    typedef void       * pointer;
    typedef size_t       size_type;

    message() noexcept;
    message(size_type size, int type = 0);
    message(message &&m) noexcept;
    message(message const &) = delete;

    ~message();

    message &operator=(message &&m) noexcept;
    message &operator=(message const &) = delete;

    operator bool () const noexcept;

    void swap(message &m) noexcept;

    void detach() noexcept;

    pointer data() noexcept;

    const_pointer data() const noexcept;

    size_type size() const noexcept;

    friend message make_message(pointer data, size_type size) noexcept;

  private:
    pointer   m_data;
    size_type m_size;

    explicit message(pointer, size_type) noexcept;
  };

  inline void swap(message &m1, message &m2) noexcept
  { m1.swap(m2); }

  message make_message(message::pointer data, message::size_type size) noexcept;

  message copy(const message &msg, message::size_type size = 0, int type = 0);

  message::size_type copy(const message &from, message &to) noexcept;

  message::size_type copy(const message &from,
                          message &to,
                          message::size_type from_offset,
                          message::size_type to_offset,
                          message::size_type size) noexcept;

}

#endif // NNXX_MESSAGE_H
