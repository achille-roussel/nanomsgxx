#ifndef NNXX_EXCEPTION_H
#define NNXX_EXCEPTION_H

#include <cerrno>
#include <utility>
#include <system_error>

namespace nnxx {

  class term_error : public std::exception {
  public:
    const char *what() const noexcept;
  };

  class timeout_error : public std::system_error {
  public:
    timeout_error();
  };

  class signal_error : public std::system_error {
  public:
    signal_error();
  };

  namespace this_thread {

  int get_errno() noexcept;

  std::errc get_errc() noexcept;

  }

  const char *strerror() noexcept;

  const char *strerror(int code) noexcept;

  void throw_error();

  void throw_error(int code);

  inline void *check_error(void *ptr)
  {
    if (ptr == nullptr) {
      throw_error();
    }
    return ptr;
  }

  inline int check_error(int code)
  {
    if (code < 0) {
      throw_error();
    }
    return code;
  }

}

#endif // NNXX_EXCEPTION_H
