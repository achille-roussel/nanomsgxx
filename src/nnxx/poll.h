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

#ifndef NNXX_POLL_H
#define NNXX_POLL_H

#include <iterator>
#include <utility>
#include <vector>
#include <nnxx/chrono.h>
#include <nnxx/nn.h>

namespace nnxx {

  class socket;

  class poll_entry : public pollfd {
  public:
    poll_entry() noexcept;
    poll_entry(int s, int ev) noexcept;
    poll_entry(socket &s, int ev) noexcept;

    void clear() noexcept;
    void set(int s, int ev) noexcept;
    void set(socket &s, int ev) noexcept;

    bool is(const socket &s) const noexcept;
    bool recv_ready() const noexcept;
    bool send_ready() const noexcept;
  };

  typedef std::vector<poll_entry> poll_vector;

  poll_entry wait_recv(socket &s) noexcept;
  poll_entry wait_send(socket &s) noexcept;
  poll_entry wait_any(socket &s)  noexcept;

  bool operator==(const poll_entry &e, const socket &s) noexcept;
  bool operator!=(const poll_entry &e, const socket &s) noexcept;
  bool operator==(const socket &s, const poll_entry &e) noexcept;
  bool operator!=(const socket &s, const poll_entry &e) noexcept;

  template < int Event, typename Iterator >
  class ready_iterator :
    public std::iterator<typename std::input_iterator_tag,
                         typename Iterator::value_type,
                         typename Iterator::difference_type,
                         typename Iterator::pointer,
                         typename Iterator::reference> {
  public:
    typedef Iterator base_iterator_type;
    typedef typename base_iterator_type::value_type      value_type;
    typedef typename base_iterator_type::difference_type difference_type;
    typedef typename base_iterator_type::pointer         pointer;
    typedef typename base_iterator_type::reference       reference;
    typedef typename std::input_iterator_tag             iterator_category;

    ready_iterator(base_iterator_type first, base_iterator_type last);
    ready_iterator(ready_iterator      &&) = default;
    ready_iterator(ready_iterator const &) = default;

    ready_iterator &operator=(ready_iterator      &&) = default;
    ready_iterator &operator=(ready_iterator const &) = default;

    bool operator==(const ready_iterator &it) const;
    bool operator!=(const ready_iterator &it) const;

    pointer   operator->() const;
    reference operator* () const;

    ready_iterator &operator++();
    ready_iterator  operator++(int);

  private:
    base_iterator_type m_cur;
    base_iterator_type m_end;
  };

  template < int Event, typename Vector >
  class ready_sequence
  {
  public:
    typedef Vector vector_type;
    typedef ready_iterator<Event, decltype(std::declval<Vector>().begin())> iterator;

    ready_sequence()               noexcept;
    ready_sequence(vector_type &v) noexcept;

    iterator begin() const;
    iterator end()   const;

  private:
    vector_type *m_vector;
  };

  typedef ready_iterator<EV_POLLIN , poll_vector::iterator>             recv_ready_iterator;
  typedef ready_iterator<EV_POLLOUT, poll_vector::iterator>             send_ready_iterator;
  typedef ready_iterator<EV_POLLIN , poll_vector::const_iterator> const_recv_ready_iterator;
  typedef ready_iterator<EV_POLLOUT, poll_vector::const_iterator> const_send_ready_iterator;
  typedef ready_sequence<EV_POLLIN , poll_vector>                       recv_ready_sequence;
  typedef ready_sequence<EV_POLLOUT, poll_vector>                       send_ready_sequence;
  typedef ready_sequence<EV_POLLIN , poll_vector const>           const_recv_ready_sequence;
  typedef ready_sequence<EV_POLLOUT, poll_vector const>           const_send_ready_sequence;

  poll_vector poll(poll_vector &&entries);
  poll_vector poll(poll_vector &&entries, time_point timeout, int flags = 0);
  poll_vector poll(poll_vector &&entries, duration timeout, int flags = 0);

  poll_vector &poll(poll_vector &entries);
  poll_vector &poll(poll_vector &entries, time_point timeout, int flags = 0);
  poll_vector &poll(poll_vector &entries, duration timeout, int flags = 0);

  template < typename Rep, typename Period >
  poll_vector &poll(poll_vector &entries,
                    const std::chrono::duration<Rep, Period> &timeout,
                    int flags = 0)
  { return poll(entries, std::chrono::duration_cast<duration>(timeout), flags); }

  template < typename Clock, typename Duration >
  poll_vector &poll(poll_vector &entries,
                    const std::chrono::time_point<Clock, Duration> &timeout,
                    int flags = 0)
  { return poll(entries, std::chrono::time_point_cast<time_point>(timeout), flags); }

  template < typename Rep, typename Period >
  poll_vector poll(poll_vector &&entries,
                   const std::chrono::duration<Rep, Period> &timeout,
                   int flags = 0)
  { return poll(std::forward<poll_vector>(entries),
                std::chrono::duration_cast<duration>(timeout), flags); }

  template < typename Clock, typename Duration >
  poll_vector poll(poll_vector &&entries,
                   const std::chrono::time_point<Clock, Duration> &timeout,
                   int flags = 0)
  { return poll(std::forward<poll_vector>(entries),
                std::chrono::time_point_cast<time_point>(timeout), flags); }

        recv_ready_sequence recv_ready(poll_vector       &entries) noexcept;
  const_recv_ready_sequence recv_ready(poll_vector const &entries) noexcept;

        send_ready_sequence send_ready(poll_vector       &entries) noexcept;
  const_send_ready_sequence send_ready(poll_vector const &entries) noexcept;

  extern template class ready_iterator<EV_POLLIN , poll_vector::iterator>;
  extern template class ready_iterator<EV_POLLOUT, poll_vector::iterator>;
  extern template class ready_iterator<EV_POLLIN , poll_vector::const_iterator>;
  extern template class ready_iterator<EV_POLLOUT, poll_vector::const_iterator>;
  extern template class ready_sequence<EV_POLLIN , poll_vector>;
  extern template class ready_sequence<EV_POLLOUT, poll_vector>;
  extern template class ready_sequence<EV_POLLIN , poll_vector const>;
  extern template class ready_sequence<EV_POLLOUT, poll_vector const>;

}

#endif // NNXX_POLL_H
