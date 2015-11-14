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
typ* RAWFile<typ>::Wczytaj(string nazwa){

	FILE * pFile;
	long lSize;
	typ * buffer;
	size_t result;

	pFile = fopen(nazwa.c_str(), "rb");
	if (pFile == NULL) { return 0; }

	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	lSize = lSize / sizeof(typ);

	buffer = new typ[lSize];
	if (buffer == NULL) { return 0; }

	result = fread(buffer,sizeof(typ), lSize, pFile);
	if (result != lSize) { return 0; }

	size = lSize;
	dane = buffer;

	fclose(pFile);
	return dane;
}

template <class typ>
void RAWFile<typ>::Zapis(string nazwa, typ* dane, long rozmiar){
	if (dane == NULL){
		dane = this->dane;
		rozmiar = size;
	}

	FILE * pFile;
	pFile = fopen(nazwa.c_str(), "wb");
	
	fwrite(dane, sizeof(typ), rozmiar, pFile);
	fclose(pFile);
}

#endif