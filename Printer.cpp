#include "Printer.h"

using namespace std;


void Print::PrintWavSamples(short** wavSamples, int numberOfSamples) {
	for (int i = 0; i < numberOfSamples; i++) {
		cout << (unsigned short)(unsigned char)wavSamples[0][i] << endl;
	}
}

void Print::PrintDataAfterDFT(Complex *data, int numberOfItems) {
	for (int i = 0; i < numberOfItems; i++)	//_________________dane do widma_________________
		cout << data[i].im << endl;
}

void Print::PrintDataAfterIDFT(short *data, int numberOfItems) {
	for (int i = 0; i < numberOfItems; i++)
		cout << data[i] << endl;
}