#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <vector>

class TCPServer
{
public:
	DWORD WINAPI recvThread(LPVOID ipParameter);
	DWORD WINAPI sendThread(LPVOID ipParameter);
	bool Start();
	bool Create();
	bool Bind();
	bool Listen(int n);
	bool Accept();
	void setClient(SOCKET c) { client = c; };
	SOCKET getClient() { return client; };
	bool Recieve();
	bool Send();
	void Close();
private:
	char* IP_ADDRESS = "127.0.0.1";
	u_short PORT = 10000;
	SOCKET server;
	long fsize;
	SOCKET client;
	struct sockaddr_in localAddr;
	struct sockaddr_in clientAddr;
	char sendBuff[MAX_PATH];
	char recvBuff[MAX_PATH];
	bool sendlong(SOCKET sock, long value);
	bool senddata(SOCKET sock, void *buf, int buflen);
	//bool sendfile(SOCKET sock, FILE *f);
	std::vector<SOCKET> list;

};


#endif