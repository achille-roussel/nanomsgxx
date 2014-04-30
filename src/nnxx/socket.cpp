#include <algorithm>
#include <cstring>
#include <nnxx/error.h>
#include <nnxx/message.h>
#include <nnxx/socket.h>

namespace nnxx {

  static int check_socket_error(int flags)
  {
    if (this_thread::get_errc() != std::errc::resource_unavailable_try_again) {
      throw_error();
    }
    if (!(flags & DONTWAIT)) {
      throw timeout_error{ };
    }
    return -1;
  }

  socket::socket() noexcept:
    m_fd(-1)
  { }

  socket::socket(socket &&s) noexcept:
    m_fd(s.m_fd)
  { s.detach(); }

  socket::socket(int domain, int protocol):
    m_fd(nn_socket(domain, protocol))
  { check_error(m_fd); }

  socket::socket(int fd) noexcept:
    m_fd(fd)
  { }

  socket::~socket()
  { force_close(); }

  socket &socket::operator=(socket &&s) noexcept
  {
    s.swap(*this);
    return *this;
  }

  socket::operator bool () const noexcept
  { return m_fd >= 0; }

  void socket::swap(socket &s) noexcept
  {
    using std::swap;
    swap(m_fd, s.m_fd);
  }

  void socket::detach() noexcept
  { m_fd = -1; }

  void socket::close()
  {
    if (m_fd >= 0) {
      check_error(nn_close(m_fd));
      m_fd = -1;
    }
  }

  void socket::force_close() noexcept
  {
    while (true) {
      try {
        close();
        break;
      }
      catch (const std::exception &) {
      }
    }
  }

  endpoint socket::bind(const char *addr)
  { return check_error(nn_bind(m_fd, addr)); }

  endpoint socket::connect(const char *addr)
  { return check_error(nn_connect(m_fd, addr)); }

  void socket::shutdown(endpoint how)
  { check_error(nn_shutdown(m_fd, how)); }

  void socket::force_shutdown(endpoint how)
  {
    while (true) {
      try {
        shutdown(how);
        break;
      }
      catch (const term_error &) {
        throw;
      }
      catch (const std::exception &) {
      }
    }
  }

  void socket::setopt(int level, int option, const void *val, size_t len)
  { check_error(nn_setsockopt(m_fd, level, option, val, len)); }

  void socket::getopt(int level, int option, void *val, size_t *len) const
  { check_error(nn_getsockopt(m_fd, level, option, val, len)); }

  int socket::send(const void *buf, size_t len, int flags, socket_address &&addr)
  {
    int n;

    if ((n = nn_sendto(m_fd, buf, len, flags, &addr)) < 0) {
      return check_socket_error(flags);
    }

    addr.detach();
    return n;
  }

  int socket::send(const void *buf, size_t len, int flags)
  {
    int n;

    if ((n = nn_send(m_fd, buf, len, flags)) < 0) {
      return check_socket_error(flags);
    }

    return n;
  }

  int socket::send(const char *str, int flags, socket_address &&addr)
  { return send(str, std::strlen(str), flags, std::move(addr)); }

  int socket::send(const char *str, int flags)
  { return send(str, std::strlen(str), flags); }

  int socket::send(message &&msg, int flags, socket_address &&addr)
  {
    message::pointer data = msg.data();
    int n;

    if ((n = nn_sendto(m_fd, &data, MSG, flags, &addr)) < 0) {
      return check_socket_error(flags);
    }

    addr.detach();
    msg.detach();
    return n;
  }

  int socket::send(message &&msg, int flags)
  {
    message::pointer data = msg.data();
    int n;

    if ((n = nn_send(m_fd, &data, MSG, flags)) < 0) {
      return check_socket_error(flags);
    }

    msg.detach();
    return n;
  }

  int socket::recv(void *buf, size_t len, int flags, socket_address &addr)
  {
    socket_address ctrl;
    int n;

    if ((n = nn_recvfrom(m_fd, buf, len, flags, &ctrl)) < 0) {
      return check_socket_error(flags);
    }

    addr = std::move(ctrl);
    return n;
  }

  int socket::recv(void *buf, size_t len, int flags)
  {
    int n;

    if ((n = nn_recv(m_fd, buf, len, flags)) < 0) {
      return check_socket_error(flags);
    }

    return n;
  }

  message socket::recv(int flags, socket_address &addr)
  {
    socket_address ctrl;
    void *p;
    int   n;

    if ((n = nn_recvfrom(m_fd, &p, MSG, flags, &ctrl)) < 0) {
      check_socket_error(flags);
      return { };
    }

    addr = std::move(ctrl);
    return make_message(p, n);
  }

  message socket::recv(int flags)
  {
    void *p;
    int   n;

    if ((n = nn_recv(m_fd, &p, MSG, flags)) < 0) {
      check_socket_error(flags);
      return { };
    }

    return make_message(p, n);
  }

  int socket::fd() const noexcept
  { return m_fd; }

  socket make_socket(int fd) noexcept
  { return socket{ fd }; }

  void swap(socket &s1, socket &s2) noexcept
  { s1.swap(s2); }

}
