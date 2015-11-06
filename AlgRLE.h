#ifndef ALGRLE_H
#define ALGRLE_H

#include <string>
#include "Koder.h"


using namespace std;

namespace _ARLE
{
	class ARLE: public Koder
	{
		string tekst;
		string zakodowany;
	public:
		ARLE();
		~ARLE();
		virtual string Koduj(string);
		virtual string Dekoduj(string = "");
	};
}

#endif

