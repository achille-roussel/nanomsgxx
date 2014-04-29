#ifndef NNXX_UNITTEST_H
#define NNXX_UNITTEST_H

#include <cstdio>
#include <cstdlib>

namespace nnxx { namespace unittest {

  int result = EXIT_SUCCESS;

  } }

#define nnxx_check(x)                                                   \
  do {                                                                  \
    if (!(x)) {                                                         \
      std::fprintf(stderr, "%s:%d: check failed: %s\n", __FILE__, __LINE__, #x); \
      nnxx::unittest::result = EXIT_FAILURE;                            \
    }                                                                   \
  } while (0)

#define nnxx_assert(x)                                                  \
  do {                                                                  \
    if (!(x)) {                                                         \
      std::fprintf(stderr, "%s:%d: assertion failed: %s\n", __FILE__, __LINE__, #x); \
      std::exit(EXIT_FAILURE);                                          \
    }                                                                   \
  } while (0)

#endif // NNXX_UNITTEST_H
