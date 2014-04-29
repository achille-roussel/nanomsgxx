#ifndef NNXX_NN_H
#define NNXX_NN_H

#include <nanomsg/nn.h>

namespace nnxx {

  typedef struct nn_pollfd pollfd;

  enum {
    SP     = AF_SP,
    SP_RAW = AF_SP_RAW,
  };

  enum {
    NS_NAMESPACE        = NN_NS_NAMESPACE,
    NS_VERSION          = NN_NS_VERSION,
    NS_DOMAIN           = NN_NS_DOMAIN,
    NS_TRANSPORT        = NN_NS_TRANSPORT,
    NS_PROTOCOL         = NN_NS_PROTOCOL,
    NS_OPTION_LEVEL     = NN_NS_OPTION_LEVEL,
    NS_SOCKET_OPTION    = NN_NS_SOCKET_OPTION,
    NS_TRANSPORT_OPTION = NN_NS_TRANSPORT_OPTION,
    NS_OPTION_TYPE      = NN_NS_OPTION_TYPE,
    NS_FLAG             = NN_NS_FLAG,
    NS_ERROR            = NN_NS_ERROR,
    NS_LIMIT            = NN_NS_LIMIT,
  };

  enum {
    TYPE_NONE = NN_TYPE_NONE,
    TYPE_INT  = NN_TYPE_INT,
    TYPE_STR  = NN_TYPE_STR,
  };

  enum {
    UNIT_NONE         = NN_UNIT_NONE,
    UNIT_BYTES        = NN_UNIT_BYTES,
    UNIT_MILLISECONDS = NN_UNIT_MILLISECONDS,
    UNIT_PRIORITY     = NN_UNIT_PRIORITY,
    UNIT_BOOLEAN      = NN_UNIT_BOOLEAN,
  };

  enum {
    // POLLIN and POLLOUT may already be defined for the standard poll function
    EV_POLLIN  = NN_POLLIN,
    EV_POLLOUT = NN_POLLOUT,
  };

  struct symbol_properties : public nn_symbol_properties {
    operator bool () const noexcept { return name != nullptr; }
  };

  symbol_properties symbol(int cst);

  void term();

  void device(class socket &s);

  void device(class socket &s1, class socket &s2);

  int poll(pollfd *fds, int nfds, int timeout);

  inline const char *c_str(const char *s) noexcept
  { return s; }

  template < typename String >
  const char *c_str(const String &s) noexcept(noexcept(s.c_str()))
  { return s.c_str(); }

}

#endif // NNXX_NN_H
