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

  NNXX_EXPORT void subscribe(socket &s, const void *topic, size_t topiclen);

  NNXX_EXPORT void subscribe(socket &s, const char *topic = "");

  template < typename String >
  void subscribe(socket &s, const String &topic)
  { subscribe(s, c_str(topic)); }

  NNXX_EXPORT void unsubscribe(socket &s, const void *topic, size_t topiclen);

  NNXX_EXPORT void unsubscribe(socket &s, const char *topic = "");

  template < typename String >
  void unsubscribe(socket &s, const String &topic)
  { unsubscribe(s, c_str(topic)); }

}

#endif // NNXX_PUBSUB_H
