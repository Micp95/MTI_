#ifndef ALGHUFF_H
#define ALGHUFF_H

#include <string>
#include "HuffDrzewo.h"
#include "Koder.h"

using namespace std;

namespace _AHuffman{

	//Klasa pomocnicza - przechowuje dwie wartosci liczbowe
	struct MM{
		int min, max;
	};

	class AHuffman: public Koder
	{
	public:
		AHuffman(int Zroznicowanie = 100) :MaksZnakow(Zroznicowanie){ znaki = NULL; }
		~AHuffman();

		virtual string Koduj(string tresc);
		virtual string Dekoduj(string tresc = "");
		virtual void Clear();

	private:
		int MaksZnakow;		//Zroznicowanie wystepujacych znakow
		string tekst;		//Zapisanie tekstu do zakodowania
		string tablica;		//Wszystkie wystepujace znaki (kolejnosc odpowiada indeksowi w tablicy znaki!
		string zakodowane;	//Przechowany zakodowany juz tekst


		Node* znaki;		//Tablica wszystkich znakow - ulatwia kodowanie tekstu
		int size;			//Ilosc znakow i rozmiar tablicy znaki

		Node* Drzewo;		//Korzen struktury drzewa

		//Przygotowanie struktury do kodowania
		void StworzListe();
		void StworzDrzewo();
		void StworzSlownik();

		//Funkcje kodujace
		string Translate();								//Tlumaczy tekst na kod
		void Przechodz(Node* element, string kod);		//Tworzy slownik przechodzac rekurencyjnie przez drzewo

		MM MinMin(Node**tab, int size);		//Funcka pomocnicza - znajduje 2 najmniejsze elementy
	};



}


#endif