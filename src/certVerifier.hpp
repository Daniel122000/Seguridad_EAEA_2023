#ifndef _CERT_VERIFIER_HPP
#define _CERT_VERIFIER_HPP

#include "signVerifier.hpp"

#include <iostream>
#include <string>

#include <openssl/x509.h>
#include <openssl/pem.h>

class CertVerifier{
  private:
    SignVerifier signV;
    
  public:
    CertVerifier();
    ~CertVerifier();
    X509* verify_user_certificate(const char* cert, bool* succ);
    X509* try_read_crt(const char* path, bool* succ);
    void verify_user_certificate_with_ca(X509* cert_user, bool* success);
};

#endif // _CERT_VERIFIER_HPP