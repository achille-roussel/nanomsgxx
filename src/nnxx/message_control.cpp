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

#include <utility>
#include <nnxx/error.h>
#include <nnxx/message_control.h>

namespace nnxx {

  message_control::message_control() noexcept
  { nn_msgctl_init(this); }

  message_control::message_control(message_control &&a) noexcept:
    nn_msgctl(a)
  { a.detach(); }

  message_control::message_control(const message_control &a)
  { check_error(nn_msgctl_copy(this, &a)); }

  message_control::~message_control()
  { nn_msgctl_term(this); }

  message_control::operator bool () const noexcept
  { return this->ctl_base != nullptr; }

  message_control &message_control::operator=(message_control &&a) noexcept
  {
    a.swap(*this);
    return *this;
  }

  message_control &message_control::operator=(const message_control &a)
  {
    message_control{ a }.swap(*this);
    return *this;
  }

  void message_control::swap(message_control &a) noexcept
  {
    using std::swap;
    swap(static_cast<nn_msgctl &>(*this),
         static_cast<nn_msgctl &>(a));
  }

  void message_control::clear() noexcept
  {
    nn_msgctl_term(this);
    nn_msgctl_init(this);
  }

  void message_control::detach() noexcept
  { nn_msgctl_init(this); }

  size_t message_control::hash() const noexcept
  { return nn_msgctl_hash(this); }

  void swap(message_control &a1, message_control &a2) noexcept
  { a1.swap(a2); }

  int compare(const message_control &a1, const message_control &a2) noexcept
  { return nn_msgctl_cmp(&a1, &a2); }

  bool operator==(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) == 0; }

  bool operator!=(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) != 0; }

  bool operator<(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) < 0; }

  bool operator>(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) > 0; }

  bool operator<=(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) <= 0; }

  bool operator>=(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) >= 0; }

}
