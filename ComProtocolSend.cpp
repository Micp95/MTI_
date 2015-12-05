#include "ComProtocol.h"
#include "ComProtocolSend.h"

#include <string>
#include <iostream>
#include <winsock.h> 
#include <time.h>
#include <ctime>
#include "Spis.h"

using namespace _MAIN;
using namespace std;

ComProtocolSend::ComProtocolSend(int port, string ip):ComProtocol(ip, port)
{

}

ComProtocolSend::~ComProtocolSend()
{


}

void ComProtocolSend::Connection()
{
	if (connect(sockfd, (sockaddr *) & my_addr, sizeof(sockaddr)) == -1) {
		err = 7;
		return;
	}
	countPack = 0;

}

int ComProtocolSend::Send(const char * buffer, long size)
{

	Package * pack = Division(buffer, size);

	int tmp;
	for (int k = 0; pack[k].buff != NULL; k++) {
		tmp = SendPackage(&pack[k]);
		if (tmp != pack[k].size)
			cout << "Paczka:\t" << k << "\tnie dotarla!" << endl;
	}



	return 0;
}
void ComProtocolSend::WaitForSendingAndEnding() {
	Package* last = new Package;
	last->buff = "END";
	last->size = 3;

	SendPackage(last);


	//Czekanie az wszystko dojdzie!
	char* te = new char[10];
	while (recv(sockfd, te, 9, 0)>0) { }
}

int ComProtocolSend::SendPackage(Package * newpack)
{
	int total = 0; // ile bajtów ju¿ wys³aliœmy
	int bytesleft = newpack->size; // ile jeszcze zosta³o do wys³ania
	int n;

	while (total < newpack->size) {
		n = send(sockfd, newpack->buff, newpack->size, 0);
		if (n == -1) { break; }
		total += n;
		bytesleft -= n;
	}

	return total; // zwróæ iloœæ faktycznie wys³anych bajtów
}


Package * ComProtocolSend::Division(const char * buff, long size)
{
	long packsize = size / MaxSize,actualy = 0;
	packsize++;

	Package* retry = new Package[packsize + 1];

	char* tmp;
	long pos, posG = 0;
	uint16_t counter = 0;
	//Tworzenie pelnych paczek
	for (; counter < packsize-1; counter++) {
		pos = 0;
		retry[counter].buff = new char[MaxSize + HeaderSize];
		tmp = CreateHeader(countPack++, MaxSize);
		Coppy(retry[counter].buff, tmp, pos, 0, HeaderSize);
		pos += 13;
		Coppy(retry[counter].buff, buff, pos, posG, MaxSize);
		posG += MaxSize;
		retry[counter].size = MaxSize + HeaderSize;
		delete[] tmp;
	}

	//Dodanie niepelnej paczki
	pos = 0;
	retry[packsize - 1].buff = new char[(size - posG) + HeaderSize];

	tmp = CreateHeader(countPack++,(size - posG));
	Coppy(retry[packsize - 1].buff, tmp, pos, 0, HeaderSize);
	pos += 13;
	Coppy(retry[packsize - 1].buff, buff, pos, posG, (size - posG));
	retry[counter].size = (size - posG) + HeaderSize;
	delete[] tmp;

	return retry;
}

char * ComProtocolSend::CreateHeader(uint16_t nb, uint8_t size)
{
	char* header = new char[HeaderSize];//13
	nb++;
	//Typ protokolu
	header[0] = 'M';
	header[1] = 'P';

	char* tmp;
	int actualy = 2, count;
	//Dodanie numeru pakietu
	tmp = TypToChar(nb);
	for (count = 0; count < 2; count++)
		header[actualy++] = tmp[count];

	//Dodanie czasu nadania
	uint64_t time = ActualTime();
	tmp = TypToChar(time);
	for (count = 0; count < 8; count++)
		header[actualy++] = tmp[count];

	//Dodanie rozmiaru
	tmp = TypToChar(size);
	header[actualy++] = tmp[0];

	return header;
}

void ComProtocolSend::Coppy(char*A, const char*B, long startA, long startB, long size){
	long end = startA + size;
	for (; startA < end; )
		A[startA++] = B[startB++];
}
