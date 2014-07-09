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

#ifdef  NNXX_SOCKET_H
#ifndef NNXX_SOCKET_HPP
#define NNXX_SOCKET_HPP

namespace nnxx {

  template < typename T >
  void socket::setopt(int level, int option, const T &val)
  { setopt(level, option, &val, sizeof(val)); }

  template < typename T >
  void socket::getopt(int level, int option, T &val) const
  {
    size_t len = sizeof(val);
    getopt(level, option, &val, &len);
  }

  template < typename T >
  T socket::getopt(int level, int option) const
  {
    T optval;
    getopt(level, option, optval);
    return optval;
  }

}

#endif // NNXX_SOCKET_HPP
#endif // NNXX_SOCKET_H

#if defined(NNXX_SOCKET_H) && defined(NNXX_MESSAGE_H)
#ifndef NNXX_SOCKET_MESSAGE
#define NNXX_SOCKET_MESSAGE

#include <iterator>

namespace nnxx {

  template < typename T >
  T socket::recv(int flags, message_control &ctl)
  {
    using std::begin;
    using std::end;
    const auto msg = this->recv(flags, ctl);
    return T{ begin(msg), end(msg) };
  }

  template < typename T >
  T socket::recv(int flags)
  {
    using std::begin;
    using std::end;
    const auto msg = this->recv(flags);
    return T{ begin(msg), end(msg) };
  }

  template < typename T >
  int socket::send(const T &obj, int flags, message_control &&ctl)
  { return send(make_message(obj), flags, ctl); }

  template < typename T >
  int socket::send(const T &obj, int flags)
  { return send(make_message(obj), flags); }

}

#endif // NNXX_SOCKET_MESSAGE
#endif // NNXX_SOCKET_H && NNXX_MESSAGE_H

