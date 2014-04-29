#include <nnxx/message_istream.h>
#include <nnxx/unittest.h>

int main() {
  nnxx::message m { 1000 };
  std::strcpy(reinterpret_cast<char *>(m.data()), "1 2 3");

  nnxx::message_istream s { std::move(m) };
  int a;
  int b;
  int c;

  s >> a;
  s >> b;
  s >> c;

  nnxx_check(a == 1);
  nnxx_check(b == 2);
  nnxx_check(c == 3);
  return nnxx::unittest::result;
}
