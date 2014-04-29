#include <cstring>
#include <utility>
#include <nnxx/message.h>
#include <nnxx/unittest.h>

int main() {
  nnxx::message m1;
  nnxx::message m2 { 1000 };

  nnxx_check(!m1);
  nnxx_check(m2);

  nnxx_check(m1.data() == nullptr);
  nnxx_check(m1.size() == 0);

  nnxx_check(m2.data() != nullptr);
  nnxx_check(m2.size() == 1000);

  m1 = std::move(m2);
  nnxx_check(m1);
  nnxx_check(!m2);

  std::strcpy(reinterpret_cast<char *>(m1.data()), "Hello World!");
  m2 = copy(m1);
  nnxx_check(to_string(m2) == "Hello World!");
  return nnxx::unittest::result;
}
