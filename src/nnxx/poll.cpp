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
#include <nnxx/poll.h>
#include <nnxx/socket.h>

namespace nnxx {

  poll_entry wait_recv(socket &s) noexcept
  { return { s, EV_POLLIN }; }

  poll_entry wait_send(socket &s) noexcept
  { return { s, EV_POLLOUT }; }

  poll_entry wait_any(socket &s) noexcept
  { return { s, EV_POLLIN | EV_POLLOUT }; }

  template < int Event, typename Iterator >
  ready_iterator<Event, Iterator>::
  ready_iterator(base_iterator_type first, base_iterator_type last):
    m_cur(std::move(first)),
    m_end(std::move(last))
  {
    while ((m_cur != m_end) && !(m_cur->revents & Event)) {
      ++m_cur;
    }
  }

  template < int Event, typename Iterator >
  bool ready_iterator<Event, Iterator>::operator==(const ready_iterator &it) const
  { return m_cur == it.m_cur; }

  template < int Event, typename Iterator >
  bool ready_iterator<Event, Iterator>::operator!=(const ready_iterator &it) const
  { return m_cur != it.m_cur; }

  template < int Event, typename Iterator >
  typename
  ready_iterator<Event, Iterator>::pointer
  ready_iterator<Event, Iterator>::operator->() const
  { return m_cur.operator->(); }

  template < int Event, typename Iterator >
  typename
  ready_iterator<Event, Iterator>::reference
  ready_iterator<Event, Iterator>::operator*() const
  { return m_cur.operator*(); }

  template < int Event, typename Iterator >
  ready_iterator<Event, Iterator> &
  ready_iterator<Event, Iterator>::operator++()
  {
    do {
      ++m_cur;
    }
    while ((m_cur != m_end) && !(m_cur->revents & Event));
    return *this;
  }    

  template < int Event, typename Iterator >
  ready_iterator<Event, Iterator>
  ready_iterator<Event, Iterator>::operator++(int)
  {
    ready_iterator tmp { *this };
    ++(*this);
    return tmp;
  }

  template < int Event, typename Vector >
  ready_sequence<Event, Vector>::
  ready_sequence() noexcept:
    m_vector(nullptr)
  { }

  template < int Event, typename Vector >
  ready_sequence<Event, Vector>::
  ready_sequence(vector_type &v) noexcept:
    m_vector(&v)
  { }

  template < int Event, typename Vector >
  typename
  ready_sequence<Event, Vector>::iterator
  ready_sequence<Event, Vector>::begin() const
  { return { m_vector->begin(), m_vector->end() }; }

  template < int Event, typename Vector >
  typename
  ready_sequence<Event, Vector>::iterator
  ready_sequence<Event, Vector>::end() const
  { return { m_vector->end(), m_vector->end() }; }

  poll_entry::poll_entry() noexcept
  { clear(); }

  poll_entry::poll_entry(int s, int ev) noexcept
  { set(s, ev); }

  poll_entry::poll_entry(socket &s, int ev) noexcept
  { set(s, ev); }

  void poll_entry::clear() noexcept
  {
    this->fd      = -1;
    this->events  = 0;
    this->revents = 0;
  }

  void poll_entry::set(int s, int ev) noexcept
  {
    this->fd      = s;
    this->events  = ev;
    this->revents = 0;
  }

  void poll_entry::set(socket &s, int ev) noexcept
  { set(s.fd(), ev); }

  bool poll_entry::is(const socket &s) const noexcept
  { return this->fd == s.fd(); }

  bool poll_entry::recv_ready() const noexcept
  { return this->revents & EV_POLLIN; }

  bool poll_entry::send_ready() const noexcept
  { return this->revents & EV_POLLOUT; }

  bool operator==(const poll_entry &e, const socket &s) noexcept
  { return e.is(s); }

  bool operator!=(const poll_entry &e, const socket &s) noexcept
  { return !e.is(s); }

  bool operator==(const socket &s, const poll_entry &e) noexcept
  { return e == s; }

  bool operator!=(const socket &s, const poll_entry &e) noexcept
  { return e != s; }

  poll_vector poll(poll_vector &&entries)
  { return std::move(poll(entries)); }

  poll_vector poll(poll_vector &&entries, duration timeout, int flags)
  { return std::move(poll(entries, timeout, flags)); }

  poll_vector poll(poll_vector &&entries, time_point timeout, int flags)
  { return std::move(poll(entries, timeout, flags)); }

  poll_vector &poll(poll_vector &entries)
  { return poll(entries, duration::max()); }

  poll_vector &poll(poll_vector &entries, time_point timeout, int flags)
  { return poll(entries, timeout - clock::now(), flags); }

  poll_vector &poll(poll_vector &entries, duration timeout, int flags)
  {
    const int t = (timeout == duration::max())
      ? -1
      : std::chrono::duration_cast<milliseconds>(timeout).count(); 

    const int n = poll(entries.data(), entries.size(), t);

    if (n < 0) {
      const auto err = this_thread::get_errc();
      if ((err != std::errc::interrupted) || !(flags & NO_SIGNAL_ERROR)) {
        throw_error();
      }
    }

    if ((n == 0) && (t != 0) && !(flags & NO_TIMEOUT_ERROR)) {
      throw_error(ETIMEDOUT);
    }

    return entries;
  }

  recv_ready_sequence recv_ready(poll_vector &entries) noexcept
  { return { entries }; }

  const_recv_ready_sequence recv_ready(poll_vector const &entries) noexcept
  { return { entries }; }

  send_ready_sequence send_ready(poll_vector &entries) noexcept
  { return { entries }; }

  const_send_ready_sequence send_ready(poll_vector const &entries) noexcept
  { return { entries }; }

  template class ready_iterator<EV_POLLIN , poll_vector::iterator>;
  template class ready_iterator<EV_POLLOUT, poll_vector::iterator>;
  template class ready_iterator<EV_POLLIN , poll_vector::const_iterator>;
  template class ready_iterator<EV_POLLOUT, poll_vector::const_iterator>;
  template class ready_sequence<EV_POLLIN , poll_vector>;
  template class ready_sequence<EV_POLLOUT, poll_vector>;
  template class ready_sequence<EV_POLLIN , poll_vector const>;
  template class ready_sequence<EV_POLLOUT, poll_vector const>;

}
