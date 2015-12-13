#include "PPMFile.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "RAWFile.h"

using namespace std;



PPMFile::PPMFile(string name):FIleName(name), err(0){
	date = NULL;
	BadPixel.Sets(0, 0, 0);
}

PPMFile::~PPMFile(){
	if (date)
		delete[] date;
}

void PPMFile::LoadFile() {
	if (FIleName == "") {
		err = 1;
		return;
	}

	//Otworzenie pliku
	fstream plik;
	plik.open(FIleName.c_str(), ios::in|ios::binary);
	if (!plik.good()){
		err = 1;
		return;
	}

	//Wczytanie nag³ówka
	int lheader=0;
	if ((lheader = LoadHeader(plik)) == -1) {
		err = 2;
		return;
	}
	plik.close();


	//Wczytanie danych - niezale¿ny system - sam otwiera plik
	if (LoadDate(lheader) == -1) {
		err = 2;
		return;
	}

	CreateArrs();

}

int PPMFile::LoadHeader(fstream& file) {
	string tmp;

	//Wczytanie 1 linijki - system zapisu
	getline(file, tmp);
	if (tmp != "P6") {
		err = 2;
		return -1;
	}

	//Wczytanie 2 linijki - komentarz/rozmiar
	getline(file, tmp);
	if ( tmp[0] == '#')		//jeœli '#' to linijka jest komentarzem, jesli nie to danymi
		getline(file, tmp);

	//Rozdzielenie szerokosci i wysokosci obrazu
	stringstream strum(tmp);
	strum >> width;
	strum >> high;

	//Wczytanie maxa
	getline(file, tmp);
	strum = stringstream(tmp);
	strum >> max;

	//Zwrot rozmiaru naglowka
	int leng = file.tellp();
	return leng;
}

void PPMFile::SaveFile(string name) {
	string file = CreateHeader();	//Tworzenie nag³ówka
	file += string(date, size);		//Dopisanie danych

	RAWFile<char> plik;
	plik.Zapis(name, file.c_str(),file.length());
}

string PPMFile::CreateHeader() {
	stringstream strum;
	string tmp;

	//Typ pliku
	string header = "P6\n";

	//Komentarz
	header += "# SPRZEDAM Opla - nowka sztuka, nie smigany!!!\t\t#UsunKonto\n";

	//Szerokosc obrazu
	strum << width;
	strum >> tmp;
	strum.clear();
	header += tmp + " ";

	//Wysokosc obrazu
	strum << high;
	strum >> tmp;
	strum.clear();
	header += tmp + "\n";

	//Zakres lliczb
	strum << max;
	strum >> tmp;
	strum.clear();
	header += tmp + "\n";


	return header;
}


int PPMFile::LoadDate(int lhead) {
	RAWFile<char> plik;
	date = plik.Wczytaj(FIleName, lhead);	//Wczytanie charow z pominieciem naglowka
	if (date == 0)
		return -1;
	size = plik.GetSize();

	return 0;
}

Pixel& PPMFile::GetPixel(int x, int y) {
	if (x >= width || y >= high || x < 0 || y < 0)
		return BadPixel;
	return arrs[x][y];
}

void PPMFile::CreateArrs() {//Tworzenie mapy pikseli

	//Alokacja pamieci
	arrs = new Pixel*[width];
	long pos = 0;
	for (int k = 0; k < width; k++) {
		arrs[k] = new Pixel[high];
	}

	//Uzupelnianie adresow pikseli
	for (int k = 0; k < high; k++)
		for (int p = 0; p < width; p++) {
			arrs[p][k].Sets(&date[pos++], &date[pos++], &date[pos++]);
			if (pos > size)
				return;
		}

}

void* PPMFile::Transform() {
	char* tmp = new char[size];
	for (int k = 0, p = size - 1; k < size; k++, p--)
		tmp[k] = date[p];

	int p,g;
	for (int k = 0; k < high; k++) {
		for (p = 0,g = (width-1)*3; p < (width / 2)*3; p += 3,g-=3) {
			swap(tmp[p + k*width*3], tmp[g + k*width*3]);
			swap(tmp[p+1 + k*width * 3], tmp[g+1 + k*width * 3]);
			swap(tmp[p+2 + k*width * 3], tmp[g+2 + k*width * 3]);
		}
	}
	
	return (void*)tmp;
}
