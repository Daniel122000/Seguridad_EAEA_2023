// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#ifndef _SERVER_EAEA_HPP
#define _SERVER_EAEA_HPP

#include <netinet/in.h>

#include <cstring>
#include <unistd.h>
#include <iostream>

#define PORT 60138 // EAEA

class ServerEAEA {
 private:
  int serverFileDescriptor, newSocket;
  struct sockaddr_in address;
	char buffer[500] = { 0 }; 

 public:
  ServerEAEA();
  char* getBuffer();
  void createSocket();
	void init_Socket();
	void bind_Socket();
  void listenForConnections();
  void acceptNewConnection();
  void readMessage();
  void sendMessage();
  void endConnection();
  void closeServer();
};

#endif
