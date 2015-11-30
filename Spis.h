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

	int dlslowa(int slowo);

	char *int_to_bin(int n, int dlugosc);
	char *dec_to_bin(char n);
	char bin_to_dec(string& teks, int a, int b);
	char bin_to_int(string& teks, int a, int b,bool sign);

}


#endif