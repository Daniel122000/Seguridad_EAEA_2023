#ifndef _DDDASDSAS
#define DDDASDSAS
#include <cstring>
#include <string>
#include <iostream>
#include <syslog.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "juhasdgfdsad.hpp"

class SIGNVERIFIER{
  public:
    SIGNVERIFIER();~SIGNVERIFIER
    ();bool VERIFICERTSIGN
    (int certNumber, char 
    const *certBase64[]);bool 
    VERIFYCERTWITHCA(std::string , std::string* ,
                                std::string*
                                , std::string* 
                                x, std::string*);};
#endif