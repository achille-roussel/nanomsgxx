#include <cstring>
#include <nnxx/pubsub.h>
#include <nnxx/socket.h>

namespace nnxx {

  void subscribe(socket &s, const void *topic, size_t topiclen)
  { s.setopt(SUB, SUB_SUBSCRIBE, topic, topiclen); }

  void subscribe(socket &s, const char *topic)
  { subscribe(s, topic, std::strlen(topic)); }

  void unsubscribe(socket &s, const void *topic, size_t topiclen)
  { s.setopt(SUB, SUB_UNSUBSCRIBE, topic, topiclen); }

  void unsubscribe(socket &s, const char *topic)
  { unsubscribe(s, topic, std::strlen(topic)); }

}
