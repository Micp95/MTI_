#include "Dzwiek.h"

#include <stdio.h>
#include <windows.h>
#include <fstream>

#include "Spis.h"

#include "RAWFile.h"
#include "Camouflage.h"

#include"Audio.h"
#include"Complex.h"
#include"DFT.h"
#include"FrequencyFilter.h"
#include<string.h>
#include"Global.h"
#include "Printer.h"

#include <time.h>
#include <cstdlib>
#include "Kwantyzacja.h"


using namespace std;
using namespace _MAIN;
using namespace _Camouflage;

int _Dzwiek::PlatformaTestowaOgolna(){

	cout << "Dzwiek." << endl;


	return 0;
}






int _Dzwiek::PlatformaTestowaMichal(){
	srand(time(NULL));
	/*
	cout << "Przeprowadzenie proby kwantyzacji:\n\n";
	cout << "\n\n\n\t\t------\n\n\n";
	cout << "Przeprowadzenie proby kwantyzacji:\n\n";
	cout << "\n\n\n\t\t------\n\n\n";
	KwantyzacjaProba("_audio\\07.raw", 44100, 44100, 1000);
	KwantyzacjaProba("_audio\\07.raw", 44100, 44100, 256);
	KwantyzacjaProba("_audio\\07.raw", 44100, 44100, 100);
	*/

	KwantyzacjaProba("_audio\\07.raw", 44100, 44100, 100, true);

	/*

	cout << "Przeprowadzenie proby kwantyzacji:\n\n";
	cout << "\n\n\n\t\t------\n\n\n";
	KwantyzacjaProba("_audio\\07.raw", 44100, 22050, 1000);
	KwantyzacjaProba("_audio\\07.raw", 44100, 22050, 256);
	KwantyzacjaProba("_audio\\07.raw", 44100, 22050, 100);
	cout << "\n\n\n\t\t------\n\n\n";
	KwantyzacjaProba("_audio\\07.raw", 44100, 11025, 1000);
	KwantyzacjaProba("_audio\\07.raw", 44100, 11025, 256);
	KwantyzacjaProba("_audio\\07.raw", 44100, 11025, 100);
	cout << "\n\n\n\t\t------\n\n\n";
	KwantyzacjaProba("_audio\\07.raw", 44100, 5500, 1000);
	KwantyzacjaProba("_audio\\07.raw", 44100, 5500, 256);
	KwantyzacjaProba("_audio\\07.raw", 44100, 5500, 100);
	*/

	return 0;
}

int _Dzwiek::PlatformaTestowaMarysia(){

	/*	Tests tests;
	tests.SelfTest();
	*/
	int size = get_file_size("C:\\Users\\Marysia\\Desktop\\looking1.wav");
	Wav_reader wr;
	//	cout << "No of samples: " << wr.numberOfSamples;
	short ** samplesTab = wr.read("C:\\Users\\Marysia\\Desktop\\looking1.wav", size);

	FrequencyFilter ff;
	short* afterFiltered = ff.Filter(samplesTab[0], wr.numberOfSamples, Global::min, Global::max);

	Print pr;
	//	pr.PrintWavSamples(samplesTab, wr.numberOfSamples);

	DFT d;
	Complex * afterDft = d.CalculateDFT(afterFiltered, wr.numberOfSamples);
	pr.PrintDataAfterDFT(afterDft, wr.numberOfSamples);

	//FrequencyFilter ff;
	//Complex* afterDftAfterFiltered = ff.Filter(afterDft, wr.numberOfSamples, Global::min, Global::max);

	//	short* result = d.CalculateIDFT(afterDft, wr.numberOfSamples);
	//	pr.PrintDataAfterIDFT(result, wr.numberOfSamples);

	return 0;
}

int _Dzwiek::PlatformaTestowaKasia(){

	ACamo cm1;
	cout << "Przeprowadzenie maskowania w dziedzinie czasu! " << endl;
	cm1.MaskTime(0.3,-0.3);
	ACamo cm2;
	cout << "Przeprowadzenie maskowania w dziedzinie czestotliwosci! " << endl;
	cm2.MaskFreq(0.02, -0.02);

	return 0;
}


void _Dzwiek::KwantyzacjaProba(string nazwa, int pprob, int prob, int kwant, bool zapis){
	RAWFile<float> plik;
	float* binarny = plik.Wczytaj(nazwa);

	Kwantyzacja koder(pprob, prob, kwant);
	wektor<float> zwrot = koder.kwantuj(binarny, plik.GetSize());

	float* odkodowane = koder.OdkodujZakres(zwrot.B, zwrot.size, float(0));

	cout << "Dla pliku:\t" << nazwa << endl
		<< "\tProbkowanie pliku:\t" << pprob << endl
		<< "\tProbkowanie wyjsciowe:\t" << prob << endl
		<< "\tIlosc progow kwantyzacji:\t" << kwant << endl;
	cout << "\n\t\tSzum kwantyzacji wyniosl:\t" << koder.SzumKwantyzacji(zwrot.A, odkodowane, zwrot.size) << endl;

	if (zapis)
		plik.Zapis(nazwa + "l", odkodowane, zwrot.size);
}