// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/

#include "clientEAEA.hpp"

#include <iostream>
#include <cstring>
#include <unistd.h>

using namespace std;

ClientEAEA::ClientEAEA() {
  create_Socket();
}

char* ClientEAEA::getBuffer() {
  return buffer;
}

int ClientEAEA::create_Socket() {
  if ((clientFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cout << "\n Socket creation error \n";
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  return 0;
}

int ClientEAEA::convert_Addresses() {
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		cout << "\nInvalid address/ Address not supported \n";
		return -1;
	}	
	return 0;
}

int ClientEAEA::create_Connection() {
	if ((connect(clientFileDescriptor, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
		cout << "\nConnection Failed \n";
		return -1;
	}
	return 0;
}

void ClientEAEA::readMessage() {
  read(clientFileDescriptor, buffer, 500);
}

void ClientEAEA::sendMessage(const char* message) {
  send(clientFileDescriptor, message, strlen(message), 0);
}

void ClientEAEA::endConnection() {
  close(clientFileDescriptor);
}

int main (int argc, char* argv[]) {    
  if(argc < 2) {
    cout << "No messages to send\n";
    return 0;
  }
    
  if(argc > 2) {
    cout << "Too many parameters.\n";
    return 1;
  }

  // Client sends message to server if message lenght is < 500
  if(strlen(argv[1]) > 500) {
    cout << " Maximum characters: 500.\n";
    return 1;
  }

  ClientEAEA client;

  client.convert_Addresses();
  client.create_Connection();

  // Client sends the message
  client.sendMessage(argv[1]); // Second argument is the message to be sent.
  cout << "Message sent: " << argv[1] << endl;

  // Client reads the server response
  client.readMessage();
  cout <<  "Server response: " << client.getBuffer() << endl;

  // Close the connected sockets
  client.endConnection();
  return 0;
}
