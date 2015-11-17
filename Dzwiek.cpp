#include "Dzwiek.h"

#include <stdio.h>
#include <windows.h>
#include <fstream>

#include "Spis.h"

#include "RAWFile.h"
#include "Camouflage.h"
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


	return 0;
}

int _Dzwiek::PlatformaTestowaKasia(){

	ACamo cm1;
	cm1.MaskTime(0.01);

	return 0;
}

