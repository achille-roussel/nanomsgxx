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

#include <algorithm>
#include <cstring>
#include <nnxx/error.h>
#include <nnxx/message.h>
#include <nnxx/message_control.h>
#include <nnxx/message_iterator.h>
#include <nnxx/socket.h>

namespace nnxx {

  static int check_socket_error(int flags)
  {
    const auto err = this_thread::get_errc();

    if (err != std::errc::resource_unavailable_try_again) {
      if ((err != std::errc::interrupted) || !(flags & NO_SIGNAL_ERROR)) {
        throw_error();
      }
    }

    else if (!(flags & DONTWAIT)) {
      if (!(flags & NO_TIMEOUT_ERROR)) {
        throw_error(ETIMEDOUT);
      }
    }

    return -1;
  }

  socket::socket() noexcept:
    m_fd(-1)
  { }

  socket::socket(socket &&s) noexcept:
    m_fd(s.m_fd)
  { s.detach(); }

  socket::socket(int domain, int protocol):
    m_fd(nn_socket(domain, protocol))
  { check_error(m_fd); }

  socket::~socket()
  { force_close(); }

  socket &socket::operator=(socket &&s) noexcept
  {
    s.swap(*this);
    return *this;
  }

  socket::operator bool () const noexcept
  { return m_fd >= 0; }

  void socket::swap(socket &s) noexcept
  {
    using std::swap;
    swap(m_fd, s.m_fd);
  }

  void socket::detach() noexcept
  { m_fd = -1; }

  void socket::close()
  {
    if (m_fd >= 0) {
      check_error(nn_close(m_fd));
      m_fd = -1;
    }
  }

  void socket::force_close() noexcept
  {
    while (true) {
      try {
        close();
        break;
      }
      catch (const std::exception &) {
      }
    }
  }

  endpoint socket::bind(const char *addr)
  { return check_error(nn_bind(m_fd, addr)); }

  endpoint socket::bind(const std::string &addr)
  { return bind(addr.c_str()); }

  endpoint socket::connect(const char *addr)
  { return check_error(nn_connect(m_fd, addr)); }

  endpoint socket::connect(const std::string &addr)
  { return connect(addr.c_str()); }

  void socket::shutdown(endpoint how)
  { check_error(nn_shutdown(m_fd, how)); }

  void socket::force_shutdown(endpoint how)
  {
    while (true) {
      try {
        shutdown(how);
        break;
      }
      catch (const term_error &) {
        throw;
      }
      catch (const std::exception &) {
      }
    }
  }

  void socket::setopt(int level, int option, const void *val, size_t len)
  { check_error(nn_setsockopt(m_fd, level, option, val, len)); }

  void socket::getopt(int level, int option, void *val, size_t *len) const
  { check_error(nn_getsockopt(m_fd, level, option, val, len)); }

  int socket::send(const void *buf, size_t len, int flags, message_control &&ctl)
  {
    int n;

    if ((n = nn_sendto(m_fd, buf, len, flags, &ctl)) < 0) {
      return check_socket_error(flags);
    }

    ctl.detach();
    return n;
  }

  int socket::send(const void *buf, size_t len, int flags)
  {
    int n;

    if ((n = nn_send(m_fd, buf, len, flags)) < 0) {
      return check_socket_error(flags);
    }

    return n;
  }

  int socket::send(const char *str, int flags, message_control &&ctl)
  { return send(str, std::strlen(str), flags, std::move(ctl)); }

  int socket::send(const char *str, int flags)
  { return send(str, std::strlen(str), flags); }

  int socket::send(message &&msg, int flags, message_control &&ctl)
  {
    message::pointer data = msg.data();
    int n;

    if ((n = nn_sendto(m_fd, &data, MSG, flags, &ctl)) < 0) {
      return check_socket_error(flags);
    }

    ctl.detach();
    msg.detach();
    return n;
  }

  int socket::send(message &&msg, int flags)
  {
    message::pointer data = msg.data();
    int n;

    if ((n = nn_send(m_fd, &data, MSG, flags)) < 0) {
      return check_socket_error(flags);
    }

    msg.detach();
    return n;
  }

  int socket::recv(void *buf, size_t len, int flags, message_control &ctl)
  {
    message_control tmp;
    int n;

    if ((n = nn_recvfrom(m_fd, buf, len, flags, &tmp)) < 0) {
      return check_socket_error(flags);
    }

    ctl = std::move(tmp);
    return n;
  }

  int socket::recv(void *buf, size_t len, int flags)
  {
    int n;

    if ((n = nn_recv(m_fd, buf, len, flags)) < 0) {
      return check_socket_error(flags);
    }

    return n;
  }

  message socket::recv(int flags, message_control &ctl)
  {
    message_control tmp;
    void *p;
    int   n;

    if ((n = nn_recvfrom(m_fd, &p, MSG, flags, &tmp)) < 0) {
      check_socket_error(flags);
      return { };
    }

    ctl = std::move(tmp);
    return make_message_from(p, n);
  }

  message socket::recv(int flags)
  {
    void *p;
    int   n;

    if ((n = nn_recv(m_fd, &p, MSG, flags)) < 0) {
      check_socket_error(flags);
      return { };
    }

    return make_message_from(p, n);
  }

  int socket::fd() const noexcept
  { return m_fd; }

  socket::iterator socket::begin()
  { return { *this }; }

  socket::iterator socket::end()
  { return { }; }

  void swap(socket &s1, socket &s2) noexcept
  { s1.swap(s2); }

}
