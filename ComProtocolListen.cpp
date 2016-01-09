#include "ComProtocol.h"
#include "ComProtocolListen.h"

#include <string>
#include <iostream>
#include <winsock.h> 
#include <cstdint>

using namespace std;

ComProtocolListen::ComProtocolListen(int port, bool DD): ComProtocol("",port,DD),buffer(0),bsize(0)
{
	bsize = 1024;
	buffer = new char[bsize];
	new_fd = 0;
	firsl = true;
}

ComProtocolListen::~ComProtocolListen()
{
	//Zamkniecie polaczenia
	if (buffer != NULL)
		delete[] buffer;

}

Package* ComProtocolListen::Listen()
{
	//Package ret;
	disconet = false;

	if (err != 0) {
		Package* ret = new Package();
		ret->err = err;
		throw SwitchgearFUN::Wyjatki::ZamkniecieStrumienia();
	//	return ret;
	}
	string acum,tmp,kod,war="END";
	int size;
	while (true) {
		if ((size = recv(new_fd, buffer, bsize - 1, 0)) == -1) {
			Package* ret2 = new Package();
			err = 6;
			cout << errno<<endl;
			ret2->err = err;
			return ret2;
		}
		else if (!size) {
			disconet = true;
			break;
		}

		tmp =  string(buffer, size);
		kod = tmp.substr(size - 3);
		if (kod == war) {
			acum += string(buffer, size-3);
			break;
		}
		else
			acum += tmp;
	}
	
	
	//ret.size = size;
	//ret.buff = buffer;
	if (!DontDisconetion)
		Disconection();
	Package* ret = Division(acum);

	return ret;
}
void ComProtocolListen::ClearPort() {
	stats = 1;
	sockaddr_in tmp = their_addr;
	int tmp2 = new_fd;



	while (true ) {
		Connection();
		if (stats == 2)
			break;
	}
	their_addr = tmp;
	new_fd = tmp2;
}

void ComProtocolListen::Connection()
{
	int sin_size;
	int nnew_fd;
	new_fd = 0;

 	if (firsl) {
		if (bind(sockfd, (sockaddr *)& my_addr, sizeof(sockaddr)) == -1) {
			err = 3;
			stats = 2;
			return;
		}


	}


	//cout << "Moje IP:\t" << inet_ntoa(my_addr.sin_addr) << endl;

	if (listen(sockfd, 10) == -1) {
		err = 4;
		return;
	}

	sin_size = sizeof(sockaddr_in);
	nnew_fd = accept(sockfd, (sockaddr *)& their_addr, &sin_size);
	stats = 1;

	if (new_fd == -1) {
		err = 5;
		return;
	}
	else if (nnew_fd != new_fd)
		new_fd = nnew_fd;

	//closesocket(sockfd);
	firsl = false;
}

void ComProtocolListen::Disconection()
{
	if ( new_fd)
		closesocket(new_fd);
	//ComProtocol::Disconection();
}

Package * ComProtocolListen::Division(string & buff)
{
	int listleng = 0;

	ListP<Package*> lista;
	ListP<Package*>* wsk = &lista;


	lista.acum = new Package();
	Package* pack = lista.acum;
	long pos = 0;
	long max = buff.size();

	uint64_t time, pot;
	int k;

	while (pos < max) {
		if (buff[pos++] == 'M' && buff[pos++] == 'P') {
			pack->num = uint8_t(buff[pos + 1]) + 256 * uint8_t(buff[pos]);//Pobranie numeru pakietu
			pos += 2;

			pack->date = 0;
			pot = 1;			//Wczytanie czasu
			for (k = pos + 7; k >= pos; k--){
				pack->date +=  uint8_t(buff[k]) * pot;
				pot *= 256;
			}
			
			pos += 8;			//Wczytanie rozmiaru paczki
			pack->ssize = (uint8_t)buff[pos++];

			pack->buff = new char[pack->ssize];
			for (k = 0; k < pack->ssize; k++)
				pack->buff[k] = buff[pos + k];
			
			pos += pack->ssize;	//Przeskoczenie na koniec paczki
			

			//Tworzenie nowej paczki do zwrotu
			wsk->next = new ListP<Package*>;
			wsk = wsk->next;
			wsk->acum = new Package();
			pack = wsk->acum;

			listleng++;
		}

	}

	wsk = &lista;
	Package* ret = new Package[listleng+1];
	for (int k = 0; k < listleng; k++) {
		ret[k] = *wsk->acum;
		wsk = wsk->next;
	}

	//ret[listleng] = *(new Package);
	return ret;
}

