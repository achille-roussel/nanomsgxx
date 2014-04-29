#ifndef NNXX_NN_H
#define NNXX_NN_H

#include <nanomsg/nn.h>

namespace nnxx {

  enum {
    SP     = AF_SP,
    SP_RAW = AF_SP_RAW,
  };

  inline const char *c_str(const char *s) noexcept
  { return s; }

  template < typename String >
  const char *c_str(const String &s) noexcept(noexcept(s.c_str()))
  { return s.c_str(); }

}

#endif // NNXX_NN_H
