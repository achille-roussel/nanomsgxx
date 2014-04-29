#ifndef NNXX_TIMEOUT_H
#define NNXX_TIMEOUT_H

#include <nnxx/chrono.h>

namespace nnxx {

  class socket;

  milliseconds get_linger(const socket &s);
  milliseconds get_recv_timeout(const socket &s);
  milliseconds get_send_timeout(const socket &s);

  void set_linger(socket &s, milliseconds t);
  void set_recv_timeout(socket &s, milliseconds t);
  void set_send_timeout(socket &s, milliseconds t);

  template < typename Rep, typename Period >
  void set_linger(socket &s, const std::chrono::duration<Rep, Period> &t)
  { set_linger(s, std::chrono::duration_cast<milliseconds>(t)); }

  template < typename Rep, typename Period >
  void set_recv_timeout(socket &s, const std::chrono::duration<Rep, Period> &t)
  { set_recv_timeout(s, std::chrono::duration_cast<milliseconds>(t)); }

  template < typename Rep, typename Period >
  void set_send_timeout(socket &s, const std::chrono::duration<Rep, Period> &t)
  { set_send_timeout(s, std::chrono::duration_cast<milliseconds>(t)); }

  class with_linger {
  public:
    with_linger(socket &s, milliseconds t);

    template < typename Rep, typename Period >
    with_linger(socket &s, const std::chrono::duration<Rep, Period> &t):
      m_socket(s),
      m_old_timeout(get_linger(s))
    { set_linger(s, t); }

    with_linger(with_linger      &&) = delete;
    with_linger(with_linger const &) = delete;

    ~with_linger() ;

    with_linger &operator=(with_linger      &&) = delete;
    with_linger &operator=(with_linger const &) = delete;

  private:
    socket &     m_socket;
    milliseconds m_old_timeout;

    void set(milliseconds);
  };

  class with_recv_timeout {
  public:
    with_recv_timeout(socket &s, milliseconds t);

    template < typename Rep, typename Period >
    with_recv_timeout(socket &s, const std::chrono::duration<Rep, Period> &t):
      m_socket(s),
      m_old_timeout(get_recv_timeout(s))
    { set_recv_timeout(s, t); }

    with_recv_timeout(with_recv_timeout      &&) = delete;
    with_recv_timeout(with_recv_timeout const &) = delete;

    ~with_recv_timeout() ;

    with_recv_timeout &operator=(with_recv_timeout      &&) = delete;
    with_recv_timeout &operator=(with_recv_timeout const &) = delete;

  private:
    socket &     m_socket;
    milliseconds m_old_timeout;

    void set(milliseconds);
  };

  class with_send_timeout {
  public:
    with_send_timeout(socket &s, milliseconds t);

    template < typename Rep, typename Period >
    with_send_timeout(socket &s, const std::chrono::duration<Rep, Period> &t):
      m_socket(s)
    { set(std::chrono::duration_cast<milliseconds>(t)); }

    with_send_timeout(with_send_timeout      &&) = delete;
    with_send_timeout(with_send_timeout const &) = delete;

    ~with_send_timeout();

    with_send_timeout &operator=(with_send_timeout      &&) = delete;
    with_send_timeout &operator=(with_send_timeout const &) = delete;

  private:
    socket &     m_socket;
    milliseconds m_old_timeout;

    void set(milliseconds);
  };

}

#endif // NNXX_TIMEOUT_H
