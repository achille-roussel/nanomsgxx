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

#ifndef NNXX_MESSAGE_ISTREAM_H
#define NNXX_MESSAGE_ISTREAM_H

#include <istream>
#include <nnxx/message_streambuf.h>

namespace nnxx {

  template < typename Char, typename Traits = std::char_traits<Char> >
  class basic_message_istream : public std::basic_istream<Char, Traits> {
    typedef typename std::basic_istream<Char, Traits> base_type;
    typedef basic_message_streambuf<Char, Traits>     message_streambuf;
  public:
    typedef typename base_type::char_type         char_type;
    typedef typename base_type::int_type          int_type;
    typedef typename base_type::pos_type          pos_type;
    typedef typename base_type::off_type          off_type;
    typedef typename base_type::traits_type       traits_type;
    typedef typename message_streambuf::size_type size_type;

    explicit basic_message_istream() noexcept;
    explicit basic_message_istream(message &&msg) noexcept;
    basic_message_istream(basic_message_istream const &) = delete;
    ~basic_message_istream();
    basic_message_istream &operator=(basic_message_istream const &&) = delete;

    basic_message_istream(basic_message_istream &&m) noexcept;
    basic_message_istream &operator=(basic_message_istream &&m) noexcept;
    void swap(basic_message_istream &m) noexcept;

    void msg(message &&m) noexcept;

  private:
    message_streambuf m_buffer;
  };

  template < typename Char, typename Traits >
  void swap(basic_message_istream<Char, Traits> &m1,
            basic_message_istream<Char, Traits> &m2) noexcept
  { m1.swap(m2); }

  typedef basic_message_istream<char> message_istream;

  extern template class basic_message_istream<char>;

}

#endif // NNXX_MESSAGE_ISTREAM_H
