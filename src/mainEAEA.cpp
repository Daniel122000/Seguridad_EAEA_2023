// Adaptado de https://gist.github.com/irbull/08339ddcd5686f509e9826964b17bb59

#include "argsVerifier.hpp"
#include "clientEAEA.hpp"
#include "serverEAEA.hpp"
#include "verifier.hpp"

void send_to_next_node(std::string message, std::string IP){
  ClientEAEA client;

  client.convert_Addresses((char*)IP.c_str());
  client.create_Connection();
  client.sendMessage(message.c_str());
  client.endConnection();
  std::string log_message = "Enviando al siguiente nodo con IP=";
  log_message.append(IP);
  Logger::log(log_message);
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
      std::cout << "Fuente del mensaje SUS o estructura incompleta." << std::endl;
    }else{

      Verifier verifier(user, signature64, plainText);
      
      // Verificar si existe el certificado para el usuario
      if(!verifier.verify_certificate()){
        state = false;
      }      

      // Verificar la firma del hash con la llave publica y el mensaje del usuario
      if (state && verifier.verify_sign()) {
        std::string log_message = "Mensaje verificado. Usuario:";
        log_message.append(user);
        log_message.append(" - Mensaje original:");
        log_message.append(plainText);
        Logger::log(log_message);
        
        // Enviar si hay IP, si no, es el nodo final
        if(strings[1] == "0"){
          Logger::log("Trayecto del mensaje completado.");
        }else{
          std::string message = "";
          message.append(strings[3])
                  .append(" ")
                  .append(user)
                  .append(" ")
                  .append(signature64)
                  .append(" ")
                  .append(plainText);
          send_to_next_node(message, strings[1]);
        }
      } else {
        Logger::log("Hay un impostor entre nosotros. Mensaje, llave publica o base64 son SUS.");
      }
    }
    
    // Close sockets
    server.endConnection();
    server.closeServer();
  }
  return 0;
}
