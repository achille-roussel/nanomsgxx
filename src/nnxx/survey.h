#ifndef NNXX_SURVEY_H
#define NNXX_SURVEY_H

#include <nanomsg/survey.h>
#include <nnxx/chrono.h>

namespace nnxx {

  class socket;

  enum {
    SURVEYOR   = NN_SURVEYOR,
    RESPONDENT = NN_RESPONDENT,
  };

  enum {
    SURVEYOR_DEADLINE = NN_SURVEYOR_DEADLINE,
  };

  milliseconds get_surveyor_deadline(const socket &s);

  template < typename Duration >
  Duration get_surveyor_deadline(const socket &s)
  { return std::chrono::duration_cast<Duration>(get_surveyor_deadline(s)); }

  void set_surveyor_deadline(socket &s, milliseconds t);

  template < typename Rep, typename Period >
  void set_surveyor_deadline(socket &s, const std::chrono::duration<Rep, Period> &t)
  { set_deadline(s, std::chrono::duration_cast<milliseconds>(t)); }

}

#endif // NNXX_SURVEY_H
