#ifndef RAWFILE_CPP
#define RAWFILE_CPP

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>


#include "RAWFile.h"
#pragma warning(disable:4996)


using namespace std;

template <class typ>
RAWFile<typ>::RAWFile() : dane(NULL)
{

}

template <class typ>
RAWFile<typ>::~RAWFile()
{

}

template <class typ>
typ* RAWFile<typ>::Wczytaj(string nazwa, int pomin) {

	//Tworzenie zmiennych
	FILE * pFile;
	long lSize;
	typ * buffer;
	size_t result;

	//Otwarcie pliku
	pFile = fopen(nazwa.c_str(), "rb");
	if (pFile == NULL) { return 0; }


	//Znalezienie rozmiaru pliku - w byteach
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	//Przesuwanie wskaznika - pominiece np. naglowka
	fseek(pFile, pomin, SEEK_SET);
	lSize -= pomin;

	lSize = lSize / sizeof(typ);		//przeliczenie rozmiaru pliku do wczytywanych danych

	buffer = new typ[lSize];			//Tworzenie bufora danych
	if (buffer == NULL) { return 0; }

	result = fread(buffer,sizeof(typ), lSize, pFile);	//Wczytanie z pliku
	if (result != lSize) { return 0; }					//Kontrola danych

	size = lSize;
	dane = buffer;

	fclose(pFile);
	return dane;
}

template <class typ>
void RAWFile<typ>::Zapis(string nazwa, const typ* dane, long rozmiar){
	if (dane == NULL){
		dane = this->dane;
		rozmiar = size;
	}

	//Otworzenie pliku
	FILE * pFile;
	pFile = fopen(nazwa.c_str(), "wb");
	
	//Zapis
	fwrite(dane, sizeof(typ), rozmiar, pFile);
	fclose(pFile);
}


//Zapis - operator

template <class typ>
fstream & operator <<(fstream & os, RAWFile<typ> & i) {
	os << __TIMESTAMP__ << endl;
	for (long k = 0; k < i.size; k++)
		os << i.dane[k] << endl;
	return os;
}

template <class typ>
ostream & operator <<(ostream & os, RAWFile<typ> & i) {
	os << "Plik: " << i.FileName << endl;
	cout << "\tPierwsze 10 probek:" << endl;
	for (long k = 0; k < 10; k++) {
		os << "\t\t";

		os.width(10);
		os.fill('.');
		os.precision(2);
		os << i.dane[k] << endl;
	}
	return os;
}



template <class typ>
void RAWFile<typ>::ZapisZakres(string nazwa, typ* inne, long rozmiar){
	if (dane == NULL){
		dane = this->dane;
		rozmiar = size;
	}

	fstream plik;
	plik.open(nazwa.c_str(), ios::out, ios::trunc);
	if (plik.good()){
		for (long k = 0; k < rozmiar; k++)
			plik << inne[k] << endl;
	}
	plik.close();
}

#endif