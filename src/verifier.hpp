#ifndef _VERIFIER_HPP
#define _VERIFIER_HPP

#include "certVerifier.hpp"

#include <string>

#include <openssl/x509.h>

class Verifier{
  private:
    CertVerifier certV;
    
  public:
    Verifier();
    ~Verifier();
    bool verify_certificate(std::string user);
};

#endif // _VERIFIER_HPP