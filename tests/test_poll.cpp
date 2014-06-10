/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Achille Roussel <achille.roussel@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <nnxx/message>
#include <nnxx/socket>
#include <nnxx/testing>

int main() {
  nnxx::socket s1 { nnxx::SP, nnxx::PAIR };
  nnxx::socket s2 { nnxx::SP, nnxx::PAIR };
  nnxx::poll_vector events;
  nnxx::recv_ready_sequence r1;
  nnxx::send_ready_sequence r2;

  s1.bind("inproc://test");
  s2.connect("inproc://test");

  try {
    // Poll for sockets that are ready for output operations, both s1 and s2
    // should be set.
    events = nnxx::poll({{ s1, nnxx::EV_POLLOUT }, { s2, nnxx::EV_POLLOUT }});
    r1 = nnxx::recv_ready(events);
    r2 = nnxx::send_ready(events);
    nnxx_assert(std::distance(r1.begin(), r1.end()) == 0);
    nnxx_assert(std::distance(r2.begin(), r2.end()) == 2);

    // Send a message on s1 and poll s2 for input operations, s1 should be set
    // and there should be no socket ready for output operations.
    s1.send("Hello World!");
    events = nnxx::poll({{ s2, nnxx::EV_POLLIN }}, std::chrono::seconds(0));

    for (auto &e : nnxx::recv_ready(events)) {
      nnxx_assert(e == s2);
      nnxx_assert(e.is(s2));
      nnxx_assert(e.recv_ready());
      nnxx_check(to_string(s2.recv()) == "Hello World!");
    }

    for (auto &e : nnxx::send_ready(events)) {
      nnxx_assert(false); // there should be no send-ready sockets
      (void)e;
    }

    // Poll for input operations on s2 which has already been flushed, so we
    // should get a timeout there.
    try {
      nnxx::poll({{ s2, nnxx::EV_POLLIN }}, std::chrono::milliseconds(10));
      nnxx_assert(false);
    }
    catch (const nnxx::timeout_error &) {
    }
  }

  // None of these conditions should happen.
  catch (const nnxx::signal_error &) {
    nnxx_assert(false);
  }
  catch (const nnxx::timeout_error &) {
    nnxx_assert(false);
  }
  catch (const std::exception &) {
    nnxx_assert(false);
  }

  return nnxx::unittest::result;
}
