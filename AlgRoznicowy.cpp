#include "AlgRoznicowy.h"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;


namespace _ARoznicowy{


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

	string ARoznicowy::Koduj(string tekst){
		this->tekst = tekst;
		int* liczby = KonwersjaLiczby(tekst);


		int AktRozm = 0;
		if (roznice != NULL)
			delete[] roznice;

		//Kompresowanie
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

		return zakodowany;
	}

	string ARoznicowy::Dekoduj(string tekst){
		if (tekst != "")
			GenerujTablice(tekst);

		int AktRozm = 0;
		int* tmp = NULL;

		for (int k = 0; k < stopien; k++){ // Przejscie przez wszystkie stopnie
			AktRozm = RozniceSize + 1 + k;
			tmp = new int[AktRozm];
			tmp[0] = poczatek[stopien-(k+1)];
			for (int p = 1; p < AktRozm; p++)
				tmp[p] = roznice[p - 1];
			
			for (int p = 1; p < AktRozm; p++)
				tmp[p] = tmp[p] + tmp[p - 1];
			
			delete[] roznice;
			roznice = tmp;

			tmp = NULL;
		}

		return KonwersaTekst(roznice, AktRozm);
	}

	void ARoznicowy::GenerujTablice(string tresc){
		//Generowanie tablicy ze stringu


	}

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



