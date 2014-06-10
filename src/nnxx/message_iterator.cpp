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

#include <nnxx/message_iterator.h>
#include <nnxx/error.h>
#include <nnxx/socket.h>

namespace nnxx {

  message_iterator::message_iterator() noexcept:
    m_socket(nullptr),
    m_message()
  { }

  message_iterator::message_iterator(socket &s):
    m_socket(&s),
    m_message(s.recv())
  { }

  bool message_iterator::operator==(const message_iterator &it) const noexcept
  { return m_socket == it.m_socket; }

  bool message_iterator::operator!=(const message_iterator &it) const noexcept
  { return m_socket != it.m_socket; }

  message_iterator::pointer message_iterator::operator->() noexcept
  { return &m_message; }

  message_iterator::reference message_iterator::operator*() noexcept
  { return m_message; }

  message_iterator &message_iterator::operator++()
  {
    try {
      m_message = m_socket->recv();
    }
    catch (const timeout_error &) {
      m_socket = nullptr;
    }
    catch (...) {
      m_socket = nullptr;
      throw;
    }
    return *this;
  }

  message_iterator message_iterator::operator++(int)
  {
    message_iterator tmp;
    tmp.m_socket  = m_socket;
    tmp.m_message = std::move(m_message);
    ++(*this);
    return tmp;
  }

}
