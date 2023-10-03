CC=g++
CFLAGS=-c -Wall -g
LDFLAGS = 

all: server client

client: clientEAEA.o
	$(CC) $(LDFLAGS) clientEAEA.o -o clientEAEA
clientEAEA.o: clientEAEA.cpp
	$(CC) $(CFLAGS) clientEAEA.cpp $(LDFLAGS)

server: serverEAEA.o
	$(CC) $(LDFLAGS) serverEAEA.cpp -o serverEAEA
serverEAEA.o: serverEAEA.cpp
	$(CC $(CFLAGS) serverEAEA.cpp $(LDFLAGS)

clean:
	rm -f *.o serverEAEA clientEAEA
