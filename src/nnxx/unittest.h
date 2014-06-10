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

#ifndef NNXX_UNITTEST_H
#define NNXX_UNITTEST_H

#include <cstdio>
#include <cstdlib>

namespace nnxx { namespace unittest {

  volatile int result = EXIT_SUCCESS;

  } }

#define nnxx_check(x)                                                   \
  do {                                                                  \
    if (!(x)) {                                                         \
      std::fprintf(stderr, "%s:%d: check failed: %s\n", __FILE__, __LINE__, #x); \
      nnxx::unittest::result = EXIT_FAILURE;                            \
    }                                                                   \
  } while (0)

#define nnxx_assert(x)                                                  \
  do {                                                                  \
    if (!(x)) {                                                         \
      std::fprintf(stderr, "%s:%d: assertion failed: %s\n", __FILE__, __LINE__, #x); \
      std::exit(EXIT_FAILURE);                                          \
    }                                                                   \
  } while (0)

#endif // NNXX_UNITTEST_H
