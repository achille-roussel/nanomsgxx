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

#ifndef NNXX_MESSAGE_SREAMBUF_H
#define NNXX_MESSAGE_SREAMBUF_H

#include <streambuf>
#include <nnxx/message.h>

namespace nnxx {

  template < typename Char, typename Traits = std::char_traits<Char> >
  class basic_message_streambuf : public std::basic_streambuf<Char, Traits> {
    typedef typename std::basic_streambuf<Char, Traits> base_type;
    typedef typename std::streamsize                    streamsize;
  public:
    typedef typename message::size_type     size_type;
    typedef typename base_type::char_type   char_type;
    typedef typename base_type::int_type    int_type;
    typedef typename base_type::pos_type    pos_type;
    typedef typename base_type::off_type    off_type;
    typedef typename base_type::traits_type traits_type;

    explicit basic_message_streambuf(size_type base_size = 1000) noexcept;
    explicit basic_message_streambuf(message &&msg) noexcept;
    basic_message_streambuf(basic_message_streambuf const &) = delete;
    basic_message_streambuf(size_type size, int type);
    ~basic_message_streambuf();
    basic_message_streambuf &operator=(basic_message_streambuf const &) = delete;

    basic_message_streambuf(basic_message_streambuf &&m) noexcept;
    basic_message_streambuf &operator=(basic_message_streambuf &&m) noexcept;
    void swap(basic_message_streambuf &m) noexcept;

    void msg(message &&m) noexcept;
    void clear() noexcept;

    message msg(int type = 0);
    message move_msg();

  protected:
    streamsize xsputn(const char_type *, streamsize);
    int_type overflow(int_type);

  private:
    size_type m_base_size;
    message   m_msg;
  };

  template < typename Char, typename Traits >
  void swap(basic_message_streambuf<Char, Traits> &m1,
            basic_message_streambuf<Char, Traits> &m2) noexcept
  { m1.swap(m2); }

  typedef basic_message_streambuf<char> message_streambuf;

  extern template class basic_message_streambuf<char>;

}

#endif // NNXX_MESSAGE_SREAMBUF_H
