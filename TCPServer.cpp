//TCP SERVER
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <cstdio>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include "TCPServer.h"
#include "StopWatch.h"
using namespace std;

TCPServer::TCPServer(const char * ipAdress, int nport)
{
	//Pomocniczne wartosci;
	long res;

	//Data wersji
	WSADATA wsaData;

	//aktywacja ws2_32.dll
	res = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (res == 0)
	{
		cout << "WSAStartup \t succesful" << endl;
	}
	else
		cout << "error WSAStartup " << WSAGetLastError() << endl;

	SOCKET slisten, client;

	slisten = socket(AF_INET, SOCK_STREAM, 0);
	if (slisten != INVALID_SOCKET)
	{
		cout << "socket \t succesful" << endl;
	}
	else
		cout << "error socket " << WSAGetLastError() << endl;

	//Informacje o polaczeniu

	sockaddr_in info;
	info.sin_addr.s_addr = inet_addr(ipAdress); //local host
	info.sin_family = AF_INET;
	info.sin_port = htons(nport);
	int infor = sizeof(info);

	res = bind(slisten, (struct sockaddr *)&info, infor);

	if (res != SOCKET_ERROR)
	{
		cout << "bind \t succesful" << endl;
	}
	else
		cout << "error bind " << WSAGetLastError() << endl;

	//Kolejka dla polaczen przychodzacych
	res = listen(slisten, SOMAXCONN);
	if (res != SOCKET_ERROR)
	{
		cout << "listen \t succesful" << endl;
	}
	else
		cout << "error listen " << WSAGetLastError() << endl;

	sockaddr_in clientinfo;
	int clients = sizeof(clientinfo);

	while (1)
	{
		client = accept(slisten, (struct sockaddr *)&clientinfo, &clients);
		if (client != SOCKET_ERROR)
			cout << "client accepted: " << inet_ntoa(clientinfo.sin_addr) << ":" << ntohs(clientinfo.sin_port) << endl;

		res = send(client, "server message received", strlen("server message received"), 0);
		if (res == SOCKET_ERROR)
			cout << "error send " << WSAGetLastError() << endl;
		
		FILE *filehandle = fopen("_pliki\\wykresEntropii.png", "rb");
		if (filehandle != NULL)
		{
			sendfile(client, filehandle);
			fclose(filehandle);
		}

		res = recv(client, recvbuf, 256, 0);
		if (res == SOCKET_ERROR)
			cout << "error recv " << WSAGetLastError() << endl;
		else
			cout << res << " bytes received " << recvbuf << endl;
	}
	
	closesocket(client);
	closesocket(slisten);
	WSACleanup();
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

bool TCPServer::sendlong(SOCKET sock, long value)
{
	value = htonl(value);
	return senddata(sock, &value, sizeof(value));
}
bool TCPServer::sendfile(SOCKET sock, FILE *f)
{
	StopWatch stoper;
	fseek(f, 0, SEEK_END);
	long filesize = ftell(f);
	rewind(f);
	if (filesize == EOF)
		return false;
	if (!sendlong(sock, filesize))
		return false;
	if (filesize > 0)
	{
		fsize = filesize;
		stoper.Start();
		char buffer[1024];
		do
		{
			size_t num = min(filesize, sizeof(buffer));
			num = fread(buffer, 1, num, f);
			if (num < 1)
				return false;
			if (!senddata(sock, buffer, num))
				return false;
			filesize -= num;
		} while (filesize > 0);
		stoper.Stop();
	}
	cout << "\n\nCzas: " << stoper.MilliSeconds() * 0.001 << " sekund" << endl;
	cout << "Rozmiar pliku: " << fsize << endl;
	cout << "Srednia predkosc: " << (fsize / (stoper.MilliSeconds() * 0.001)) / 1048576 << "MB/sec" << endl;
	return true;
}