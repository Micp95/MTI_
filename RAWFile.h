#ifndef RAWFILE_H
#define RAWFILE_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>


using namespace std;


template <class typ>
class RAWFile
{
public:
	RAWFile();
	~RAWFile();

	typ* Wczytaj(string nazwa);
	void Zapis(string nazwa, typ* inne = NULL, long size = 0);
	void ZapisZakres(string nazwa, typ* inne = NULL, long size = 0);
	long GetSize(){ return size; }

private:
	typ* dane;
	long size;
};

//Klasa szablonowa - sposob pozwalajacy rozdzielenie deklaracji od definicji
#include "RAWFile.cpp"

#endif