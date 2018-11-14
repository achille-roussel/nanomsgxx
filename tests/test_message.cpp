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

#include <cstring>
#include <utility>
#include <nnxx/message>
#include <nnxx/testing>

int main() {
  nnxx::message m1;
  const nnxx::message::size_type size_m2 = 12;
  nnxx::message m2 { size_m2 };

  nnxx_check(!m1);
  nnxx_check(m2);

  nnxx_check(m1.data() == nullptr);
  nnxx_check(m1.empty());

  nnxx_check(m2.data() != nullptr);
  nnxx_check(m2.size() == size_m2);

  m1 = std::move(m2);
  nnxx_check(m1);
  nnxx_check(!m2);

  std::string string_to_send = "Hello World!";
  std::copy(string_to_send.begin(), string_to_send.end(), reinterpret_cast<char *>(m1.data()));
  m2 = copy(m1);

  nnxx_check(to_string(m2) == string_to_send);
  return nnxx::unittest::result;
}
