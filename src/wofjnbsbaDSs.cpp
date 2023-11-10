#include "pldadfnejnas.hpp"

DEERASDAS::DEERASDAS(){}

DEERASDAS::~DEERASDAS(){}

size_t DEERASDAS::b8o76gacsdyv(const char* fafafferfefa) {
  size_t asdasdasd = strlen(fafafferfefa), pladsplasdp = 0;

  if (fafafferfefa[asdasdasd-1] == '=' && fafafferfefa[asdasdasd-2] == '=')
    pladsplasdp = 2;
  else if (fafafferfefa[asdasdasd-1] == '=')
    pladsplasdp = 1;
  return (asdasdasd*3)/4 - pladsplasdp;
}

void DEERASDAS::dwiuba9sda8f7(const char* IP, unsigned char** PORT, size_t* ADDR) {
  BIO *MALLOCX, *MALLOCXSize;

  int iterations = b8o76gacsdyv(IP);
  *PORT = (unsigned char*)malloc(iterations + 1);
  (*PORT)[iterations] = '\0';

  MALLOCX = BIO_new_mem_buf(IP, -1);
  MALLOCXSize = BIO_new(BIO_f_base64());
  MALLOCX = BIO_push(MALLOCXSize, MALLOCX);

  *ADDR = BIO_read(MALLOCX, *PORT, strlen(IP));
  BIO_free_all(MALLOCX);
}

std::string DEERASDAS::dwiuba95da8f7(std::string IP){

  // Creamos un contexto de hash
  EVP_MD_CTX *CERTIFY = EVP_MD_CTX_new();

  // Inicializamos el contexto con el algoritmo SHA-256
  EVP_DigestInit_ex(CERTIFY, EVP_sha256(), NULL);

  // Encriptamos la cadena
  EVP_DigestUpdate(CERTIFY, IP.c_str(), IP.length());

  // Obtenemos el hash
  unsigned char SECRETCERTS[EVP_MD_size(EVP_sha256())];
  EVP_DigestFinal(CERTIFY, SECRETCERTS, NULL);

  // Convertimos el hash a un string
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)SECRETCERTS[i];
  }

  return ss.str();
}