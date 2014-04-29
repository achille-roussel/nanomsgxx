#include <nnxx/message.h>
#include <nnxx/reqrep.h>
#include <nnxx/socket.h>
#include <nnxx/unittest.h>

int main() {
  nnxx::socket s1 { nnxx::SP, nnxx::REP };
  nnxx::socket s2 { nnxx::SP, nnxx::REQ };
  nnxx::socket s3 { nnxx::SP, nnxx::REQ };

  s1.bind("inproc://test");
  s2.connect("inproc://test");
  s3.connect("inproc://test");

  nnxx_check(s2.send("Hello World! 1") == 14);
  nnxx_check(s3.send("Hello World! 2") == 14);

  nnxx_check(to_string(s1.recv()) == "Hello World! 1");
  nnxx_check(s1.send("1") == 1);

  nnxx_check(to_string(s1.recv()) == "Hello World! 2");
  nnxx_check(s1.send("2") == 1);

  nnxx_check(to_string(s2.recv()) == "1");
  nnxx_check(to_string(s3.recv()) == "2");
  return nnxx::unittest::result;
}
