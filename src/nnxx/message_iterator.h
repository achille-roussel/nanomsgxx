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

#ifndef NNXX_MESSAGE_ITERATOR_H
#define NNXX_MESSAGE_ITERATOR_H

#include <nnxx/message.h>

namespace nnxx {

  class socket;

  class message_iterator :
    public std::iterator<std::input_iterator_tag,
                         message,
                         std::ptrdiff_t,
                         message *,
                         message &> {
  public:
    typedef typename std::input_iterator_tag iterator_category;
    typedef typename std::ptrdiff_t          difference_type;
    typedef message                          value_type;
    typedef message *                        pointer;
    typedef message &                        reference;

    message_iterator() noexcept;
    message_iterator(socket &s);
    message_iterator(message_iterator      &&) = default;
    message_iterator(message_iterator const &) = default;

    message_iterator &operator=(message_iterator      &&) = default;
    message_iterator &operator=(message_iterator const &) = default;

    bool operator==(const message_iterator &it) const noexcept;
    bool operator!=(const message_iterator &it) const noexcept;

    pointer   operator->() noexcept;
    reference operator *() noexcept;

    message_iterator &operator++();
    message_iterator  operator++(int);

  private:
    socket *m_socket;
    message m_message;
  };

}

#endif // NNXX_MESSAGE_ITERATOR_H
