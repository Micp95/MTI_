#include "Siec.h"

#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <time.h>
#include <cstdlib>

#include "Spis.h"

#include "TCPClient.h"
#include "TCPServer.h"

#include "ComProtocol.h"
#include "ComProtocolListen.h"
#include "ComProtocolSend.h"
#include "RAWFile.h"
#include "MP3Transmition.h"
#include "Switchgear.h"
#include "SwitchgearClient.h"


using namespace std;
using namespace _MAIN;

DWORD WINAPI recvThread(LPVOID ipParameter);
DWORD WINAPI sendThread(LPVOID ipParameter);
int _Siec::PlatformaTestowaOgolna(){

	cout << "Siec." << endl;


	return 0;
}




int _Siec::PlatformaTestowaMichal(){
	
	
	char k;
	while (true) {
		system("cls");
		cout << "1.Server\n2.Client\n\n";
		cin >> k;
		try {
			if (k > 47 && k < 58) {
				throw SwitchgearFUN::Wyjatki::PodamaCyfra();
			}

		}
		catch (SwitchgearFUN::Wyjatki::PodamaCyfra) {
			break;
		}
	}



	if (k == 49) {
		Switchgear baza(3432);
		baza.Server(10);
	}
	else {
		SwitchgearClient kbaza(3432);
	//	kbaza.Client("192.168.215.20");
//		kbaza.Client("169.254.21.220");
		kbaza.Client("25.128.73.116");
	}
	/*

	if (k == 1)
		PobieraniePlikuMP3(4314, "porn.mp3");
	else
	{
		//192.168.215.20
		MP3Trasmition strumien("porn.pcm", "192.168.215.20", 4314);
		strumien.Transmition();
		cout << "Poszlo" << endl;
	}
	*/

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



void _Siec::PobieraniePlikuMP3(int port, string nazwa) {
	ComProtocolListen strumien(port);
	strumien.Connection();
	cout << "connect" << endl;
	Package* paczki = strumien.Listen();
	string porn = "";
	if (!paczki->err) {
		uint64_t fd = ActualTime();
		int k, p;
		for (k = 0, p = 1; paczki[k].buff != NULL; k++, p++) {
			porn += string(paczki[k].buff, paczki[k].ssize);
			if (paczki[k].num != p) {
				cout << "Brak paczki:\t" << p << "Nadeszla:\t" << paczki[k].num << endl;
			}
		}
		cout << "\nCzas wysylania:\t" << fd - paczki[0].date << endl;

		RAWFile<const char> strumien;
		strumien.Zapis(nazwa, porn.c_str(), porn.length());
	}
	strumien.Disconection();
}
