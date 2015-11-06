#include "Spis.h"

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <cstdlib>

#include "StopWatch.h"

#include "Spis.h"
#include "AlgHuff.h"
#include "AlgLZ.h"
#include "AlgRLE.h"
#include "AlgRoznicowy.h"
#include "Entropy.h"

using namespace std;
using namespace _AHuffman;
using namespace _ALZ;
using namespace _ARLE;
using namespace _ARoznicowy;
using namespace AEntropy;

using namespace std;

namespace _MAIN{
	string Wczytaj(string nazwa, bool bin){
		string zwrot = "";
		fstream plik;
		if (bin)
			plik.open(nazwa.c_str(), ios::in | ios::binary);
		else
			plik.open(nazwa.c_str(), ios::in);

		char *bufor = new char[1024];
		if (plik.good() == true)
		{
			while (!plik.eof()){
				plik.read(bufor, 1024);
				if (!bin)
					zwrot += string(bufor, plik.gcount());
				else
				{
					for (int k = 0; k < plik.gcount(); k++){
						zwrot += dec_to_bin(bufor[k]);
					}
				}

			}
		}


		plik.close();
		return zwrot;
	}
	void Zapis(string nazwa, string tekst, bool bin){

		fstream plik;
		bin = true;
		if (bin)
			plik.open(nazwa.c_str(), ios::out | ios::binary | ios::trunc);
		else
			plik.open(nazwa.c_str(), ios::out | ios::trunc);

		char *bufor = new char[1024];
		if (plik.good() == true)
		{
			if (!bin)
				plik.write(tekst.c_str(), tekst.length());
			else
			{
				string zwrot = "";
				int start = 0;
				for (start; start + 8 < tekst.length(); start += 8){
					zwrot += bin_to_dec(tekst, start, start + 8);
				}
				if (start != tekst.length())
					zwrot += bin_to_dec(tekst, start, tekst.length());
				plik.write(zwrot.c_str(), zwrot.length());
			}

		}

		delete[] bufor;
		plik.close();
	}

	char *dec_to_bin(char n) {
		static char tab[8]; int i;

		for (i = 8; i; i--) {
			if (n & 1)
				tab[i - 1] = '1';
			else
				tab[i - 1] = '0';
			n >>= 1;
		}

		return tab;
	}

	char bin_to_dec(string& teks, int a, int b){
		//	char zwrot = '\0';
		string pom = "";

		pom += teks.substr(a, b - a);
		if (b - a != 7){
			for (int k = 0; k < 8 - (b - a); k++)
				pom += '0';
		}
		int liczba = 0;
		int waga = 1;
		for (int k = pom.length() - 1; k > 0; k--, waga *= 2){
			if (pom[k] == '1')
				liczba += waga;
		}


		return (char)(liczba);
	}


	long long WykonajAlgorytm(koder select, string plik, bool BinWczyt, bool BinZapis, int bufor){
		Koder* KodWsk;

		switch (select){
		case Huffman:
			KodWsk = new AHuffman();
			break;
		case LZ77:
			KodWsk = new ALZ77(bufor, bufor);
			break;
		case RLE:
			KodWsk = new ARLE();
			break;
		case Roznicowy:
			KodWsk = new ARoznicowy();
			break;
		default:
			KodWsk = new Koder();
			break;
		}

		StopWatch stoper;
		string tresc = Wczytaj("_pliki\\" + plik, BinWczyt);
		if (tresc == "")
			return 0;

		string tmp = plik.substr(0, 2);
		tmp += "k";
		tmp += plik.substr(2);


		string zakodowane="";

		stoper.Start();
		zakodowane = KodWsk->Koduj(tresc);
		stoper.Stop();

		Zapis("_pliki\\" + tmp, zakodowane, BinZapis);

		return stoper.MilliSeconds();
	}

	void WykonajTestAlgorytmu(koder select, int repeat){

		string name= "";
		switch (select){
		case Huffman:
			name = "Huffman";
			break;
		case LZ77:
			name = "LZ77";
			break;
		case RLE:
			name = "RLE";
			break;
		case Roznicowy:
			name = "Roznicowy";
			break;
		default:
			break;
		}
		cout << "Aktualnie trwa wykonywanie algorytmu " << name << "\tIlosc prob:\t" << repeat << "\n\n";


		long long Time = 0;
		long long totalTime = 0;


		//------------------------------Binarny--------------------------
		//Plik Binarny, 100kb, 11.jpg
		cout << "Plik binarny:\n";
		for (int k = 0; k < repeat; k++){
			Time = WykonajAlgorytm(select, "11.jpg", true, true);
			totalTime += Time;
		}
		cout << "\tPlik: 11.jpg\trozmiar:\t100kb" <<"\tCzas:\t"<< totalTime/repeat  <<endl;
		totalTime = 0;

		//Plik Binarny, 50b, 12.jpg
		for (int k = 0; k < repeat; k++){
			Time = WykonajAlgorytm(select, "12.jpg", true, true);
			totalTime += Time;
		}
		cout << "\tPlik: 12.jpg\trozmiar:\t50kb" << "\tCzas:\t" << totalTime / repeat << endl;
		totalTime = 0;

		//Plik Binarny, 25kb, 13.jpg
		for (int k = 0; k < repeat; k++){
			Time = WykonajAlgorytm(select, "13.jpg", true, true);
			totalTime += Time;
		}
		cout << "\tPlik: 13.jpg\trozmiar:\t25kb" << "\tCzas:\t" << totalTime / repeat << endl;
		totalTime = 0;



		//------------------------------Tekstowy--------------------------
		//Plik Tekstowy, 100kb, 21.cpp
		cout << "Plik Tekstowy:\n";
		for (int k = 0; k < repeat; k++){
			Time = WykonajAlgorytm(select, "21.cpp", false, true);
			totalTime += Time;
		}
		cout << "\tPlik: 21.cpp\trozmiar:\t100kb" << "\tCzas:\t" << totalTime / repeat << endl;
		totalTime = 0;

		//Plik Tekstowy, 50b, 22.cpp
		for (int k = 0; k < repeat; k++){
			Time = WykonajAlgorytm(select, "22.cpp", false, true);
			totalTime += Time;
		}
		cout << "\tPlik: 22.cpp\trozmiar:\t50kb" << "\tCzas:\t" << totalTime / repeat << endl;
		totalTime = 0;

		//Plik Tekstowy, 25kb, 23.cpp
		for (int k = 0; k < repeat; k++){
			Time = WykonajAlgorytm(select, "23.cpp", false, true);
			totalTime += Time;
		}
		cout << "\tPlik: 23.cpp\trozmiar:\t25kb" << "\tCzas:\t" << totalTime / repeat << endl;
		totalTime = 0;



		//------------------------------Spakowany--------------------------
		//Plik Spakowany, 100kb, 31.zip
		cout << "Plik spakowany:\n";
		for (int k = 0; k < repeat; k++){
			Time = WykonajAlgorytm(select, "31.zip", true, true);
			totalTime += Time;
		}
		cout << "\tPlik: 31.zip\trozmiar:\t100kb" << "\tCzas:\t" << totalTime / repeat << endl;
		totalTime = 0;

		//Plik Spakowany, 50b, 32.zip
		for (int k = 0; k < repeat; k++){
			Time = WykonajAlgorytm(select, "32.zip", true, true);
			totalTime += Time;
		}
		cout << "\tPlik: 32.zip\trozmiar:\t50kb" << "\tCzas:\t" << totalTime / repeat << endl;
		totalTime = 0;

		//Plik Spakowany, 25kb, 33.zip
		for (int k = 0; k < repeat; k++){
			Time = WykonajAlgorytm(select, "33.zip", true, true);
			totalTime += Time;
		}
		cout << "\tPlik: 33.zip\trozmiar:\t25kb" << "\tCzas:\t" << totalTime / repeat << endl;
		totalTime = 0;


	}

}

