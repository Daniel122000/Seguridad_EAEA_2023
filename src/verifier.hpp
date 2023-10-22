#ifndef _VERIFIER_HPP
#define _VERIFIER_HPP

#include "certVerifier.hpp"
#include "signVerifier.hpp"
#include "coder.hpp"

#include <string>

#include <openssl/x509.h>

class Verifier{
  private:
    CertVerifier certV;
    SignVerifier signV;
    Coder coder;
    bool success = true;
    std::string _user;
    std::string _signature64;
    std::string _plain;
    X509* user_cert;

  public:
    Verifier();
    Verifier(std::string user, std::string signature64, std::string plain);
    ~Verifier();
    bool verify_certificate();
    bool verify_sign();
};

#endif // _VERIFIER_HPP