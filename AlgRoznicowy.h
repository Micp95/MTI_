#ifndef ALGROZNICOWY_H
#define ALGROZNICOWY_H

#include <string>
#include <iostream>
#include "Koder.h"

using namespace std;

namespace _ARoznicowy{

	class ARoznicowy: public Koder
	{
	public:
		ARoznicowy(int stopien = 1);
		~ARoznicowy();

		virtual string Koduj(string tekst);
		virtual string Dekoduj(string tekst = "");

		virtual void Clear();

		string Podglad();
	private:
		string tekst;
		string zakodowany;
		int stopien;

		int* roznice;
		int RozniceSize;

		int* poczatek;			//Przechowane poczatki

		int* KonwersjaLiczby(string tekst);
		string KonwersaTekst(int* liczby, int size);
		void GenerujTablice(string tresc);


		//Wsparcie binarne
		int maksRoznica();
		string KodBin();
		int dlslow;				//Dlugosc zapisywanych slow

	};
}

#endif