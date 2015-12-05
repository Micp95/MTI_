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


using namespace std;
using namespace _MAIN;


int _Siec::PlatformaTestowaOgolna(){

	cout << "Siec." << endl;


	return 0;
}




int _Siec::PlatformaTestowaMichal(){

	cout << "1.Sluchanie\n2.Wysylanie\n\n";
	int k;
	cin >> k;

	if (k == 1)
		PobieraniePlikuMP3(4314, "porn.mp3");
	else
	{
		//192.168.215.20
		MP3Trasmition strumien("porn.pcm", "10.22.115.61", 4314);
		strumien.Transmition();
		cout << "Poszlo" << endl;
	}

	return 0;
}

int _Siec::PlatformaTestowaMarysia(){

	return 0;
}

int _Siec::PlatformaTestowaKasia(){

	cout << "Siec!" << endl;
	//TCPServer server("192.168.1.5", 54345);
	TCPClient client("192.168.1.5", 54345);
	
	return 0;
}





void _Siec::PobieraniePlikuMP3(int port, string nazwa){
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
		cout << "\nCzas wysylania:\t" << fd - paczki[k - 1].date << endl;

		RAWFile<const char> strumien;
		strumien.Zapis(nazwa, porn.c_str(), porn.length());
	}
	strumien.Disconection();
}

