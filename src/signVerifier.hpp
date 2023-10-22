#ifndef _SIGN_VERIFIER_HPP
#define _SIGN_VERIFIER_HPP

#include "coder.hpp"

#include <openssl/x509.h>
#include <openssl/pem.h>
#include <iostream>

class SignVerifier{
  private:
    Coder coder;
    
  public:
    SignVerifier();
    ~SignVerifier();
    X509_REQ* try_read_csr(X509* cert, bool* success);
    EVP_PKEY* try_read_pubkey(X509_REQ* csr, char** out);
    void extract_user_public_key(X509* cert_user, bool* success, char** pubkey_char_user);
    EVP_PKEY* load_public_key_from_string(const char* public_key_pem);
    bool rsa_verify_signature( RSA* rsa, unsigned char* MsgHash, size_t MsgHashLen,
                         const char* Msg, size_t MsgLen, bool* Authentic);
    RSA* create_public_rsa(char* key);
    bool verify_signature(char* publicKey, std::string plainText, char* signatureBase64);
};

#endif // _SIGN_VERIFIER_HPP