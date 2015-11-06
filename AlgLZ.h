#ifndef ALGLZ_H
#define ALGLZ_H

#include <string>
#include <iostream>
#include "Koder.h"

using namespace std;

namespace _ALZ{


	//Struktura tr�jek - element listy jednokierunkowej
	struct Trojka 
	{
		Trojka(char z, int p, int c) :znak(z), p(p), c(c){}
		Trojka(){
			znak = NULL;
			p = NULL;
			c = NULL;
			next = NULL;
		}
		Trojka(string tresc);


		string wyswielt();
		Trojka* next;

		int c;		//dlugosc
		int p;		//index
		char znak;

	};



	class ALZ77: public Koder
	{
	public:
		ALZ77(int wslownik, int wwejscie);
		~ALZ77();

		virtual string Koduj(string tresc);
		virtual string Dekoduj(string tresc = "");

		char SymbolPoczatkowy;
	private:
		int bs;		//Bufor slownika - wielkosc
		int bw;		//Bufor wejsciowy - wielkosc

		char* slownik;		//Bufor s�ownika
		char* wejscie;		//Bufor wejscia

		Trojka* ZapisaneTrojki;		//Zakodowane trojki


		Trojka* Wyszukaj();						//Wyszukiwanie schematu
		void PrzesuniecieBufora(int przes);		//Przesuniecie buforu: s�ownik i wej�cie =
		string BuforWejsciowy();


		string dane;	//Przechowane dane
		int danewsk;	//Przechowany indeks aktualnie wczytanych danych
		


		//Pomocnicza funcka INLINE do wypisywania buforu
		void WypiszBufor(){
			for (int k = 0; k < bs; k++)
				cout << slownik[k] << " ";
			cout << "\t";
			for (int k = 0; k < bw; k++)
				cout << wejscie[k] << " ";

		}


	};




}


#endif