// Adaptado de https://gist.github.com/irbull/08339ddcd5686f509e9826964b17bb59
#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/x509.h>

RSA* createPublicRSA(char* key) {
  RSA *rsa = NULL;
  BIO *keybio;
  keybio = BIO_new_mem_buf((const void*)key, -1);
  if (keybio==NULL) {
      return 0;
  }
  rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa,NULL, NULL);
  return rsa;
}

bool RSAVerifySignature( RSA* rsa,
                         unsigned char* MsgHash,
                         size_t MsgHashLen,
                         const char* Msg,
                         size_t MsgLen,
                         bool* Authentic) {
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

size_t calcDecodeLength(const char* b64input) {
  size_t len = strlen(b64input), padding = 0;

  if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
    padding = 2;
  else if (b64input[len-1] == '=') //last char is =
    padding = 1;
  return (len*3)/4 - padding;
}

void Base64Decode(const char* b64message, unsigned char** buffer, size_t* length) {
  BIO *bio, *b64;

  int decodeLen = calcDecodeLength(b64message);
  *buffer = (unsigned char*)malloc(decodeLen + 1);
  (*buffer)[decodeLen] = '\0';

  bio = BIO_new_mem_buf(b64message, -1);
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_push(b64, bio);

  *length = BIO_read(bio, *buffer, strlen(b64message));
  BIO_free_all(bio);
}

bool verifySignature(char* publicKey, std::string plainText, char* signatureBase64) {
  RSA* publicRSA = createPublicRSA(publicKey);
  unsigned char* encMessage;
  size_t encMessageLength;
  bool authentic;
  Base64Decode(signatureBase64, &encMessage, &encMessageLength);
  bool result = RSAVerifySignature(publicRSA, encMessage, encMessageLength, plainText.c_str(), plainText.length(), &authentic);
  return result & authentic;
}

std::string sha256(std::string text){

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

X509_REQ* try_read_csr(X509* cert, bool* success){ // Uso el csr del CA?
  // Obtener el .csr del certificado
  X509_REQ *csr = X509_to_X509_REQ(cert, nullptr, EVP_get_digestbyname("sha256"));
  
  if (csr == nullptr) {
    *success = false;
    return NULL;
  }

  return csr;
}

X509* try_read_crt(const char* path, bool* success){
  // Abrir el archivo del certificado
  FILE *fp = fopen(path, "rb");
  if (fp == NULL) {
    *success = false;
    return NULL;
  }

  // Leer el certificado del archivo
  X509 *cert = PEM_read_X509(fp, NULL, NULL, NULL);
  fclose(fp);
  
  return cert;
}

EVP_PKEY* try_read_pubkey(X509_REQ* csr, char** out){
  EVP_PKEY* pubkey = X509_REQ_get_pubkey(csr);

  BIO* bio = BIO_new(BIO_s_mem());
  PEM_write_bio_PUBKEY(bio, pubkey);

  BIO_get_mem_data(bio, out);
  return pubkey;
}

EVP_PKEY* load_public_key_from_string(const char* public_key_pem) {
    BIO* bio = BIO_new_mem_buf(public_key_pem, -1);
    if (bio == nullptr) {
        fprintf(stderr, "Error al crear el objeto BIO\n");
        return nullptr;
    }

    EVP_PKEY* public_key = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
    if (public_key == nullptr) {
        fprintf(stderr, "Error al leer la clave pública desde la cadena PEM\n");
        BIO_free(bio);
        return nullptr;
    }

    BIO_free(bio);
    return public_key;
}

int main(int argc, char const *argv[]) { // ------------------------------------------MAIN

  if(argc != 4){
    std::cout << "Uso: <usuario.nac> <hash firmado y en base64> <mensaje texto plano>\n";
    //return 1;
  }

  if(strlen(argv[1]) > 30 || strlen(argv[1]) < 15){
    std::cout << "Usuario " << argv[1] << " SUS.\n";
    //return 1;
  }else if(strlen(argv[2]) > 500){
    std::cout << "Codigo base64 SUS.\n";
    return 1;
  }else if(strlen(argv[3]) > 500){
    std::cout << "Mensaje demasiado extenso. 500 caracteres maximo.\n";
    return 1;
  }

  std::string user_crt_path = "../crt/"; // Certificado del usuario
  user_crt_path.append(argv[1]).append(".crt");
  bool success = true;
  X509* cert_user = try_read_crt(user_crt_path.c_str(), &success);
  if (!success) {
    std::cout << "No existe el certificado para " << argv[1] << std::endl;
    X509_free(cert_user);
    return 1;
  }

  // Validar certificado usuario con certificado CA
  // Cargar certificado CA
  X509* cert_CA = try_read_crt("../ca/CAG5.crt", &success);
  if (!success) {
    std::cout << "No existe el certificado de la CA. Ya valimos." << std::endl;
    X509_free(cert_CA);
    return 1;
  }
  // Extraer .csr de CA
  X509_REQ* csr_CA = try_read_csr(cert_CA, &success);
  if (!success) {
    std::cout << "No se pudo cargar el .csr de la CA. Ya valimos." << std::endl;
    return 1;
  }
  // Extraer llave publica de .csr de CA
  char* pubkey_char_CA = nullptr;
  EVP_PKEY* pubkey_CA = try_read_pubkey(csr_CA, &pubkey_char_CA);
  if(!pubkey_char_CA){
    std::cout << "Error al leer llave publica de la CA." << std::endl;
    return 1;
  }
  // Verificar con la lalve publica de CA el certificado del usuario
  // Verificar la firma del certificado
  if (X509_verify(cert_user, pubkey_CA) != 1) {
      fprintf(stderr, "La firma del certificado esta SUS, cancelar.");
  } else {
      printf("La firma del certificado esta a cachete.");
  }

  /*std::string plainText = "JugadaTosty";
  std::string signature = "oMpQMOBaA/vUb0gnBCqIj9QpbWHgliwlS7ojIUlCZlI4li/V5q5r/xAxVWd66KrL\n"\
"nKBfXyjbCePD7jvvM2gJoBNXPu8qAwGtvTZxs9wgziRcZz4QYmsYDZcDOR1xGmsS\n"\
"/+9vptQB1uFUsYQ66uzgk/T1XjF9F+dOvzK64XL/7NH5i9E0Cuq39r1WhIVM0kGF\n"\
"kfOcl39fov0KE13W8NR4PTWNwph2k5uaiNH3ZH9E/8mDaMVLeKUnTcFUTpiN6TSr\n"\
"6uqawPJ+cEZ8Z0jdFGBXLea25flkYSxyY2mV5dMf71gy5D3sh7PU71xzxfqwDSh6\n"\
"tjQywhmiYmUYBJ+IZ8MkPA==";

  bool authentic = verifySignature(pubkey_char_user, sha256(plainText), (char*)signature.c_str());

  if ( authentic ) {
    std::cout << "Todo bien, por ahora." << std::endl;
  } else {
    std::cout << "Hay un impostor entre nosotros. Mensaje o llave SUS." << std::endl;
  }*/
  return 0;
}