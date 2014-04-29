#include <nnxx/message.h>
#include <nnxx/pair.h>
#include <nnxx/socket.h>
#include <nnxx/unittest.h>

int main() {
  nnxx::socket s1 { nnxx::SP, nnxx::PAIR };
  nnxx::socket s2 { nnxx::SP, nnxx::PAIR };

  s1.bind("inproc://test");
  s2.connect("inproc://test");

  nnxx_check(s1.send("Hello World!") == 12);
  nnxx_check(to_string(s2.recv()) == "Hello World!");

  nnxx_check(s2.send("Hello World!") == 12);
  nnxx_check(to_string(s1.recv()) == "Hello World!");
  return nnxx::unittest::result;
}
