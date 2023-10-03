// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#include <arpa/inet.h>
#include <cstdio>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 60138

class ClientEAEA {
 public:
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char buffer[500];

 public:
  ClientEAEA();
  int init_Socket();
  int convert_Addresses();
  int create_Connection();
  void readMessage();
  void sendMessage(char* message);
  void endConnection();
};