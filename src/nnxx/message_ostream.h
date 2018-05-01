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

#ifndef NNXX_MESSAGE_OSTREAM_H
#define NNXX_MESSAGE_OSTREAM_H

#include <ostream>
#include <nnxx/message_streambuf.h>

namespace nnxx {

  template < typename Char, typename Traits = std::char_traits<Char> >
  class basic_message_ostream : public std::basic_ostream<Char, Traits> {
    typedef typename std::basic_ostream<Char, Traits> base_type;
    typedef basic_message_streambuf<Char, Traits>     message_streambuf;
  public:
    typedef typename base_type::char_type         char_type;
    typedef typename base_type::int_type          int_type;
    typedef typename base_type::pos_type          pos_type;
    typedef typename base_type::off_type          off_type;
    typedef typename base_type::traits_type       traits_type;
    typedef typename message_streambuf::size_type size_type;

    explicit basic_message_ostream(size_type base_size = 1000) noexcept;
    explicit basic_message_ostream(message &&msg) noexcept;
    basic_message_ostream(basic_message_ostream const &) = delete;
    ~basic_message_ostream();
    basic_message_ostream &operator=(basic_message_ostream const &) = delete;

    basic_message_ostream(basic_message_ostream &&m) noexcept;
    basic_message_ostream &operator=(basic_message_ostream &&m) noexcept;
    void swap(basic_message_ostream &m) noexcept;

    void    msg(message &&m) noexcept;
    message msg(int type = 0);
    message move_msg();

  private:
    message_streambuf m_buffer;
  };

  template < typename Char, typename Traits >
  void swap(basic_message_ostream<Char, Traits> &m1,
            basic_message_ostream<Char, Traits> &m2) noexcept
  { m1.swap(m2); }

  typedef basic_message_ostream<char> message_ostream;

  extern template class basic_message_ostream<char>;

}

#endif // NNXX_MESSAGE_OSTREAM_H
