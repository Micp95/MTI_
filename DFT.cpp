#include"Complex.h"
#include"DFT.h"
#include<math.h>

/*
Complex DFT::CalculateKHarmonic(short * samples, int numberOfSamples, int k) {

	Complex Ak;

	double w_re = cos((2 * pi) / numberOfSamples);
	double w_im = sin((2 * pi) / numberOfSamples);

	Complex w(w_re, w_im);	//skladowa zespolona - w

	for (int n = 0; n < numberOfSamples; n++) {
		Ak = Ak + w.power(-k*n) * samples[n];
	}
	return Ak;
}
*/

Complex DFT::CalculateKHarmonicDFT(short * samples, int numberOfSamples, int k) {
	int sign = -1;
		
	Complex Ak;
	double pow = (( sign * 2.0 * pi * k) / numberOfSamples);
	double coss, sinn;
	for (int j = 0; j < numberOfSamples; j++) {
		coss = cos(j * pow);
		sinn = sin(j * pow);

		Ak.re = Ak.re + (samples[j] * coss);
		Ak.im = Ak.im + (samples[j] * sinn);
	}

		//Ak.re /= numberOfSamples;
		//Ak.im /= numberOfSamples;

	return Ak;
}

Complex* DFT::CalculateDFT(short * samples, int numberOfSamples) {

	Complex * tab = new Complex[numberOfSamples];

	for (int i = 0; i < numberOfSamples; i++) {
		tab[i] = this->CalculateKHarmonicDFT(samples, numberOfSamples, i);
	}
	return tab;
}

short DFT::CalculateKHarmonicIDFT(Complex * harmonic, int numberOfSamples, int k) {
	int sign = 1;
	short value = 0;
	Complex Ak;

	double pow = ((sign * 2.0 * pi * k) / numberOfSamples);
	double coss;

	for (int j = 0; j < numberOfSamples; j++) {
		coss = cos(j * pow);
		
		Ak.re = Ak.re + (harmonic[j].re * coss);
	}
	value = (short)Ak.re;
	return value;
}

short* DFT::CalculateIDFT(Complex * harmonic, int numberOfSamples) {

	short * tab = new short[numberOfSamples];

	for (int i = 0; i < numberOfSamples; i++) {
		tab[i] = CalculateKHarmonicIDFT(harmonic, numberOfSamples, i);
	}
	return tab;

}

//--------------------------------------------------------------------------------------
double  DFT::CalculateValue(Complex* harmonic, int numberOfSamples, int k) {

	Complex value;

	double w_re = cos((2 * pi) / numberOfSamples);
	double w_im = sin((2 * pi) / numberOfSamples);

	Complex w(w_re, w_im);	//skladowa zespolona - w

	for (int n = 0; n < numberOfSamples; n++) {
		value = value + (w.power(k*n) * harmonic[n]);
	}
	return value.re;
}
double* DFT::CalculateIDFT2(Complex * harmonic, int numberOfSamples) {

	double inwerseOfN = 1.0 / numberOfSamples;
	double *tab = new double[numberOfSamples];
	for (int i = 0; i < numberOfSamples; i++) {
		tab[i] = this->CalculateValue(harmonic, numberOfSamples, i);
		tab[i] *= inwerseOfN;
	}
	return tab;
}