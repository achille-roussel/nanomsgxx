#ifndef NNXX_REQREP_H
#define NNXX_REQREP_H

#include <nanomsg/reqrep.h>

namespace nnxx {

  enum {
    REQ = NN_REQ,
    REP = NN_REP,
  };
  
  enum {
    REP_RESEND_IVL = NN_REQ_RESEND_IVL,
  };

}

#endif // NNXX_REQREP_H
