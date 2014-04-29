#include <nnxx/socket.h>
#include <nnxx/unittest.h>

int main() {
  nnxx::socket s;
  nnxx_check(!s);
  nnxx_check(s.fd() == -1);
  return nnxx::unittest::result;
}
