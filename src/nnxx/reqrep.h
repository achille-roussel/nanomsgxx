#ifndef NNXX_REQREP_H
#define NNXX_REQREP_H

#include <nanomsg/reqrep.h>
#include <nnxx/chrono.h>

namespace nnxx {

  class socket;

  enum {
    REQ = NN_REQ,
    REP = NN_REP,
  };
  
  enum {
    REQ_RESEND_IVL = NN_REQ_RESEND_IVL,
  };

  milliseconds get_resend_interval(const socket &s);

  void set_resend_interval(socket &s, milliseconds i);

  template < typename Rep, typename Period >
  void set_resend_interval(socket &s,
                           const std::chrono::duration<Rep, Period> &i)
  { set_resend_interval(s, std::chrono::duration_cast<milliseconds>(i)); }

}

#endif // NNXX_REQREP_H
