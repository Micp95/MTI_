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

	typ* Wczytaj(string nazwa, int pomin = 0);
	void Zapis(string nazwa, const typ* inne = NULL, long size = 0);
	void ZapisZakres(string nazwa, typ* inne = NULL, long size = 0);
	long GetSize(){ return size; }

	typ* dane;
private:
	long size;
	string FileName;

	template <class typ>
	friend fstream & operator <<(fstream & os, RAWFile<typ> & i);

	template <class typ>
	friend ostream & operator <<(ostream & os, RAWFile<typ> & i);
};

//Klasa szablonowa - sposob pozwalajacy rozdzielenie deklaracji od definicji
#include "RAWFile.cpp"

#endif