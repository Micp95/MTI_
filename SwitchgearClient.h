#pragma once
#ifndef SWITCHGEARCLIENT_H
#define SWITCHGEARCLIENT_H


#include <string>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>


using namespace std;

namespace SwitchgearFUN {
	DWORD WINAPI ListenClient(LPVOID lpParam);
	DWORD WINAPI HandlingClient(LPVOID lpParam);
	DWORD WINAPI ListenServer(LPVOID lpParam);
}


class SwitchgearClient
{
public:
	SwitchgearClient(int port) :port(port), endflag(false){}
	void Client(string ip);


private:
	int port;
	string ipserver;

	sockaddr_in ServerAdres;
	int ServerFD;

	int status;
	string paczka;


	string chat;
	string keybuff;



	void ActualScreen(string text);
	void DrowScreen();
	bool ref;


	friend DWORD WINAPI SwitchgearFUN::ListenServer(LPVOID lpParam);

protected:
	bool endflag;
};



#endif