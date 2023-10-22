// Adaptado de https://gist.github.com/irbull/08339ddcd5686f509e9826964b17bb59
#include <sstream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>

#include "argsVerifier.hpp"
#include "clientEAEA.hpp"
#include "serverEAEA.hpp"
#include "verifier.hpp"

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

void send_to_next_node(std::string message){
   /*ClientEAEA client;

    client.convert_Addresses();
    client.create_Connection();
    client.sendMessage(message.c_str());
    std::cout << "Message sent: " << message << std::endl;
    client.endConnection();*/
}

int main(int argc, char const *argv[]) { // -----------------------------------MAIN

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
    std::string user;
    std::string signature;
    std::string plainText;

    ArgsVerifier verifier;
    if(!verifier.verify_arguments_node(message, strings, &user, &signature, &plainText)){
      std::cout << "Argumentos invalidos. Esperando otros mensajes." << std::endl;
    }else{ // ARGS NOT NECESSARILY GOOD
      Verifier verifier;
      // Verificar si existe el certificado para el usuario
      if(!verifier.verify_certificate(user)){
        return 1;
      }
      if(!verifier.verify_sign()){

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

    }
    
    // Close sockets
    server.endConnection();
    server.closeServer();
  }
  return 0;
}
