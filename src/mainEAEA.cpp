// Adaptado de https://gist.github.com/irbull/08339ddcd5686f509e9826964b17bb59
#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/x509.h>

#include "clientEAEA.hpp"
#include "serverEAEA.hpp"
#include "argsVerifier.hpp"

RSA* create_public_rsa(char* key) {
  RSA *rsa = NULL;
  BIO *keybio;
  keybio = BIO_new_mem_buf((const void*)key, -1);
  if (keybio==NULL) {
      return 0;
  }
  rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa,NULL, NULL);
  return rsa;
}

bool rsa_verify_signature( RSA* rsa,
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

size_t calc_decode_length(const char* b64input) {
  size_t len = strlen(b64input), padding = 0;

  if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
    padding = 2;
  else if (b64input[len-1] == '=') //last char is =
    padding = 1;
  return (len*3)/4 - padding;
}

void base64_decode(const char* b64message, unsigned char** buffer, size_t* length) {
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

bool verify_signature(char* publicKey, std::string plainText, char* signatureBase64) {
  RSA* publicRSA = create_public_rsa(publicKey);
  unsigned char* encMessage;
  size_t encMessageLength;
  bool authentic;
  base64_decode(signatureBase64, &encMessage, &encMessageLength);
  bool result = rsa_verify_signature(publicRSA, encMessage, encMessageLength, plainText.c_str(), plainText.length(), &authentic);
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
    std::cout << "No existe el certificado para el usuario dado." << std::endl;
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

X509* verify_user_certificate(const char* user, bool* success){
  std::string user_crt_path = "../crt/"; // Certificado del usuario
  user_crt_path.append(user).append(".crt");
  
  return try_read_crt(user_crt_path.c_str(), success);
}

void verify_user_certificate_with_ca(X509* cert_user, bool* success){
  // Validar certificado usuario con certificado CA
  // Cargar certificado CA
  X509* cert_CA = try_read_crt("../ca/CAG5.crt", success);
  if (!success) {
    std::cout << "No existe el certificado de la CA. Ya valimos." << std::endl;
    X509_free(cert_CA);
    return;
  }
  // Extraer .csr de CA
  X509_REQ* csr_CA = try_read_csr(cert_CA, success);
  if (!success) {
    X509_free(cert_CA);
    X509_REQ_free(csr_CA);
    std::cout << "No se pudo cargar el .csr del certificado de la CA. Ya valimos." << std::endl;
    return;
  }
  // Extraer llave publica de .csr de CA
  char* pubkey_char_CA = nullptr;
  EVP_PKEY* pubkey_CA = try_read_pubkey(csr_CA, &pubkey_char_CA);
  if(!pubkey_char_CA){
    X509_free(cert_CA);
    X509_REQ_free(csr_CA);
    EVP_PKEY_free(pubkey_CA);
    std::cout << "Error al leer llave publica de la CA." << std::endl;
    return;
  }
  // Verificar con la lalve publica de CA el certificado del usuario
  // Verificar la firma del certificado
  if (X509_verify(cert_user, pubkey_CA) != 1) {
    X509_free(cert_CA);
    X509_REQ_free(csr_CA);
    EVP_PKEY_free(pubkey_CA);
    std::cout << "El certificado del usuario esta SUS, cancelar." << std::endl;
    return;
  } else {
    std::cout << "El certificado del usuario esta legal." << std::endl;
  }
  X509_free(cert_CA);
  X509_REQ_free(csr_CA);
  EVP_PKEY_free(pubkey_CA);
  return;
}

void extract_user_public_key(X509* cert_user, bool* success, char** pubkey_char_user){
  // Extraer .csr del usuario
  X509_REQ* csr_user = try_read_csr(cert_user, success);
  if (!success) {
    X509_REQ_free(csr_user);
    std::cout << "No se pudo cargar el .csr del certificado del usuario." << std::endl;
    return;
  }
  // Extraer llave publica de .csr del usuario
  try_read_pubkey(csr_user, pubkey_char_user);
  if(!pubkey_char_user){
    X509_REQ_free(csr_user);
    std::cout << "Error al leer llave publica del usuario." << std::endl;
    return;
  }
  X509_REQ_free(csr_user);
  X509_free(cert_user);
  return;
}

void send_to_next_node(std::string message){
   /*ClientEAEA client;

    client.convert_Addresses();
    client.create_Connection();
    client.sendMessage(message.c_str());
    std::cout << "Message sent: " << message << std::endl;
    client.endConnection();*/
}

int main(int argc, char const *argv[]) { // ------------------------------------------MAIN

  // Server listening
  std::string strings[4];
  strings[0] = argv[1];
  strings[1] = argv[2];
  strings[2] = argv[3];
  strings[3] = argv[4];

  while(true) {
    ServerEAEA server;
    server.listenForConnections();
    server.acceptNewConnection();

    // Server reads the client message
    server.readMessage();
    std::string message = server.getBuffer();

    ArgsVerifier verifier;
    if(!verifier.verify_arguments_node(message, strings)){
      std::cout << "Argumentos invalidos. Esperando otros mensajes." << std::endl;
    }else{
       // Server sends response to client
      server.sendMessage();
      //send(new_socket, hello, strlen(hello), 0);
    }
    
    // Close sockets
    server.endConnection();
    server.closeServer();
  }
  
  std::string user = argv[1];
  std::string signature = argv[2];
  std::string plainText = argv[3];
  
  // Verificar si existe el certificado para el usuario
  bool success = true;
  X509* cert_user = verify_user_certificate(user.c_str(), &success);
  
  if(!success){
    X509_free(cert_user);
    return 1;
  }

  // Verificar si el certificado del usuario es valido, usando el certificado de CA
  verify_user_certificate_with_ca(cert_user, &success);
  if(!success){
    X509_free(cert_user);
    return 1;
  }
  
  // Extraer la llave publica del usuario para verificar la firma
  char* pubkey_char_user = nullptr; // Llave publica formato .pem
  extract_user_public_key(cert_user, &success, &pubkey_char_user);  

  // Verificar la firma del hash con la llave publica y el mensaje del usuario
  if (verify_signature(pubkey_char_user, sha256(plainText), (char*)signature.c_str())) {
    std::cout << "Todo bien, por ahora." << std::endl;
    // Enviar si hay IP, si no, es el nodo final
    std::string message = "";
    message.append(user).append(" ").append(signature).append(" ").append(plainText);
    send_to_next_node(message);
  } else {
    std::cout << "Hay un impostor entre nosotros. Mensaje o llave son SUS." << std::endl;
    return 1;
  }
  return 0;
}
