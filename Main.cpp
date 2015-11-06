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

using namespace _MAIN;


//#define TESTKODER
//#define TESTPLIKI



int main()
{
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

	AHuffman koder1;

	string tresc;

	string nazw = "03.zip";
	string nazw2 = "01.jpg";
	string tmp;


	tresc = Wczytaj("pliki\\" + nazw, true );
	tmp = nazw.substr(0, 2);
	tmp += "k";
	tmp += nazw.substr(2);


	stoper.Start();
	Zapis("pliki\\"+tmp, koder1.Koduj(tresc), true);
	stoper.Stop();
	cout << "\n\n\t\tCzas:\t\t" << stoper.MilliSeconds() << endl;

	
	tresc = Wczytaj("pliki\\" + nazw2, true);
	tmp = nazw2.substr(0, 2);
	tmp += "k";
	tmp += nazw2.substr(2);

	stoper.Start();
	Zapis("pliki\\" + tmp, koder1.Koduj(tresc), true);
	stoper.Stop();
	cout << "\n\n\t\tCzas:\t\t" << stoper.MilliSeconds()<<endl;

#endif

	WykonajTestAlgorytmu(Huffman,1);

	system("pause");
	return 0;
}




