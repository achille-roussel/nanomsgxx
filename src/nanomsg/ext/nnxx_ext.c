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

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/ext/nnxx_ext.h>

static size_t nn_memhash (const char *s, size_t n)
{
  size_t h = 0;
  size_t i;

  for (i = 0; i != n; ++i, ++s) {
    h = (*s) + (h << 6) + (h << 16) - h;
  }
  return h;
}

static int nn_check_raw_socket (int s)
{
  size_t optlen;
  int    optval;

  /*  Making sure the socket domain is AF_SP_RAW. */
  optlen = sizeof(optval);
  optval = 0;
  if (nn_getsockopt (s, NN_SOL_SOCKET, NN_DOMAIN, &optval, &optlen)) {
    return -1;
  }
  if (optval != AF_SP_RAW) {
    errno = ENOTSUP;
    return -1;
  }
  return 0;
}

void nn_msgctl_init (struct nn_msgctl *ctl)
{
  memset (ctl, 0, sizeof(*ctl));
}

void nn_msgctl_term (struct nn_msgctl *ctl)
{
  if (ctl->ctl_base) {
    nn_freemsg (ctl->ctl_base);
  }
}

int nn_msgctl_copy (struct nn_msgctl *to,
                           const struct nn_msgctl *from)
{
  void * control = NULL;

  /*  Copy control base if it was allocated. */
  if (from->ctl_base) {
    control = nn_allocmsg (from->ctl_len, 0);
    if (!control) {
      errno = ENOMEM;
      return -1;
    }
    memmove (control, from->ctl_base, from->ctl_len);
  }

  /*  Copy to destination object. */
  to->ctl_base = control;
  to->ctl_len = from->ctl_len;
  return 0;
}

int nn_msgctl_cmp (const struct nn_msgctl *ctl1,
                          const struct nn_msgctl *ctl2)
{
  int k;
  int n;

  /*  Compare type of control buffers. */
  if (!ctl1->ctl_base && !ctl2->ctl_base) {
    return 0;
  }
  if (!ctl1->ctl_base) {
    return -1;
  }
  if (!ctl2->ctl_base) {
    return 1;
  }

  /*  Compare content of control buffers. */
  n = ctl1->ctl_len < ctl2->ctl_len ? ctl1->ctl_len : ctl2->ctl_len;
  k = memcmp (ctl1->ctl_base, ctl2->ctl_base, n);
  if (k != 0) {
    return k;
  }
  return ctl1->ctl_len - ctl2->ctl_len;
}

size_t nn_msgctl_hash (const struct nn_msgctl *ctl)
{
  return ctl->ctl_base == NULL
    ? 0
    : nn_memhash ((const char *) ctl->ctl_base, ctl->ctl_len);
}

int nn_recvfrom (int s, void *buf, size_t buflen, int flags,
                 struct nn_msgctl *ctl)
{
  struct nn_iovec vec [1];
  struct nn_msghdr msg;
  void * control;
  int n;

  /*  If the caller is not interested in getting the sender's ctless we simply
      delegate to nn_recv. */
  if (!ctl) {
    return nn_recv (s, buf, buflen, flags);
  }

  /*  Making sure the operation is supported. */
  if (nn_check_raw_socket (s)) {
    return -1;
  }

  /*  Receiving a message. */
  nn_msgctl_init (ctl);
  vec [0].iov_base = buf;
  vec [0].iov_len = buflen;
  memset (&msg, 0, sizeof(msg));
  msg.msg_iov = vec;
  msg.msg_iovlen = 1;
  msg.msg_control = &control;
  msg.msg_controllen = NN_MSG;
  n = nn_recvmsg (s, &msg, flags);
  if (n < 0) {
    return -1;
  }

  /*  Set control object. */
  ctl->ctl_base = control;
  ctl->ctl_len = msg.msg_controllen;
  return n;
}

int nn_sendto (int s, const void *buf, size_t buflen, int flags,
               const struct nn_msgctl *ctl)
{
  struct nn_iovec vec [1];
  struct nn_msghdr msg;
  void * control;

  /*  If the caller doesn't specify a receiver ctless we simply delegate to
      nn_send. */
  if (!ctl) {
    return nn_send (s, buf, buflen, flags);
  }

  /*  Make sure the operation is supported. */
  if (nn_check_raw_socket (s)) {
    return -1;
  }

  /*  Sending the message. */
  control = ctl->ctl_base;
  vec [0].iov_base = (void *) buf;
  vec [0].iov_len = buflen;
  memset (&msg, 0, sizeof(msg));
  msg.msg_iov = vec;
  msg.msg_iovlen = 1;
  msg.msg_control = &control;
  msg.msg_controllen = NN_MSG;
  return nn_sendmsg (s, &msg, flags);
}
