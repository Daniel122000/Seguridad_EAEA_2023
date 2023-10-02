// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

class Client {
  public:
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char buffer[1024];

  public:
    Client();
    int init_Socket();
    int convert_Addresses();
    int create_Connection();
    void readMessage();
    void sendMessage(char* message);
    void endConnection();
};