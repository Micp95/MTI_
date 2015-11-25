#include "FrequencyFilter.h"

short* FrequencyFilter::Filter(short * samples, int numberOfSamples, int min, int max) {

	for (int i = 0; i < numberOfSamples; i++) {
		if (samples[i] > max) 
			samples[i] = 0;
		else if(samples[i] < min)
			samples[i] = 0;
	}
	return samples;
}