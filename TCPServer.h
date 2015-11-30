#ifndef TCPSERVER_H
#define TCPSERVER_H


class TCPServer
{
	char recvbuf[256];
	bool senddata(SOCKET sock, void *buf, int buflen);
	bool sendlong(SOCKET sock, long value);
	bool sendfile(SOCKET sock, FILE *f);
	long fsize;
public:
	TCPServer(const char*, int);
};
#endif