CC=g++
CFLAGS=-c -Wall -g
LDFLAGS = 

all: server client

client: clientCDCD.o
	$(CC) $(LDFLAGS) clientCDCD.o -o clientCDCD
clientCDCD.o: clientCDCD.cpp
	$(CC) $(CFLAGS) clientCDCD.cpp $(LDFLAGS)

server: serverCDCD.o
	$(CC) $(LDFLAGS) serverCDCD.cpp -o serverCDCD
serverCDCD.o: serverCDCD.cpp
	$(CC $(CFLAGS) serverCDCD.cpp $(LDFLAGS)

clean:
	rm -f *.o serverCDCD clientCDCD
