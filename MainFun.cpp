#include "Spis.h"

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <cstdlib>


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
		//bin = true;
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

	int dlslowa(int slowo){
		int licznik = 0;

		do {
			slowo /= 2;
			licznik++;
		} while (slowo > 1);

		return licznik;
	}

	char *int_to_bin(int n, int dlugosc){
		char * tab = new char[dlugosc];
		char znak;
		if (n < 0)
			znak = '1';
		else
			znak = '0';

		for (int i = 0; i < dlugosc; i++)
			tab[i] = znak;
	
		int i;
		for (i = dlugosc; i >0; i--){

			if (n & 1)
				tab[i - 1] = '1';
			else
				tab[i - 1] = '0';
			n >>= 1;
		}
		return tab;
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

	char bin_to_int(string& teks, int a, int b,bool sign){
		string pom = "";

		pom += teks.substr(a, b - a);

		if (sign && pom[0] == '1'){
			string tmp = "";
			for (int k = 0; k < pom.length(); k++)
				if (pom[k] == '0')
					tmp += '1';
				else
					tmp += '0';
			pom = tmp;
		}
		else
			sign = false;


		int liczba = 0;
		int waga = 1;
		for (int k = pom.length() - 1; k >= 0; k--, waga *= 2){
			if (pom[k] == '1')
				liczba += waga;
		}

		if (sign){
			liczba++;
			liczba = -liczba;
		}
		

		return liczba;
	}

}

