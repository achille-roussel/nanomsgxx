/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Achille Roussel <achille.roussel@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef NNXX_MESSAGE_H
#define NNXX_MESSAGE_H

#include <iosfwd>
#include <iterator>
#include <string>
#include <nnxx/nn.h>

namespace nnxx {

  class message {
  public:
    typedef void const * const_pointer;
    typedef void       * pointer;
    typedef char       * iterator;
    typedef char const * const_iterator;
    typedef size_t       size_type;

    explicit message(size_type size, int type = 0);
    message() noexcept;
    message(message &&m) noexcept;
    message(message const &) = delete;

    ~message();

    message &operator=(message &&m) noexcept;
    message &operator=(message const &) = delete;

    operator bool () const noexcept;

    void resize(size_type size);

    void swap(message &m) noexcept;

    void detach() noexcept;

    pointer data() noexcept;

    const_pointer data() const noexcept;

    size_type size() const noexcept;

    bool empty() const noexcept;

    iterator begin() noexcept;
    iterator end()   noexcept;

    const_iterator begin() const noexcept;
    const_iterator end()   const noexcept;

    friend message make_message_from(pointer data, size_type size) noexcept;

  private:
    pointer   m_data;
    size_type m_size;

    explicit message(pointer, size_type) noexcept;
  };

  void swap(message &m1, message &m2) noexcept;

  message make_message_from(message::pointer data, message::size_type size) noexcept;

  message copy(const message &msg, message::size_type size = 0, int type = 0);

  message::size_type copy(const message &from, message &to) noexcept;
  message::size_type copy(const message &from,
                                      message &to,
                                      message::size_type from_offset,
                                      message::size_type to_offset,
                                      message::size_type size) noexcept;

  std::string to_string(const message &msg);

  template < typename Iterator >
  message make_message(Iterator first, Iterator last)
  {
    typedef typename std::iterator_traits<Iterator> traits;
    typedef typename traits::value_type   type;
    typedef typename traits::value_type * pointer;
    using std::copy;
    using std::distance;
    message msg (distance(first, last) * sizeof(type));
    copy(first,
         last,
         reinterpret_cast<pointer>(msg.data()));
    return msg;
  }

  template < typename Iterable >
  message make_message(Iterable &&obj)
  {
    using std::begin;
    using std::end;
    return make_message(begin(obj), end(obj));
  }

  template < typename Char, typename Traits >
  std::basic_ostream<Char, Traits> &
  operator <<(std::basic_ostream<Char, Traits> &out, const message &msg)
  {
    const auto data = static_cast<const Char *>(msg.data());
    const auto size = msg.size() / sizeof(Char);
    out.write(data, size);
    return out;
  }

  extern template std::ostream &operator<<(std::ostream &, const message &);

}

#include <nnxx/socket.hpp>
#endif // NNXX_MESSAGE_H
