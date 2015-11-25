#ifndef DFT_H
#define DFT_H

#include"Complex.h"

class DFT {
public:
	bool isInverse;
	const double pi = 3.1415926535;

	DFT(bool is = false) : isInverse(is) {};

	Complex* CalculateDFT(short * samples, int numberOfSamples);
	Complex CalculateKHarmonicDFT(short * samples, int numberOfSamples, int k);

	short* CalculateIDFT(Complex * harmonic, int numberOfSamples);
	short CalculateKHarmonicIDFT(Complex * harmonic, int numberOfSamples, int k);

	//--------------------------------------------------------------------------
	double* CalculateIDFT2(Complex * harmonic, int numberOfSamples);
	double  CalculateValue(Complex* harmonic, int numberOfSamples, int k);
};

#endif