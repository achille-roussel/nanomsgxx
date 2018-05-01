#ifndef NNXX_MESSAGE_SREAMBUF_HPP
#define NNXX_MESSAGE_SREAMBUF_HPP

#include <algorithm>

namespace nnxx {

  template < typename Char, typename Traits >
  basic_message_streambuf<Char, Traits>::
  basic_message_streambuf(size_type base_size) noexcept:
    base_type(),
    m_base_size(base_size),
    m_msg()
  { }

  template < typename Char, typename Traits >
  basic_message_streambuf<Char, Traits>::
  basic_message_streambuf(size_type size, int type):
    base_type(),
    m_base_size(size),
    m_msg(size * sizeof(char_type), type)
  { clear(); }

  template < typename Char, typename Traits >
  basic_message_streambuf<Char, Traits>::
  basic_message_streambuf(message &&msg) noexcept:
    base_type(),
    m_base_size(msg.empty() ? 1000 : msg.size()),
    m_msg(std::move(msg))
  { clear(); }

  template < typename Char, typename Traits >
  basic_message_streambuf<Char, Traits>::
  ~basic_message_streambuf()
  { }

  template < typename Char, typename Traits >
  void basic_message_streambuf<Char, Traits>::clear() noexcept
  {
    const auto b = reinterpret_cast<char_type *>(m_msg.data());
    const auto e = reinterpret_cast<char_type *>(m_msg.data()) + m_msg.size();
    this->setg(b, b, e);
    this->setp(b, e);
  }

  template < typename Char, typename Traits >
  void basic_message_streambuf<Char, Traits>::msg(message &&m) noexcept
  {
    m_msg = std::move(m);
    clear();
  }

  template < typename Char, typename Traits >
  message basic_message_streambuf<Char, Traits>::msg(int type)
  { message m(this->pptr() - this->pbase(), type);

    std::copy(reinterpret_cast<const char_type *>(this->pbase()),
         reinterpret_cast<const char_type *>(this->pptr()),
         reinterpret_cast<char_type *>(m.data()));

    return m;}

  template < typename Char, typename Traits >
  message basic_message_streambuf<Char, Traits>::move_msg()
  {
    message m;
    m_msg.resize(this->pptr() - this->pbase());
    m_msg.swap(m);
    clear();
    return m;
  }

  template < typename Char, typename Traits >
  typename
  basic_message_streambuf<Char, Traits>::streamsize
  basic_message_streambuf<Char, Traits>::xsputn(const char_type *s, streamsize n)
  {
    using std::copy;
    streamsize ret = 0;

    while (ret < n) {
      streamsize buflen = static_cast<streamsize>(this->epptr() - this->pptr());

      if (buflen) {
	streamsize len = std::min(buflen, n - ret);
	copy(s, s + len, this->pptr());
	this->pbump(len);
	ret += len;
	s += len;
      }
      if (ret < n)
	overflow(traits_type::eof());
    }
    return ret;
  }

  template < typename Char, typename Traits >
  typename
  basic_message_streambuf<Char, Traits>::int_type
  basic_message_streambuf<Char, Traits>::overflow(int_type c)
  {
    const auto n = m_msg.size();

    if (!m_msg) {
      m_msg = message{ m_base_size * sizeof(char_type) };
    }
    else {
      m_msg.resize(2 * m_msg.size());
    }

    const auto b = reinterpret_cast<char_type *>(m_msg.data());
    const auto e = reinterpret_cast<char_type *>(m_msg.data()) + m_msg.size();
    this->setp(b, e);
    this->pbump(n);

    if (!traits_type::eq_int_type(c, traits_type::eof())) {
      *(this->pptr()) = char_type(c);
      this->pbump(1);
    }

    return ~traits_type::eof();
  }

  template < typename Char, typename Traits >
  basic_message_streambuf<Char, Traits>::
  basic_message_streambuf(basic_message_streambuf &&m) noexcept:
    base_type(std::move(m)),
    m_base_size(m.m_base_size),
    m_msg(std::move(m.m_msg))
  { m.clear(); }

  template < typename Char, typename Traits >
  basic_message_streambuf<Char, Traits> &
  basic_message_streambuf<Char, Traits>::
  operator=(basic_message_streambuf &&m) noexcept
  {
    m.swap(*this);
    return *this;
  }

  template < typename Char, typename Traits >
  void basic_message_streambuf<Char, Traits>::
  swap(basic_message_streambuf &m) noexcept
  {
    using std::swap;
    base_type::swap(m);
    swap(m_base_size, m.m_base_size);
    swap(m_msg, m.m_msg);
  }

}

#endif // NNXX_MESSAGE_SREAMBUF_H
