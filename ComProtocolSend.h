#pragma once
#ifndef COMPROTOCOLSEND_H
#define COMPROTOCOLSEND_H


#include <string>
#include <iostream>
#include <winsock.h> 
#include "ComProtocol.h"
#include "Spis.h"
#include <cstdint>

using namespace std;


class ComProtocolSend: public ComProtocol
{
public:
	ComProtocolSend(int port, string ip);
	~ComProtocolSend();

	virtual void Connection();
	virtual void Disconection() {}
	int Send(const char* buffer, long size);

	void WaitForSendingAndEnding();
	Package* Division(const char* buff, long size);
private:
	char* CreateHeader(uint16_t nb, uint8_t size);

	template <class typ>
	char* TypToChar(typ& value);
	void Coppy(char*A,const char*B, long startA,long startB, long size);
	int SendPackage(Package*newpack);
	uint16_t countPack;
};




template<class typ>
char   * ComProtocolSend::TypToChar(typ & value)
{
	int size = sizeof(typ);
	char* retry = new char[size];

	retry[size-1] = value & 0xFF;
	for (int k = 0, p = size - 2; k < size-1; k++, p--) {
		retry[p] = value >> 8;
		value = value >> 8;
	}

	return retry;
}


#endif
