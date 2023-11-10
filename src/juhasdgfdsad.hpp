#ifndef _SERVER_HPP
#define _SERVER_HPP
#include <string>
#include <syslog.h>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
class SERVER{
  public:
    SERVER(
    );  ~SERVER();
    static void LISTEN(std
    ::string);};
#endif // _SERVER_HPP