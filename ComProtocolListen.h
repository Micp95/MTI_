#pragma once
#ifndef COMPROTOCOLLISTEN_H
#define COMPROTOCOLLISTEN_H


#include <string>
#include <iostream>
#include <winsock.h> 
#include "ComProtocol.h"

using namespace std;


class ComProtocolListen: public ComProtocol
{
public:
	ComProtocolListen(int port);
	~ComProtocolListen();

	Package* Listen();
	virtual void Connection();
	virtual void Disconection();


	Package* Division(string& buff);
	sockaddr_in their_addr;		// informacja o adresie osoby ³¹cz¹cej siê
private:
	char* buffer;
	long bsize;

	int new_fd;					//Dystrybutor gniazda nowego polaczenia



};



#endif