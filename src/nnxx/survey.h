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

#ifndef NNXX_SURVEY_H
#define NNXX_SURVEY_H

#include <nanomsg/survey.h>
#include <nnxx/chrono.h>

namespace nnxx {

  class socket;

  enum {
    SURVEYOR   = NN_SURVEYOR,
    RESPONDENT = NN_RESPONDENT,
  };

  enum {
    SURVEYOR_DEADLINE = NN_SURVEYOR_DEADLINE,
  };

  milliseconds get_surveyor_deadline(const socket &s);

  template < typename Duration >
  Duration get_surveyor_deadline(const socket &s)
  { return std::chrono::duration_cast<Duration>(get_surveyor_deadline(s)); }

  void set_surveyor_deadline(socket &s, milliseconds t);

  template < typename Rep, typename Period >
  void set_surveyor_deadline(socket &s, const std::chrono::duration<Rep, Period> &t)
  { set_deadline(s, std::chrono::duration_cast<milliseconds>(t)); }

}

#endif // NNXX_SURVEY_H
