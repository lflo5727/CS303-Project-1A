#ifndef ERRORHANDLE_H
#define ERRORHANDLE_H
#include <stdexcept>


class errorHandle : public std::invalid_argument {
  public:
    errorHandle(std::string msg) : std::invalid_argument(msg) {}
};

#endif // ERRORHANDLE_H
