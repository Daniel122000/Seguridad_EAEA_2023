// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#include "client.hpp"

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

Client::Client(){}

int Client::init_Socket() {

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	return 0;
}

int Client::convert_Addresses() {
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}	
	return 0;
}

int Client::create_Connection() {
	if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	return 0;
}

void Client::readMessage(){
    read(client_fd, buffer, 500);
}

void Client::sendMessage(){
    char* message = "Hello from client";
    send(client_fd, message, strlen(message), 0);
}

void Client::endConnection(){
    close(client_fd);
}

int main (int argc, char* argv[]){
    Client client;

    // Client
    client.init_Socket();
    client.convert_Addresses();
    client.create_Connection();

    // valread = read(new_socket, buffer, 1024);

    // Client sends message to server
    client.sendMessage();
    printf("Message sent\n");

    // Client reads the message
    client.readMessage();
	printf("%s\n", client.buffer);

	// closing the connected sockets
    client.endConnection();
}