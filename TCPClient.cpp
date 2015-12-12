//TCP CLIENT
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <cstdio>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include "TCPClient.h"
#include "StopWatch.h"

using namespace std;

TCPClient::TCPClient(const char * ipAdress, int nport)
{
	long rc;
	WSADATA wsaDATA;
	SOCKET sConnect;
	sockaddr_in compar;

	rc = WSAStartup(MAKEWORD(2, 0), &wsaDATA);

	if (rc == 0)
	{
		cout << "WSAStartup \t succesful" << endl;
	}
	else
		cout << "error WSAStartup " << WSAGetLastError() << endl;

	sConnect = socket(AF_INET, SOCK_STREAM, 0);

	if (sConnect != INVALID_SOCKET)
	{
		cout << "socket \t succesful" << endl;
	}
	else
		cout << "error socket " << WSAGetLastError() << endl;

	compar.sin_addr.s_addr = inet_addr(ipAdress);
	compar.sin_family = AF_INET;
	compar.sin_port = htons(nport);
	int comparat = sizeof(compar);

	rc = connect(sConnect, (struct sockaddr *)&compar, comparat);

	if (rc != SOCKET_ERROR)
	{
		cout << "connect \t succesful" << endl;
	}
	else
		cout << "error connect" << WSAGetLastError() << endl;

	while (1)
	{
		memset(&sendbuf, 0, sizeof(sendbuf));
		memset(&recvbuf, 0, sizeof(recvbuf));

		rc = recv(sConnect, recvbuf, 256, 0);
		if (rc == SOCKET_ERROR)
			cout << "error recv " << WSAGetLastError << endl;
		else
			cout << rc << "bytes received " << recvbuf << endl;

		FILE *filehandle = fopen("_pliki\\Tomsiator 2015.rar", "wb");
		if (filehandle != NULL)
		{
			bool ok = readfile(sConnect, filehandle);
			fclose(filehandle);

			if (ok)
			{
				cout << "udalo sie" << endl;
			}
			else
				remove("_pliki\\Tomsiator 2015.rar");
		}

		cout << "send: ";
		cin.getline(sendbuf, 256);

		rc = send(sConnect, sendbuf, strlen(sendbuf), 0);

		if (rc == SOCKET_ERROR)
			cout << "error send " << WSAGetLastError << endl;
		else
		{
			cout << rc << "bytes send " << endl;
			break;
		}

	}

	closesocket(sConnect);
	WSACleanup();
}

bool TCPClient::readdata(SOCKET sock, void *buf, int buflen)
{
	char * pbuf = (char *)buf;

	while (buflen > 0)
	{
		int num = recv(sock, pbuf, buflen, 0);
		if (num == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				continue;
			}
			return false;
		}
		else if (num == 0)
			return false;

		pbuf += num;
		buflen -= num;
	}
	return true;
}
bool TCPClient::readlong(SOCKET sock, long *value)
{
	if (!readdata(sock, value, sizeof(value)))
		return false;

	*value = ntohl(*value);
	return true;
}
bool TCPClient::readfile(SOCKET sock, FILE *f)
{
	StopWatch stoper;
	long filesize;
	long fsize;
	if (!readlong(sock, &filesize))
		return false;
	if (filesize > 0)
	{
		fsize = filesize;
		stoper.Start();
		char buffer[1024];
		do
		{

			int num = min(filesize, sizeof(buffer));
			if (!readdata(sock, buffer, num))
				return false;
			int offset = 0;
			do
			{
				size_t written = fwrite(&buffer[offset], 1, num - offset, f);
				if (written < 1)
					return false;
				offset += written;

			} while (offset < num);
			filesize -= num;
		} while (filesize > 0);
		stoper.Stop();
	}
	else
		filesize = 0;
	cout << "\n\nCzas: " << stoper.MilliSeconds() * 0.001 << " sekund" << endl;
	cout << "Rozmiar pliku: " << fsize << endl;
	cout << "Srednia predkosc: " << (fsize / (stoper.MilliSeconds() * 0.001)) / 1048576 << "MB/sec" << endl;
	return true;
}