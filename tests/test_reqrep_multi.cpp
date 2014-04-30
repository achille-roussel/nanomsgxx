#include <nnxx/message.h>
#include <nnxx/reqrep.h>
#include <nnxx/socket.h>
#include <nnxx/unittest.h>

int main() {
  nnxx::socket s1 { nnxx::SP_RAW, nnxx::REP };
  nnxx::socket s2 { nnxx::SP, nnxx::REQ };
  nnxx::socket s3 { nnxx::SP, nnxx::REQ };
  nnxx::socket_address a1;
  nnxx::socket_address a2;

  s1.bind("inproc://test");
  s2.connect("inproc://test");
  s3.connect("inproc://test");

  nnxx_check(s2.send("Hello World! 1") == 14);
  nnxx_check(s3.send("Hello World! 2") == 14);

  auto m1 = s1.recv(0, a1);
  auto m2 = s1.recv(0, a2);

  nnxx_check(s1.send(std::move(m2), 0, std::move(a2)) == 14);
  nnxx_check(s1.send(std::move(m1), 0, std::move(a1)) == 14);

  nnxx_check(to_string(s2.recv()) == "Hello World! 1");
  nnxx_check(to_string(s3.recv()) == "Hello World! 2");
  return nnxx::unittest::result;
}
