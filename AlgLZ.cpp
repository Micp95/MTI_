#include "AlgLZ.h"
#include <iostream>
#include <string>



using namespace std;


namespace _ALZ{

	ALZ77::ALZ77(int wslownik, int wwejscie) :bs(wslownik), bw(wwejscie)
	{
		slownik = new char[bs];
		wejscie = new char[bw];
		ZapisaneTrojki = NULL;
	}

	ALZ77::~ALZ77()
	{
		if (slownik != NULL)
			delete[] slownik;

		if (wejscie != NULL)
			delete[] wejscie;

		if (ZapisaneTrojki != NULL)
			delete[] ZapisaneTrojki;
	}



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

		Trojka* glowny = NULL;
		Trojka* tmp = NULL;
		Trojka*tmpZ = NULL;
		ZapisaneTrojki = tmpZ = NULL;
		while (wejscie[0] != NULL){
			tmp = Wyszukaj();
			PrzesuniecieBufora(tmp->c);

			if (tmpZ == NULL)
			{
				glowny = tmp;
				tmpZ = glowny;
			//	ZapisaneTrojki = tmp;
			//	tmpZ = ZapisaneTrojki;
			}
			else{
				tmpZ->next = tmp;
				tmpZ = tmp;
				tmpZ->next = NULL;
			}


			
		}

		tmp = glowny;
		while (tmp != NULL){
			cout << tmp->wyswielt() << " ";
			tmp = tmp->next;

		}
		cout << endl;


		return "";
	}

	string ALZ77::Dekoduj(string tresc){

		return "";
	}


	Trojka* ALZ77::Wyszukaj(){

		int pocz = 0;
		int maksdl = 0;

		int aktdl = 0;
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

		char znak;
		if (aktdl != 0){
			
			znak = wejscie[maksdl];
		}
		else{
			znak = wejscie[0];
			maksdl = 0;
			aktdl = 0;
		}



		Trojka* zwrot = new Trojka(znak, pocz, maksdl);
		WypiszBufor();
		cout << pocz << " " << maksdl << " " << znak << endl;

		return zwrot;
	}

	void ALZ77::PrzesuniecieBufora(int przes){
		przes++;

		//Przesuwanie w buforach (s³ownik wejscie)
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



}

