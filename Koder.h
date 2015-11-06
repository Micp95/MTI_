#ifndef KODER_H
#define KODER_H

#include <string>
#include <iostream>

using namespace std;

class Koder{
public:
	virtual string Koduj(string tresc);
	virtual string Dekoduj(string tresc);


};



#endif