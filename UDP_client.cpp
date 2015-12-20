#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include <cstdio>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include<sstream>
#include <stdint.h> // GG: ustandaryzowane typy ca³kowite

#include"UDP_client.h"
#include "StopWatch.h"

using namespace std;

ClientUDP::ClientUDP(int localPort, const char * IP, int remotePort) {
	/*	1. inicjowanie winsocka
	2. tworzenie socketu
	3. polaczenie z serwerem - wyslanie komuikatu inicjujacego
	4. odbieranie danych
	5. rozlaczenie
	*/
	//struct sockaddr_in server, client;
	struct sockaddr_in server_address;
	WSADATA w;
	SOCKET s;


	cout << "\nClient: Initialising Winsock..." << endl;
	if (WSAStartup(MAKEWORD(2, 2), &w) != NO_ERROR) {
		cout << "Failed. Error Code : " << WSAGetLastError() << endl;
		exit(EXIT_FAILURE);
	}


	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket : " << WSAGetLastError() << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	server_address.sin_family = AF_INET;					//AF_INET - IPv4, AF_INET6 - IPv6
	server_address.sin_addr.s_addr = inet_addr(IP);			//przyjmuje tylko z tego komputera
	server_address.sin_port = htons(remotePort);

	//cout << "Press key." << endl;
	int stop;
	//cin >> stop;

	char *data = "start";
	int dataLength = strlen(data) + 1;


	char *frame = new char[7 + dataLength];
	int offset = 0;

	*(uint16_t *)(frame + offset) = 1; // numer ramki
	offset += sizeof(uint16_t);

	*(uint64_t *)(frame + offset) = 1000000000; // czas nadania pakietu // nalezy pobrac aktualny czas systemowy najlepiej w mili lub nano sekundach
	offset += sizeof(uint64_t);

	*(uint8_t *)(frame + offset) = dataLength; // ustawiamy informacje o rozmiarze wysylanych danych
	offset += sizeof(uint8_t);

	for (int i = 0; i < dataLength; i++) {
		*(uint8_t *)(frame + offset) = data[i];
		offset += sizeof(uint8_t);
	}

	int sizeOfLength = sizeof(frame);
	int frameLength = offset;
	cout << frameLength;

	int slen = sizeof(server_address); 
	cout << "\nClient: Sending messages." << endl;


	fstream file;
	stringstream toMakeName;
	string tmp;
	toMakeName << localPort;
	toMakeName >> tmp;

	file.open("plik_" + tmp + ".txt", ios::app); // +local port
	file << "me: " << localPort << "\tfrom server - " << inet_ntoa(server_address.sin_addr) << " : " << ntohs(server_address.sin_port) << "\n";

	//wysylam jedna ramke udp
	sendto(s, frame, frameLength, 0, (struct sockaddr *) &server_address, slen);
	StopWatch stopWatch;// = new StopWatch;
	stopWatch.Start();

	int work = 1;
	uint32_t iler = 0, licznikr = 0;

	while (work) {
		// blokujace
		int count = recvfrom(s, inBuffer, 256, 0, (struct sockaddr *) &server_address, &slen);


		if (count > 0) {
			//	cout << (uint32_t )inBuffer[0] << " ";
//			file << (uint32_t)inBuffer[0] << "\t" << stopWatch.ActMiliSeconds() << "\n";	//czas dojscia poszczegolnej paczki

			for (int iter = 4; iter < 256; iter++) {
				file << inBuffer[iter];
			}
			file << "\n";
			if (licznikr == 0)
			{
				iler = (uint32_t)inBuffer[0];
			}
			else
			{
				if (licznikr != (uint32_t)inBuffer[0]) {
					//cout << "ERROR " << "\n";
				}
				if ((uint32_t)inBuffer[0] == iler) work = 0;
			}
			licznikr++;
		}

		if (licznikr > iler) work = 0;

		//cin >> stop;
		//if (stop == 0) work = 0;
	}

	stopWatch.Stop();
	file.close();
	cout << "Client receive data." << endl;
	cin >> work;
	closesocket(s);
	WSACleanup();
}
