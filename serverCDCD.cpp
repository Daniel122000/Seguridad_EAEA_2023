// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#include "serverCDCD.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define PORT 52685 //CDCD

Server::Server(){}

void Server::createSocket() {
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
}

void Server::init_Socket () {
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
}

void Server::attach_Socket() {
    // Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}	
}

void Server::listenForConnections() {
    if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
}

void Server::readMessage(){
    read(new_socket, buffer, 500);
}

void Server::sendMessage(){
    char* message = "Hello from server";
    send(new_socket, message, strlen(message), 0);
}

void Server::endConnection(){
    close(new_socket);
}

void Server::closeServer(){
    shutdown(server_fd, SHUT_RDWR);
}

int main (int argc, char* argv[]){
    Server server;

    // Server
    server.createSocket();
    server.init_Socket();
    server.attach_Socket();
    server.listenForConnections();

    // Server reads the message
	server.readMessage();
	printf("%s\n", server.buffer);

    // Server sends response to client
    server.sendMessage();
	//send(new_socket, hello, strlen(hello), 0);
	printf("Message sent\n");

	// closing the connected sockets
    server.endConnection();
    server.closeServer();
}
