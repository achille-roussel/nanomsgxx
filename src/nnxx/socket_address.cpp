#include <utility>
#include <nnxx/error.h>
#include <nnxx/socket_address.h>

namespace nnxx {

  socket_address::socket_address() noexcept
  { nn_sockaddr_ctrl_init(this); }

  socket_address::socket_address(socket_address &&a) noexcept:
    nn_sockaddr_ctrl(a)
  { a.detach(); }

  socket_address::socket_address(const socket_address &a)
  { check_error(nn_sockaddr_ctrl_copy(this, &a)); }

  socket_address::~socket_address()
  { nn_sockaddr_ctrl_term(this); }

  socket_address::operator bool () const noexcept
  { return sa_control != nullptr; }

  socket_address &socket_address::operator=(socket_address &&a) noexcept
  {
    a.swap(*this);
    return *this;
  }

  socket_address &socket_address::operator=(const socket_address &a)
  {
    socket_address{ a }.swap(*this);
    return *this;
  }

  void socket_address::swap(socket_address &a) noexcept
  {
    using std::swap;
    swap(static_cast<nn_sockaddr_ctrl &>(*this),
         static_cast<nn_sockaddr_ctrl &>(a));
  }

  void socket_address::clear() noexcept
  {
    nn_sockaddr_ctrl_term(this);
    nn_sockaddr_ctrl_init(this);
  }

  void socket_address::detach() noexcept
  { nn_sockaddr_ctrl_init(this); }

  size_t socket_address::hash() const noexcept
  { return nn_sockaddr_ctrl_hash(this); }

  void swap(socket_address &a1, socket_address &a2) noexcept
  { a1.swap(a2); }

  int compare(const socket_address &a1, const socket_address &a2) noexcept
  { return nn_sockaddr_ctrl_cmp(&a1, &a2); }

  bool operator==(const socket_address &a1, const socket_address &a2) noexcept
  { return compare(a1, a2) == 0; }

  bool operator!=(const socket_address &a1, const socket_address &a2) noexcept
  { return compare(a1, a2) != 0; }

  bool operator<(const socket_address &a1, const socket_address &a2) noexcept
  { return compare(a1, a2) < 0; }

  bool operator>(const socket_address &a1, const socket_address &a2) noexcept
  { return compare(a1, a2) > 0; }

  bool operator<=(const socket_address &a1, const socket_address &a2) noexcept
  { return compare(a1, a2) <= 0; }

  bool operator>=(const socket_address &a1, const socket_address &a2) noexcept
  { return compare(a1, a2) >= 0; }

}
