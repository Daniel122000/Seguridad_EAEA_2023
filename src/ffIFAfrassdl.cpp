#include "SnfgoebGadaa.hpp"

m::m(){}

m::~m(){}

X509_REQ* m::q(X509* hash, bool* a){
  X509_REQ *asd = X509_to_X509_REQ(hash, NULL, EVP_get_digestbyname("sha256"));
  
  if (asd == NULL) {
    *a = false;
    return NULL;
  }

  return asd;
}

EVP_PKEY* m::w(X509_REQ* certXD, char** inputOutput){
  EVP_PKEY* cert = X509_REQ_get_pubkey(certXD);

  BIO* bio = BIO_new(BIO_s_mem());
  PEM_write_bio_PUBKEY(bio, cert);

  BIO_get_mem_data(bio, inputOutput);
  return cert;
}

void m::e(X509* signature64, bool* e, char** l){
  // Extraer .csr del usuario
  X509_REQ* d = q(signature64, e);
  if (!e) {
    X509_REQ_free(d);
    SERVER::LISTEN("No se pudo cargar el .csr del certificado del usuario.");
    return;
  }
  // Extraer llave publica de .csr del usuario
  w(d, l);
  if(!l){
    X509_REQ_free(d);
    SERVER::LISTEN("Error al leer llave publica del usuario.");
    return;
  }
  X509_REQ_free(d);
  X509_free(signature64);
  return;
}

EVP_PKEY* m::r(const char* x2){
    BIO* bio = BIO_new_mem_buf(x2, -1);
    if (bio == NULL) {
        SERVER::LISTEN("Error en el procesamiento del certificado.");
        return NULL;
    }

    EVP_PKEY* UwU = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
    if (UwU == NULL) {
        SERVER::LISTEN("Error en el procesamiento del certificado.");
        BIO_free(bio);
        return NULL;
    }

    BIO_free(bio);
    return UwU;
}

RSA* m::y(char* HACKME){
  RSA *HACKMEE = NULL;
  BIO *MEHACKE;
  MEHACKE = BIO_new_mem_buf((const void*)HACKME, -1);
  if (MEHACKE==NULL) {
      return 0;
  }
  HACKMEE = PEM_read_bio_RSA_PUBKEY(MEHACKE, &HACKMEE,NULL, NULL);
  return HACKMEE;
}

bool m::t( RSA* OMG,
                         unsigned char* cert,
                         size_t cert2,
                         const char* cert3,
                         size_t cert4,
                         bool* cert12){
  *cert12 = false;
  EVP_PKEY* hash  = EVP_PKEY_new();
  EVP_PKEY_assign_RSA(hash, OMG);
  EVP_MD_CTX* hashed = EVP_MD_CTX_create();

  if (EVP_DigestVerifyInit(hashed,NULL, EVP_sha256(),NULL,hash)<=0) {
    return false;
  }
  if (EVP_DigestVerifyUpdate(hashed, cert3, cert4) <= 0) {
    return false;
  }
  int repeat1 = EVP_DigestVerifyFinal(hashed, cert, cert2);
  if (repeat1==1) {
    *cert12 = true;
    EVP_MD_CTX_free(hashed);
    return true;
  } else if(repeat1==0){
    *cert12 = false;
    EVP_MD_CTX_free(hashed);
    return true;
  } else{
    *cert12 = false;
    EVP_MD_CTX_free(hashed);
    return false;
  }
}

bool m::qwerty(char* qwerty, std::string hash, char* plain){
  RSA* f = y(qwerty);
  unsigned char* cert;
  size_t certLen;
  bool b64;
  c.dwiuba9sda8f7(plain, &cert, &certLen);
  bool result = t(f, cert, certLen, hash.c_str(), hash.length(), &b64);
  return result & b64;
}