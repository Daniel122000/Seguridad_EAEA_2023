// Adaptado de https://gist.github.com/irbull/08339ddcd5686f509e9826964b17bb59

#include "argsVerifier.hpp"
#include "clientEAEA.hpp"
#include "serverEAEA.hpp"
#include "verifier.hpp"

void send_to_next_node(std::string message){
   /*ClientEAEA client;

    client.convert_Addresses();
    client.create_Connection();
    client.sendMessage(message.c_str());
    std::cout << "Message sent: " << message << std::endl;
    client.endConnection();*/
    std::cout << "Enviando al siguietne nodo." << std::endl;
    std::cout << message << std::endl;
}

int main(int argc, char const *argv[]) { // -----------------------------------MAIN

  // Server listening
  std::string strings[4];
  strings[0] = argv[1];
  strings[1] = argv[2];
  strings[2] = argv[3];
  strings[3] = argv[4];

  while(true) {
    bool state = true;
    ServerEAEA server;
    server.listenForConnections();
    server.acceptNewConnection();

    // Server reads the client message
    server.readMessage();
    std::string message = server.getBuffer();
    std::string user;
    std::string signature64;
    std::string plainText;

    ArgsVerifier args_verifier;
    if(!args_verifier.verify_arguments_node(message, strings, &user, &signature64, &plainText)){
      std::cout << "Argumentos invalidos. Esperando otros mensajes." << std::endl;
    }else{ // ARGS NOT NECESSARILY GOOD

      Verifier verifier(user, signature64, plainText);
      
      // Verificar si existe el certificado para el usuario
      if(!verifier.verify_certificate()){
        state = false;
      }      

      // Verificar la firma del hash con la llave publica y el mensaje del usuario
      if (state && verifier.verify_sign()) {
        std::cout << "Todo bien, por ahora." << std::endl;
        // Enviar si hay IP, si no, es el nodo final
        std::string message = "";
        message.append(user).append(" ").append(signature64).append(" ").append(plainText);
        send_to_next_node(message);
      } else {
        std::cout << "Hay un impostor entre nosotros. Mensaje o llave son SUS." << std::endl;
      }
    }
    
    // Close sockets
    server.endConnection();
    server.closeServer();
  }
  return 0;
}
