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

#ifndef NNXX_NN_H
#define NNXX_NN_H

#include <nanomsg/nn.h>

namespace nnxx {

  typedef struct nn_pollfd pollfd;

  enum {
    SOCKADDR_MAX = NN_SOCKADDR_MAX,
  };

  enum {
    SP     = AF_SP,
    SP_RAW = AF_SP_RAW,
  };

  enum {
    NS_NAMESPACE        = NN_NS_NAMESPACE,
    NS_VERSION          = NN_NS_VERSION,
    NS_DOMAIN           = NN_NS_DOMAIN,
    NS_TRANSPORT        = NN_NS_TRANSPORT,
    NS_PROTOCOL         = NN_NS_PROTOCOL,
    NS_OPTION_LEVEL     = NN_NS_OPTION_LEVEL,
    NS_SOCKET_OPTION    = NN_NS_SOCKET_OPTION,
    NS_TRANSPORT_OPTION = NN_NS_TRANSPORT_OPTION,
    NS_OPTION_TYPE      = NN_NS_OPTION_TYPE,
    NS_FLAG             = NN_NS_FLAG,
    NS_ERROR            = NN_NS_ERROR,
    NS_LIMIT            = NN_NS_LIMIT,
  };

  enum {
    TYPE_NONE = NN_TYPE_NONE,
    TYPE_INT  = NN_TYPE_INT,
    TYPE_STR  = NN_TYPE_STR,
  };

  enum {
    UNIT_NONE         = NN_UNIT_NONE,
    UNIT_BYTES        = NN_UNIT_BYTES,
    UNIT_MILLISECONDS = NN_UNIT_MILLISECONDS,
    UNIT_PRIORITY     = NN_UNIT_PRIORITY,
    UNIT_BOOLEAN      = NN_UNIT_BOOLEAN,
  };

  enum {
    // POLLIN and POLLOUT may already be defined for the standard poll function
    EV_POLLIN  = NN_POLLIN,
    EV_POLLOUT = NN_POLLOUT,
  };

  enum {
    DONTWAIT = NN_DONTWAIT,
    // These constant shall not collide with NN_DONTWAIT or any other flag used
    // on the nn_recv and nn_send functions.
    NO_SIGNAL_ERROR  = 1 << 14,
    NO_TIMEOUT_ERROR = 1 << 15,
  };

  struct symbol_properties : public nn_symbol_properties {
    operator bool () const noexcept { return name != nullptr; }
  };

  symbol_properties symbol(int cst);

  void term();

  void device(class socket &s);

  void device(class socket &s1, class socket &s2);

  int poll(pollfd *fds, int nfds, int timeout);

}

#endif // NNXX_NN_H
