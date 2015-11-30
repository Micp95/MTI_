#ifndef TCPCLIENT_H
#define TCPCLIENT_H


class TCPClient
{
	char sendbuf[256];
	char recvbuf[256];
	bool readdata(SOCKET sock, void *buf, int buflen);
	bool readlong(SOCKET sock, long *value);
	bool readfile(SOCKET sock, FILE *f);
	

public:
	TCPClient(const char *, int);
};

#endif