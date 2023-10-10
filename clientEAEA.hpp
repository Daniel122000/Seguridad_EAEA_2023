// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#ifndef _CLIENT_EAEA_HPP
#define _CLIENT_EAEA_HPP

#include <arpa/inet.h>

#define PORT 60138

class ClientEAEA {
 private:
	int clientFileDescriptor;
	struct sockaddr_in serv_addr;
	char buffer[500];

 public:
  ClientEAEA();
  char* getBuffer();
  int create_Socket();
  int convert_Addresses();
  int create_Connection();
  void readMessage();
  void sendMessage(const char* message);
  void endConnection();
};

#endif
