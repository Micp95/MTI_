#pragma once
#ifndef MP3TRANSMITION_H
#define MP3TRANSMITION_H

#include <string>

using namespace std;

class MP3Trasmition
{
public:
	MP3Trasmition(string file, string ip, int port):File(file),IP(ip),port(port) {}	
	~MP3Trasmition();
	void Transmition();
private:
	string File;
	string IP;
	int port;
};





#endif