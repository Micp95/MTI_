//TCP SERVER
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <cstdio>
#include <iostream>
#include <WinSock2.h>
#include <vector>
#include <Windows.h>
#include "TCPServer.h"
#include "StopWatch.h"
using namespace std;
FILE *f = fopen("_pliki\\Tomsiator 2015.rar", "rb");

void TCPServer::filetoSend(char * name)
{
	FILE *file = fopen(name, "rb");
	f = file;
}

bool TCPServer::Start()
{
	WSADATA WSA;
	if (WSAStartup(MAKEWORD(2, 2), &WSA) != 0)
	{
		cout << "error WSAStartup " << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "WSA succesfull" << endl;
		return true;
	}
}

bool TCPServer::Create()
{
	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server == INVALID_SOCKET)
	{
		cout << "error socket " << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "Socket succesfull!" << endl;
		localAddr.sin_family = AF_INET;
		localAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
		localAddr.sin_port = htons(PORT);
		memset(localAddr.sin_zero, 0x00, 8);
		return true;
	}
}

bool TCPServer::Bind()
{
	if (bind(server, (struct sockaddr*)&localAddr, sizeof(localAddr)) != 0)
	{
		cout << "error bind " << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "bind \t succesful" << endl;
		return true;
	}
}

bool TCPServer::Listen(int n)
{
	if (listen(server, n) != 0)
	{
		cout << "error listen " << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "listen succesfull" << endl;
		return true;
	}
}

bool TCPServer::Accept()
{
	int addrLen = sizeof(clientAddr);
	memset(&clientAddr, 0x00, addrLen);
	client = accept(server, (struct sockaddr*)&clientAddr, &addrLen);
	list.push_back(client);
	if (client == INVALID_SOCKET)
	{
		cout << "error socket " << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "\nclient accepted: " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;
		return true;
	}
}

bool TCPServer::Recieve()
{
	memset(recvBuff, '\0', sizeof(recvBuff));

	strcpy(sendBuff, "\nNawiazano polaczenie \n");
	send(client, "\nNawiazano polaczenie \n", 23, 0);

	if (recv(client, recvBuff, sizeof(recvBuff), 0) == SOCKET_ERROR)
	{
		//cout << "Socket error" << endl;
		return false;
	}
	else
	{
		//strcpy(sendBuff, "Good Bye");
		//send(client, sendBuff, sizeof(sendBuff), 0);
		closesocket(client);
	}
	return true;
}
void TCPServer::Close()
{
	closesocket(server);
	closesocket(client);
	WSACleanup();
}
bool TCPServer::Send()
{
	StopWatch stoper;
	fseek(f, 0, SEEK_END);
	long filesize = ftell(f);
	rewind(f);
	if (filesize == EOF)
	{
		cout << "Return1" << endl;
		return false;
	}
	if (!sendlong(client, filesize))
	{
		cout << "Return2" << endl;
		return false;
	}
	if (filesize > 0)
	{
		fsize = filesize;
		stoper.Start();
		char buffer[1024];
		do
		{
			size_t num = min(filesize, sizeof(buffer));
			num = fread(buffer, 1, num, f); //tuuu
			if (num < 1)
			{
				cout << "false1" << endl;
				return false;
			}
			if (!senddata(client, buffer, num))
			{
				cout << "false2" << endl;
				return false;
			}
			filesize -= num;
		} while (filesize > 0);
		stoper.Stop();
	}
	cout << "\n\nCzas: " << stoper.MilliSeconds() * 0.001 << " sekund" << endl;
	cout << "Rozmiar pliku: " << fsize << endl;
	cout << "Srednia predkosc: " << (fsize / (stoper.MilliSeconds() * 0.001)) / 1048576 << "MB/sec" << endl;
	return true;
	/*memset(sendBuff, 0x00, sizeof(recvBuff));
	cout << "idzie";
	//cin.getline(sendBuff, sizeof(sendBuff));
	if (send(client, sendBuff, (int)strlen(sendBuff), 0) == SOCKET_ERROR)
	{
	cout << "Dupa1" << endl;
	return false;
	}
	else
	{
	//cout << "Dupa2" << endl;
	return true;
	}*/
	//return true;
}
bool TCPServer::sendlong(SOCKET sock, long value)
{
	value = htonl(value);
	return senddata(sock, &value, sizeof(value));
}
bool TCPServer::senddata(SOCKET sock, void *buf, int buflen)
{
	const char *pbuf = (const char *)buf;

	while (buflen > 0)
	{
		int num = send(sock, pbuf, buflen, 0);
		if (num == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				// optional: use select() to check for timeout to fail the send
				continue;
			}
			return false;
		}

		pbuf += num;
		buflen -= num;
	}

	return true;
}


