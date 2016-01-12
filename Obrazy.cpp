#include "Obrazy.h"

#include <string>
#include <iostream>

#include "RAWFile.h"
#include "PPMFile.h"
#include "ImageConverter.h"
#include "ImageScale.h"
#include "QualityCheck.h"

#include"ReductionChrominanceChannels.h"
#include"ReductionAmountOfColours.h"

using namespace std;
using namespace _Obrazy;
int _Obrazy::PlatformaTestowaOgolna() {

	return 0;
}
int _Obrazy::PlatformaTestowaMichal() {

		/*
	PPMFile plik("_images\\fgd.ppm");
	plik.LoadFile();


	for (int k = 0; k < plik.high; k++) {
		plik.GetPixel(k-1, k).Set(255, 0, 0);//B
		plik.GetPixel(k, k).Set(0, 255, 0);//G
		plik.GetPixel(k+1, k).Set(0, 0, 255);//R
	}
	plik.SaveFile("_pliki\\fgddd.ppm");

	ImageConverter konwertor;

	konwertor.Convert("_pliki\\fgddd.ppm", "_pliki\\fgddd.bmp");
	konwertor.Convert("_pliki\\fgddd.bmp", "_pliki\\fgddd.png");




	for (int k = 0; k < plik.high; k++) {
		plik.GetPixel(100, k).Set(255, 0, 0);//R
		plik.GetPixel(101, k).Set(0, 255, 0);//G
		plik.GetPixel(102, k).Set(0, 0, 255);//B
	}

	for (int k = 0; k < plik.high; k++) {
		plik.GetPixel(200, k).Set(255, 0, 0);//R
		plik.GetPixel(201, k).Set(255, 0, 0);//R
		plik.GetPixel(202, k).Set(255, 0, 0);//R
	}

	for (int k = 0; k < plik.width; k++) {
		plik.GetPixel(k, 200).Set(255, 0, 0);//R
		plik.GetPixel(k, 200).Set(255, 0, 0);//R
		plik.GetPixel(k, 200).Set(255, 0, 0);//R
	}

	*/

	WykonajKonwersje("_images\\fgd.ppm");
	PoliczRozmiary("_images\\fgd.ppm");

	return 0;
}
int _Obrazy::PlatformaTestowaKasia() 
{/*
	cout << "KONWERSJA DO SKALI SZAROSCI!" << endl;
	ConvertToGrey plik("obraz.ppm"); // konwersja do skali szarosci

	cout << "KONWERSJA DO CZERNI I BIELI!" << endl;
	ConvertToBaW plik2("obraz.ppm"); // konwersja do czerni i bieli
	

	cout << "\nSprawdzanie dla tiff" << endl;
	CheckQuality check1("obrazek.ppm", "obrazek.tif");
	cout << "\nSprawdzanie dla png" << endl;
	CheckQuality check2("obrazek.ppm", "obrazek.png");
	cout << "\nSprawdzanie dla jpg" << endl;
	CheckQuality check3("obrazek.ppm", "obrazek.jpg");
	cout << "\nSprawdzanie dla gif" << endl;
	CheckQuality check4("obrazek.ppm", "obrazek.gif");
	return 0;*/
	return 0;
}


int _Obrazy::PlatformaTestowaMarysia() {

	ReductionChrominanceChannels rcc1("krajobraz_1920x1080_004.ppm", "krajobraz_1920x1080_004_yyy.ppm");
	ReductionChrominanceChannels rcc2("zrzut_ekranu.ppm", "zrzut_ekranu_yyy.ppm");
	ReductionChrominanceChannels rcc3("pingwin.ppm", "pingwin_yyy.ppm");
	rcc1.ReduceChrominance("4:4:4");
	rcc2.ReduceChrominance("4:4:4");
	rcc3.ReduceChrominance("4:4:4");

		rcc1.Save();
		rcc2.Save();
		rcc3.Save();

	rcc1.ConvertAllToRGB();
	rcc2.ConvertAllToRGB();
	rcc3.ConvertAllToRGB();

	//-----------------------

	ReductionAmountOfColours raoc1("krajobraz_1920x1080_004.ppm", "krajobraz_1920x1080_004_xxx.ppm");
	ReductionAmountOfColours raoc2("zrzut_ekranu.ppm", "zrzut_ekranu_xxx.ppm");
	ReductionAmountOfColours raoc3("pingwin.ppm", "pingwin_xxx.ppm");

	raoc1.ReduceColours();
	raoc2.ReduceColours();
	raoc3.ReduceColours();
	
	raoc1.Save();
	raoc2.Save();
	raoc3.Save();

	return 0;
}


void _Obrazy::WykonajKonwersje(string name) {

	ImageConverter konwertor;

	int kropka = name.find_last_of('.');
	name = name.substr(0,kropka);


	//To BMP - bezstratny
	konwertor.Convert(name + ".ppm", name + ".bmp");

	//JPEG
	konwertor.Convert(name + ".bmp", name + "_50" + ".jpeg" ,50);
	konwertor.Convert(name + ".bmp", name + "_75" + ".jpeg" ,75);
	konwertor.Convert(name + ".bmp", name + "_90" + ".jpeg" ,90);

	//PNG
	konwertor.Convert(name + ".bmp", name  + ".png" );

	//GIF
	konwertor.Convert(name + ".bmp", name + ".gif");

	//TIFF
	konwertor.Convert(name + ".bmp", name + "_0" + ".tiff",0);
	konwertor.Convert(name + ".bmp", name + "_1" + ".tiff",1);
}

void _Obrazy::PoliczRozmiary(string name) {
	int kropka = name.find_last_of('.');
	name = name.substr(0, kropka );

	string name2 = name+ ".csv";
	fstream zapis;
	zapis.open(name2.c_str(), ios::out | ios::trunc);

	DopiszPlik(name + ".ppm", zapis);
	DopiszPlik(name + ".bmp", zapis);
	DopiszPlik(name + "_90.jpeg", zapis);
	DopiszPlik(name + "_75.jpeg", zapis);
	DopiszPlik(name + "_50.jpeg", zapis);
	DopiszPlik(name + ".gif", zapis);
	DopiszPlik(name + "_1.tiff", zapis);
	DopiszPlik(name + "_0.tiff", zapis);
	DopiszPlik(name + ".png", zapis);

	zapis.close();

}

void _Obrazy::DopiszPlik(const string& name, fstream &plik){

	RAWFile<char> Plik;
	char* tmp = Plik.Wczytaj(name);
	plik << name <<"\t";
	plik << Plik.GetSize() / 1000;
	if (tmp != NULL) 
		delete[] tmp;
	plik << endl;
}