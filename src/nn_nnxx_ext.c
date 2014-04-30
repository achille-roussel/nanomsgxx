#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <nanomsg/reqrep.h>
#include <nn_nnxx_ext.h>

static int nn_check_socket_domain_and_protocol (int s, int *d, int *p)
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
  *d = optval;

  /*  Making sure the socket protocol is NN_REQ or NN_REP. */
  optlen = sizeof(optval);
  optval = 0;
  if (nn_getsockopt (s, NN_SOL_SOCKET, NN_PROTOCOL, &optval, &optlen)) {
    return -1;
  }
  if ((optval != NN_REP) && (optval != NN_REQ)) {
    errno = ENOTSUP;
    return -1;
  }
  *p = optval;

  /*  Everything is fine. */
  return 0;
}

void nn_sockaddr_ctrl_init (struct nn_sockaddr_ctrl *addr)
{
  memset (addr, 0, sizeof(*addr));
}

void nn_sockaddr_ctrl_term (struct nn_sockaddr_ctrl *addr)
{
  if (addr->sa_control) {
    nn_freemsg (addr->sa_control);
    addr->sa_control = NULL;
  }
}

int nn_sockaddr_ctrl_copy (struct nn_sockaddr_ctrl *to,
                           const struct nn_sockaddr_ctrl *from)
{
  void * control = NULL;

  if (from->sa_control) {
    control = malloc (from->sa_controllen);
    if (!control) {
      errno = ENOMEM;
      return -1;
    }
    memmove (control, from->sa_control, from->sa_controllen);
  }
  to->sa_protocol = from->sa_protocol;
  to->sa_control = control;
  to->sa_controllen = from->sa_controllen;
  return 0;
}

int nn_sockaddr_ctrl_cmp (const struct nn_sockaddr_ctrl *addr1,
                          const struct nn_sockaddr_ctrl *addr2)
{
  int k;
  int n;

  /*  Compare protocols. */
  if (addr1->sa_protocol != addr2->sa_protocol) {
    return addr1->sa_protocol - addr2->sa_protocol;
  }

  /*  Compare type of control buffers. */
  if (!addr1->sa_control && !addr2->sa_control) {
    return 0;
  }
  if (!addr1->sa_control) {
    return -1;
  }
  if (!addr2->sa_control) {
    return 1;
  }

  /*  Compare content of control buffers. */
  n = addr1->sa_controllen < addr2->sa_controllen
    ? addr1->sa_controllen
    : addr2->sa_controllen;
  k = memcmp (addr1->sa_control, addr2->sa_control, n);
  if (k != 0) {
    return k;
  }
  return addr1->sa_controllen - addr2->sa_controllen;
}

int nn_recvfrom (int s, void *buf, size_t buflen, int flags,
                 struct nn_sockaddr_ctrl *addr)
{
  struct nn_iovec vec [1];
  struct nn_msghdr msg;
  void * control;
  int domain;
  int protocol;
  int n;

  /*  If the caller is not interested in getting the sender's address we simply
      delegate to nn_recv. */
  if (!addr) {
    return nn_recv (s, buf, buflen, flags);
  }

  /*  Making sure the operation is supported and the arguments are valid. */
  if (nn_check_socket_domain_and_protocol (s, &domain, &protocol)) {
    return -1;
  }

  /*  Recieving a message. */
  nn_sockaddr_ctrl_init (addr);
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

  /*  Set the address object. */
  addr->sa_protocol = protocol;
  addr->sa_control = control;
  addr->sa_controllen = msg.msg_controllen;
  return n;
}

int nn_sendto (int s, const void *buf, size_t buflen, int flags,
               const struct nn_sockaddr_ctrl *addr)
{
  struct nn_iovec vec [1];
  struct nn_msghdr msg;
  void * control;
  int domain;
  int protocol;

  /*  If the caller doesn't specify a reciever address we simply delegate to
      nn_send. */
  if (!addr) {
    return nn_send (s, buf, buflen, flags);
  }

  /*  Make sure the operation is supported and the arguments are valid. */
  if (nn_check_socket_domain_and_protocol (s, &domain, &protocol)) {
    return -1;
  }
  if (addr->sa_protocol != protocol) {
    errno = EINVAL;
    return -1;
  }

  /*  Sending the message. */
  control = addr->sa_control;
  vec [0].iov_base = (void *) buf;
  vec [0].iov_len = buflen;
  memset (&msg, 0, sizeof(msg));
  msg.msg_iov = vec;
  msg.msg_iovlen = 1;
  msg.msg_control = &control;
  msg.msg_controllen = NN_MSG;
  return nn_sendmsg (s, &msg, flags);
}
