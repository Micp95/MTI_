#ifndef KOMPRESJE_H
#define KOMPRESJE_H

#include "Spis.h"

using namespace std;


namespace _Kompresja{

	int PlatformaTestowaOgolna();

	int PlatformaTestowaMichal();
	int PlatformaTestowaKasia();
	int PlatformaTestowaMarysia();


	long long WykonajAlgorytm(koder select, string plik, bool BinWczyt, bool BinZapis, int bufor = 4);
	void WykonajTestAlgorytmu(koder select, int repeat);
	
}

#endif