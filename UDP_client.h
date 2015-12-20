#ifndef CLIENT_H
#define CLIENT_H

class ClientUDP {
	char inBuffer[256];
	char outBuffer[256];

public:
	ClientUDP(int localPort, const char * IP, int remotePort);
};

#endif

