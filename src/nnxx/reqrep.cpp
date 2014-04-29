#include <nnxx/reqrep.h>
#include <nnxx/socket.h>

namespace nnxx {

  milliseconds get_resend_interval(const socket &s)
  { return milliseconds(getsockopt<int>(s, REQ, REQ_RESEND_IVL)); }

  void set_resend_interval(socket &s, milliseconds i)
  { setsockopt(s, REQ, REQ_RESEND_IVL, static_cast<int>(i.count())); }

}
