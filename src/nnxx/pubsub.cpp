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
#include <nnxx/pubsub.h>
#include <nnxx/socket.h>

namespace nnxx {

  void subscribe(socket &s, const void *topic, size_t topiclen)
  { s.setopt(SUB, SUB_SUBSCRIBE, topic, topiclen); }

  void subscribe(socket &s, const char *topic)
  { subscribe(s, topic, std::strlen(topic)); }

  void subscribe(socket &s, const std::string &topic)
  { subscribe(s, topic.data(), topic.size()); }

  void subscribe(socket &s)
  { subscribe(s, "", 0); }

  void unsubscribe(socket &s, const void *topic, size_t topiclen)
  { s.setopt(SUB, SUB_UNSUBSCRIBE, topic, topiclen); }

  void unsubscribe(socket &s, const char *topic)
  { unsubscribe(s, topic, std::strlen(topic)); }

  void unsubscribe(socket &s, const std::string &topic)
  { unsubscribe(s, topic.data(), topic.size()); }

  void unsubscribe(socket &s)
  { unsubscribe(s, "", 0); }

}
