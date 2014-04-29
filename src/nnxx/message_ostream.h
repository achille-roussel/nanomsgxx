#ifndef NNXX_MESSAGE_OSTREAM_H
#define NNXX_MESSAGE_OSTREAM_H

#include <ostream>
#include <nnxx/message_streambuf.h>

namespace nnxx {

  template < typename Char, typename Traits = std::char_traits<Char> >
  class basic_message_ostream : public std::basic_ostream<Char, Traits> {
    typedef typename std::basic_ostream<Char, Traits> base_type;
    typedef basic_message_streambuf<Char, Traits>     message_streambuf;
  public:
    typedef typename base_type::char_type   char_type;
    typedef typename base_type::int_type    int_type;
    typedef typename base_type::pos_type    pos_type;
    typedef typename base_type::off_type    off_type;
    typedef typename base_type::traits_type traits_type;

    basic_message_ostream() noexcept;
    basic_message_ostream(basic_message_ostream &&m) noexcept;
    basic_message_ostream(basic_message_ostream const &) = delete;
    basic_message_ostream(message &&msg) noexcept;

    ~basic_message_ostream();

    basic_message_ostream &operator=(basic_message_ostream &&m) noexcept;
    basic_message_ostream &operator=(basic_message_ostream const &&) = delete;

    void swap(basic_message_ostream &m) noexcept; 
    void msg(message &&m) noexcept;

    message msg(int type = 0);
    message move_msg() noexcept;

  private:
    message_streambuf m_buffer;
  };

  template < typename Char, typename Traits >
  void swap(basic_message_ostream<Char, Traits> &m1,
            basic_message_ostream<Char, Traits> &m2) noexcept
  { m1.swap(m2); }

  typedef basic_message_ostream<char> message_ostream;

  extern template class basic_message_ostream<char>;

}

#endif // NNXX_MESSAGE_OSTREAM_H
