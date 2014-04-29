#include <nnxx/error.h>
#include <nnxx/message.h>
#include <nnxx/pair.h>
#include <nnxx/socket.h>
#include <nnxx/timeout.h>
#include <nnxx/unittest.h>

int main() {
  nnxx::socket s { nnxx::SP, nnxx::PAIR };

  s.bind("inproc://test");

  // Set a timeout of receive operations peformed in this scope.
  try { nnxx::with_recv_timeout _ { s, std::chrono::milliseconds(10) };
    s.recv();
    nnxx_assert(false);
  }
  catch (const nnxx::timeout_error &) {
  }
  catch (const std::exception &) {
    nnxx_assert(false);
  }

  return nnxx::unittest::result;
}

