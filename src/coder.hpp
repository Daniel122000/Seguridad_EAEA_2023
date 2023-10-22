#ifndef _CODER_HPP
#define _CODER_HPP

#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/pem.h>
#include <openssl/bio.h>

class Coder{
  public:
    Coder();
    ~Coder();
    size_t calc_decode_length(const char* b64input);
    void base64_decode(const char* b64message, unsigned char** buffer, size_t* length);
    std::string sha256(std::string text);

};

#endif // _CODER_HPP