#ifndef SERVER_H
#define SERVER_H

class ServerUDP {
	char inBuffer[256];
	char outBuffer[256];
	long sizeOfFile;

public:
	ServerUDP(int localPort);
};

#endif
