#ifndef NNXX_MESSAGE_ISTREAM_H
#define NNXX_MESSAGE_ISTREAM_H

#include <istream>
#include <nnxx/message_streambuf.h>

namespace nnxx {

  template < typename Char, typename Traits = std::char_traits<Char> >
  class basic_message_istream : public std::basic_istream<Char, Traits> {
    typedef typename std::basic_istream<Char, Traits> base_type;
    typedef basic_message_streambuf<Char, Traits>     message_streambuf;
  public:
    typedef typename base_type::char_type   char_type;
    typedef typename base_type::int_type    int_type;
    typedef typename base_type::pos_type    pos_type;
    typedef typename base_type::off_type    off_type;
    typedef typename base_type::traits_type traits_type;

    basic_message_istream() noexcept;
    basic_message_istream(basic_message_istream &&m) noexcept;
    basic_message_istream(basic_message_istream const &) = delete;
    basic_message_istream(message &&msg) noexcept;

    ~basic_message_istream();

    basic_message_istream &operator=(basic_message_istream &&m) noexcept;
    basic_message_istream &operator=(basic_message_istream const &&) = delete;

    void swap(basic_message_istream &m) noexcept; 
    void msg(message &&m) noexcept;

  private:
    message_streambuf m_buffer;
  };

  template < typename Char, typename Traits >
  void swap(basic_message_istream<Char, Traits> &m1,
            basic_message_istream<Char, Traits> &m2) noexcept
  { m1.swap(m2); }

  typedef basic_message_istream<char> message_istream;

  extern template class basic_message_istream<char>;

}

#endif // NNXX_MESSAGE_ISTREAM_H
