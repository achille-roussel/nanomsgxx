#include <algorithm>
#include <cstdio>
#include <ostream>
#include <nnxx/error.h>
#include <nnxx/message.h>

namespace nnxx {

  message::message() noexcept:
    m_data(nullptr),
    m_size(0)
  { }

  message::message(size_type size, int type):
    m_data(nn_allocmsg(size, type)),
    m_size(size)
  { check_error(m_data); }

  message::message(pointer data, size_type size) noexcept:
    m_data(data),
    m_size(size)
  { }

  message::message(message &&m) noexcept:
    m_data(m.m_data),
    m_size(m.m_size)
  { m.detach(); }

  message::~message()
  {
    if (m_data != nullptr) {
#ifdef NDEBUG
      nn_freemsg(m_data);
#else
      if (nn_freemsg(m_data) != 0) {
        std::fprintf(stderr, "warning: nn_freemsg: %s\n", strerror());
      }
#endif
    }
  }

  message &message::operator=(message &&m) noexcept
  {
    m.swap(*this);
    return *this;
  }

  void message::swap(message &m) noexcept
  {
    using std::swap;
    swap(m_data, m.m_data);
    swap(m_size, m.m_size);
  }

  void message::detach() noexcept
  {
    m_data = nullptr;
    m_size = 0;
  }

  message::operator bool () const noexcept
  { return m_data != nullptr; }

  message::pointer message::data() noexcept
  { return m_data; }

  message::const_pointer message::data() const noexcept
  { return m_data; }

  message::size_type message::size() const noexcept
  { return m_size; }

  message::size_type copy(const message &from, message &to) noexcept
  { return copy(from, to, 0, 0, std::min(from.size(), to.size())); }

  message::size_type copy(const message &from,
                          message &to,
                          message::size_type from_offset,
                          message::size_type to_offset,
                          message::size_type size) noexcept
  {
    using std::copy;
    using std::min;
    const message::size_type n1 = from.size();
    const message::size_type n2 = to.size();

    if ((from_offset >= n1) || (to_offset >= n2)) {
      return 0;
    }

    size = min(size, n1 - from_offset);
    size = min(size, n2 - to_offset);

    if (size == 0) {
      return 0;
    }

    copy(reinterpret_cast<const char *>(from.data()) + from_offset,
         reinterpret_cast<const char *>(from.data()) + from_offset + size,
         reinterpret_cast<char *>(to.data()));
    return size;
  }

  message copy(const message &msg, message::size_type size, int type)
  {
    using std::max;

    if ((size = max(size, msg.size())) == 0) {
      return { };
    }

    message new_msg { size, type };
    copy(msg, new_msg);
    return new_msg;
  }

  message make_message(message::pointer data, message::size_type size) noexcept
  { return message{ data, size }; }

  std::string to_string(const message &msg)
  {
    auto s = reinterpret_cast<const char *>(msg.data());
    auto t = s + msg.size();
    auto p = s;

    while ((p != t) && ((*p) != '\0')) {
      ++p;
    }

    return { s, p };
  }

  template std::ostream &operator<<(std::ostream &, const message &);

}
