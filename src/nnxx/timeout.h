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

#ifndef NNXX_TIMEOUT_H
#define NNXX_TIMEOUT_H

#include <nnxx/chrono.h>

namespace nnxx {

  class socket;

  milliseconds get_linger(const socket &s);
  milliseconds get_recv_timeout(const socket &s);
  milliseconds get_send_timeout(const socket &s);

  template < typename Duration >
  Duration get_linger(const socket &s)
  { return std::chrono::duration_cast<Duration>(get_linger(s)); }

  template < typename Duration >
  Duration get_recv_timeout(const socket &s)
  { return std::chrono::duration_cast<Duration>(get_recv_timeout(s)); }

  template < typename Duration >
  Duration get_send_timeout(const socket &s)
  { return std::chrono::duration_cast<Duration>(get_send_timeout(s)); }

  void set_linger(socket &s, milliseconds t);
  void set_recv_timeout(socket &s, milliseconds t);
  void set_send_timeout(socket &s, milliseconds t);

  template < typename Rep, typename Period >
  void set_linger(socket &s, const std::chrono::duration<Rep, Period> &t)
  { set_linger(s, std::chrono::duration_cast<milliseconds>(t)); }

  template < typename Rep, typename Period >
  void set_recv_timeout(socket &s, const std::chrono::duration<Rep, Period> &t)
  { set_recv_timeout(s, std::chrono::duration_cast<milliseconds>(t)); }

  template < typename Rep, typename Period >
  void set_send_timeout(socket &s, const std::chrono::duration<Rep, Period> &t)
  { set_send_timeout(s, std::chrono::duration_cast<milliseconds>(t)); }

  class with_linger {
  public:
    with_linger(socket &s, milliseconds t);

    template < typename Rep, typename Period >
    with_linger(socket &s, const std::chrono::duration<Rep, Period> &t):
      m_socket(s),
      m_old_timeout(get_linger(s))
    { set_linger(s, t); }

    with_linger(with_linger      &&) = delete;
    with_linger(with_linger const &) = delete;

    ~with_linger() ;

    with_linger &operator=(with_linger      &&) = delete;
    with_linger &operator=(with_linger const &) = delete;

  private:
    socket &     m_socket;
    milliseconds m_old_timeout;
  };

  class with_recv_timeout {
  public:
    with_recv_timeout(socket &s, milliseconds t);

    template < typename Rep, typename Period >
    with_recv_timeout(socket &s, const std::chrono::duration<Rep, Period> &t):
      m_socket(s),
      m_old_timeout(get_recv_timeout(s))
    { set_recv_timeout(s, t); }

    with_recv_timeout(with_recv_timeout      &&) = delete;
    with_recv_timeout(with_recv_timeout const &) = delete;

    ~with_recv_timeout() ;

    with_recv_timeout &operator=(with_recv_timeout      &&) = delete;
    with_recv_timeout &operator=(with_recv_timeout const &) = delete;

  private:
    socket &     m_socket;
    milliseconds m_old_timeout;
  };

  class with_send_timeout {
  public:
    with_send_timeout(socket &s, milliseconds t);

    template < typename Rep, typename Period >
    with_send_timeout(socket &s, const std::chrono::duration<Rep, Period> &t):
      m_socket(s),
      m_old_timeout(get_send_timeout(s))
    { set_send_timeout(s, t); }

    with_send_timeout(with_send_timeout      &&) = delete;
    with_send_timeout(with_send_timeout const &) = delete;

    ~with_send_timeout();

    with_send_timeout &operator=(with_send_timeout      &&) = delete;
    with_send_timeout &operator=(with_send_timeout const &) = delete;

  private:
    socket &     m_socket;
    milliseconds m_old_timeout;
  };

}

#endif // NNXX_TIMEOUT_H
