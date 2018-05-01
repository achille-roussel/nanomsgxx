#ifndef NNXX_MESSAGE_ISTREAM_HPP
#define NNXX_MESSAGE_ISTREAM_HPP

#include <utility>

namespace nnxx {

  template < typename Char, typename Traits >
  basic_message_istream<Char, Traits>::
  basic_message_istream() noexcept:
    base_type(nullptr),
    m_buffer()
  { this->rdbuf(&m_buffer); }

  template < typename Char, typename Traits >
  basic_message_istream<Char, Traits>::
  basic_message_istream(message &&msg) noexcept:
    base_type(nullptr),
    m_buffer(std::move(msg))
  { this->rdbuf(&m_buffer); }

  template < typename Char, typename Traits >
  basic_message_istream<Char, Traits>::
  ~basic_message_istream()
  { }

  template < typename Char, typename Traits >
  void basic_message_istream<Char, Traits>::msg(message &&m) noexcept
  { m_buffer.msg(std::move(m)); }

  template < typename Char, typename Traits >
  basic_message_istream<Char, Traits>::
  basic_message_istream(basic_message_istream &&m) noexcept:
    base_type(std::move(m)),
    m_buffer(std::move(m.m_buffer))
  {
    this->rdbuf(&m_buffer);
    m.rdbuf(&(m.m_buffer));
  }

  template < typename Char, typename Traits >
  basic_message_istream<Char, Traits> &
  basic_message_istream<Char, Traits>::
  operator=(basic_message_istream &&m) noexcept
  {
    m.swap(*this);
    return *this;
  }

  template < typename Char, typename Traits >
  void basic_message_istream<Char, Traits>::
  swap(basic_message_istream &m) noexcept
  {
    using std::swap;
    base_type::swap(m);
    swap(m_buffer, m.m_buffer);
  }

}

#endif // NNXX_MESSAGE_ISTREAM_HPP
