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

#include <string.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/ext/nnxx_ext.h>
#include <nnxx/testing>

int main() {
  struct nn_msgctl ctl1;
  struct nn_msgctl ctl2;
  int s1 = nn_socket (AF_SP_RAW, NN_REP);
  int s2 = nn_socket (AF_SP, NN_REQ);
  int s3 = nn_socket (AF_SP, NN_REQ);
  void *buf1 = nullptr;
  void *buf2 = nullptr;

  nnxx_assert (s1 >= 0);
  nnxx_assert (s2 >= 0);

  /*  Connecting sockets. */
  nnxx_assert (nn_bind (s1, "inproc://test") >= 0);
  nnxx_assert (nn_connect (s2, "inproc://test") >= 0);
  nnxx_assert (nn_connect (s3, "inproc://test") >= 0);

  /*  Sending requests. */
  nnxx_assert (nn_send (s2, "Hello World! (1)", 16, 0) == 16);
  nnxx_assert (nn_send (s3, "Hello World! (2)", 16, 0) == 16);

  /*  Recieving requests. */
  nnxx_assert (nn_recvfrom (s1, &buf1, NN_MSG, 0, &ctl1) == 16);
  nnxx_assert (nn_recvfrom (s1, &buf2, NN_MSG, 0, &ctl2) == 16);

  /*  Making sure we have the correct data. */
  nnxx_assert (memcmp (buf1, "Hello World! (1)", 16) == 0);
  nnxx_assert (memcmp (buf2, "Hello World! (2)", 16) == 0);

  /*  Sending responses back in reverse order. */
  nnxx_assert (nn_sendto (s1, &buf2, NN_MSG, 0, &ctl2) == 16);
  nnxx_assert (nn_sendto (s1, &buf1, NN_MSG, 0, &ctl1) == 16);

  /*  Recieving responses. */
  nnxx_assert (nn_recv (s2, &buf1, NN_MSG, 0) == 16);
  nnxx_assert (nn_recv (s3, &buf2, NN_MSG, 0) == 16);

  /*  Making sure the clients got the right responses. */
  nnxx_assert (memcmp (buf1, "Hello World! (1)", 16) == 0);
  nnxx_assert (memcmp (buf2, "Hello World! (2)", 16) == 0);

  /*  Releasing resources. */
  nn_freemsg (buf2);
  nn_freemsg (buf1);
  nn_close (s2);
  nn_close (s1);
  return nnxx::unittest::result;
}
