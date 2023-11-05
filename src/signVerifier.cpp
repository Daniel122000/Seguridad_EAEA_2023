#include "signVerifier.hpp"

SignVerifier::SignVerifier(){}

SignVerifier::~SignVerifier(){}

X509_REQ* SignVerifier::try_read_csr(X509* cert, bool* success){ // Uso el csr del CA?
  // Obtener el .csr del certificado
  X509_REQ *csr = X509_to_X509_REQ(cert, NULL, EVP_get_digestbyname("sha256"));
  
  if (csr == NULL) {
    *success = false;
    return NULL;
  }

  return csr;
}

EVP_PKEY* SignVerifier::try_read_pubkey(X509_REQ* csr, char** out){
  EVP_PKEY* pubkey = X509_REQ_get_pubkey(csr);

  BIO* bio = BIO_new(BIO_s_mem());
  PEM_write_bio_PUBKEY(bio, pubkey);

  BIO_get_mem_data(bio, out);
  return pubkey;
}

void SignVerifier::extract_user_public_key(X509* cert_user, bool* success, char** pubkey_char_user){
  // Extraer .csr del usuario
  X509_REQ* csr_user = try_read_csr(cert_user, success);
  if (!success) {
    X509_REQ_free(csr_user);
    Logger::log("No se pudo cargar el .csr del certificado del usuario.");
    return;
  }
  // Extraer llave publica de .csr del usuario
  try_read_pubkey(csr_user, pubkey_char_user);
  if(!pubkey_char_user){
    X509_REQ_free(csr_user);
    Logger::log("Error al leer llave publica del usuario.");
    return;
  }
  X509_REQ_free(csr_user);
  X509_free(cert_user);
  return;
}

EVP_PKEY* SignVerifier::load_public_key_from_string(const char* public_key_pem){
    BIO* bio = BIO_new_mem_buf(public_key_pem, -1);
    if (bio == NULL) {
        Logger::log("Error en el procesamiento del certificado.");
        return NULL;
    }

    EVP_PKEY* public_key = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
    if (public_key == NULL) {
        Logger::log("Error en el procesamiento del certificado.");
        BIO_free(bio);
        return NULL;
    }

    BIO_free(bio);
    return public_key;
}

RSA* SignVerifier::create_public_rsa(char* key){
  RSA *rsa = NULL;
  BIO *keybio;
  keybio = BIO_new_mem_buf((const void*)key, -1);
  if (keybio==NULL) {
      return 0;
  }
  rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa,NULL, NULL);
  return rsa;
}

bool SignVerifier::rsa_verify_signature( RSA* rsa,
                         unsigned char* MsgHash,
                         size_t MsgHashLen,
                         const char* Msg,
                         size_t MsgLen,
                         bool* Authentic){
  *Authentic = false;
  EVP_PKEY* pubKey  = EVP_PKEY_new();
  EVP_PKEY_assign_RSA(pubKey, rsa);
  EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();

  if (EVP_DigestVerifyInit(m_RSAVerifyCtx,NULL, EVP_sha256(),NULL,pubKey)<=0) {
    return false;
  }
  if (EVP_DigestVerifyUpdate(m_RSAVerifyCtx, Msg, MsgLen) <= 0) {
    return false;
  }
  int AuthStatus = EVP_DigestVerifyFinal(m_RSAVerifyCtx, MsgHash, MsgHashLen);
  if (AuthStatus==1) {
    *Authentic = true;
    EVP_MD_CTX_free(m_RSAVerifyCtx);
    return true;
  } else if(AuthStatus==0){
    *Authentic = false;
    EVP_MD_CTX_free(m_RSAVerifyCtx);
    return true;
  } else{
    *Authentic = false;
    EVP_MD_CTX_free(m_RSAVerifyCtx);
    return false;
  }
}

bool SignVerifier::verify_signature(char* publicKey, std::string plainText, char* signatureBase64){
  RSA* publicRSA = create_public_rsa(publicKey);
  unsigned char* encMessage;
  size_t encMessageLength;
  bool authentic;
  coder.base64_decode(signatureBase64, &encMessage, &encMessageLength);
  bool result = rsa_verify_signature(publicRSA, encMessage, encMessageLength, plainText.c_str(), plainText.length(), &authentic);
  return result & authentic;
}