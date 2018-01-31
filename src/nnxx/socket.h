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

#include <string>
#include <nnxx/nn.h>

// Some system define DOMAIN in math.h, this constant is defined for internal use
// only so we're fine undefining it.
#ifdef DOMAIN
#undef DOMAIN
#endif

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
    RCVMAXSIZE        = NN_RCVMAXSIZE,
    MAXTTL            = NN_MAXTTL,
  };

  enum {
    MSG = NN_MSG,
  };

  typedef int endpoint;

  class message;
  class message_control;
  class message_iterator;

  class socket {
  public:
    typedef message          value_type;
    typedef message *        pointer;
    typedef message &        reference;
    typedef message_iterator iterator;
    typedef message const *  const_pointer;
    typedef message const &  const_reference;

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

    endpoint bind(const std::string &addr);

    endpoint connect(const char *addr);

    endpoint connect(const std::string &addr);

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

    iterator begin();
    iterator end();

  private:
    int m_fd;
  };

  void swap(socket &s1, socket &s2) noexcept;

}

#include <iterator>

namespace std {

  template < >
  class back_insert_iterator<nnxx::socket>
    : public std::iterator<std::output_iterator_tag, void, void, void, void> {
  public:
    typedef typename std::output_iterator_tag iterator_category;
    typedef void difference_type;
    typedef void value_type;
    typedef void pointer;
    typedef void reference;

    back_insert_iterator(nnxx::socket &s) noexcept;
    back_insert_iterator(back_insert_iterator      &&) = default;
    back_insert_iterator(back_insert_iterator const &) = default;

    template < typename T >
    back_insert_iterator &operator=(T &&obj);
    back_insert_iterator &operator=(back_insert_iterator      &&) = default;
    back_insert_iterator &operator=(back_insert_iterator const &) = default;

    back_insert_iterator &operator*();
    back_insert_iterator &operator++();
    back_insert_iterator &operator++(int);

  private:
    nnxx::socket *m_socket;
  };

  inline
  back_insert_iterator<nnxx::socket>::
  back_insert_iterator(nnxx::socket &s) noexcept:
    m_socket(&s)
  { }

  template < typename T >
  inline
  back_insert_iterator<nnxx::socket> &
  back_insert_iterator<nnxx::socket>::operator=(T &&obj)
  {
    m_socket->send(std::forward<T>(obj));
    return *this;
  }

  inline
  back_insert_iterator<nnxx::socket> &
  back_insert_iterator<nnxx::socket>::operator*()
  { return *this; }

  inline
  back_insert_iterator<nnxx::socket> &
  back_insert_iterator<nnxx::socket>::operator++()
  { return *this; }

  inline
  back_insert_iterator<nnxx::socket> &
  back_insert_iterator<nnxx::socket>::operator++(int)
  { return *this; }

}

#include <nnxx/socket.hpp>
#endif // NNXX_SOCKET_H
