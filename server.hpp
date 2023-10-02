// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

class Server {
 public:
  int server_fd, new_socket, valread;
  struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[500] = { 0 };

 public:
  Server();
  void createSocket();
	void init_Socket();
	void attach_Socket();
  void listenForConnections();
  void readMessage();
  void sendMessage();
  void endConnection();
  void closeServer();
};

