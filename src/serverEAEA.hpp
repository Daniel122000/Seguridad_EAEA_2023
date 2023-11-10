// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#ifndef _SERVER_EAEA_HPP
#define _SERVER_EAEA_HPP

#include <netinet/in.h>
#include <arpa/inet.h>

#include <cstring>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#define IN_PORT 60138 // EAEA

class ServerEAEA {
 private:
  int serverFileDescriptor, newSocket;
  struct sockaddr_in address;
	char buffer[1024] = { 0 }; 

 public:
  ServerEAEA();
  ServerEAEA(std::string);
  char* getBuffer();
  void createSocket();
	void init_Socket(std::string);
	void bind_Socket();
  void listenForConnections();
  void acceptNewConnection();
  void readMessage();
  void sendMessage();
  void endConnection();
  void closeServer();
  //inline void flushBuffer(){this->buffer = { 0 };};
};

#endif
