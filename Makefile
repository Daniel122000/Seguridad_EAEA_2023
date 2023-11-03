CC=g++
LDFLAGS = -lssl -lcrypto

all: delivery main

delivery:
	$(CC) src/delivery.cpp src/argsVerifier.cpp src/logger.cpp src/clientEAEA.cpp -o src/delivery

main:
	$(CC) src/mainEAEA.cpp src/argsVerifier.cpp src/verifier.cpp src/signVerifier.cpp src/certVerifier.cpp src/coder.cpp src/clientEAEA.cpp src/serverEAEA.cpp src/logger.cpp -o src/main $(LDFLAGS)

clean:
	rm -f src/delivery src/main
