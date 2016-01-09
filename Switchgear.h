#ifndef SWITCHGEAR_H
#define SWITCHGEAR_H
#pragma once
#include <string>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>


using namespace std;

namespace SwitchgearFUN {
	DWORD WINAPI ListenClient(LPVOID lpParam);
	DWORD WINAPI HandlingClient(LPVOID lpParam);
	DWORD WINAPI ListenServer(LPVOID lpParam);

	class Wyjatki {
	public:
		class Przerwane {};
		class BrakCyfry {};
		class PodamaCyfra {};
		class ZamkniecieStrumienia {};

	};
}


class Switchgear
{
public:
	Switchgear(int port) :port(port), MAX_THREADS(20),endflag(false){  }
	void Server(int max);
private:
	int port;
	int MAX_THREADS;


	int MAX_USERS;
	int* UsersStatus;
	sockaddr_in* UsersAdres;
	int* UsersFD;
	int lastAdd;
	string* UserPack;

	int lasdel;

protected:
	bool endflag;


	friend DWORD WINAPI SwitchgearFUN::ListenClient(LPVOID lpParam);
	friend DWORD WINAPI SwitchgearFUN::HandlingClient(LPVOID lpParam);
	friend DWORD WINAPI SwitchgearFUN::ListenServer(LPVOID lpParam);
};



#endif