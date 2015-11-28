#include "Kompresje.h"

//biblioteki ogolnodostepne
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <cstdlib>

//nasze biblioteki
#include "StopWatch.h"
#include "Spis.h"
#include "AlgHuff.h"
#include "AlgLZ.h"
#include "AlgRLE.h"
#include "AlgRoznicowy.h"
#include "Entropy.h"

using namespace std;
using namespace _Kompresja;
using namespace _AHuffman;
using namespace _ALZ;
using namespace _ARLE;
using namespace _ARoznicowy;
using namespace AEntropy;
using namespace _MAIN;



//Definey do testowania

//#define TESTKODER
//#define TESTPLIKI
//#define TESTENTROPY


int _Kompresja::PlatformaTestowaOgolna(){

	cout << "Kompresja." << endl;


#ifdef TESTKODER

	AHuffman koder1;
	ALZ77 koder2(4, 4);
	ARLE koder3;
	ARoznicowy koder4(2);

	koder WyborKodera = nic;

	if (WyborKodera != nic)
		cout << "Tresc do zakodowania:\t\t" << tresc << "\n\n";

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

#endif

#ifdef TESTPLIKI
	StopWatch stoper;

	ARoznicowy koder1;

	string tresc;

	string nazw = "00.cpp";
	string nazw2 = "01.jpg";
	string tmp;


	//tresc = Wczytaj("_pliki\\" + nazw, false );
	tresc = "aabbaa";
	tmp = nazw.substr(0, 2);
	tmp += "k";
	tmp += nazw.substr(2);
	string tmgfdg;
	long long total = 0;
	for (int k = 0; k < 1; k++){

		stoper.Start();
		tmgfdg = koder1.Koduj(tresc);
		stoper.Stop();
		total += stoper.MilliSeconds();


	}
	cout << "\n\n\t\tCzas:\t\t" << total << endl;



	Zapis("_pliki\\" + tmp, tmgfdg, true);

	string tm = Wczytaj("_pliki\\00k.cpp", true);
	cout << endl << koder1.Dekoduj(tm);

	/*

	tresc = Wczytaj("pliki\\" + nazw2, true);
	tmp = nazw2.substr(0, 2);
	tmp += "k";
	tmp += nazw2.substr(2);

	stoper.Start();
	Zapis("pliki\\" + tmp, koder1.Koduj(tresc), true);
	stoper.Stop();
	cout << "\n\n\t\tCzas:\t\t" << stoper.MilliSeconds()<<endl;
	*/

#endif

#ifdef GENERATORPLIKU
	srand(time(NULL));
	string generowany = "";
	int test;
	for (long long i = 0; i < 25000; i++){
		test = rand() % 10 + 47;
		generowany += (char)(test);
	}
	Zapis("r2.txt", generowany, false);
#endif


#ifdef TESTENTROPY

	string nazwy[] = { "21k.cpp", "22k.cpp", "23k.cpp" };

	string nazwy2[] = { "31k.zip", "32k.zip", "33k.zip" };

	string nazwy3[] = { "11k.jpg", "12k.jpg", "13k.jpg" };


	string foldery[] = { "zwykly", "LZ77", "RLE", "Roznicowy", "Huffman" };


	cout << "ENTROPIA!!\n\n";
	string tekst;
	double tmp = 0;
	Entropy* wsk;		//Wskaznik na entropie


	string naz;
	string sciezka = "_pliki\\Entropy\\";
	for (int k = 0; k < 5; k++){
		cout << "\t" << foldery[k] << endl;

		for (int p = 0; p < 3; p++){
			if (k != 0)
				naz = nazwy[p];
			else
				naz = nazwy[p].substr(0, 2) + nazwy[p].substr(3);

			tekst = Wczytaj(sciezka + foldery[k] + "\\" + naz);
			wsk = new Entropy(tekst);
			tmp += wsk->EntropyVal;
			delete wsk;
		}
		cout << "\t\tDla plikow tekstowych:\t" << tmp / 3 << endl;
		tmp = 0;

		if (k != 2){

			for (int p = 0; p < 3; p++){
				if (k != 0)
					naz = nazwy[p];
				else
					naz = nazwy[p].substr(0, 2) + nazwy[p].substr(3);
				tekst = Wczytaj(sciezka + foldery[k] + "\\" + naz, true);
				wsk = new Entropy(tekst);
				tmp += wsk->EntropyVal;
				delete wsk;
			}
			cout << "\t\tDla plikow skompresowanych:\t" << tmp / 3 << endl;
			tmp = 0;

			for (int p = 0; p < 3; p++){
				if (k != 0)
					naz = nazwy[p];
				else
					naz = nazwy[p].substr(0, 2) + nazwy[p].substr(3);
				tekst = Wczytaj(sciezka + foldery[k] + "\\" + naz, true);
				wsk = new Entropy(tekst);
				tmp += wsk->EntropyVal;
				delete wsk;
			}
			cout << "\t\tDla plikow binarnych:\t" << tmp / 3 << endl;
			tmp = 0;

		}

	}
#endif


	//WykonajTestAlgorytmu(Huffman,1);

	return 0;
}

void RastrigianFun()
{
	double x = 0;
	int A = 10;
	string wartosci = "";
	double ForCos = 2 * 3.14* x;
	for (double x = -5.12; x < 5.12; x += 0.001)
	{
		double fun = A + (x*x - A * cos(ForCos));
		int temp = (int)fun;
		temp += 32;
		wartosci += (char)temp;
	}
	Zapis("_pliki\\Rastrigian.txt", wartosci);

}

int _Kompresja::PlatformaTestowaMichal(){
	RastrigianFun();
	cout <<"czas \t\t"<<WykonajAlgorytm(LZ77, "Rastrigian.txt", false, true)<<endl;

	return 0;
}

int _Kompresja::PlatformaTestowaMarysia(){


	return 0;
}

int _Kompresja::PlatformaTestowaKasia(){


	return 0;
}




long long _Kompresja::WykonajAlgorytm(koder select, string plik, bool BinWczyt, bool BinZapis, int bufor){
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


	string zakodowane = "";

	stoper.Start();
	zakodowane = KodWsk->Koduj(tresc);
	stoper.Stop();

	Zapis("_pliki\\" + tmp, zakodowane, BinZapis);

	return stoper.MilliSeconds();
}
void _Kompresja::WykonajTestAlgorytmu(koder select, int repeat){

	string name = "";
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
	cout << "\tPlik: 11.jpg\trozmiar:\t100kb" << "\tCzas:\t" << totalTime / repeat << endl;
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
		Time = WykonajAlgorytm(select, "21.cpp", false, false);
		totalTime += Time;
	}
	cout << "\tPlik: 21.cpp\trozmiar:\t100kb" << "\tCzas:\t" << totalTime / repeat << endl;
	totalTime = 0;

	//Plik Tekstowy, 50b, 22.cpp
	for (int k = 0; k < repeat; k++){
		Time = WykonajAlgorytm(select, "22.cpp", false, false);
		totalTime += Time;
	}
	cout << "\tPlik: 22.cpp\trozmiar:\t50kb" << "\tCzas:\t" << totalTime / repeat << endl;
	totalTime = 0;

	//Plik Tekstowy, 25kb, 23.cpp
	for (int k = 0; k < repeat; k++){
		Time = WykonajAlgorytm(select, "23.cpp", false, false);
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

