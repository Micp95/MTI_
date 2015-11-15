#include "Dzwiek.h"

#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <time.h>
#include <cstdlib>

#include "Spis.h"

#include "RAWFile.h"
#include "Kwantyzacja.h"

using namespace std;
using namespace _MAIN;

int _Dzwiek::PlatformaTestowaOgolna(){

	cout << "Dzwiek." << endl;

	
	return 0;
}



int _Dzwiek::PlatformaTestowaMichal(){
	srand(time(NULL));

	cout << "Przeprowadzenie proby kwantyzacji:\n\n";
	cout << "\n\n\n\t\t------\n\n\n";
	KwantyzacjaProba("_audio\\05.raw", 44100, 22050, 1000);
	KwantyzacjaProba("_audio\\05.raw", 44100, 22050, 256);
	KwantyzacjaProba("_audio\\05.raw", 44100, 22050, 100);
	cout << "\n\n\n\t\t------\n\n\n";
	KwantyzacjaProba("_audio\\05.raw", 44100, 11025, 1000);
	KwantyzacjaProba("_audio\\05.raw", 44100, 11025, 256);
	KwantyzacjaProba("_audio\\05.raw", 44100, 11025, 100);
	cout << "\n\n\n\t\t------\n\n\n";
	KwantyzacjaProba("_audio\\05.raw", 44100, 5500, 1000);
	KwantyzacjaProba("_audio\\05.raw", 44100, 5500, 256);
	KwantyzacjaProba("_audio\\05.raw", 44100, 5500, 100);

	return 0;
}

int _Dzwiek::PlatformaTestowaMarysia(){


	return 0;
}

int _Dzwiek::PlatformaTestowaKasia(){


	return 0;
}


void _Dzwiek::KwantyzacjaProba(string nazwa, int pprob, int prob, int kwant){
	RAWFile<float> plik;
	float* binarny = plik.Wczytaj(nazwa);

	Kwantyzacja koder(pprob, prob, kwant);
	wektor<float> zwrot = koder.kwantuj(binarny, plik.GetSize());

	float* odkodowane = koder.OdkodujZakres(zwrot.B, zwrot.size, float(0));
	/*
	for (int k = 0; k < 10; k++){
		cout << zwrot.A[k] << "\t" << zwrot.B[k] << "\t" << odkodowane[k] << endl;
	}
	cout << endl << plik.GetSize() << endl;
	cout << endl << zwrot.size << endl;
	plik.Zapis("_audio\\05k.raw", odkodowane, zwrot.size);
	*/

	cout << "Dla pliku:\t" << nazwa << endl
		<< "\tProbkowanie pliku:\t" << pprob << endl
		<< "\tProbkowanie wyjsciowe:\t" << prob << endl
		<< "\tIlosc progow kwantyzacji:\t" << kwant << endl;
	cout << "\n\t\tSzum kwantyzacji wyniosl:\t" << koder.SzumKwantyzacji(zwrot.A, odkodowane, zwrot.size) << endl;
}