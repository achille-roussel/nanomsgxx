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

#ifndef NNXX_SOCKET_H
#define NNXX_SOCKET_H

#include <nnxx/nn.h>

namespace nnxx {

  enum {
    SOCKET = NN_SOL_SOCKET, // SOL_SOCKET is already defined
  };

  enum {
    DOMAIN            = NN_DOMAIN,
    PROTOCOL          = NN_PROTOCOL,
    LINGER            = NN_LINGER,
    SNDBUF            = NN_SNDBUF,
    RCVBUF            = NN_RCVBUF,
    SNDTIMEO          = NN_SNDTIMEO,
    RCVTIMEO          = NN_RCVTIMEO,
    RECONNECT_IVL     = NN_RECONNECT_IVL,
    RECONNECT_IVL_MAX = NN_RECONNECT_IVL_MAX,
    SNDPRIO           = NN_SNDPRIO,
    IPV4ONLY          = NN_IPV4ONLY,
    SOCKET_NAME       = NN_SOCKET_NAME,
  };

  enum {
    MSG = NN_MSG,
  };

  enum {
    DONTWAIT = NN_DONTWAIT,
  };

  typedef int endpoint;

  class message;
  class message_control;

  class socket {
  public:
    socket() noexcept;
    socket(socket &&s) noexcept;
    socket(socket const &) = delete;
    socket(int domain, int protocol);

    ~socket();

    socket &operator=(socket &&s) noexcept;
    socket &operator=(socket const &) = delete;

    operator bool () const noexcept;

    void swap(socket &s) noexcept;

    void detach() noexcept;

    void close();

    void force_close() noexcept;

    endpoint bind(const char *addr);

    template < typename String >
    endpoint bind(const String &addr);

    endpoint connect(const char *addr);

    template < typename String >
    endpoint connect(const String &addr);

    void shutdown(endpoint how);

    void force_shutdown(endpoint how);

    void setopt(int level, int option, const void *val, size_t len);

    template < typename T >
    void setopt(int level, int option, const T &val);

    void getopt(int level, int option, void *optval, size_t *len) const;

    template < typename T >
    void getopt(int level, int option, T &val) const;

    template < typename T >
    T getopt(int level, int option) const;

    int send(const void *buf, size_t len, int flags, message_control &&ctl);

    int send(const void *buf, size_t len, int flags = 0);

    int send(const char *str, int flags, message_control &&ctl);

    int send(const char *str, int flags = 0);

    int send(message &&msg, int flags, message_control &&ctl);

    int send(message &&msg, int flags = 0);

    template < typename T >
    int send(const T &obj, int flags, message_control &&ctl);

    template < typename T >
    int send(const T &obj, int flags = 0);

    int recv(void *buf, size_t len, int flags, message_control &ctl);

    int recv(void *buf, size_t len, int flags = 0);

    template < typename T >
    T recv(int flags, message_control &ctl);

    template < typename T >
    T recv(int flags = 0);

    message recv(int flags, message_control &ctl);

    message recv(int flags = 0);

    int fd() const noexcept;

    friend socket make_socket(int fd) noexcept;

  private:
    int m_fd;

    explicit socket(int) noexcept;
  };

  void swap(socket &s1, socket &s2) noexcept;

  socket make_socket(int fd) noexcept;

}

#include <nnxx/socket.hpp>
#endif // NNXX_SOCKET_H
