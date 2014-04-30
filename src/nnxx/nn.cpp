#include <nnxx/error.h>
#include <nnxx/nn.h>
#include <nnxx/socket.h>

namespace nnxx {

  symbol_properties symbol(int i)
  {
    symbol_properties sp;
    sp.value = 0;
    sp.name  = nullptr;
    sp.ns    = 0;
    sp.type  = 0;
    sp.unit  = 0;
    nn_symbol_info(i, &sp, sizeof(sp));
    return sp;
  }

  void term()
  { nn_term(); }

  void device(socket &s1)
  {
    socket s2;
    device(s1, s2);
  }

  void device(socket &s1, socket &s2)
  {
    nn_device(s1.fd(), s2.fd());
    throw_error();
  }

  int poll(pollfd *fds, int nfds, int timeout)
  { printf("poll: timeout = %d\n", timeout); return check_error(nn_poll(fds, nfds, timeout)); }

}
