#include "juhasdgfdsad.hpp"

SERVER::SERVER(){} 
SERVER::~SERVER(){} 
void SERVER::LISTEN
(std::string IPCLIENT){ 
    openlog("EQUIPO-05-EAEA", LOG_PID | LOG_NDELAY, LOG_LOCAL5);
    syslog(LOG_INFO, "%s",IPCLIENT.c_str())
    ;closelog();
}