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

#include <algorithm>
#include <string>
#include <thread>
#include <vector>
#include <nnxx/message>
#include <nnxx/socket>
#include <nnxx/testing>

static std::vector<std::string> messages = {
  "Hello", "World!", "How", "are", "you?",
};

int main() {
  std::thread t1 { []() {
      nnxx::socket s { nnxx::SP, nnxx::PAIR };
      s.bind("inproc://test");
      std::copy(messages.begin(), messages.end(), std::back_inserter(s));
    } };

  std::thread t2 { []() {
      nnxx::socket s { nnxx::SP, nnxx::PAIR };
      s.connect("inproc://test");

      int i = 0;

      for (const nnxx::message &msg : s) {
        const auto str = to_string(msg);
        nnxx_assert(str == messages[i++]);

        if (str == (*messages.rbegin())) {
          break;
        }
      }
    } };

  t1.join();
  t2.join();
  return nnxx::unittest::result;
}
