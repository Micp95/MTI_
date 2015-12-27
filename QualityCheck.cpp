#include "QualityCheck.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "RAWFile.h"

using namespace std;

CheckQuality::CheckQuality(string name1, string name2)
{
	//PPMFile plikppm("_pliki\\" + name1);
	//plikppm.LoadFile();
	//fstream plikppm("_pliki\\" + name2, ios::in | ios::binary);
	//fstream plik2("_pliki\\" + name2, ios::in | ios::binary);
	
	RAWFile<char> plik;
	RAWFile<char> plikppm;

	char * dateppm = plikppm.Wczytaj("_pliki\\" + name1, 0); //oryginalny
	char * date = plik.Wczytaj("_pliki\\" + name2, 0);
	long size = plik.GetSize(); //pliki skonwertowanego
	long sizeppm = plikppm.GetSize(); //pliku oryginalnego
	

	//cout << lhead << endl;
	//cout << size << " " << sizeppm << endl;

	double MSE = 0;
	for (int i = 0; i < size; i++)
	{
		int temp;
		
		temp = (int)dateppm[i] - (int)date[i];
		MSE += (temp * temp);
		
	}
	for (int i = size; i < sizeppm; i++)
	{
		MSE += ((int)dateppm[i] * (int)dateppm[i]);
	}
	MSE *= (1.000000000 / sizeppm);
	cout << "\nMSE: " << MSE << endl;

	double PSNR = 0;
	double temp = 255 * 255;
	PSNR = 10 * log10(temp / MSE);

	cout << "PSNR: " << PSNR << endl;
	//cout << size << endl;
	//cout << plikppm.width  << endl;
	

	
			//cout << arrs[i][j].B << endl;
			//int tempik = (int)*plik2.GetPixel(i, j).R;
			//double temp = pow(((int)*plikppm.GetPixel(i, j).R - (int)*plik2.GetPixel(i, j).R), 2) + pow(((int)*plikppm.GetPixel(i, j).G - (int)*plik2.GetPixel(i, j).G), 2) + pow(((int)*plikppm.GetPixel(i, j).B - (int)*plik2.GetPixel(i, j).B), 2);
			//cout << (int)*plikppm.GetPixel(i, j).B << endl;
			//cout << tempik << endl;
			//MSE += fabs(sqrt(temp));
			//cout << MSE << endl;
			
	
}
int CheckQuality::LoadHeader(fstream& file) {
	string tmp;

	//Wczytanie 1 linijki - system zapisu
	getline(file, tmp);


	//Wczytanie 2 linijki - komentarz/rozmiar
	getline(file, tmp);
	if (tmp[0] == '#')		//jeœli '#' to linijka jest komentarzem, jesli nie to danymi
		getline(file, tmp);

	//Rozdzielenie szerokosci i wysokosci obrazu
	stringstream strum(tmp);
	strum >> width;
	strum >> high;

	//Wczytanie maxa
	
	//Zwrot rozmiaru naglowka
	int leng = file.tellp();
	return leng;
}