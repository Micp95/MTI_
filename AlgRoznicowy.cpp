#include "AlgRoznicowy.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Spis.h"


using namespace _MAIN;
using namespace std;


namespace _ARoznicowy{


	//---------------------------Konnstr, Destr, Clear-------------
	void ARoznicowy::Clear(){
		if (roznice != NULL)
			delete[] roznice;

		if (poczatek != NULL)
			delete[] poczatek;

		tekst = "";
		zakodowany = "";
		RozniceSize = 0;
		dlslow = 0;
	}

	ARoznicowy::ARoznicowy(int stopien) 
	{
		if (stopien < 1)
			this->stopien = 1;
		else
			this->stopien = stopien;

		poczatek = new int[stopien];
		roznice = NULL;
	}

	ARoznicowy::~ARoznicowy()
	{
		if (roznice != NULL)
			delete[] roznice;

		if (poczatek != NULL)
			delete[] poczatek;

	}


	//-------------------------Metody podstawowe-------------
	string ARoznicowy::Koduj(string tekst){
		this->tekst = tekst;
		int* liczby = KonwersjaLiczby(tekst);		//Zmiana charow na wartosci liczbowe

		int AktRozm = 0;
		if (roznice != NULL)
			delete[] roznice;

		//Kompresowanie - w zaleznosci od stopnia 
		for (int k = 0; k < stopien; k++){

			//Przechowywanie poczatkowych wartosci
			poczatek[k] = liczby[0];

			//Szykowanie tablic z roznicami
			AktRozm = tekst.length() - (k + 1);
			roznice = new int[AktRozm];

			//Generowanie roznic
			for (int p = 0; p < AktRozm; p++){
				roznice[p] = liczby[p + 1] - liczby[p];
			}

			//Czyszczenie pamieci
			delete[] liczby;
			liczby = roznice;
			roznice = NULL;
		}

		roznice = liczby;
		RozniceSize = AktRozm;
		zakodowany = Podglad();

		return KodBin();
	}

	string ARoznicowy::Dekoduj(string tekst){

		//Jesli dostaje wejscie, rokodowuje wejscie, jesli nie uzywa to co przechowuje
		if (tekst != "")
			GenerujTablice(tekst);

		int AktRozm = 0;
		int* tmp = NULL;

		for (int k = 0; k < stopien; k++){ // Przejscie przez wszystkie stopnie
			AktRozm = RozniceSize + 1 + k;
			tmp = new int[AktRozm];

			//Dopisanie poczatku
			tmp[0] = poczatek[stopien-(k+1)];

			//Dopisanie reszty tablicy
			for (int p = 1; p < AktRozm; p++)
				tmp[p] = roznice[p - 1];

			//Zdekodowanie tablicy
			for (int p = 1; p < AktRozm; p++)
				tmp[p] = tmp[p] + tmp[p - 1];
			
			delete[] roznice;
			roznice = tmp;
			RozniceSize = AktRozm;

			tmp = NULL;
		}

		return KonwersaTekst(roznice, AktRozm); //Powrotna zamiana roznic na tekst
	}



	//--------------------Metody wspierajace pliki binarne-----------
	void ARoznicowy::GenerujTablice(string tresc){
		if (poczatek)
			delete[] poczatek;
		if (roznice != NULL)
			delete[] roznice;

		long long index = 0;

		//Wczytanie poczatkow - znaki
		poczatek = new int[stopien];
		for (int k = 0; k < stopien; k++){
			poczatek[k] = (int)bin_to_dec(tresc, index, index + 8);
			index += 8;
		}


		//Wczytywanie rozmiaru tablicy roznic
		RozniceSize = bin_to_int(tresc, index, index + 32, false);
		index += 32;
		roznice = new int[RozniceSize];


		//Wczytywanie kolejnych roznic
		for (int k = 0; k < RozniceSize; k++){
			if (index + dlslow > tresc.length())
				return;
			roznice[k] = bin_to_int(tresc, index, index + dlslow, true);
			index += dlslow;
		}
	}

	int ARoznicowy::maksRoznica(){
		//Wyszulanie maksymalnej roznicy
		int maks = 0, tmp;
		for (int k = 0; k < RozniceSize; k++){
			tmp = roznice[k];
			if (tmp < 0)
				tmp = -tmp;
			if (tmp > maks)
				maks = tmp;
		}
		return maks;
	}

	string ARoznicowy::KodBin(){		//Kodowanie tablic do postaci skompresowanej i binarnej
		string zwrot = "";
		char* wczyt;		//Pomocnicza tablica do wczytywania
		
		//Zapis poczatkow
		for (int k = 0; k < stopien; k++){
			zwrot += dec_to_bin((char)(poczatek[k]));
		}

		//Zapis ilosci roznic
		wczyt = int_to_bin(RozniceSize, 32);
		zwrot += string(wczyt, 32);
		delete[] wczyt;

		//Liczenie minimalnej dlugosci slow
		int tmp = maksRoznica();
		dlslow = dlslowa(tmp);
		dlslow++; //miejsce na znak!!

		//Dopisywanie kolejnych roznic
		for (int k = 0; k < RozniceSize; k++){
			wczyt = int_to_bin(roznice[k], dlslow);
			zwrot += string(wczyt, dlslow);
			delete[] wczyt;
		}

		return zwrot;
	}


	//-----------------------Pomocnicze-----------------	
	string ARoznicowy::Podglad(){
		string tmp = "";
		
		ostringstream ss;

		for (int k = 0; k < stopien; k++){
			ss << poczatek[k];
			tmp += ss.str();
			ss.str("");
			ss.clear();
			tmp += " ";
		}
		tmp += "\t|\t";
		for (int k = 0; k < RozniceSize; k++){
			ss << roznice[k];
			tmp += ss.str();
			ss.str("");
			ss.clear();
			tmp += " ";
		}

		return tmp;
	}


	//---------------------Konwersje danych---------------
	int* ARoznicowy::KonwersjaLiczby(string tekst){
		int* tmp = new int[tekst.length()];
		for (int k = 0; k < tekst.length(); k++){
			tmp[k] = (int)tekst[k];
		}
		return tmp;
	}

	string ARoznicowy::KonwersaTekst(int* liczby, int size){
		string tmp = "";
		ostringstream ss;
		for (int k = 0; k < size; k++){
			tmp +=  (char)liczby[k];
		}
		return tmp;
	}


}



