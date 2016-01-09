#include "Switchgear.h"
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

using namespace std;

namespace SwitchgearFUN {


	//Nasluchujacy daje znak do zamkniecia watku - informacje, ze dotarla cala paczka!!

	DWORD WINAPI ListenClient(LPVOID lpParam) {
		Switchgear* baza = (Switchgear*)lpParam;


		HANDLE* UsersThread = new HANDLE[baza->MAX_USERS];
		DWORD* UsersDate= new DWORD[baza->MAX_USERS];




		ComProtocolListen nasl(baza->port,true);

		bool cont = false;
		while (true) {
			if (baza->endflag)
				break;

			nasl.Connection();
			if (nasl.new_fd == 0)
				continue;


			for (int k = 0; k < baza->MAX_USERS; k++) {
				if (baza->UsersFD[k] == nasl.new_fd) {
					cont = true;
					break;
				}
			}



			if (cont) {
				cont = false;
				continue;
			}

			for (int k = 0; k < baza->MAX_USERS; k++) {
				if (baza->UsersStatus[k] == -1 ) { //Pusty - dodajemy!!
					baza->UsersStatus[k] = 0;
					baza->UsersAdres[k] = nasl.their_addr;
					baza->UsersFD[k] = nasl.new_fd;

					baza->lastAdd = k;
					//Otworzenie watku dla obslugi klienta
					UsersThread[k] = CreateThread(NULL, 0, SwitchgearFUN::HandlingClient,(void*)baza, 0, &UsersDate[k]);

					break;			//Powrot do nasluchiwania
				}
			}
		}


		return 0;
	}

	DWORD WINAPI HandlingClient(LPVOID lpParam) {
		Switchgear* baza = (Switchgear*)lpParam;
		int MyUser = baza->lastAdd;
		baza->lastAdd = -1;

		ComProtocolListen nasl(baza->port,true);

		nasl.new_fd = baza->UsersFD[MyUser];
		nasl.their_addr = baza->UsersAdres[MyUser];

		Package* paczki;

		string buffPaczka = "";
		while (true) { //nieskonczona - gdy mamy uzytkownika

			if (baza->endflag)
				break;


			nasl.SetErr(0);
			paczki = nasl.Listen();

			if (nasl.disconet) {//Uzytkownik zamknol strumien
				nasl.Disconection();
				baza->UsersStatus[MyUser] = -1;
			//	baza->UsersFD[MyUser] = 0;
				break;
			}

			//Sklejenie pakietow
			for (int k = 0; paczki[k].buff != NULL; k++)
				buffPaczka += string(paczki[k].buff, paczki[k].ssize);

 
			while (baza->UsersStatus[MyUser] == 1)//Opoznienie - zamrozenie watku - czekanie az serwer odbierze stara paczke
				Sleep(100);
	
			if (buffPaczka == "q") {
				nasl.Disconection();
			//	baza->UsersStatus[MyUser] = -1;
		//		baza->UsersFD[MyUser] = 0;
			//	baza->lasdel = MyUser;
				break;
			}


			baza->UserPack[MyUser] = buffPaczka;
			baza->UsersStatus[MyUser] = 1;


			buffPaczka = "";
		}




		Sleep(1000);

		closesocket(baza->UsersFD[MyUser]);

		baza->UsersFD[MyUser] = 0;
		baza->UsersStatus[MyUser] = -1;


		return 0;
	}



	//Client
	DWORD WINAPI ListenServer(LPVOID lpParam) {//Funkcja do nasluchiwania serera (zmiana!!)


		SwitchgearClient* baza = (SwitchgearClient*)lpParam;

		ComProtocolListen nasl(baza->port,true);
		nasl.new_fd = baza->ServerFD;
		nasl.their_addr = baza->ServerAdres;


		Package* paczki;
		string buffPaczka = "";

		while (true) {

			if (baza->endflag)
				break;

			try {
				paczki = nasl.Listen();
			}
			catch (SwitchgearFUN::Wyjatki::ZamkniecieStrumienia) {
				nasl.Disconection();
				baza->endflag = true;
				break;
			}

			if (nasl.disconet) {//zamkniecie strumienia
				nasl.Disconection();
				break;
			}

			//Sklejenie pakietow
			for (int k = 0; paczki[k].buff != NULL; k++)
				buffPaczka += string(paczki[k].buff, paczki[k].ssize);

			baza->ActualScreen(buffPaczka);
			baza->status = 1;
			buffPaczka = "";
		}


		return 0;
	}
}

void Switchgear::Server(int max) {
	MAX_USERS = max;
	lasdel = -1;



	//PMYDATA pDataArray[MAX_THREADS];
	DWORD*   dwThreadIdArray = new DWORD[MAX_THREADS];
	HANDLE*  hThreadArray= new HANDLE[MAX_THREADS];


	HANDLE  Listner;
	DWORD  dwListner;

	UsersStatus = new int[MAX_USERS];
	UsersFD = new int[MAX_USERS];
	UsersAdres = new sockaddr_in[MAX_USERS];
	UserPack = new string[MAX_USERS];

	for (int k = 0; k < MAX_USERS; k++)
		UsersStatus[k] = -1;

	Listner = CreateThread(NULL,0, SwitchgearFUN::ListenClient,(void*)this,0,&dwListner);
	ComProtocolSend Client(port,"",true);

	int k, p;
	char znak = 0;
	int ilosc = 0;
	char wybor = 0;
	while (true) {
		for (k = 0; k < MAX_USERS; k++)
			cout << UsersStatus[k] << " ";
		cout << endl;

		ilosc = 0;
		for (k = 0; k < MAX_USERS; k++) {
			if (UsersStatus[k] == 1) {//uzytkownik cos wyslal
				for (p = 0; p < MAX_USERS; p++) {
					if (UsersStatus[p] != -1 ) {
						Client.sockfd = UsersFD[p];
						Client.my_addr = UsersAdres[p];

						Client.Send(UserPack[k].c_str(), UserPack[k].length());
						UsersStatus[p] = 0;
					}
				}
			}

			if (UsersStatus[k] != -1)
				ilosc++;
		}
		system("cls");
		cout << "Ilosc uzytkownikow :\t" << ilosc << endl;

		while (1)
		{
			if (kbhit()) {
				wybor = getch();
				if (wybor == 'q')
					break;
			}
			else
				break;
		}

		if (wybor == 'q') {
			endflag = true;
			break;
		}
		Sleep(1000);

	}
	endflag = true;
	Sleep(100);
}
