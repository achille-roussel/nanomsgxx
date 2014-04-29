#include <nnxx/error.h>
#include <nnxx/nn.h>

namespace nnxx {

  namespace this_thread {

  int get_errno() noexcept
  { return nn_errno(); }

  std::errc get_errc() noexcept
  { return std::errc(get_errno()); }

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
      throw std::bad_alloc{ };
    default:
      throw std::system_error{ std::make_error_code(std::errc(code)) };
    }
  }

}
