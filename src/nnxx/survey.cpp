#include <nnxx/socket.h>
#include <nnxx/survey.h>

namespace nnxx {

  milliseconds get_surveyor_deadline(const socket &s)
  { return milliseconds(getsockopt<int>(s, SURVEYOR, SURVEYOR_DEADLINE)); }

  void set_surveyor_deadline(socket &s, milliseconds t)
  { setsockopt(s, SURVEYOR, SURVEYOR_DEADLINE, static_cast<int>(t.count())); }

}

