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

#include <nnxx/socket.h>
#include <nnxx/timeout.h>

namespace nnxx {

  milliseconds get_linger(const socket &s)
  { return milliseconds(s.getopt<int>(SOCKET, LINGER)); }

  milliseconds get_recv_timeout(const socket &s)
  { return milliseconds(s.getopt<int>(SOCKET, RCVTIMEO)); }

  milliseconds get_send_timeout(const socket &s)
  { return milliseconds(s.getopt<int>(SOCKET, SNDTIMEO)); }

  void set_linger(socket &s, milliseconds t)
  { s.setopt(SOCKET, LINGER, static_cast<int>(t.count())); }

  void set_recv_timeout(socket &s, milliseconds t)
  { s.setopt(SOCKET, RCVTIMEO, static_cast<int>(t.count())); }

  void set_send_timeout(socket &s, milliseconds t)
  { s.setopt(SOCKET, SNDTIMEO, static_cast<int>(t.count())); }

  with_linger::with_linger(socket &s, milliseconds t):
    m_socket(s),
    m_old_timeout(get_linger(s))
  { set_linger(s, t); }

  with_linger::~with_linger()
  { set_linger(m_socket, m_old_timeout); }

  with_recv_timeout::with_recv_timeout(socket &s, milliseconds t):
    m_socket(s),
    m_old_timeout(get_recv_timeout(s))
  { set_recv_timeout(s, t); }

  with_recv_timeout::~with_recv_timeout()
  { set_recv_timeout(m_socket, m_old_timeout); }

  with_send_timeout::with_send_timeout(socket &s, milliseconds t):
    m_socket(s),
    m_old_timeout(get_send_timeout(s))
  { set_send_timeout(s, t); }

  with_send_timeout::~with_send_timeout()
  { set_send_timeout(m_socket, m_old_timeout); }

}
