#include "Obrazy.h"

#include <string>
#include <iostream>

#include "RAWFile.h"
#include "PPMFile.h"
#include "ImageConverter.h"

using namespace std;
using namespace _Obrazy;



int _Obrazy::PlatformaTestowaOgolna() {

	return 0;
}



int _Obrazy::PlatformaTestowaMichal() {

	PPMFile plik("_pliki\\fgd.ppm");
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

	/*

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

	WykonajKonwersje("_pliki\\fgd.ppm");
	PoliczRozmiary("_pliki\\fgd.ppm");

	return 0;
}


int _Obrazy::PlatformaTestowaKasia() {


	return 0;
}

int _Obrazy::PlatformaTestowaMarysia() {


	return 0;
}


void _Obrazy::WykonajKonwersje(string name) {

	ImageConverter konwertor;

	int kropka = name.find_last_of('.');
	name = name.substr(0,kropka+1);

	konwertor.Convert(name + "ppm", name + "bmp");
	konwertor.Convert(name + "bmp", name + "jpeg",90);

	/*
	konwertor.Convert(name + "bmp", name + "jpeg" + "_50" ,50);
	konwertor.Convert(name + "bmp", name + "jpeg" + "_75",75);
	konwertor.Convert(name + "bmp", name + "jpeg" + "_90",90);

	*/

	konwertor.Convert(name + "bmp", name + "gif");
	konwertor.Convert(name + "bmp", name + "tiff",1);
	konwertor.Convert(name + "bmp", name + "png",2);



}

void _Obrazy::PoliczRozmiary(string name) {
	int kropka = name.find_last_of('.');
	name = name.substr(0, kropka + 1);

	long *wyniki = new long[6];
	char *tmp;
	int count = 0;

	RAWFile<char> Plik;

	tmp = Plik.Wczytaj(name + "ppm");
	wyniki[count++] = Plik.GetSize() / 1000;
	delete[] tmp;

	tmp = Plik.Wczytaj(name + "bmp");
	wyniki[count++] = Plik.GetSize() / 1000;
	delete[] tmp;

	tmp = Plik.Wczytaj(name + "jpeg");
	wyniki[count++] = Plik.GetSize() / 1000;
	delete[] tmp;

	tmp = Plik.Wczytaj(name + "gif");
	wyniki[count++] = Plik.GetSize() / 1000;
	delete[] tmp;

	tmp = Plik.Wczytaj(name + "tiff");
	wyniki[count++] = Plik.GetSize() / 1000;
	delete[] tmp;

	tmp = Plik.Wczytaj(name + "png");
	wyniki[count++] = Plik.GetSize()/1000;
	delete[] tmp;

	count = 0;
	string name2 = name+ "csv";
	fstream zapis;
	zapis.open(name2.c_str(), ios::out | ios::trunc);

	zapis << name << "ppm\t" << wyniki[count++] << endl;
	zapis << name << "bmp\t" << wyniki[count++] << endl;
	zapis << name << "jpeg\t" << wyniki[count++] << endl;
	zapis << name << "gif\t" << wyniki[count++] << endl;
	zapis << name << "tiff\t" << wyniki[count++] << endl;
	zapis << name << "png\t" << wyniki[count++] << endl;

	zapis.close();

}