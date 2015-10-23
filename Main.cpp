#include <iostream>
#include "Spis.h"
#include "AlgHuff.h"


using namespace std;
using namespace _AHuffman;

int main(){
	AHuffman koder;
	koder.Koduj("abbccc");

	system("pause");
	return 0;
}