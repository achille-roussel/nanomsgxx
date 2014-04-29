#include <nnxx/error.h>
#include <nnxx/nn.h>

using namespace std;

namespace nnxx {

  const char *termination::what() const noexcept
  { return strerror(ETERM); }

  namespace this_thread {

  int get_errno() noexcept
  { return nn_errno(); }

  errc get_errc() noexcept
  { return errc(get_errno()); }

  }

  const char *strerror() noexcept
  { return strerror(this_thread::get_errno()); }

  const char *strerror(int code) noexcept
  { return nn_strerror(code); }

  void throw_error()
  { throw_error(this_thread::get_errno()); }

  void throw_error(int code)
  {
    switch (code) {
    case ENOMEM:
      throw bad_alloc{ };
    case ETERM:
      throw termination{ };
    default:
      throw system_error{ make_error_code(errc(code)), strerror() };
    }
  }

}
