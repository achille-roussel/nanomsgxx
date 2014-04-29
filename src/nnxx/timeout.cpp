#include <nnxx/socket.h>
#include <nnxx/timeout.h>

namespace nnxx {

  milliseconds get_linger(const socket &s)
  { return milliseconds(getsockopt<int>(s, SOCKET, LINGER)); }

  milliseconds get_recv_timeout(const socket &s)
  { return milliseconds(getsockopt<int>(s, SOCKET, RCVTIMEO)); }

  milliseconds get_send_timeout(const socket &s)
  { return milliseconds(getsockopt<int>(s, SOCKET, SNDTIMEO)); }

  void set_linger(socket &s, milliseconds t)
  { setsockopt(s, SOCKET, LINGER, static_cast<int>(t.count())); }

  void set_recv_timeout(socket &s, milliseconds t)
  { setsockopt(s, SOCKET, RCVTIMEO, static_cast<int>(t.count())); }

  void set_send_timeout(socket &s, milliseconds t)
  { setsockopt(s, SOCKET, SNDTIMEO, static_cast<int>(t.count())); }

  with_linger::with_linger(socket &s, milliseconds t):
    m_socket(s),
    m_old_timeout(get_linger(s))
  { set_linger(s, t); }

  with_linger::~with_linger()
  { set_linger(m_socket, m_old_timeout); }

  with_recv_timeout::with_recv_timeout(socket &s, milliseconds t):
    m_socket(s),
    m_old_timeout(get_recv_timeout(s))
  { set_recv_timeout(s, t); }

  with_recv_timeout::~with_recv_timeout()
  { set_recv_timeout(m_socket, m_old_timeout); }

  with_send_timeout::with_send_timeout(socket &s, milliseconds t):
    m_socket(s),
    m_old_timeout(get_send_timeout(s))
  { set_send_timeout(s, t); }

  with_send_timeout::~with_send_timeout()
  { set_send_timeout(m_socket, m_old_timeout); }

}
