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

#ifndef NNXX_EXCEPTION_H
#define NNXX_EXCEPTION_H

#include <cerrno>
#include <utility>
#include <system_error>

namespace nnxx {
  using std::errc;

  class term_error : public std::exception {
  public:
    const char *what() const noexcept;
  };

  class timeout_error : public std::system_error {
  public:
    timeout_error();
  };

  class signal_error : public std::system_error {
  public:
    signal_error();
  };

  namespace this_thread {
  int  get_errno() noexcept;
  errc get_errc()  noexcept;
  }

  const char *strerror()         noexcept;
  const char *strerror(int code) noexcept;

  [[noreturn]] void throw_error();
  [[noreturn]] void throw_error(int code);

  inline void *check_error(void *ptr)
  {
    if (ptr == nullptr) {
      throw_error();
    }
    return ptr;
  }

  inline int check_error(int code)
  {
    if (code < 0) {
      throw_error();
    }
    return code;
  }

}

#endif // NNXX_EXCEPTION_H
