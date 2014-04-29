#ifndef NNXX_MESSAGE_SREAMBUF_H
#define NNXX_MESSAGE_SREAMBUF_H

#include <streambuf>
#include <nnxx/message.h>

namespace nnxx {

  template < typename Char, typename Traits = std::char_traits<Char> >
  class basic_message_streambuf : public std::basic_streambuf<Char, Traits> {
    typedef typename std::basic_streambuf<Char, Traits> base_type;
    typedef typename std::streamsize                    streamsize;
  public:
    typedef typename message::size_type     size_type;
    typedef typename base_type::char_type   char_type;
    typedef typename base_type::int_type    int_type;
    typedef typename base_type::pos_type    pos_type;
    typedef typename base_type::off_type    off_type;
    typedef typename base_type::traits_type traits_type;

    basic_message_streambuf() noexcept;
    basic_message_streambuf(basic_message_streambuf &&m) noexcept;
    basic_message_streambuf(basic_message_streambuf const &) = delete;
    basic_message_streambuf(size_type size, int type);
    basic_message_streambuf(message &&msg) noexcept;

    ~basic_message_streambuf();

    basic_message_streambuf &operator=(basic_message_streambuf &&m) noexcept;
    basic_message_streambuf &operator=(basic_message_streambuf const &) = delete;

    void swap(basic_message_streambuf &m) noexcept;
    void msg(message &&m) noexcept;
    void clear() noexcept;

    message msg(int type = 0);
    message move_msg() noexcept;

  protected:
    streamsize xsputn(const char_type *, streamsize);
    int_type overflow(int_type);

  private:
    message m_msg;
  };

  template < typename Char, typename Traits >
  void swap(basic_message_streambuf<Char, Traits> &m1,
            basic_message_streambuf<Char, Traits> &m2) noexcept
  { m1.swap(m2); }

  typedef basic_message_streambuf<char> message_streambuf;

  extern template class basic_message_streambuf<char>;

}

#endif // NNXX_MESSAGE_SREAMBUF_H
