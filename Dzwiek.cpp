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

//	ACamo cm1;
//	cm1.MaskTime(0.01);

	return 0;
}

