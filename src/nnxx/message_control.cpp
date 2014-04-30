#include <utility>
#include <nnxx/error.h>
#include <nnxx/message_control.h>

namespace nnxx {

  message_control::message_control() noexcept
  { nn_msgctl_init(this); }

  message_control::message_control(message_control &&a) noexcept:
    nn_msgctl(a)
  { a.detach(); }

  message_control::message_control(const message_control &a)
  { check_error(nn_msgctl_copy(this, &a)); }

  message_control::~message_control()
  { nn_msgctl_term(this); }

  message_control::operator bool () const noexcept
  { return this->ctl_base != nullptr; }

  message_control &message_control::operator=(message_control &&a) noexcept
  {
    a.swap(*this);
    return *this;
  }

  message_control &message_control::operator=(const message_control &a)
  {
    message_control{ a }.swap(*this);
    return *this;
  }

  void message_control::swap(message_control &a) noexcept
  {
    using std::swap;
    swap(static_cast<nn_msgctl &>(*this),
         static_cast<nn_msgctl &>(a));
  }

  void message_control::clear() noexcept
  {
    nn_msgctl_term(this);
    nn_msgctl_init(this);
  }

  void message_control::detach() noexcept
  { nn_msgctl_init(this); }

  size_t message_control::hash() const noexcept
  { return nn_msgctl_hash(this); }

  void swap(message_control &a1, message_control &a2) noexcept
  { a1.swap(a2); }

  int compare(const message_control &a1, const message_control &a2) noexcept
  { return nn_msgctl_cmp(&a1, &a2); }

  bool operator==(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) == 0; }

  bool operator!=(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) != 0; }

  bool operator<(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) < 0; }

  bool operator>(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) > 0; }

  bool operator<=(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) <= 0; }

  bool operator>=(const message_control &a1, const message_control &a2) noexcept
  { return compare(a1, a2) >= 0; }

}
