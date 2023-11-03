// Adapted from: https://www.geeksforgeeks.org/socket-programming-cc/
#include "clientEAEA.hpp"

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
  serv_addr.sin_port = htons(OUT_PORT);
  return 0;
}

int ClientEAEA::convert_Addresses(char* IP) {
	if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) {
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
