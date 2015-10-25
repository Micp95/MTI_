#include <iostream>
#include "Spis.h"
#include "AlgHuff.h"
#include "AlgLZ.h"
#include "AlgRLE.h"

using namespace std;
using namespace _AHuffman;
using namespace _ALZ;
using namespace _ARLE;

enum koder{
	Huffman = 0, LZ77, RLE
};


int main()
{
	AHuffman koder1;
	ALZ77 koder2(4, 4);
	ARLE koder3;


	string tresc = "ddddddddddddddddddddddddkkkkpppppffxxx";
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

	default:
		break;

	}


	


	system("pause");
	return 0;
}