#ifndef SPIS_H
#define SPIS_H

#include <string>
#include <iostream>

using namespace std;

enum koder{
	nic = -1, Huffman = 0, LZ77, RLE, Roznicowy
};

namespace _MAIN{
	string Wczytaj(string nazwa, bool bin = false);
	void Zapis(string nazwa, string tekst, bool bin = false);


	char *dec_to_bin(char n);
	char bin_to_dec(string& teks, int a, int b);

	long long WykonajAlgorytm(koder select, string plik, bool BinWczyt, bool BinZapis, int bufor = 4);

	void WykonajTestAlgorytmu(koder select,int repeat);
}


#endif