#ifndef ALGRLE_H
#define ALGRLE_H

#include <string>

using namespace std;

namespace _ARLE
{
	class ARLE
	{
		string tekst;
		string zakodowany;
	public:
		ARLE();
		~ARLE();
		string Koduj(string);
		string Dekoduj(string = "");
	};
}

#endif

