// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#include "clientEAEA.hpp"

using namespace std;

ClientEAEA::ClientEAEA() {
  create_Socket();
}

char* ClientEAEA::getBuffer() {
  return buffer;
}

int ClientEAEA::create_Socket() {
  if ((clientFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cout << "\n Socket creation error \n";
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  return 0;
}

int ClientEAEA::convert_Addresses() {
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
	  cout << "\nInvalid address/ Address not supported \n";
	  return -1;
	}	
	return 0;
}

int ClientEAEA::create_Connection() {
	if ((connect(clientFileDescriptor, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
		cout << "\nConnection Failed \n";
		return -1;
	}
	return 0;
}

void ClientEAEA::readMessage() {
  read(clientFileDescriptor, buffer, 500);
}

void ClientEAEA::sendMessage(const char* message) {
  send(clientFileDescriptor, message, strlen(message), 0);
}

void ClientEAEA::endConnection() {
  close(clientFileDescriptor);
}

int main (int argc, char* argv[]) {  //-----------------------------------MAIN  
    
  if(argc > 2) {
    cout << "Too many parameters.\n";
    return 1;
  }

  ClientEAEA client;

  client.convert_Addresses();
  client.create_Connection();

 // Ruta relativa al archivo que deseas leer
  std::string fileRoute = "dummy.txt";

  // Abrir el archivo en modo de lectura
  std::ifstream file;
  file.open(fileRoute, ifstream::in);

  // Verificar si el archivo se abrió correctamente
  if (file.is_open()) {
      std::string linea;
      // Leer el archivo línea por línea
      while (std::getline(file, linea)) {
          // Client sends message to server if message lenght is < 500
          const char* lineaChar = linea.c_str();
          if(strlen(lineaChar) > 500) {
            cout << " Maximum characters: 500.\n";
            break;
          }
          // Client sends the message
          
          client.sendMessage(lineaChar);
          cout << "Message sent: " << lineaChar << endl;

          // Client reads the server response
          //client.readMessage();
          //cout <<  "Server response: " << client.getBuffer() << endl;
          // Procesar la línea, puedes imprimirlo o enviarlo al syslog
          //syslog(LOG_INFO, "Línea leída: %s", linea.c_str());
      }
      // Cerrar el archivo después de leer
      file.close();
  } else {
      // Si no se puede abrir el archivo, enviar un mensaje al syslog
      //syslog(LOG_ERR, "No se pudo abrir el archivo: %s", fileRoute.c_str());
      cout << "Error al abrir." << endl;
  }


  // Close the connected sockets
  client.endConnection();
  return 0;
}
