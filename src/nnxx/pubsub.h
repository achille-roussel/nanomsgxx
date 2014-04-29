#ifndef NNXX_PUBSUB_H
#define NNXX_PUBSUB_H

#include <nanomsg/pubsub.h>
#include <nnxx/nn.h>

namespace nnxx {

  class socket;

  enum {
    PUB = NN_PUB,
    SUB = NN_SUB,
  };

  enum {
    SUB_SUBSCRIBE   = NN_SUB_SUBSCRIBE,
    SUB_UNSUBSCRIBE = NN_SUB_UNSUBSCRIBE,
  };

  void subscribe(socket &s, const void *topic, size_t topiclen);

  void subscribe(socket &s, const char *topic);

  template < typename String >
  void subscribe(socket &s, const String &topic)
  { subscribe(s, c_str(topic)); }

}

#endif // NNXX_PUBSUB_H
