#ifndef NNXX_SURVEY_H
#define NNXX_SURVEY_H

#include <nanomsg/survey.h>

namespace nnxx {

  enum {
    SURVEYOR   = NN_SURVEYOR,
    RESPONDENT = NN_RESPONDENT,
  };

  enum {
    SURVEYOR_DEADLINE = NN_SURVEYOR_DEADLINE,
  };

}

#endif // NNXX_SURVEY_H
