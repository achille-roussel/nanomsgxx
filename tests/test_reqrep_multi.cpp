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
  nnxx::socket s1 { nnxx::SP_RAW, nnxx::REP };
  nnxx::socket s2 { nnxx::SP, nnxx::REQ };
  nnxx::socket s3 { nnxx::SP, nnxx::REQ };
  nnxx::message_control c1;
  nnxx::message_control c2;

  s1.bind("inproc://test");
  s2.connect("inproc://test");
  s3.connect("inproc://test");

  nnxx_check(s2.send("Hello World! 1") == 14);
  nnxx_check(s3.send("Hello World! 2") == 14);

  auto m1 = s1.recv(0, c1);
  auto m2 = s1.recv(0, c2);

  nnxx_check(s1.send(std::move(m2), 0, std::move(c2)) == 14);
  nnxx_check(s1.send(std::move(m1), 0, std::move(c1)) == 14);

  nnxx_check(to_string(s2.recv()) == "Hello World! 1");
  nnxx_check(to_string(s3.recv()) == "Hello World! 2");
  return nnxx::unittest::result;
}
