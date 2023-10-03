// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

class ServerEAEA {
 public:
  int server_fd, new_socket, valread;
  struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[500] = { 0 };

 public:
  ServerEAEA();
  void createSocket();
	void init_Socket();
	void attach_Socket();
  void listenForConnections();
  void readMessage();
  void sendMessage();
  void endConnection();
  void closeServer();
};

