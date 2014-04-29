#ifndef NNXX_SOCKET_H
#define NNXX_SOCKET_H

#include <nnxx/nn.h>

namespace nnxx {

  enum {
    SOCKET = NN_SOL_SOCKET, // SOL_SOCKET is already defined
  };

  enum {
    DOMAIN            = NN_DOMAIN,
    PROTOCOL          = NN_PROTOCOL,
    LINGER            = NN_LINGER,
    SNDBUF            = NN_SNDBUF,
    RCVBUF            = NN_RCVBUF,
    SNDTIMEO          = NN_SNDTIMEO,
    RCVTIMEO          = NN_RCVTIMEO,
    RECONNECT_IVL     = NN_RECONNECT_IVL,
    RECONNECT_IVL_MAX = NN_RECONNECT_IVL_MAX,
    SNDPRIO           = NN_SNDPRIO,
    IPV4ONLY          = NN_IPV4ONLY,
    SOCKET_NAME       = NN_SOCKET_NAME,
  };

  enum {
    MSG = NN_MSG,
  };

  enum {
    DONTWAIT = NN_DONTWAIT,
  };

  typedef int endpoint;

  class message;

  class socket {
  public:
    socket() noexcept;
    socket(socket &&s) noexcept;
    socket(socket const &) = delete;
    socket(int domain, int protocol);

    ~socket();

    socket &operator=(socket &&s) noexcept;
    socket &operator=(socket const &) = delete;

    operator bool () const noexcept;

    void swap(socket &s) noexcept;

    void detach() noexcept;

    void close();

    void force_close() noexcept;

    endpoint bind(const char *addr);

    template < typename String >
    endpoint bind(const String &addr)
    { return bind(c_str(addr)); }

    endpoint connect(const char *addr);

    template < typename String >
    endpoint connect(const String &addr)
    { return connect(c_str(addr)); }

    void shutdown(endpoint how);

    void force_shutdown(endpoint how);

    void setopt(int level, int option, const void *val, size_t len);

    template < typename T >
    void setopt(int level, int option, const T &val)
    { setopt(level, option, &val, sizeof(val)); }

    void getopt(int level, int option, void *optval, size_t *len) const;

    template < typename T >
    size_t getopt(int level, int option, T &val) const
    {
      size_t len = sizeof(val);
      getopt(level, option, &val, &len);
      return len;
    }

    int send(const void *buf, size_t len, int flags = 0);

    int send(const char *str, int flags = 0);

    int send(message &&msg, int flags = 0);

    template < typename String >
    int send(const String &s, int flags = 0)
    { return send(c_str(s), flags); }

    int recv(void *buf, size_t len, int flags = 0);

    message recv(int flags = 0);

    int fd() const noexcept;

    friend socket make_socket(int fd) noexcept;

  private:
    int m_fd;

    explicit socket(int) noexcept;
  };

  inline void swap(socket &s1, socket &s2) noexcept
  { s1.swap(s2); }

  template < typename T >
  void setsockopt(socket &s, int level, int option, const T &val)
  { s.setopt(level, option, val); }

  template < typename T >
  void getsockopt(const socket &s, int level, int option)
  {
    T val;
    s.getopt(level, option, val);
    return val;
  }

  socket make_socket(int fd) noexcept;

}

#endif // NNXX_SOCKET_H
