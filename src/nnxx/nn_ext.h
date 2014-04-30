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

#ifndef NNXX_NN_EXT_H
#define NNXX_NN_EXT_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <nanomsg/nn.h>

struct nn_sockaddr_ctrl {
  int16_t sa_protocol;
  void *  sa_control;
  size_t  sa_controllen;
};

extern void nn_sockaddr_ctrl_init (struct nn_sockaddr_ctrl *addr);

extern void nn_sockaddr_ctrl_term (struct nn_sockaddr_ctrl *addr);

extern int nn_sockaddr_ctrl_copy (struct nn_sockaddr_ctrl *to,
                                  const struct nn_sockaddr_ctrl *from);

extern int nn_sockaddr_ctrl_cmp (const struct nn_sockaddr_ctrl *addr1,
                                 const struct nn_sockaddr_ctrl *addr2);

extern size_t nn_sockaddr_ctrl_hash (const struct nn_sockaddr_ctrl *addr);

extern int nn_recvfrom (int s, void *buf, size_t buflen, int flags,
                        struct nn_sockaddr_ctrl *addr);

extern int nn_sendto (int s, const void *buf, size_t buflen, int flags,
                      const struct nn_sockaddr_ctrl *addr);

#ifdef __cplusplus
}
#endif
#endif /* NNXX_NN_EXT_H */

