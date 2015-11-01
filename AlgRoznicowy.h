#ifndef ALGROZNICOWY_H
#define ALGROZNICOWY_H

#include <string>
#include <iostream>


using namespace std;

namespace _ARoznicowy{

	class ARoznicowy
	{
	public:
		ARoznicowy(int stopien = 1);
		~ARoznicowy();

		string Koduj(string& tekst);
		string Dekoduj(string tekst = "");

		string Podglad();
	private:
		string tekst;
		string zakodowany;
		int stopien;

		int* roznice;
		int RozniceSize;

		int* poczatek;

		int* KonwersjaLiczby(string tekst);
		string KonwersaTekst(int* liczby, int size);
		void GenerujTablice(string tresc);



	};




}


#endif