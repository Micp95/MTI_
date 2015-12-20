#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <stdint.h> // GG: ustandaryzowane typy ca³kowite
#include <cstdio>
#include <WinSock2.h>
#include <Windows.h>

#include"UDP_server.h"
#include "StopWatch.h"
#include"RAWFile.h"

using namespace std;

ServerUDP::ServerUDP(int localPort) {
	/*	1. inicjalizowanie winsocka
	2. tworzenie socketu
	3. bind socket
	4. czekanie na klienta
	5. otwarcie polaczenia
	6. nadawanie
	7. zamkniecie
	*/

	SOCKET s;
	WSADATA w;
	struct sockaddr_in binding_rules, s_client;

	struct sockaddr_in clients[4];
	//	IN_ADDR adresses[4];
	//	USHORT ports[4];
	int active[5] = { 0, 0, 0, 0, 0 };
	uint32_t transsmisionCounter[4] = { 0, 0, 0, 0 };
//	uint32_t numberOfFrames = 100;	//testowanie 100 ramek

	//	int clientsCounter = 0;

	cout << "\nServer: Initialising Winsock..." << endl;
	if (WSAStartup(MAKEWORD(2, 2), &w) != NO_ERROR) {
		cout << "Failed. Error Code : " << WSAGetLastError() << endl;
		exit(EXIT_FAILURE);
	}

	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket : " << WSAGetLastError() << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	DWORD nonBlocking = 1;
	if (ioctlsocket(s, FIONBIO, &nonBlocking) != 0)
	{
		printf("failed to set non-blocking socket\n");
		exit(EXIT_FAILURE);
	}

	//Prepare the sockaddr_in structure
	//ZeroMemory(&server, sizeof(server));

	binding_rules.sin_family = AF_INET;						//AF_INET - IPv4, AF_INET6 - IPv6
	binding_rules.sin_addr.s_addr = INADDR_ANY;				//przyjmuje wszystkie odwolania
															//server.sin_addr.s_addr = inet_addr("127.0.0.1");	//przyjmuje tylko z tego komputera
	binding_rules.sin_port = htons(localPort);

	if (bind(s, (struct sockaddr *)&binding_rules, sizeof(binding_rules)) == SOCKET_ERROR) {
		cout << "Bind failed with error code : " << WSAGetLastError() << endl;
		exit(EXIT_FAILURE);
	}
	
		//otwieram plik do przeslania
		RAWFile<char> rawToSend;
		char* toSend = rawToSend.Wczytaj("C:\\Users\\Marysia\\Desktop\\looking1.wav");
		long sizeOfFileToSend = rawToSend.GetSize();
		int fileIterator = 0;
				int sizeOfPackage = 256;
				int sizeOfHeader = 8;
				uint32_t numberOfFrames = sizeOfFileToSend / (sizeOfPackage - sizeOfHeader);
	
	int work = 1;
	int rozmAddr = sizeof(s_client);
	cout << "Waiting for connection." << endl;
	while (work) {

		// nieblokujace
		int count = recvfrom(s, inBuffer, 255, 0, (struct sockaddr *) &s_client, &rozmAddr);	//odbieram cala ramke udp
		if (count > 0) {
			cout << endl << "Received packet from : " << inet_ntoa(s_client.sin_addr) << " : " << ntohs(s_client.sin_port) << endl;
		}
	
		int idx = 0;
		if (count == 17) {
			//if( spr_poprawnosci_ramki)
			cout << "Client connected. ( " << inet_ntoa(s_client.sin_addr) << " )" << endl;


			while (active[idx] != 0) {
				idx++;
			}

			if (idx == 5)
				cout << "przektoczony limit klientow";
			else {
				clients[idx].sin_addr = s_client.sin_addr;

				clients[idx].sin_family = s_client.sin_family;
				clients[idx].sin_port = s_client.sin_port;

				active[idx] = 1;
				transsmisionCounter[idx] = 0;
			}
		}

		for (int i = 0;i < 4; i++) {
			if (active[i] == 1) {

				int offset = 0;
				char *frame = new char[256];
				int frameLength = 256;
				int slen = sizeof(clients[i]);
				if (transsmisionCounter[i] == 0) {
					*(uint32_t *)(frame + offset) = numberOfFrames;
					offset += sizeof(uint32_t);
				}
				//else {

					*(uint32_t *)(frame + offset) = transsmisionCounter[i];
					offset += sizeof(uint32_t);
					// przepisanie z pliku do ramek
					for (int iner = offset; iner < 256 - (2*sizeof(uint32_t)); iner++) {
						if (fileIterator < sizeOfFileToSend) {
							frame[iner] = toSend[fileIterator++];
						}
						else
							frame[iner] = 0;
					}
				//}
				sendto(s, frame, frameLength, 0, (struct sockaddr *) &clients[i], slen);

				//	cout << transsmisionCounter[i] << " ";

				transsmisionCounter[i]++;
				// if(transsmisionCounter[i]==70)transsmisionCounter[i]++; // sztuczny blad

				if (transsmisionCounter[i] > numberOfFrames) {
					active[i] = 0;
				}

			}
		}

		if (1 == 0) {

			int offset = 0;

			uint16_t frameNumber = *(uint16_t *)(inBuffer + offset) = 1; 
			offset += sizeof(uint16_t);

			uint64_t serverTime = *(uint64_t *)(inBuffer + offset) = 1000000000; 
			offset += sizeof(uint64_t);

			uint8_t dataLength = *(uint8_t *)(inBuffer + offset);

															
			for (int offset = 0, left = dataLength; offset < dataLength;) 
			{
				int count = recvfrom(s, inBuffer + offset, left, 0, (struct sockaddr *) &s_client, &rozmAddr); 

																											  

				if (count == SOCKET_ERROR) {
					closesocket(s);
					WSACleanup();
					return; 
				}

				offset = count;
				left -= count;
			}

			for (int i = 0; i < dataLength; ++i)
				cout << inBuffer[i];

			cout << endl;
		}

	}

	cout << "Server die." << endl;

	closesocket(s);
	WSACleanup();

}