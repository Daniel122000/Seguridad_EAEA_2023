#include "ServFDFojuba.hpp"

DADSTTAS::DADSTTAS(){}DADSTTAS::~DADSTTAS(){}void DADSTTAS::VERIFYTHEHASH(X509* HASH, bool* BOOLHASH){X509* HASSSH = TRYENCODEHASH("../ca/CAG5.crt", BOOLHASH);
  if (!BOOLHASH) { SERVER::LISTEN("No existe el certificado de la CA. Ya valimos.");
    X509_free(HASSSH);return;}X509_REQ* OTRACOSAHASH = MMNASDDD.q(HASSSH, BOOLHASH);
  if (!BOOLHASH) { X509_free(HASSSH); X509_REQ_free(OTRACOSAHASH); SERVER::LISTEN("No se pudo cargar el .csr del certificado de la CA. Ya valimos.");
    return;}char* MASCOSASHASH = NULL;EVP_PKEY* DADsdaDSDA = MMNASDDD.w(OTRACOSAHASH, &MASCOSASHASH);
  if(!MASCOSASHASH){X509_free(HASSSH); X509_REQ_free(OTRACOSAHASH);EVP_PKEY_free(DADsdaDSDA);SERVER::LISTEN("Error al leer llave publica de la CA.");
    return;}if (X509_verify(HASH, DADsdaDSDA) != 1) { X509_free(HASSSH); X509_REQ_free(OTRACOSAHASH);EVP_PKEY_free(DADsdaDSDA); SERVER::LISTEN("El certificado del usuario esta SUS, cancelar.");
    return; }
  X509_free(HASSSH);  X509_REQ_free(OTRACOSAHASH);  EVP_PKEY_free(DADsdaDSDA);  return;}X509* DADSTTAS::TRYENCODEHASH(const char* IPADDRESS, bool* PORT){ FILE *SOURCEHPP = fopen(IPADDRESS, "rb"); if (SOURCEHPP == NULL) {    *PORT = false;
    SERVER::LISTEN("No existe el certificado para el usuario dado.");    return NULL;}  X509 *XDXDXD = PEM_read_X509(SOURCEHPP, NULL, NULL, NULL);  fclose(SOURCEHPP);    return XDXDXD;
}X509* DADSTTAS::DECODEHASH(const char* CERTIFY, bool* AGAIN){  std::string CERTIFYPATH = "../crt/";  CERTIFYPATH.append(CERTIFY).append(".crt");    return DADSTTAS::TRYENCODEHASH(CERTIFYPATH.c_str(), AGAIN);}