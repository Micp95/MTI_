#include <iostream>
#include <string>
#include <fstream>

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

enum koder{
	Huffman = 0, LZ77, RLE, Roznicowy
};

namespace _MAIN{
	string Wczytaj(string nazwa,bool bin = false);
	void Zapis(string nazwa, string tekst, bool bin = false);

}
using namespace _MAIN;



int main()
{
	AHuffman koder1;
	ALZ77 koder2(4, 4);
	ARLE koder3;
	ARoznicowy koder4(2);
	
//	Zapis("test.txt", "abc", true);
//	cout << Wczytaj("02.jpg",true)<<endl;

	string tresc = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaasfdsf";
	Entropy e1(tresc);
	koder WyborKodera = RLE;


	cout << "Tresc do zakodowania:\t\t" << tresc<<"\n\n";

	switch (WyborKodera){
	case Huffman:

		cout << "\n\nTresc zakodowana:\t\t" << koder1.Koduj(tresc) << endl;
		cout << "\nTresc odkodowana:\t\t" << koder1.Dekoduj() << endl << endl;
		break;
	case LZ77:

		cout << "\nZakodowane:" << "\n\tZnak poczatku:\t" << koder2.SymbolPoczatkowy << "\n\tTrojki:\t" << koder2.Koduj(tresc) << endl;
		cout << "\n\nDekodowane:\t\t" << koder2.Dekoduj() << endl << endl;
		break;
	case RLE:
		cout << "\n\nTresc zakodowana:\t\t" << koder3.Koduj(tresc) << endl;
		cout << "\nTresc odkodowana:\t\t" << koder3.Dekoduj() << endl << endl;
		break;
	case Roznicowy:
		cout << "\n\nTresc zakodowana:\t\t" << koder4.Koduj(tresc) << endl;
		cout << "\nTresc odkodowana:\t\t" << koder4.Dekoduj() << endl << endl;
		break;
	default:
		break;

	}


	


	system("pause");
	return 0;
}


namespace _MAIN{
	string Wczytaj(string nazwa, bool bin){
		string zwrot="";
		fstream plik;
		if ( bin )
			plik.open(nazwa.c_str(), ios::in | ios::binary);
		else
			plik.open(nazwa.c_str(), ios::in);
		
		char *bufor = new char[1024];
		if (plik.good() == true)
		{
			while (!plik.eof()){
				plik.read(bufor, 1024);
				zwrot += string(bufor, plik.gcount());
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
			plik.open(nazwa.c_str(), ios::out|ios::trunc);

		char *bufor = new char[1024];
		if (plik.good() == true)
		{
			plik.write(tekst.c_str(), tekst.length());
		}

		delete[] bufor;
		plik.close();
	}

}

