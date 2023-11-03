#include "logger.hpp"

Logger::Logger(){}

Logger::~Logger(){}

void Logger::log(std::string text){
    std::string header = "EQUIPO-05-EAEA:";
    syslog(LOG_LOCAL5, header.append(text).c_str());
}