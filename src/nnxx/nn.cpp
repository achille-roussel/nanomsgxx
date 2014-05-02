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

#include <nnxx/error.h>
#include <nnxx/nn.h>
#include <nnxx/socket.h>

namespace nnxx {

  symbol_properties symbol(int i)
  {
    symbol_properties sp;
    sp.value = 0;
    sp.name  = nullptr;
    sp.ns    = 0;
    sp.type  = 0;
    sp.unit  = 0;
    nn_symbol_info(i, &sp, sizeof(sp));
    return sp;
  }

  void term()
  { nn_term(); }

  void device(socket &s1)
  {
    socket s2;
    device(s1, s2);
  }

  void device(socket &s1, socket &s2)
  {
    nn_device(s1.fd(), s2.fd());
    throw_error();
  }

  int poll(pollfd *fds, int nfds, int timeout)
  { return check_error(nn_poll(fds, nfds, timeout)); }

}
