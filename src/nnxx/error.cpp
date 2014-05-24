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

using namespace std;

namespace nnxx {

  const char *term_error::what() const noexcept
  { return strerror(ETERM); }

  timeout_error::timeout_error():
    system_error(make_error_code(errc(ETIMEDOUT)), strerror(ETIMEDOUT))
  { }

  signal_error::signal_error():
    system_error(make_error_code(errc(EINTR)), strerror(EINTR))
  { }

  namespace this_thread {

  int get_errno() noexcept
  { return nn_errno(); }

  errc get_errc() noexcept
  { return errc(get_errno()); }

  }

  const char *strerror() noexcept
  { return strerror(this_thread::get_errno()); }

  const char *strerror(int code) noexcept
  { return nn_strerror(code); }

  void throw_error()
  { throw_error(this_thread::get_errno()); }

  void throw_error(int code)
  {
    switch (code) {
    case ENOMEM:
      throw bad_alloc{ };

    case ETERM:
      throw term_error{ };

    case ETIMEDOUT:
      throw timeout_error{ };

    case EINTR:
      throw signal_error{ };

    default:
      throw system_error{ make_error_code(errc(code)), strerror() };
    }
  }

}
