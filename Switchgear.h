#ifndef SWITCHGEAR_H
#define SWITCHGEAR_H
#pragma once
#include <string>
using namespace std;

class Switchgear
{
public:
	Switchgear(int port) :port(port) {}
	void Server();
	void Client(string ip);
private:
	int port;
};



#endif