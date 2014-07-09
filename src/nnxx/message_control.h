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

#ifndef NNXX_MESSAGE_CONTROL_H
#define NNXX_MESSAGE_CONTROL_H

#include <nanomsg/ext/nnxx_ext.h>

namespace nnxx {

  class message_control : public nn_msgctl {
  public:
    message_control() noexcept;
    message_control(message_control &&a) noexcept;
    message_control(message_control const &a);

    ~message_control();

    operator bool () const noexcept;
    message_control &operator=(message_control &&a) noexcept;
    message_control &operator=(message_control const &a);

    void swap(message_control &a) noexcept;
    void clear() noexcept;
    void detach() noexcept;
    size_t hash() const noexcept;
  };

  void swap(message_control &a1, message_control &a2) noexcept;

  int compare(const message_control &a1, const message_control &a2) noexcept;

  bool operator==(const message_control &a1, const message_control &a2) noexcept;
  bool operator!=(const message_control &a1, const message_control &a2) noexcept;
  bool operator<(const message_control &a1, const message_control &a2) noexcept;
  bool operator>(const message_control &a1, const message_control &a2) noexcept;
  bool operator<=(const message_control &a1, const message_control &a2) noexcept;
  bool operator>=(const message_control &a1, const message_control &a2) noexcept;

  struct message_control_hash {
    size_t operator()(const message_control &ctl) const noexcept
    { return ctl.hash(); }
  };

}

#ifndef NNXX_NO_STD_EXT
namespace std {

  template < >
  struct hash<nnxx::message_control> : public nnxx::message_control_hash
  { };

}
#endif // NNXX_NO_STD_EXT
#endif // NNXX_MESSAGE_CONTROL_H
