#include <iostream>
#include <system_error>
#include <nnxx/message.h>
#include <nnxx/pair.h>
#include <nnxx/socket.h>

int main() {
  try {
    nnxx::socket s1 { nnxx::SP, nnxx::PAIR };
    nnxx::socket s2 { nnxx::SP, nnxx::PAIR };
    const char *addr = "inproc://example";

    s1.bind(addr);
    s2.connect(addr);

    s1.send("Hello World!");

    nnxx::message msg = s2.recv();
    std::cout << msg << std::endl;
    return 0;
  }
  catch (const std::system_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
