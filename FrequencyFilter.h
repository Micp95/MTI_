#ifndef FREQ_H
#define FREQ_H

class FrequencyFilter {
public:
	short* Filter(short * samples, int numberOfSamples, int min, int max);
};

#endif