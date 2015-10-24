#include <iostream>
#include "Spis.h"
#include "AlgHuff.h"


using namespace std;
using namespace _AHuffman;

int main(){

	//Dziala

	string tresc = "abbccc";
	AHuffman koder;

	cout << "Tresc do zakodowania:\t\t" << tresc;
	cout << "\n\nTresc zakodowana:\t\t" << koder.Koduj(tresc) << endl;
	cout << "\nTresc odkodowana:\t\t" << koder.Dekoduj() << endl<<endl;
	

	system("pause");
	return 0;
}