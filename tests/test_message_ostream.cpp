#include <nnxx/message_ostream.h>
#include <nnxx/unittest.h>

int main() {
  nnxx::message_ostream s;
  nnxx::message m;

  s << "Hello World! ";
  s << 42;
  m = std::move(s.move_msg());

  nnxx_check(std::strncmp(reinterpret_cast<char *>(m.data()), "Hello World! 42", 15) == 0);
  return nnxx::unittest::result;
}
