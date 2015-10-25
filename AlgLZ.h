#ifndef ALGLZ_H
#define ALGLZ_H

#include <string>
#include <iostream>

using namespace std;

namespace _ALZ{


	//Struktura trójek - element listy jednokierunkowej
	struct Trojka
	{
		Trojka(char z, int p, int c) :znak(z), p(p), c(c){}
		Trojka(){
			znak = NULL;
			p = NULL;
			c = NULL;
			next = NULL;
		}

		string wyswielt();
		Trojka* next;

		int c;		//dlugosc
		int p;		//index
		char znak;

	};



	class ALZ77
	{
	public:
		ALZ77(int wslownik, int wwejscie);
		~ALZ77();

		string Koduj(string tresc);
		string Dekoduj(string tresc = "");

	private:
		int bs;		//Bufor slownika - wielkosc
		int bw;		//Bufor wejsciowy - wielkosc

		char* slownik;		//Bufor s³ownika
		char* wejscie;		//Bufor wejscia

		char SymbolPoczatkowy;
		Trojka* ZapisaneTrojki;		//Zakodowane trojki


		Trojka* Wyszukaj();						//Wyszukiwanie schematu
		void PrzesuniecieBufora(int przes);		//Przesuniecie buforu: s³ownik i wejœcie =


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