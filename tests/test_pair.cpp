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
#include <vector>
#include <nnxx/message>
#include <nnxx/socket>
#include <nnxx/testing>

int main() {
  const std::vector<std::string> messages { "Hello World!" };

  nnxx::socket s1 { nnxx::SP, nnxx::PAIR };
  nnxx::socket s2 { nnxx::SP, nnxx::PAIR };
  s1.bind("inproc://test");
  s2.connect("inproc://test");

  std::copy(messages.begin(), messages.end(), std::back_inserter(s1));

  for (const nnxx::message &msg : s2) {
    nnxx_check(to_string(msg) == messages[0]);
    break;
  }

  return nnxx::unittest::result;
}
