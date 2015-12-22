#include "SwitchgearClient.h"
#include <iostream>
#include <string>
#include <winsock.h> 
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include <conio.h>

#include "ComProtocol.h"
#include "ComProtocolSend.h"
#include "ComProtocolListen.h"

#pragma warning(disable:4996)

void SwitchgearClient::Client(string ip) {

	HANDLE  Listner;
	DWORD  dwListner;

	ComProtocolSend Server(port, ip, true);
	Server.Connection();
	if (Server.err != 0)
		return;
	
	ServerAdres = Server.my_addr;
	ServerFD = Server.sockfd;
	
	Listner = CreateThread(NULL, 0, SwitchgearFUN::ListenServer, (void*)this, 0, &dwListner);

	string tmp;

	char wybor;
	bool disc = false;

	cout << "What is your name?" << endl;
	string name;
	cin >> name;
	cin.ignore();

	ref = true;
	while (true) {
		if (ref) {
			DrowScreen();
			ref = false;
		}

		//Sprawdzenie co w buforze
		while (1)
		{
			if (kbhit()) {
				ref = true;
				wybor = getch();
				if (wybor == '\r') {
					if (keybuff == "q") {//quit
						Server.Send("q", 1);
						Server.WaitForSendingAndEnding();
						disc = true;
						break;
					}
					keybuff = name + ":\t" + keybuff;
					Server.Send(keybuff.c_str(), keybuff.length());
					keybuff = "";
				}
				else if (wybor == 8) //backspace
					keybuff = keybuff.substr(keybuff.length() - 1);
				else
					keybuff += wybor;
			}
			else
				break;
		}

		if (disc) {
			CloseHandle(Listner);
			break;
		}

		Sleep(10);
	}
	endflag = true;
	Sleep(100);
}

void SwitchgearClient::ActualScreen(string text) {
	chat += "\t" + text;
	chat += "\n";
	ref = true;
}
void SwitchgearClient::DrowScreen() {
	system("cls");
	cout << "\t\t------Chat------\t\t\tv0.2\n\n" << endl;
	cout << chat<<endl;

	cout << "\n\n\t\tClick q to disconnect" << endl;
	cout << "\t\t:" << keybuff << endl;
}