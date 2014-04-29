#ifndef NNXX_CHRONO_H
#define NNXX_CHRONO_H

#include <chrono>

namespace nnxx {

  typedef std::chrono::system_clock clock;
  typedef clock::duration           duration;
  typedef clock::time_point         time_point;

  using std::chrono::hours;
  using std::chrono::minutes;
  using std::chrono::seconds;
  using std::chrono::milliseconds;
  using std::chrono::microseconds;
  using std::chrono::nanoseconds;

}

#endif // NNXX_CHRONO_H
