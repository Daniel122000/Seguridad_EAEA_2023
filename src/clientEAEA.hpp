// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#ifndef _CLIENT_EAEA_HPP
#define _CLIENT_EAEA_HPP

#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <syslog.h>
#include <unistd.h>

#define OUT_PORT 60138 // EAEA

class ClientEAEA {
 private:
	int clientFileDescriptor;
	struct sockaddr_in serv_addr;
	char buffer[1024];

 public:
  ClientEAEA();
  char* getBuffer();
  int create_Socket();
  int convert_Addresses(char* IP);
  int create_Connection();
  void readMessage();
  void sendMessage(const char* message);
  void endConnection();
};

#endif
