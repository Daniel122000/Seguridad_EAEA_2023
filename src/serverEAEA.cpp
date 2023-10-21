// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#include "serverEAEA.hpp"

ServerEAEA::ServerEAEA() {
  createSocket();
  init_Socket();
  bind_Socket();
}

char* ServerEAEA::getBuffer() {
  return buffer;
}

void ServerEAEA::createSocket() {
	if ((serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
}

void ServerEAEA::init_Socket () {
  int opt = 1;
	if (setsockopt(serverFileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT); 
}

void ServerEAEA::bind_Socket() {
	if (bind(serverFileDescriptor, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}	
}

void ServerEAEA::listenForConnections() {
  if (listen(serverFileDescriptor, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
}

void ServerEAEA::acceptNewConnection() {
  int address_length = sizeof(address);
  newSocket = accept(serverFileDescriptor, (struct sockaddr*)&address, (socklen_t*)&address_length);
  if (newSocket < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }
}

void ServerEAEA::readMessage() {
  int reading_value = read(newSocket, buffer, 500);
  if (reading_value == 0) {
    close(newSocket);
    newSocket = 0;
  } 
}

void ServerEAEA::sendMessage() {
  const char* message = "Hello dear client";
  send(newSocket, message, strlen(message), 0);
}

void ServerEAEA::endConnection() {
  close(newSocket);
}

void ServerEAEA::closeServer() {
  shutdown(serverFileDescriptor, SHUT_RDWR);
}

int main (int argc, char* argv[]) {
  
  while(true) {
    ServerEAEA server;
    server.listenForConnections();
    server.acceptNewConnection();

    // Server reads the client message
    server.readMessage();
    std::string message = server.getBuffer();
    std::cout << "Client message: " << message << std::endl;
    std::string user = message; //sub str

    // Server sends response to client
    server.sendMessage();
    //send(new_socket, hello, strlen(hello), 0);

    // closing the connected sockets
    server.endConnection();
    server.closeServer();
  }
  
}
