#ifndef _LOGGER_HPP
#define _LOGGER_HPP

#include <string>
#include <syslog.h>

class Logger{
  public:
    Logger();
    ~Logger();
    static void log(std::string text);
};
#endif // _LOGGER_HPP