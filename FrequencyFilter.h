#ifndef FREQ_H
#define FREQ_H
#include"Complex.h"

class FrequencyFilter {
public:
	short* Filter(short * samples, int numberOfSamples, int min, int max);
	Complex* Filter(Complex* harmonic, int numberOfSamples, int min, int max);
};

#endif