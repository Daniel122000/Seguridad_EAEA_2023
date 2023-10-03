CC=g++
CFLAGS=-c -Wall -g
LDFLAGS = 

all: server client

client: client.o
	$(CC) $(LDFLAGS) client.o -o client
client.o: client.cpp
	$(CC) $(CFLAGS) client.cpp $(LDFLAGS)

server: server.o
	$(CC) $(LDFLAGS) server.cpp -o server
server.o: server.cpp
	$(CC $(CFLAGS) server.cpp $(LDFLAGS)

clean:
	rm -f *.o server client
