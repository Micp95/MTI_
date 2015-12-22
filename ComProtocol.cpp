#include "ComProtocol.h"

#include <string>
#include <iostream>
#include <winsock.h> 

using namespace std;


int ComProtocol::strums = 0;

ComProtocol::ComProtocol()
{
	Constr("", 0);
}

ComProtocol::ComProtocol(string ip, int port, bool DD)
{
	DontDisconetion = DD;
	Constr(ip, port);
}

ComProtocol::~ComProtocol()
{
	strums--;
	if (!strums) {			//Zamkniece biblioteki
		WSACleanup();
	}
	Disconection();
}

void ComProtocol::Disconection()
{
	if (sockfd)
		closesocket(sockfd);
}

void ComProtocol::Constr(string ip, int port)	//Otworzenie biblioteki
{
	HeaderSize = 13;
	MaxSize = 255;

	strums++;
	sockfd = 0;
	WSAData wsaData;
	err = 0;
	if (WSAStartup(MAKEWORD(1, 1), &(wsaData)) != 0){
		cout << "\n\nNie udana proba otworzenia biblioteki!" << endl;
		err = 1;
		return;
	}

	if (port != 0 ){

		sockfd = socket(AF_INET, SOCK_STREAM, 0); // zrób sprawdzanie b³êdów!
		if (sockfd == -1) {
			err = 2;
			return;
		}

		my_addr.sin_family = AF_INET; // host byte order
		my_addr.sin_port = htons(port); // short, network byte order

		if (ip != "")
			my_addr.sin_addr.s_addr = inet_addr(ip.c_str());
		else
			my_addr.sin_addr.s_addr = htonl( INADDR_ANY );
		memset(&(my_addr.sin_zero), '\0', 8); // wyzeruj resztê struktury
	}

}
