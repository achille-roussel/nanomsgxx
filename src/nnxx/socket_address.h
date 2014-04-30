#ifndef NNXX_SOCKET_ADDRESS_H
#define NNXX_SOCKET_ADDRESS_H

#include <nnxx/nn_ext.h>

namespace nnxx {

  class socket_address : public nn_sockaddr_ctrl {
  public:
    socket_address() noexcept;
    socket_address(socket_address &&a) noexcept;
    socket_address(socket_address const &a);

    ~socket_address();

    operator bool () const noexcept;
    socket_address &operator=(socket_address &&a) noexcept;
    socket_address &operator=(socket_address const &a);

    void swap(socket_address &a) noexcept;
    void clear() noexcept;
    void detach() noexcept;
    size_t hash() const noexcept;
  };

  void swap(socket_address &a1, socket_address &a2) noexcept;

  int compare(const socket_address &a1, const socket_address &a2) noexcept;

  bool operator==(const socket_address &a1, const socket_address &a2) noexcept;

  bool operator!=(const socket_address &a1, const socket_address &a2) noexcept;

  bool operator<(const socket_address &a1, const socket_address &a2) noexcept;

  bool operator>(const socket_address &a1, const socket_address &a2) noexcept;

  bool operator<=(const socket_address &a1, const socket_address &a2) noexcept;

  bool operator>=(const socket_address &a1, const socket_address &a2) noexcept;

}

#endif // NNXX_SOCKET_ADDRESS_H
