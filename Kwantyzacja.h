#ifndef KWANTYZACJA_H
#define KWANTYZACJA_H

#include <iostream>
#include <string>

using namespace std;

//Struktura przechowujaca zwracane tablice i rozmiar
template <class typ>
struct wektor
{
	wektor(){ A = NULL, B = NULL; }
	typ* A;
	int* B;
	long  size;
};

class Kwantyzacja
{
public:
	Kwantyzacja();
	Kwantyzacja(int ilejest, int probkowanie,int kwanty);
	~Kwantyzacja();

	template <class typ>
	wektor<typ> kwantuj(typ* dane, long ilosc);

	template <class typ>
	typ* OdkodujZakres(int*dane, long ilosc,typ wybor, double krok = 0);

	template <class typ>
	double SzumKwantyzacji(typ* org, typ* przetworzone,long size ,int proba = 0);

private:
	template <class typ>
	int Przydziel(typ dane);

	template <class typ>
	typ PolowaZakresu(typ* dane, long zakres);
	
	double proba;
	int kwanty;
	double krok;
};



//Szablony

//Glowna funkcja - przyjmuje dane, nastepnie je przetwarza
template <class typ>
wektor<typ> Kwantyzacja::kwantuj(typ* dane, long ilosc){
	wektor<typ> zwrot;
	long  size = ilosc / (long)proba;		//rozmiar zwracanej tablicy

	zwrot.A = new typ[size];				//tablica zawierajaca nie przetworzone dane
	zwrot.B = new int[size];				//Tablica zawierajaca dane kwantowane
	zwrot.size = size;
	
	typ pol = PolowaZakresu(dane,ilosc);	//Znalezienie polowy zakresu - przejscie na dodatnie liczby
	krok = (pol * 2) / kwanty;				//Obliczenie kroku


	for (long k = 0; k < size; k ++){
		zwrot.A[k] = dane[k*(int)proba];						//Przechowanie oryginalu
		zwrot.B[k] = Przydziel(dane[k*(int)proba] + pol);	//Zapis kwantu
	}

	return zwrot;
}

template <class typ>
int Kwantyzacja::Przydziel(typ dane){

	for (float k = 0; k < kwanty; k++){
		if (dane  >(k - 0.5)*krok && dane  <= (k + 0.5)*krok)	//Znalezienie odpowiedniego przedzialu dla liczby
			return k;
	}
	return 0;
}

template <class typ>
typ Kwantyzacja::PolowaZakresu(typ* dane, long zakres){

	//Wyliczenie sredniego obiektu z danych
	typ akum = 0;
	for (int k = 0; k < 10; k++)
		akum += dane[rand() % zakres];
	akum /= 10;

	//Jesli jest nim cos z przedzialu (-1,1) to znaczy, ze plik sklada siê z liczb zmienno przecinkowych
	if (akum > -1 && akum < 1)
		return 1;

	//Jesli plik sklada sie z liczb calkowitych - wyliczenie ile jestesmy w stanie zapisac na danej ilosci bitow
	int bits = sizeof(typ) * 8;
	bits--;
	long wart = 1;
	for (int k = 0; k < bits; k++)
		wart *= 2;

	return wart/2;
}

template <class typ>
typ* Kwantyzacja::OdkodujZakres(int*dane, long ilosc, typ wybor, double krok){
	if (!krok)
		krok = this->krok;

	//Wyliczenie polowy - przeksztalcenie kroku
	//krok = (pol * 2) / kwanty;
	typ pol = (krok* kwanty) / 2;

	typ* zwrot = new typ[ilosc];
	for (long k = 0; k < ilosc; k++){
		zwrot[k] = ((typ)dane[k] * krok)-pol;		//Odkodowanie sygnalu
	}
	return zwrot;
}

template <class typ>
double Kwantyzacja::SzumKwantyzacji(typ* org, typ* przetworzone, long size, int proba){
	if (!proba)
		proba = this->proba;
	double ocena = 0;

	for (long k = 0; k < size; k++)
		ocena += (org[k] - przetworzone[k]);
	ocena /= (double)proba;

	return ocena;
}

#endif