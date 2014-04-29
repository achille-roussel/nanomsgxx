#include <nnxx/message.h>
#include <nnxx/survey.h>
#include <nnxx/socket.h>
#include <nnxx/unittest.h>

int main() {
  nnxx::socket s1 { nnxx::SP, nnxx::SURVEYOR };
  nnxx::socket s2 { nnxx::SP, nnxx::RESPONDENT };
  nnxx::socket s3 { nnxx::SP, nnxx::RESPONDENT };

  s1.bind("inproc://test");
  s2.connect("inproc://test");
  s3.connect("inproc://test");

  nnxx_check(s1.send("Hello World!") == 12);

  nnxx_check(to_string(s2.recv()) == "Hello World!");
  nnxx_check(to_string(s3.recv()) == "Hello World!");
  return nnxx::unittest::result;
}
