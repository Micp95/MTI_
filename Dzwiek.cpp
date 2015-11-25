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


using namespace std;
using namespace _MAIN;
using namespace _Camouflage;

int _Dzwiek::PlatformaTestowaOgolna(){

	cout << "Dzwiek." << endl;


	return 0;
}






int _Dzwiek::PlatformaTestowaMichal(){
	RAWFile<float> plik;
	float* binarny = plik.Wczytaj("_audio\\02.snd");
	cout << plik.GetSize()<<endl;
	plik.Zapis("_audio\\03.snd");


	return 0;
}

int _Dzwiek::PlatformaTestowaMarysia(){

	/*	Tests tests;
	tests.SelfTest();
	*/

	int size = get_file_size("_pliki//looking1.wav");
	cout << size << endl;

	Wav_reader wr;
	//cout << "No of samples: " << wr.numberOfSamples;
	short ** samplesTab = wr.read("_pliki//looking1.wav", size);

	FrequencyFilter ff;
	short* afterFiltered = ff.Filter(samplesTab[0], wr.numberOfSamples, Global::min, Global::max);

	/*	cout << "filtered:\n";
	for (int i = 0; i < Global::toPrint; i++)
	cout << "\t" << i << ": " << afterFiltered[i] << endl;
	*/

	DFT d;
	/*	Complex * afterDft = d.CalculateDFT(samplesTab[0], size);

	//_________________dane do widma_________________
	for (int i = 0; i < size; i++)
	cout << afterDft[i].im << endl;
	*/

	//__________________dane do widma po dft, filtrowaniu, idft______________________
	Complex * afterDft = d.CalculateDFT(afterFiltered, wr.numberOfSamples);		//filtrowane
	short * valueAfterIdft = d.CalculateIDFT(afterDft, wr.numberOfSamples);

	for (int i = 0; i < wr.numberOfBytesPerSample; i++)
		cout << valueAfterIdft[i] << endl;

	/*
	Complex harmonic = d.CalculateKHarmonicDFT(samplesTab[0], wr.numberOfSamples, 1);		//wypisanie harmonicznych
	cout << harmonic.re << "\t" << harmonic.im << endl;

	cout << "harmonic:\n";
	for (int i = 0; i < Global::toPrint; i++)
	cout << "\t" << i << ": " << afterDft[i].re << " , " << afterDft[i].im << endl;

	cout << "result:\n";
	for (int i = 0; i < Global::toPrint; i++)
	cout << "\t" << i << ": " << valueAfterIdft[i] << endl;
	*/
	/*	Compare cc;
	cout << "\nrate:\t" << cc.CompareAndRate(afterFiltered, valueAfterIdft, Global::toPrint) << endl;
	*/

	return 0;
}

int _Dzwiek::PlatformaTestowaKasia(){

//	ACamo cm1;
//	cm1.MaskTime(0.01);

	return 0;
}

