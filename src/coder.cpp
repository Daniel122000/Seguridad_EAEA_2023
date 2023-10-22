#include "coder.hpp"

Coder::Coder(){}

Coder::~Coder(){}

size_t Coder::calc_decode_length(const char* b64input) {
  size_t len = strlen(b64input), padding = 0;

  if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
    padding = 2;
  else if (b64input[len-1] == '=') //last char is =
    padding = 1;
  return (len*3)/4 - padding;
}

void Coder::base64_decode(const char* b64message, unsigned char** buffer, size_t* length) {
  BIO *bio, *b64;

  int decodeLen = calc_decode_length(b64message);
  *buffer = (unsigned char*)malloc(decodeLen + 1);
  (*buffer)[decodeLen] = '\0';

  bio = BIO_new_mem_buf(b64message, -1);
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_push(b64, bio);

  *length = BIO_read(bio, *buffer, strlen(b64message));
  BIO_free_all(bio);
}

std::string Coder::sha256(std::string text){

  // Creamos un contexto de hash
  EVP_MD_CTX *ctx = EVP_MD_CTX_new();

  // Inicializamos el contexto con el algoritmo SHA-256
  EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);

  // Encriptamos la cadena
  EVP_DigestUpdate(ctx, text.c_str(), text.length());

  // Obtenemos el hash
  unsigned char hash[EVP_MD_size(EVP_sha256())];
  EVP_DigestFinal(ctx, hash, NULL);

  // Convertimos el hash a un string
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }

  return ss.str();
}