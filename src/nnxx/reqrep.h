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

#ifndef NNXX_REQREP_H
#define NNXX_REQREP_H

#include <nanomsg/reqrep.h>
#include <nnxx/chrono.h>

namespace nnxx {

  class socket;

  enum {
    REQ = NN_REQ,
    REP = NN_REP,
  };
  
  enum {
    REQ_RESEND_IVL = NN_REQ_RESEND_IVL,
  };

  milliseconds get_resend_interval(const socket &s);

  template < typename Duration >
  Duration get_resend_interval(const socket &s)
  { return std::chrono::duration_cast<Duration>(get_resend_interval(s)); }

  void set_resend_interval(socket &s, milliseconds i);

  template < typename Rep, typename Period >
  void set_resend_interval(socket &s,
                           const std::chrono::duration<Rep, Period> &i)
  { set_resend_interval(s, std::chrono::duration_cast<milliseconds>(i)); }

}

#endif // NNXX_REQREP_H
