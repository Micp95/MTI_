#pragma once
#ifndef COMPROTOCOL_H
#define COMPROTOCOL_H

#include <string>
#include <iostream>
#include <winsock.h> 
#include <cstdint>
#include "Switchgear.h"
#include "SwitchgearClient.h"

using namespace std;

struct Package
{
	char* buff;
	long size;
	string kto;
	int err;

	uint16_t num;
	uint64_t date;
	uint8_t ssize;

	Package():buff(0),size(0),kto(""),err(0) {}
};

template <class typ>
struct ListP{
	typ acum;
	ListP* next;
	ListP() { next = NULL; }
	~ListP() { 
		if (next) delete next; 
		if (acum) delete acum;
	}
};


class ComProtocol
{
public:
	ComProtocol();
	ComProtocol(string ip, int port, bool DD = false);
	~ComProtocol();

	//int Send(char* buffer, long size);
	virtual void Connection() = 0;
	virtual void Disconection();

protected:
	void Constr(string ip, int port);

	int sockfd;				//Dystrybutor gniazda
	sockaddr_in my_addr;	//Przechowywany adres docelowy

	int HeaderSize;
	int MaxSize;


	int err;
	bool DontDisconetion;
private:
	static int strums;

	friend Switchgear;
	friend SwitchgearClient;
};




#endif