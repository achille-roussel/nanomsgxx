#ifndef NNXX_MESSAGE_OSTREAM_HPP
#define NNXX_MESSAGE_OSTREAM_HPP

#include <utility>

namespace nnxx {

  template < typename Char, typename Traits >
  basic_message_ostream<Char, Traits>::
  basic_message_ostream(size_type base_size) noexcept:
    base_type(nullptr),
    m_buffer(base_size)
  { this->rdbuf(&m_buffer); }

  template < typename Char, typename Traits >
  basic_message_ostream<Char, Traits>::
  basic_message_ostream(message &&msg) noexcept:
    base_type(nullptr),
    m_buffer(std::move(msg))
  { this->rdbuf(&m_buffer); }

  template < typename Char, typename Traits >
  basic_message_ostream<Char, Traits>::
  ~basic_message_ostream()
  { }

  template < typename Char, typename Traits >
  void basic_message_ostream<Char, Traits>::msg(message &&m) noexcept
  { m_buffer.msg(std::move(m)); }

  template < typename Char, typename Traits >
  message basic_message_ostream<Char, Traits>::msg(int type)
  { return m_buffer.msg(type); }

  template < typename Char, typename Traits >
  message basic_message_ostream<Char, Traits>::move_msg()
  { return m_buffer.move_msg(); }

  template < typename Char, typename Traits >
  basic_message_ostream<Char, Traits>::
  basic_message_ostream(basic_message_ostream &&m) noexcept:
    base_type(std::move(m)),
    m_buffer(std::move(m.m_buffer))
  {
    this->rdbuf(&m_buffer);
    m.rdbuf(&(m.m_buffer));
  }

  template < typename Char, typename Traits >
  basic_message_ostream<Char, Traits> &
  basic_message_ostream<Char, Traits>::
  operator=(basic_message_ostream &&m) noexcept
  {
    m.swap(*this);
    return *this;
  }

  template < typename Char, typename Traits >
  void basic_message_ostream<Char, Traits>::
  swap(basic_message_ostream &m) noexcept
  {
    using std::swap;
    base_type::swap(m);
    swap(m_buffer, m.m_buffer);
  }

}

#endif // NNXX_MESSAGE_OSTREAM_HPP
