#include <nnxx/message.h>
#include <nnxx/pipeline.h>
#include <nnxx/socket.h>
#include <nnxx/unittest.h>

int main() {
  nnxx::socket s1 { nnxx::SP, nnxx::PUSH };
  nnxx::socket s2 { nnxx::SP, nnxx::PULL };
  nnxx::socket s3 { nnxx::SP, nnxx::PULL };

  s1.bind("inproc://test");
  s2.connect("inproc://test");
  s3.connect("inproc://test");

  nnxx_check(s1.send("Hello World! 1") == 14);
  nnxx_check(s1.send("Hello World! 2") == 14);

  nnxx_check(to_string(s2.recv()) == "Hello World! 1");
  nnxx_check(to_string(s3.recv()) == "Hello World! 2");
  return nnxx::unittest::result;
}
