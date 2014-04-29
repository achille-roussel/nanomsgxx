#ifndef NNXX_PIPELINE_H
#define NNXX_PIPELINE_H

#include <nanomsg/pipeline.h>

namespace nnxx {

  enum {
    PULL = NN_PULL,
    PUSH = NN_PUSH,
  };

}

#endif // NNXX_PIPELINE_H
