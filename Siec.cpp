#include "Siec.h"

#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <time.h>
#include <cstdlib>

#include "Spis.h"

#include "TCPClient.h"
#include "TCPServer.h"


using namespace std;
using namespace _MAIN;

DWORD WINAPI recvThread(LPVOID ipParameter);
DWORD WINAPI sendThread(LPVOID ipParameter);
int _Siec::PlatformaTestowaOgolna(){

	cout << "Siec." << endl;


	return 0;
}




int _Siec::PlatformaTestowaMichal(){

	return 0;
}

int _Siec::PlatformaTestowaMarysia(){

	return 0;
}



int _Siec::PlatformaTestowaKasia(){

	cout << "Siec!" << endl;
	HANDLE hRecvThread = NULL;

	TCPServer Server;
	Server.Start();
	Server.Create();
	Server.Bind();
	Server.Listen(1);

	while (true)
	{
		if (!Server.Accept()) break;

		SOCKET clientRecvSocket;
		clientRecvSocket = Server.getClient();
		hRecvThread = CreateThread(NULL, 0, recvThread, (LPVOID)clientRecvSocket, 0, NULL);   // moj trop
		if (hRecvThread == NULL)
		{
			cout << "Recv error!" << endl;
			break;
		}

		CloseHandle(hRecvThread);
	}
	Server.Close();
	system("pause");
	//TCPClient client("127.0.0.1", 10000);
	
	return 0;
}

DWORD WINAPI sendThread(LPVOID ipParameter)
{
	SOCKET csocket = (SOCKET)ipParameter;
	TCPServer client;
	client.setClient(csocket);

	while (true)
	{
		if (!client.Send()) break;
		else break;
	}
	return 0;
};

DWORD WINAPI recvThread(LPVOID ipParameter)
{
	SOCKET csocket = (SOCKET)ipParameter;
	TCPServer client;
	client.setClient(csocket);
	HANDLE hSendThread = NULL;
	SOCKET clientSendSocket;
	clientSendSocket = client.getClient();
	hSendThread = CreateThread(NULL, 0, sendThread, (LPVOID)clientSendSocket, 0, NULL);
	if (hSendThread == NULL)
	{
		cout << "Send" << endl;
	}
	while (true)
	{

		if (!client.Recieve())
		{
			break;
		}

	}
	CloseHandle(hSendThread);
	return 0;
};
