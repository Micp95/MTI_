#include "AlgLZ.h"
#include <iostream>
#include <string>

#include"Spis.h"


using namespace std;
using namespace _MAIN;

namespace _ALZ{

	//----------------------------Konstr, Destr, Clear--------------------
	void ALZ77::Clear(){
		SymbolPoczatkowy = 0;
		if (slownik)
			delete[] slownik;
		if (wejscie)
			delete[]wejscie;

		if (ZapisaneTrojki)
			delete ZapisaneTrojki;

		dane = "";
		danewsk = 0;
	}

	ALZ77::ALZ77(int wslownik, int wwejscie) :bs(wslownik), bw(wwejscie)
	{
		slownik = new char[bs];
		wejscie = new char[bw];
		ZapisaneTrojki = NULL;
	}

	ALZ77::~ALZ77()
	{
		if (slownik)
			delete[] slownik;

		if (wejscie)
			delete[] wejscie;

		if (ZapisaneTrojki)
			delete ZapisaneTrojki;
	}



	//----------------------------Funkcje glowne (publiczne)-------------
	string ALZ77::Koduj(string tresc){
		dane = tresc;

		SymbolPoczatkowy = dane[0];

		//Wypelnienie slownika poczatkowa wartoscia
		for (int k = 0; k < bs; k++)
			slownik[k] = dane[0];

		//Zaladowanie danych do wejscia
		for (int k = 0; k < bw; k++, danewsk++){
			if (danewsk < dane.length())
				wejscie[k] = dane[danewsk];
			else
				wejscie[k] = NULL;
		}

		//Zmienne pomocnicze
		Trojka* glowny, *tmp, *tmpZ;
		ZapisaneTrojki = tmpZ = glowny = NULL;

		//Wykonanie algorytmu
		while (wejscie[0] != NULL){
			tmp = Wyszukaj();
			PrzesuniecieBufora(tmp->c);

			if (tmpZ == NULL){
				glowny = tmp;
				tmpZ = glowny;
			}
			else{
				tmpZ->next = tmp;
				tmpZ = tmp;
				tmpZ->next = NULL;
			}
		}

		ZapisaneTrojki = glowny;
		return zakoduj();	//Zwrot w postaci binarnej
	}

	string ALZ77::Dekoduj(string tresc){

		//Sprawdzenie czy z pliku - jesli nie dekoduje wg. danych kodera
		if (tresc != "")
			RozkodujBin(tresc);

		//Wypelnienie slownika symbolem poczatkowym
		for (int k = 0; k < bs; k++)
			slownik[k] = SymbolPoczatkowy;
		//Zerowanie wejscia
		for (int k = 0; k < bw; k++)
			wejscie[k] = NULL;

		//Brak dodatkowego wejscia
		danewsk = dane.length();

		Trojka* aktualna = ZapisaneTrojki;


		string odszyfrowany = "";

		//Algorytm wykonuje sie dopoki ma trojki
		while (aktualna != NULL){

			//Ustawianie buforu wejsciowego
			for (int k = 0; k < aktualna->c; k++)
				wejscie[k] = slownik[aktualna->p + k];
			wejscie[aktualna->c] = aktualna->znak;

			odszyfrowany += BuforWejsciowy();
			PrzesuniecieBufora(aktualna->c);

			aktualna = aktualna->next;
		}

		return odszyfrowany;
	}


	//---------------------------Obsluga pliku binarnego-----------------
	string ALZ77::zakoduj(){
		string zwrot = "";


		//Dodanie symbolu poczatkowego
		zwrot += dec_to_bin(SymbolPoczatkowy);


		//Pomocnicze zmienne
		Trojka* tmp = ZapisaneTrojki;
		int dl = dlslowa(bs);
		char* tabtmp;


		//Dopoki sa trojki - dopisuje je do wyjscia
		while (tmp)
		{
			tabtmp =  int_to_bin(tmp->p, dl);
			zwrot += string(tabtmp,dl);
			delete[] tabtmp;

			tabtmp = int_to_bin(tmp->c, dl);
			zwrot += string(tabtmp, dl);
			delete[] tabtmp;

			zwrot += dec_to_bin(tmp->znak);
			tmp = tmp->next;
		}
		return zwrot;
	}

	void ALZ77::RozkodujBin(string& tresc){


		//Dla pewnosci - zwolnienie pamieci
		if (ZapisaneTrojki)
			delete ZapisaneTrojki;

		//Zmienne pomocnicze
		int dl = dlslowa(bs);
		Trojka* tmp, *tmp2;
		tmp = NULL;
		long long filelen = tresc.length();
		long long index = 0;
		SymbolPoczatkowy = bin_to_dec(tresc, index, index + 8);	//odczytanie znaku poczatkowego
		index += 8;
		int p, c;
		char znak;

		//Dopoki nie odczytalismy calego pliku
		while (index < filelen){

			//Pobranie odpowiednich danych
			p = bin_to_int(tresc, index, index + dl,false);
			index += dl;
			c = bin_to_int(tresc, index, index + dl, false);
			index += dl;
			znak = bin_to_dec(tresc, index, index + 8);
			index += 8;

			//Stworzenie odpowiedniej trojki
			tmp2 = new Trojka(znak, p, c);
			if (tmp){
				tmp->next = tmp2;
				tmp = tmp2;
			}
			else
				ZapisaneTrojki = tmp = tmp2;
		}
	}



	//---------------------------Funkcje algorytmu------------------
	Trojka* ALZ77::Wyszukaj(){

		int pocz = 0;
		int maksdl = 0;
		int aktdl = 0;


		//Petla wyszukujaca najdluzszego podciagu
		for (int k = 0; k < bs; k++){
			aktdl = 0;
			for (int p = 0; p < bw-1; p++){
				if (k+p < bs && slownik[k + p] == wejscie[p] && wejscie[p] != NULL){
					aktdl++;
				}
				else
					break;
			}
			if (aktdl > maksdl){
				maksdl = aktdl;
				pocz = k;
			}
		}

		//Dopisanie znaku do trojki i jesli pusta, uzupelnienie reszty
		char znak;
		if (aktdl != 0){
			znak = wejscie[maksdl];
		}
		else{
			znak = wejscie[0];
			maksdl = 0;
			aktdl = 0;
		}

		//Fizyczne tworzenie trojki i zwrot
		Trojka* zwrot = new Trojka(znak, pocz, maksdl);
		return zwrot;
	}

	void ALZ77::PrzesuniecieBufora(int przes){
		przes++;

		//Przesuwanie w buforach (s³ownik, wejscie)
		int tmp,tmp2;
		for (int k = 0; k < bw + bs;k++){
			if (k < bs){	//slownik
				tmp = k - przes;
				if (tmp >= 0)
					slownik[tmp] = slownik[k];
			}
			else
			{				//bufor
				tmp = k - bs;
				tmp2 = tmp - przes;
				if (tmp2 < 0)
					slownik[tmp2 + bs] = wejscie[tmp];
				else
					wejscie[tmp2]= wejscie[tmp];
			}

		}

		//Dodawanie nowych danych
		for (int k = bw - przes; k < bw; k++, danewsk++){
			if (danewsk < dane.length())
				wejscie[k] = dane[danewsk];
			else
				wejscie[k] = NULL;
		}


	}

	string ALZ77::BuforWejsciowy(){
		string zwrot= "";

		for (int k = 0; k < bw && wejscie[k] != NULL; k++)
			zwrot += wejscie[k];
		
		return zwrot;
	}



	//--------------------TROJKI--------------------------

	string Trojka::wyswielt(){
		string zwrot = "("; 
		zwrot += (p + 48);
		zwrot += ","; 
		zwrot += (c + 48);
		zwrot += ",";
		zwrot += znak;
		zwrot += ")";
		return zwrot;
	}

	Trojka::Trojka(string tresc){
		int p1 = tresc.find(',');
		int p2 = tresc.find(',', p1 + 1);

		znak = tresc[p2 + 1];
		p = atoi(tresc.substr(1, p1).c_str());
		c = atoi(tresc.substr(p1+1, p2).c_str());
		next = NULL;
		
	}

}

