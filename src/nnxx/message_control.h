#ifndef NNXX_MESSAGE_CONTROL_H
#define NNXX_MESSAGE_CONTROL_H

#include <nnxx/nn_ext.h>

namespace nnxx {

  class message_control : public nn_msgctl {
  public:
    message_control() noexcept;
    message_control(message_control &&a) noexcept;
    message_control(message_control const &a);

    ~message_control();

    operator bool () const noexcept;
    message_control &operator=(message_control &&a) noexcept;
    message_control &operator=(message_control const &a);

    void swap(message_control &a) noexcept;
    void clear() noexcept;
    void detach() noexcept;
    size_t hash() const noexcept;
  };

  void swap(message_control &a1, message_control &a2) noexcept;

  int compare(const message_control &a1, const message_control &a2) noexcept;

  bool operator==(const message_control &a1, const message_control &a2) noexcept;

  bool operator!=(const message_control &a1, const message_control &a2) noexcept;

  bool operator<(const message_control &a1, const message_control &a2) noexcept;

  bool operator>(const message_control &a1, const message_control &a2) noexcept;

  bool operator<=(const message_control &a1, const message_control &a2) noexcept;

  bool operator>=(const message_control &a1, const message_control &a2) noexcept;

}

#endif // NNXX_MESSAGE_CONTROL_H
