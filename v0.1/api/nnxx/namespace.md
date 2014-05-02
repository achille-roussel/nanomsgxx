---
layout: v0.1/cpppage
title: nnxx (namespace)
path_prefix: ../../
---

The **nnxx** namespace contains all nanomsgxx symbols.

#### Constants

```c++
#include <nnxx/nn.h>
```

```c++
enum {
  SP     = AF_SP,
  SP_RAW = AF_SP_RAW,
};

enum {
  NS_NAMESPACE        = NN_NS_NAMESPACE,
  NS_VERSION          = NN_NS_VERSION,
  NS_DOMAIN           = NN_NS_DOMAIN,
  NS_TRANSPORT        = NN_NS_TRANSPORT,
  NS_PROTOCOL         = NN_NS_PROTOCOL,
  NS_OPTION_LEVEL     = NN_NS_OPTION_LEVEL,
  NS_SOCKET_OPTION    = NN_NS_SOCKET_OPTION,
  NS_TRANSPORT_OPTION = NN_NS_TRANSPORT_OPTION,
  NS_OPTION_TYPE      = NN_NS_OPTION_TYPE,
  NS_FLAG             = NN_NS_FLAG,
  NS_ERROR            = NN_NS_ERROR,
  NS_LIMIT            = NN_NS_LIMIT,
};

enum {
  TYPE_NONE = NN_TYPE_NONE,
  TYPE_INT  = NN_TYPE_INT,
  TYPE_STR  = NN_TYPE_STR,
};

enum {
  UNIT_NONE         = NN_UNIT_NONE,
  UNIT_BYTES        = NN_UNIT_BYTES,
  UNIT_MILLISECONDS = NN_UNIT_MILLISECONDS,
  UNIT_PRIORITY     = NN_UNIT_PRIORITY,
  UNIT_BOOLEAN      = NN_UNIT_BOOLEAN,
};

enum {
  EV_POLLIN  = NN_POLLIN,
  EV_POLLOUT = NN_POLLOUT,
};

enum {
  DONTWAIT         = NN_DONTWAIT,
  NO_SIGNAL_ERROR  = 1 << 14,
  NO_TIMEOUT_ERROR = 1 << 15,
};
```