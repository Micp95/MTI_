#ifndef PRINTER_H
#define PRINTER_H
#include"Complex.h"
#include<iostream>


class Print {
public:
	void PrintWavSamples(short** wavSamples, int numberOfSamples);
	void PrintDataAfterDFT(Complex *data, int numberOfItems);
	void PrintDataAfterIDFT(short *data, int numberOfItems);
};


#endif